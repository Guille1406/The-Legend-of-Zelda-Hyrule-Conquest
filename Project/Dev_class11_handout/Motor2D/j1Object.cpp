#include "j1Object.h"
#include "j1Map.h"
#include "O_Chest.h"
#include "j1Collision.h"
bool j1Object::Start()
{
	return true;
}

bool j1Object::PreUpdate()
{
	return true;
}

bool j1Object::Update(float)
{
	return true;
}

bool j1Object::PostUpdate()
{
	return true;
}

bool j1Object::CleanUp()
{
	return true;
}

Object* j1Object::CreateObject(char* type_name, pugi::xml_node object)
{
	Object* ret = nullptr;
	if (!strcmp(type_name, "chest"))
		ret = CreateChest(object);
	else if (!strcmp(type_name, "text"))
		ret = CreateText(object);
	else if (!strcmp(type_name, "door"))
		ret = CreateDoor(object);

	
	return ret;
}

Object * j1Object::CreateChest(pugi::xml_node object)
{
	Chest temp_chest;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_chest.rect = { x,y,w,h };
	temp_chest.type = objectType::chest;
	temp_chest.active = true;

	Object* ret = new Chest(temp_chest);
	ret->collider = App->collision->AddCollider({ temp_chest.rect }, collider_chest, (Entity*)ret, this);
	V_Objects->push_back(ret);

	return ret;
}

Object * j1Object::CreateText(pugi::xml_node object)
{
	return nullptr;
}

Object * j1Object::CreateDoor(pugi::xml_node object)
{
	return nullptr;
}


