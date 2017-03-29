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

#include "S_World.h"
#include "S_Dungeon.h"
#include "S_MainMenu.h"
#include "S_Options.h"
#include "S_OptionsAudio.h"
#include "S_OptionsControls.h"
#include "S_OptionsGameplay.h"
#include "S_OptionsVideo.h"
#include "S_QuitGame.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
	
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	
	
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	//Main menu
	scene_list.push_back(new S_MainMenu);
	(*scene_list.back()).scene_name = Scene_ID::mainmenu;
	//Campaign

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
	
	//World
	scene_list.push_back(new S_World);
	(*scene_list.back()).scene_name = Scene_ID::world;
	scene_list.push_back(new S_Dungeon);
	(*scene_list.back()).scene_name = Scene_ID::dungeon;

	for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend(); ++item)
	{
		(*item)->Awake();
		if ((*item)->scene_name == Scene_ID::mainmenu) {
			active_scene = (*item);
			prev_scene = (*item);
			loaded_scene = (*item);
			active_scene->Start();
		}
	}
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	if (active_scene != prev_scene) {
		active_scene->Start();
		prev_scene = active_scene;
	}
	active_scene->PreUpdate();
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{	
	
	active_scene->Update();
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	active_scene->PostUpdate();
	bool ret = true;

	/*
	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	*/

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	
	
	return true;
}

bool j1Scene::ChangeScene(Scene_ID name)
{
	for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend(); ++item)
	{
		if ((*item)->scene_name == name) {
			active_scene->Clean();
			active_scene = *item;
			loaded_scene = active_scene;
			return true;
		}
	}
	return false;
}