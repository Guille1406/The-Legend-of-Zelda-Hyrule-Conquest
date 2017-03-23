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



#include <stdio.h>
#include <conio.h>
#include <iostream>


#include "S_World.h"
#include "S_Dungeon.h"
#include "S_MainMenu.h"
#include "S_Options.h"
#include "S_QuitGame.h"
#include <list>;
using namespace std;


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
	scene_list = new p2List<MainScene*>();
	//S_Inventory* temp = new S_Inventory();
	
	//Main menu
	p2List_item<MainScene*>* MainMenu= scene_list->add(new S_MainMenu);
	MainMenu->data->scene_name = Scene_ID::mainmenu;

	p2List_item<MainScene*>* Options = scene_list->add(new S_Options);
	Options->data->scene_name = Scene_ID::options;

	p2List_item<MainScene*>* QuitGame = scene_list->add(new S_QuitGame);
	QuitGame->data->scene_name = Scene_ID::quitgame;
	
	//World
	p2List_item<MainScene*>* World = scene_list->add(new S_World);
	World->data->scene_name = Scene_ID::world;

	p2List_item<MainScene*>* Dungeon = scene_list->add(new S_Dungeon);
	Dungeon->data->scene_name = Scene_ID::dungeon;

	active_scene = MainMenu->data;
	prev_scene = MainMenu->data;
	loaded_scene = MainMenu->data;
	active_scene->Start();


	

	//debug_tex = App->tex->Load("maps/path2.png");

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

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

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
	

	p2List_item<MainScene*>* temp = scene_list->start;
	while (temp != NULL) {
		if (temp->data->scene_name == name) {
			active_scene->Clean();
			active_scene = temp->data;
			loaded_scene = active_scene;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

