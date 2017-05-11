#ifndef _ENTITY_
#define _ENTITY_
#include "j1App.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include "p2Point.h"
#include <vector>
#include "Animation.h"
#include"j1CutSceneManager.h"
class Enemy;


enum objectType {
	chest,
	giant_chest,
	button,
	double_button,
	diana,
	change_height,
	door,
	warp,
	object_fall,
	colour_blocks,
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
	heart_container,
	nothing,
	block,
	object_music,
	bridge,
	bush,

	npc,

	electric_ball,



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
	virtual bool MoveTo(int, int);

public:
	int logic_height=	0;
	Collider* collider= nullptr;
	Collider* eye_collider = nullptr;
	int	last_animation =		 0;
	std::string					sprites_folder = empty_char;
	pugi::xml_document			sprites_file;
	std::vector<Animation>		sprites_vector;
	Animation					actual_animation;
	SDL_Texture*				entity_texture=nullptr;
	iPoint pos = { 0,0 };
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

	int GetLogic(int minus_height, iPoint pos, bool is_horitzontal);

	std::vector<Object*> FindObject(std::string name);
	void CreateColliders(Object&);
	void DeleteCollider(Object& object);

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
	Object* CreateFall(pugi::xml_node, int height);
	Object* CreateColourBlock(pugi::xml_node object, int height);
	Object* CreateHeart(Enemy* n_enemy, int height);
	Object* CreateMovableObject(pugi::xml_node, int height);
	Object* CreateBlock(pugi::xml_node object, int height);
	Object* CreateMusic(pugi::xml_node object, int height);
	Object* CreateBridge(pugi::xml_node object, int height);
	Object* CreateHeartContainer(pugi::xml_node object, int height);
	Object* CreateBush(pugi::xml_node object, int height);

	Object* CreateNPC(pugi::xml_node object, int height);

	Object* CreateElectricBall(pugi::xml_node object, int height);

	void StartCollision(Collider* collider1, Collider* collider2);
	void OnCollision(Collider* collider1, Collider* collider2);
	void EndCollision(Collider* collider1, Collider* collider2);
	virtual Entity* GetEntityFromId(EntityType_Cutscene ent);
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
	virtual void EndAction() {};

public:
	//Needed for animation


public:

	SDL_Rect rect = {0,0,0,0};
	bool active=false;
	objectType type= objectType::nothing;
	std::string name = empty_char;
	std::vector<Object*> connected_object;
	std::vector<iPoint> collider_tiles;
	bool tokill = false;
	SDL_Rect texture_rect = { 0,0,0,0 };
	Animation object_animation;
};


#endif