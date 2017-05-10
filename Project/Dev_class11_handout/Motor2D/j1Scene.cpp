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
#include "j1HUD.h"

#include "S_World.h"

#include "S_Temporal_Boss_Room.h"
#include "S_ColourPuzzle.h"
#include "S_MainMenu.h"
#include "S_Campaign.h"
#include "S_Options.h"
#include "S_OptionsAudio.h"
#include "S_OptionsControls.h"
#include "S_OptionsGameplay.h"
#include "S_OptionsVideo.h"
#include "S_QuitGame.h"
#include "S_Credits.h"
#include "S_InGameMenu.h"
#include "S_End.h"
#include "S_Dungeon_Entry.h"
#include "S_Dungeon_Right_Down.h"
#include "S_Dungeon_Right_Up.h"
#include "S_Dungeon_SecondFloor_Centre.h"
#include "S_Dungeon_SecondFloor_Right.h"
#include "S_BeforeDungeon.h"
#include "S_SecretExit.h"
#include "S_Village.h"
#include "S_Forest.h"
#include "S_VideoIntro.h"
#include "S_House_1.h"
#include "S_House_2.h"
#include "S_House_3.h"
#include "S_Ric_House.h"
#include"S_CastleCutScene.h"
#include"Enemy_Test_Scene.h"

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
	//Video
	scene_list.push_back(new S_VideoIntro);
	(*scene_list.back()).scene_name = Scene_ID::introvideo;
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
	scene_list.push_back(new S_Credits);
	(*scene_list.back()).scene_name = Scene_ID::credits;
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
	scene_pointer = nullptr;

	scene_pointer = new S_SecretExit;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::secret_exit;
	scene_pointer = nullptr;


	scene_pointer = new S_Village;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::village;
	scene_pointer = nullptr;

	scene_pointer = new S_House_1;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::house_1;
	scene_pointer = nullptr;

	scene_pointer = new S_House_2;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::house_2;
	scene_pointer = nullptr;


	scene_pointer = new S_House_3;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::house_3;
	scene_pointer = nullptr;


	scene_pointer = new S_Ric_House;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::ric_house;
	scene_pointer = nullptr;



	scene_pointer = new S_Forest;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::forest;
	scene_pointer = nullptr;

	scene_pointer = new S_TempBossRoom;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::tempbossroom;

	scene_pointer = new S_BeforeDungeon;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::before_dungeon;

	scene_pointer = new S_DungeonEntry;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::dungeon_entry;

	scene_pointer = new S_DungeonRightDown;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::dungeon_right_down;

	scene_pointer = new S_DungeonRightUp;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::dungeon_right_up;

	scene_pointer = new S_DungeonSecondFloorCentre;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::dungeon_secondfloor_centre;

	scene_pointer = new S_DungeonSecondFloorRight;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::dungeon_second_floor_right;
	
	scene_pointer = new S_ColourPuzzle;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::colourpuzzle;

	scene_pointer = new S_Enemy_Test_Scene;
	scene_list.push_back(scene_pointer);
	world_scenes_vector.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::testenemies;
	
	scene_pointer = new S_End;
	scene_list.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::Send;

	scene_pointer = new S_CastleCutScene;
	scene_list.push_back(scene_pointer);
	(*scene_list.back()).scene_name = Scene_ID::startcutscenegame;

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
			if ((*item)->scene_name == Scene_ID::introvideo)
			{
				main_active_scene = (*item);
				sub_active_scene = (*item);
			}
		}
	}

	credits_logo_atlas = App->tex->Load("gui/credits_logo.png");

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

	App->tex->UnLoad(credits_logo_atlas);
		
	return true;
}

bool j1Scene::ChangeScene(Scene_ID name)
{
	for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend(); ++item)
		if ((*item)->scene_name == name)
		{
			if(*item != main_active_scene)
			main_active_scene->Clean();
			main_active_scene = *item;
			App->hud->SceneChanged();
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