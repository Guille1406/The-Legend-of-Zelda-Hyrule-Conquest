#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <list>

#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Gui.h"
#include "j1Collision.h"
#include "j1Enemy.h"
#include "j1FileSystem.h"

#include "S_World.h"
#include "S_Dungeon.h"
#include "S_MainMenu.h"
#include "S_Campaign.h"
#include "S_Options.h"
#include "S_OptionsAudio.h"
#include "S_OptionsControls.h"
#include "S_OptionsGameplay.h"
#include "S_OptionsVideo.h"
#include "S_QuitGame.h"
#include "S_InGameMenu.h"
#include "S_End.h"

j1Scene::j1Scene() : j1Module()
{
	name = "scene";
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	return true;
}

// Called before the first frame
bool j1Scene::Start()
{
	//Main menu
	scene_list.push_back(new S_MainMenu);
	(*scene_list.back()).scene_name = Scene_ID::mainmenu;
	//Campaign
	scene_list.push_back(new S_Campaign);
	(*scene_list.back()).scene_name = Scene_ID::campaign;
	//Options menu
	scene_list.push_back(new S_Options);
	(*scene_list.back()).scene_name = Scene_ID::options;
	scene_list.push_back(new S_OptionsAudio);
	(*scene_list.back()).scene_name = Scene_ID::optionsaudio;
	scene_list.push_back(new S_OptionsControls);
	(*scene_list.back()).scene_name = Scene_ID::optionscontrols;
	scene_list.push_back(new S_OptionsGameplay);
	(*scene_list.back()).scene_name = Scene_ID::optionsgameplay;
	scene_list.push_back(new S_OptionsVideo);
	(*scene_list.back()).scene_name = Scene_ID::optionsvideo;
	//Credits
	//Quit Game
	scene_list.push_back(new S_QuitGame);
	(*scene_list.back()).scene_name = Scene_ID::quitgame;

	//Ingamemenu
	ingame_menu_scene = new S_InGameMenu;
	scene_list.push_back(ingame_menu_scene);
	(*scene_list.back()).scene_name = Scene_ID::ingamemenu;
	
	//World
	MainScene* scene_pointer = nullptr;
	scene_pointer = new S_World;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::world;
	scene_pointer = new S_Dungeon;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::dungeon;
	scene_pointer = new S_End;
	scene_list.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::Send;

	//XML congig read
	pugi::xml_document	config_file;
	pugi::xml_node		config;

	bool ret = false;

	//Load XML
	char* buf = nullptr;
	int size = App->fs->Load("gui/gui_config.xml", &buf);
	pugi::xml_parse_result result = config_file.load_buffer(buf, size);
	RELEASE(buf);

	if (result == NULL)
		LOG("Could not load map xml file gui_config.xml. pugi error: %s", result.description());
	else
		config = config_file.child("gui_config");

	//Set config
	if (config.empty() == false)
		ret = true;

	if (ret == true)
	{
		for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend() && ret == true; ++item)
		{
			ret = (*item)->Awake(config.child((*item)->scene_str.c_str()));//send here xml for gui text
			if ((*item)->scene_name == Scene_ID::mainmenu)
			{
				main_active_scene = (*item);
				sub_active_scene = (*item);
			}
		}
	}
	return ret;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	if (main_active_scene != prev_scene)
	{
		main_active_scene->Start();
		prev_scene = main_active_scene;
		sub_active_scene = main_active_scene;
	}

	main_active_scene->PreUpdate();
	if(main_active_scene != sub_active_scene)
		sub_active_scene->PreUpdate();

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	main_active_scene->Update();
	if (main_active_scene != sub_active_scene)
		sub_active_scene->Update();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	main_active_scene->PostUpdate();
	if (main_active_scene != sub_active_scene)
		sub_active_scene->PostUpdate();

	if (sub_scene_to_load)
	{
		ShowNewScene(new_sub_scene_to_load);
		sub_scene_to_load = false;
	}
	return true;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend(); ++item)
	{
		(*item)->buttons.clear();
		delete *item;
	}
		
	return true;
}

bool j1Scene::ChangeScene(Scene_ID name)
{
	for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend(); ++item)
		if ((*item)->scene_name == name)
		{
			main_active_scene->Clean();
			main_active_scene = *item;
			return true;
		}
	return false;
}

bool j1Scene::Show(Scene_ID name)
{
	new_sub_scene_to_load = name;
	sub_scene_to_load = true;
	return true;
}

bool j1Scene::ShowNewScene(Scene_ID name)
{
	if (main_active_scene != sub_active_scene)
		Hide();
	for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend(); ++item)
		if ((*item)->scene_name == name)
		{
			sub_active_scene = (*item);
			sub_active_scene->Start();
			return true;
		}
	return false;
}

bool j1Scene::Hide()
{
	sub_active_scene->Clean();
	sub_active_scene = main_active_scene;
	return true;
}

bool j1Scene::AnyWorldActive() const
{
	for (std::vector<MainScene*>::const_iterator item = world_scenes_vector.begin(); item != world_scenes_vector.cend(); ++item)
		if ((*item) == main_active_scene)
			return true;
	return false;
}