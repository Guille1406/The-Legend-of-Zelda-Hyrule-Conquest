#ifndef _ENTITY_
#define _ENTITY_
#include "j1App.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"

enum objectType {
	chest,
	door,
	locked_door,
	cliff,
	change_height,
	/*
	.
	.
	.
	*/

};

class Entity {
public:
	Entity() {};
	~Entity() {};

public:
	
};

class Object : public Entity {
public:
	Object() {
		
	};
	~Object() {};

	void Action() {};

public:

	SDL_Rect rect;
	bool active;
	objectType type;
	Collider* collider;
	/* 
	Contenido del cofre
	Puntero a escena donde lleva
	Texto
	.
	.
	.
	
	*/

};
class j1Object : public j1Module {

public:
	j1Object() {
		V_Objects = new std::vector<Object*>;

		allow_collision.push_back(true);
		allow_collision.push_back(true);
		allow_collision.push_back(true);
	};
	~j1Object() {};

	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

	Object* CreateObject(char*, pugi::xml_node);
	Object* CreateChest(pugi::xml_node);
	Object* CreateText(pugi::xml_node);
	Object* CreateDoor(pugi::xml_node);
	Object* CreateChangeHeight(pugi::xml_node);
	Object* CreateJump(pugi::xml_node);


public: 
	std::vector<Object*>* V_Objects;
	std::vector<bool> allow_collision;
};


#endif