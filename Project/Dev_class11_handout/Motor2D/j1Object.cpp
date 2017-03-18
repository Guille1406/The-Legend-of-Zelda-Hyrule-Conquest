#include "j1Object.h"
#include "j1Map.h"
#include"O_Button.h"
#include "O_Chest.h"
#include "O_ChangeHeight.h"
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
	else if (!strcmp(type_name, "button"))
		ret = CreateButton(object);
	else if (!strcmp(type_name, "change_height"))
		ret = CreateChangeHeight(object);
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

Object * j1Object::CreateButton(pugi::xml_node object)
{
	Button temp_button;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_button.rect = { x,y,w,h };
	temp_button.type = objectType::button;
	temp_button.active = true;

	Object* ret = new Button(temp_button);
	ret->collider = App->collision->AddCollider({ temp_button.rect }, collider_button, (Entity*)ret, this);
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


Object * j1Object::CreateChangeHeight(pugi::xml_node object)
{
	ChangeHeight temp_height;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_height.rect = { x,y,w,h };
	temp_height.type = objectType::change_height;
	temp_height.active = true;
	auto attribute = object.child("properties").child("property");
	while (strcmp(attribute.attribute("name").as_string(), "height")) {
		attribute = attribute.next_sibling();
	}

	temp_height.height = attribute.attribute("value").as_int();
	Object* ret = new ChangeHeight(temp_height);
	ret->collider = App->collision->AddCollider({ temp_height.rect }, collider_change_height, (Entity*)ret, this);
	V_Objects->push_back(ret);
	return nullptr;
}

