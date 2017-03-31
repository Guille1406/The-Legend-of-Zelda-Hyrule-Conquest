#ifndef _ENTITY_
#define _ENTITY_
#include "j1App.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include "p2Point.h"


enum objectType {
	chest,
	giant_chest,
	button,
	change_height,
	door,
	locked_door,
	object_jump,
	object_lever, 
	lever_block_blue,
	lever_block_red,
	green_rupee,
	red_rupee,
	blue_rupee,
	movable_block,
	sign,
	jar,
	key,
	bost_key,
	heart,

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
	int logic_height;
	Collider* collider;
};

class Object : public Entity {
public:
	Object() {
		int x = 0;
	};
	~Object() {};

	virtual void Action() {};

public:

	SDL_Rect rect;
	bool active;
	objectType type;
	std::string name;
	std::vector<Object*> connected_object;
	std::vector<iPoint> collider_tiles;
	
};
class j1Object : public j1Module {

public:
	j1Object() {
		//V_Objects = new std::vector<Object*>;

	
	};
	~j1Object() {};

	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

	std::vector<Object*> FindObject(std::string name);
	void CreateColliders(Object&);

	Object* CreateObject(char*, pugi::xml_node, int height);
	Object* CreateChest(pugi::xml_node, int height);
	Object* CreateButton(pugi::xml_node, int height);
	Object* CreateText(pugi::xml_node, int height);
	Object* CreateChangeHeight(pugi::xml_node object, int height);
	Object* CreateJump(pugi::xml_node object, int height);
	Object* CreateDoor(pugi::xml_node object, int height);

public: 
	std::vector<Object*> V_Objects;

};


#endif