#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include <list>

#include "j1Module.h"
#include "j1Gui.h"
#include "SDL\include\SDL.h"
#include "MainScene.h"

using namespace std;

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool ChangeScene(Scene_ID);

	bool Show(Scene_ID);
	bool Hide();

	const MainScene* GetActiveScene() const
	{
		if (main_active_scene == sub_active_scene)
			return main_active_scene;
		else
			return sub_active_scene;
		return nullptr;
	}

	const MainScene* GetPreviousScene() const
	{
		return prev_scene;
	}

	MainScene* InGameMenuScene() const
	{
		return ingame_menu_scene;
	}

	bool AnyWorldActive() const;

	const std::list<MainScene*>* Get_scene_list() const
	{
		return &scene_list;
	}

private:
	bool ShowNewScene(Scene_ID);

private:
	MainScene* main_active_scene = nullptr;
	MainScene* sub_active_scene = nullptr;
	MainScene* prev_scene = nullptr;
	std::list<MainScene*> scene_list;
	std::vector<MainScene*> world_scenes_vector;

	MainScene* ingame_menu_scene = nullptr;

	Scene_ID new_sub_scene_to_load = Scene_ID::campaign;
	bool sub_scene_to_load = false;

	

public:
	bool blocks_out = false;
	bool heart_1 = true;
	bool heart_2 = true;
	bool heart_3 = true;
};

#endif // __j1SCENE_H__