#ifndef __j1SCENE_H__
#define __j1SCENE_H__

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

	
private:
	MainScene* active_scene = nullptr;
	MainScene* prev_scene = nullptr;
	MainScene* loaded_scene = nullptr;
	//std::list<MainScene*>* scene_list = nullptr;
	p2List<MainScene*>* scene_list  = nullptr;

	
};

#endif // __j1SCENE_H__