#ifndef _ENTITY_
#define _ENTITY_
#include "j1App.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include "p2Point.h"
#include <vector>
#include "Animation.h"

enum objectType {
	chest,
	giant_chest,
	button,
	double_button,
	diana,
	change_height,
	door,
	warp,
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
	nothing,

	/*
	.
	.
	.
	*/

};


class Object;

class Entity {
public:
	Entity() {};
	~Entity() {};
	virtual void ChangeAnimation(int);
	virtual void LoadAnimation(const char*);
public:
	int logic_height=	0;
	Collider* collider= nullptr;
	int	last_animation =		 0;
	std::string					sprites_folder = empty_char;
	pugi::xml_document			sprites_file;
	std::vector<Animation>		sprites_vector;
	Animation					actual_animation;
	SDL_Texture*				entity_texture=nullptr;

};

class j1Object : public j1Module {

public:
	j1Object() {
		

	
	};
	~j1Object() {};

	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

	void Draw(int height);

	std::vector<Object*> FindObject(std::string name);
	void CreateColliders(Object&);

	Object* CreateObject(char*, pugi::xml_node, int height);
	Object* CreateChest(pugi::xml_node, int height);
	Object* CreateButton(pugi::xml_node, int height);
	Object* CreateDoubleButton(pugi::xml_node, int height);
	Object* CreateDiana(pugi::xml_node, int height);
	Object* CreateText(pugi::xml_node, int height);
	Object* CreateChangeHeight(pugi::xml_node object, int height);
	Object* CreateJump(pugi::xml_node object, int height);
	Object* CreateJump(SDL_Rect rect, int height);
	Object* CreateDoor(pugi::xml_node object, int height);
	Object* CreateWarp(pugi::xml_node, int height);

public: 
	std::vector<Object*> V_Objects;
	SDL_Texture* objects_texture=	nullptr;

};


class Object : public Entity {

public:
	Object() {
		this->entity_texture = App->object->objects_texture;
	};
	~Object() {};

	virtual void Action() {};

public:
	//Needed for animation


public:

	SDL_Rect rect = {0,0,0,0};
	bool active=false;
	objectType type= objectType::nothing;
	std::string name = empty_char;
	std::vector<Object*> connected_object;
	std::vector<iPoint> collider_tiles;

	SDL_Rect texture_rect = { 0,0,0,0 };

};


#endif