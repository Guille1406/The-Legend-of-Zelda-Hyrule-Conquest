#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"

#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1FileSystem.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "j1App.h"
#include "j1Console.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"
#include "j1Camera.h"
#include "j1InputManager.h"
#include "j1Collision.h"
#include "j1Object.h"
#include "j1Enemy.h"
#include "j1HUD.h"

// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(ptimer);

	input = new j1Input();
	win = new j1Window();
	render = new j1Render();
	tex = new j1Textures();
	audio = new j1Audio();
	scene = new j1Scene();
	fs = new j1FileSystem();
	map = new j1Map();
	pathfinding = new j1PathFinding();
	font = new j1Fonts();
	gui = new j1Gui();
	console = new j1Console();
	player = new j1Player();
	fadetoblack = new j1FadeToBlack();
	camera = new j1Camera();
	inputM = new j1InputManager();
	collision = new j1Collision();
	object = new j1Object();
	enemy = new j1Enemy();
	hud = new j1HUD();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(fs);
	AddModule(input);
	AddModule(inputM);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map);
	AddModule(pathfinding);
	AddModule(font);
	
	// scene lastAddModule(scene);
	AddModule(scene);
	AddModule(object);
	AddModule(enemy);
	AddModule(player);
	AddModule(collision);
	// gui after all to print above all
	AddModule(gui);
	AddModule(hud);
	AddModule(fadetoblack);

	//Console
	AddModule(console);

	//camera
	AddModule(camera);

	// render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
j1App::~j1App()
{

	for (std::list<j1Module*>::reverse_iterator item = modules.rbegin(); item != modules.crend(); ++item) {
		RELEASE((*item));
	}

	modules.clear();
}

void j1App::AddModule(j1Module* module)
{
	module->Init();
	modules.push_back(module);
}

// Called before render is available
bool j1App::Awake()
{
	PERF_START(ptimer);

	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;
		
	config = LoadConfig(config_file);

	if(config.empty() == false)
	{
		// self-config
		ret = true;
		app_config = config.child("app");
		title=app_config.child("title").child_value();
		organization=app_config.child("organization").child_value();

		int cap = app_config.attribute("framerate_cap").as_int(-1);

		if(cap > 0)
		{
			capped_ms = 1000 / cap;
		}
	}

	player->Disable();
	enemy->Disable();
	hud->Disable();

	if(ret == true)
	{
		for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.cend() && ret == true; ++item)
			ret = (*item)->Awake(config.child((*item)->name.GetString()));
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool j1App::Start()
{
	SDL_StartTextInput();
	PERF_START(ptimer);
	bool ret = true;

	for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.cend() && ret == true; ++item)
		ret = (*item)->IsEnabled() ? (*item)->Start() : true;

	startup_time.Start();

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool j1App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node j1App::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	char* buf;
	int size = App->fs->Load("config.xml", &buf);
	pugi::xml_parse_result result = config_file.load_buffer(buf, size);
	RELEASE(buf);

	if(result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------
void j1App::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void j1App::FinishUpdate()
{
	if(want_to_save == true)
		SavegameNow();

	if(want_to_load == true)
		LoadGameNow();

	// Framerate calculations --

	if(last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	avg_fps = float(frame_count) / startup_time.ReadSec();
	seconds_since_startup = startup_time.ReadSec();
	last_frame_ms = frame_time.Read();
	frames_on_last_update = prev_last_sec_frame_count;

	App->win->SetTitle("The Legend of Zelda Hyrule Conquest, Summit Games");

	if(capped_ms > 0 && last_frame_ms < capped_ms)
	{
		j1PerfTimer t;
		SDL_Delay(capped_ms - last_frame_ms);
		LOG("We waited for %d milliseconds and got back in %f", capped_ms - last_frame_ms, t.ReadMs());
	}
}

// Call modules before each loop iteration
bool j1App::PreUpdate()
{
	bool ret = true;
	j1Module* pModule = NULL;

	for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.cend() && ret == true; ++item) {

		pModule = *item;

		if (pModule->active == false) {
			continue;
		}

		ret = (*item)->PreUpdate();


	}


	return ret;
}

// Call modules on each loop iteration
bool j1App::DoUpdate()
{
	bool ret = true;

	j1Module* pModule = NULL;

	for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.cend() && ret == true; ++item) {

		pModule = *item;

		if (pModule->active == false) {
			continue;
		}

		ret = (*item)->Update(dt);


	}

	return ret;
}

// Call modules after each loop iteration
bool j1App::PostUpdate()
{
	bool ret = true;

	j1Module* pModule = NULL;

	for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.cend() && ret == true; ++item) {
		pModule = *item;
		if (pModule->active == false) {
			continue;
		}
		ret = (*item)->PostUpdate();
	}

	ret &= !wanttoquit;

	return ret;
}

