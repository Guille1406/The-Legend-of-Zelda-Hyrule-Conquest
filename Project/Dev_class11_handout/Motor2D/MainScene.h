#ifndef _MAINSCENE_
#define _MAINSCENE_

#include "j1App.h"

#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "p2Log.h"

enum Scene_ID {
	inventory,
	map,
	world,
	dungeon
};

class MainScene {
public:

	MainScene() {};
	~MainScene() {};

	virtual bool Start() {
		return true;
	};
	
	virtual bool PreUpdate() {
		return true;
	};
	virtual bool Update() {
		return true;
	};
	virtual bool PostUpdate() {
		return true;
	};
	virtual bool Clean() {
		return true;
	}

public:
	Scene_ID scene_name;
	SDL_Texture* atlas;

	/*
	Map
	Textures
	Enemies
	.
	.
	.
	*/

};

#endif // !_MAINSCENE_