// Called before quitting
bool j1App::CleanUp()
{
	PERF_START(ptimer);
	bool ret = true;

	for (std::list<j1Module*>::reverse_iterator item = modules.rbegin(); item != modules.crend(); ++item) {
		ret = (*item)->CleanUp();
	}

	PERF_PEEK(ptimer);
	return ret;
}

// ---------------------------------------
int j1App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* j1App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* j1App::GetTitle() const
{
	return title.c_str();
}

// ---------------------------------------
float j1App::GetDT() const
{
	return dt;
}

// ---------------------------------------
const char* j1App::GetOrganization() const
{
	return organization.c_str();
}

// Load / Save
void j1App::LoadGame(const char* file)
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list
	want_to_load = true;
	load_game=("%s%s", fs->GetSaveDirectory(), file);
}

// ---------------------------------------
void j1App::SaveGame(const char* file) const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	want_to_save = true;
	save_game=file;
}

// ---------------------------------------
void j1App::GetSaveGames(p2List<std::string>& list_to_fill) const
{
	// need to add functionality to file_system module for this to work
}

bool j1App::LoadGameNow()
{
	bool ret = false;

	char* buffer;
	uint size = fs->Load(load_game.c_str(), &buffer);

	if(size > 0)
	{
		pugi::xml_document data;
		pugi::xml_node root;

		pugi::xml_parse_result result = data.load_buffer(buffer, size);
		RELEASE(buffer);

		if(result != NULL)
		{
			LOG("Loading new Game State from %s...", load_game.c_str());

			root = data.child("game_state");
			ret = true;
			std::list<j1Module*>::iterator item = modules.begin();
			for (; item != modules.cend() && ret == true; ++item) {
				ret = (*item)->Load(root.child((*item)->name.GetString()));

			}

			data.reset();
			if(ret == true)
				LOG("...finished loading");
			else
				LOG("...loading process interrupted with error on module %s", ((*item) != NULL) ? (*item)->name.GetString() : "unknown");
		}
		else
			LOG("Could not parse game state xml file %s. pugi error: %s", load_game.c_str(), result.description());
	}
	else
		LOG("Could not load game state xml file %s", load_game.c_str());

	want_to_load = false;
	return ret;
}

bool j1App::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", save_game.c_str());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;
	
	root = data.append_child("game_state");
	std::list<j1Module*>::const_iterator item = modules.cbegin();
	for (; item != modules.cend() && ret == true; ++item) {

		ret = (*item)->Save(root.append_child((*item)->name.GetString()));
	}

	if(ret == true)
	{
		std::stringstream stream;
		data.save(stream);

		// we are done, so write data to disk
		fs->Save(save_game.c_str(), stream.str().c_str(), stream.str().length());
		LOG("... finished saving", save_game.c_str());
	}
	else
		LOG("Save process halted from an error in module %s", ((*item) != NULL) ? (*item)->name.GetString() : "unknown");

	data.reset();
	want_to_save = false;
	return ret;
}

void j1App::WantToQuit()
{
	wanttoquit = true;
}