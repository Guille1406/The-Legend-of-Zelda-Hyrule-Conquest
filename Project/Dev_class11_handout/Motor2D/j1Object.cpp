#include "j1Object.h"
#include "j1Map.h"
#include"O_Button.h"
#include "O_DoubleButton.h"
#include "O_Chest.h"
#include "O_ChangeHeight.h"
#include "O_Jump.h"
#include "O_Door.h"
#include "O_Warp.h"
#include "O_Diana.h"
#include "O_Fall.h"
#include "O_ColourBlock.h"
#include "j1Collision.h"
#include "Character.h"
#include "j1FileSystem.h"
#include"j1Player.h"
#include"j1HUD.h"
#include"O_Heart.h"
#include "O_Movable_BLock.h"

bool j1Object::Start()
{
	objects_texture = App->tex->Load("textures/items v2.png");
	return true;
}

bool j1Object::PreUpdate()
{
	return true;
}

bool j1Object::Update(float)
{
	for (int i = 0; i < V_Objects.size(); i++)
		if (V_Objects[i]->type == double_button) {
			//DoubleButton* temp_button = (DoubleButton*)V_Objects[i];
			//temp_button->characters_on = 0;
		}

	//Blit all the objects

	return true;
}

bool j1Object::PostUpdate()
{


	for (int i = 0; i < V_Objects.size(); i++) {
		if (V_Objects[i]->tokill == true) {
			V_Objects[i]->collider->to_delete = true;
			std::vector<Object*>::iterator it = std::find(V_Objects.begin(), V_Objects.end(), V_Objects[i]);
			V_Objects.erase(it);
		}
	}



	/*for (int i = 0; i < V_Objects.size(); i++) {
		if (V_Objects[i]->type == objectType::warp) {
			if (App->player->loop_game_menu == true) {
				//App->player->loop_game_menu = false;
				App->player->Disable();
				App->enemy->Disable();
				App->object->Disable();
				App->map->Disable();
				App->hud->Disable();
				V_Objects[i]->Action();

			}
		}
	}*/

	return true;
}

bool j1Object::CleanUp()
{
	App->tex->UnLoad(objects_texture);
	for (std::vector<Object*>::iterator item = V_Objects.begin(); item != V_Objects.cend(); ++item)
		RELEASE(*item);
	V_Objects.clear();

	return true;
}

void j1Object::Draw(int height)
{
	for (int i = 0; i < V_Objects.size(); i++) {
		Object* object = V_Objects[i];
		if (object->active && object->logic_height == height) {}
			App->render->Blit(object->entity_texture, object->rect.x, object->rect.y, &object->texture_rect);
	}
}

int j1Object::GetLogic(int height, iPoint pos, bool is_horitzontal)
{
	
		//Takes the id of the two front tiles of each player, depending on the locig height of each player
		std::vector<MapLayer*> vector = App->map->V_Colision;

		iPoint tile_pos = pos;
		
		int i =0, j = 0;
		i = vector[height]->Get(tile_pos.x, tile_pos.y);
		j = vector[height]->Get(tile_pos.x + 1*is_horitzontal, tile_pos.y + 1*!is_horitzontal);
		

		//if (i == App->map->CANT_PASS_COL_ID || j == App->map->CANT_PASS_COL_ID) return App->map->CANT_PASS_COL_ID;

		if (i != 0)return i;
		if (j != 0)return j;
		return 0;
	

}

std::vector<Object*> j1Object::FindObject(std::string name)
{
	std::vector<Object*> ret_vec;
	
	for (int i = 0; i < V_Objects.size(); i++) {
		Object* temp = V_Objects[i];
		
		if (name == temp->name && name != empty_char) {
			ret_vec.push_back( V_Objects[i]);
		}
	}
	
	return ret_vec;
}

void j1Object::CreateColliders(Object& object)
{
	std::vector<iPoint> temp_vector;
	for (int i = 0; i < object.rect.w / 16; i++) {
		for (int n = 0; n < object.rect.h / 16; n++) {
			iPoint temp;
			temp.x = object.rect.x + i * 16;
			temp.y = object.rect.y + n * 16;
			//object.collider_tiles.push_back(temp);
			//if(App->map->V_Colision[0][object.logic_height].data[temp.y*App->map->data.width + temp.x] != App->map->CANT_PASS_COL_ID)	{
			if (App->map->V_Colision[object.logic_height]->data != nullptr)
				if (App->map->V_Colision[object.logic_height]->data[(temp.y / 16) *  App->map->data.height + temp.x / 16] != App->map->CANT_PASS_COL_ID)
				{
					App->map->V_Colision[object.logic_height]->data[(temp.y / 16) * App->map->data.height + temp.x / 16] = App->map->CANT_PASS_COL_ID;
					//object.collider_tiles.push_back(temp);
					temp_vector.push_back(temp);
				}
		}
	}
	object.collider_tiles = temp_vector;
}

Object* j1Object::CreateObject(char* type_name, pugi::xml_node object, int height)
{
	Object* ret = nullptr;
	if (!strcmp(type_name, "chest"))
		ret = CreateChest(object, height);
	else if (!strcmp(type_name, "text"))
		ret = CreateText(object, height);
	else if (!strcmp(type_name, "door"))
		ret = CreateDoor(object, height);
	else if (!strcmp(type_name, "warp"))
		ret = CreateWarp(object, height);
	else if (!strcmp(type_name, "button"))
		ret = CreateButton(object, height);
	else if (!strcmp(type_name, "double_button"))
		ret = CreateDoubleButton(object, height);
	else if (!strcmp(type_name, "change_height"))
		ret = CreateChangeHeight(object, height);
	else if (!strcmp(type_name, "jump"))
		ret = CreateJump(object, height);
	else if (!strcmp(type_name, "diana"))
		ret = CreateDiana(object, height);
	else if (!strcmp(type_name, "fall"))
		ret = CreateFall(object, height);
	else if (!strcmp(type_name, "Colour Panel"))
		ret = CreateColourBlock(object, height);
	else if(!strcmp(type_name, "movable"))
		ret = CreateMovableObject(object, height);
	return ret;
}

Object * j1Object::CreateChest(pugi::xml_node object, int height)
{
	Chest temp_chest;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_chest.logic_height = height;
	temp_chest.name = object.attribute("name").as_string();
	temp_chest.rect = { x,y,w,h };
	temp_chest.type = objectType::chest;
	temp_chest.active = true;

	Object* ret = new Chest(temp_chest);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_chest, (Entity*)ret, this);
	V_Objects.push_back(ret);

	return ret;
}

Object * j1Object::CreateButton(pugi::xml_node object, int height)
{
	Button temp_button;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_button.logic_height = height;
	temp_button.name = object.attribute("name").as_string();
	temp_button.rect = { x,y,w,h };
	temp_button.type = objectType::button;
	temp_button.active = true;

	Object* ret = new Button(temp_button);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_button, (Entity*)ret, this);
	V_Objects.push_back(ret);

	//FindObject("door_1");
	return ret;
}

Object * j1Object::CreateDoubleButton(pugi::xml_node object, int height)
{
	DoubleButton temp_button;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_button.logic_height = height;
	temp_button.name = object.attribute("name").as_string();
	temp_button.rect = { x,y,w,h };
	temp_button.type = objectType::double_button;
	temp_button.active = true;

	Object* ret = new DoubleButton(temp_button);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_double_button, (Entity*)ret, this);
	V_Objects.push_back(ret);

	//FindObject("door_1");
	return ret;
}

Object * j1Object::CreateDiana(pugi::xml_node object, int height)
{
	Diana temp_diana;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_diana.logic_height = height;
	temp_diana.name = object.attribute("name").as_string();
	temp_diana.rect = { x,y,w,h };
	temp_diana.type = objectType::diana;
	temp_diana.active = true;

	pugi::xml_node attribute = object.child("properties").child("property");
	while (strcmp(attribute.attribute("name").as_string(), "dir") && attribute) {
		attribute = attribute.next_sibling();
	}
	temp_diana.dir = attribute.attribute("value").as_int();

	switch (temp_diana.dir) {

		//UP
	case 0:
		temp_diana.texture_rect = rect_diana_up_idle;
		break;

		//DOWN
	case 1:
		temp_diana.texture_rect = rect_diana_down_idle;
		break;

		//LEFT
	case 2:
		temp_diana.texture_rect = rect_diana_left_idle;
		break;

		//RIGHT
	case 3:
		temp_diana.texture_rect = rect_diana_right_idle;
		break;
	}

	Object* ret = new Diana(temp_diana);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_diana, (Entity*)ret, this);

	V_Objects.push_back(ret);

	
	return ret;
}

Object * j1Object::CreateText(pugi::xml_node object, int height)
{
	return nullptr;
}

Object * j1Object::CreateDoor(pugi::xml_node object, int height)
{
	Door temp_door;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_door.name = object.attribute("name").as_string();
	temp_door.rect = { x,y,w,h };
	temp_door.type = objectType::door;
	temp_door.active = true;
	temp_door.logic_height = height;

	pugi::xml_node attribute = object.child("properties").child("property");
	while (strcmp(attribute.attribute("name").as_string(), "dir")) {
		attribute = attribute.next_sibling();
	}
	temp_door.dir = attribute.attribute("value").as_int();

	for (int i = 0; i < temp_door.rect.w / 16; i++) {
		for (int n = 0; n < temp_door.rect.h / 16; n++) {
			iPoint temp;
			temp.x = temp_door.rect.x + i * 16;
			temp.y = temp_door.rect.y + n * 16;
			//if(App->map->V_Colision[0][temp_door.logic_height].data[temp.y*App->map->data.width + temp.x] != App->map->CANT_PASS_COL_ID)
			temp_door.collider_tiles.push_back(temp);
			//App->map->V_Colision[0][temp_door.logic_height].data[temp.y*App->map->data.width + temp.x] = App->map->TILE_COL_ID;
		}
	}
	
	switch (temp_door.dir) {

		//UP
	case 0:
		temp_door.texture_rect = rect_door_up;
		break;

		//DOWN
	case 1:
		temp_door.texture_rect = rect_door_down;
		break;

		//LEFT
	case 2:
		temp_door.texture_rect = rect_door_left;
		break;

		//RIGHT
	case 3:
		temp_door.texture_rect = rect_door_right;
		break;
	}

	Object* ret = new Door(temp_door);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_door, (Entity*)ret, this);
	
	V_Objects.push_back(ret);

	return ret;
}

Object* j1Object::CreateHeart(Enemy* n_enemy, int height) {

	Heart temp_corazon;

	temp_corazon.name = "heart";
	temp_corazon.rect = { n_enemy->pix_world_pos.x ,n_enemy->pix_world_pos.y,rect_Heart.w,rect_Heart.h};
	temp_corazon.texture_rect = rect_Heart;
	temp_corazon.type = objectType::heart;
	temp_corazon.active = true;
	temp_corazon.logic_height = n_enemy->logic_height;

	Object* ret = new Heart(temp_corazon);
	ret->collider = App->collision->AddCollider(temp_corazon.rect, COLLIDER_TYPE::collider_heart, (Entity*)ret, this);

	V_Objects.push_back(ret);

	return ret;
}

Object * j1Object::CreateMovableObject(pugi::xml_node object, int height)
{
	Movable_Block temp_block;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();

	temp_block.logic_height = height;
	temp_block.name = object.attribute("name").as_string();
	temp_block.rect = { x,y,w,h };
	temp_block.type = objectType::change_height;
	temp_block.active = true;

	for (int i = 0; i < temp_block.rect.w / 16; i++) {
		for (int n = 0; n < temp_block.rect.h / 16; n++) {
			iPoint temp;
			temp.x = temp_block.rect.x + i * 16;
			temp.y = temp_block.rect.y + n * 16;
			//if(App->map->V_Colision[0][temp_door.logic_height].data[temp.y*App->map->data.width + temp.x] != App->map->CANT_PASS_COL_ID)
			temp_block.collider_tiles.push_back(temp);
			//App->map->V_Colision[0][temp_door.logic_height].data[temp.y*App->map->data.width + temp.x] = App->map->TILE_COL_ID;
		}
	}

	Object* ret = new Movable_Block(temp_block);
	ret->collider = App->collision->AddCollider(temp_block.rect, COLLIDER_TYPE::collider_movable_object, (Entity*)ret, this);
	
	V_Objects.push_back(ret);
	return ret;
}

Object * j1Object::CreateWarp(pugi::xml_node object, int height)
{
	//we should change this
	Warp temp_warp;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_warp.logic_height = height;
	temp_warp.name = object.attribute("name").as_string();
	temp_warp.rect = { x,y,w,h };
	temp_warp.type = objectType::warp;
	temp_warp.active = true;
	pugi::xml_node attribute = object.child("properties").child("property");
	while (strcmp(attribute.attribute("name").as_string(), "scene") && attribute) {
		attribute = attribute.next_sibling();
	}
	temp_warp.scene = (Scene_ID)attribute.attribute("value").as_int();

	attribute = object.child("properties").child("property");
	while (strcmp(attribute.attribute("name").as_string(), "x") && attribute) {
		attribute = attribute.next_sibling();
	}
	temp_warp.warp_pos.x = (Scene_ID)attribute.attribute("value").as_int();
	attribute = object.child("properties").child("property");
	while (strcmp(attribute.attribute("name").as_string(), "y") && attribute) {
		attribute = attribute.next_sibling();
	}
	temp_warp.warp_pos.y = (Scene_ID)attribute.attribute("value").as_int();

	Object* ret = new Warp(temp_warp);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_warp, (Entity*)ret, this);
	V_Objects.push_back(ret);

	//FindObject("door_1");
	return ret;

}

Object * j1Object::CreateFall(pugi::xml_node object, int height)
{
	Fall temp_fall;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_fall.logic_height = height;
	temp_fall.name = object.attribute("name").as_string();
	temp_fall.rect = { x,y,w,h };
	temp_fall.type = objectType::object_fall;
	temp_fall.active = true;
	

	Object* ret = new Fall(temp_fall);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_fall, (Entity*)ret, this);
	V_Objects.push_back(ret);

	//FindObject("door_1");
	return ret;

	
}

Object * j1Object::CreateColourBlock(pugi::xml_node object, int height)
{
	ColourBlock temp_colour_block;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_colour_block.logic_height = height;
	temp_colour_block.name = object.attribute("name").as_string();
	temp_colour_block.rect = { x,y,w,h };
	temp_colour_block.type = objectType::colour_blocks;
	temp_colour_block.active = true;


	Object* ret = new ColourBlock(temp_colour_block);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_colour_block, (Entity*)ret, this);
	V_Objects.push_back(ret);

	//FindObject("door_1");
	return ret;
	
}

void j1Object::StartCollision(Collider * collider1, Collider * collider2)
{
	Character* character = nullptr;
	if (collider1->type == collider_link || collider2->type == collider_link)
		character = App->player->Link;
	else if (collider1->type == collider_zelda || collider2->type == collider_zelda)
		character = App->player->Zelda;
	else if (collider1->type == front_zelda || collider2->type == front_zelda)
		character = App->player->Zelda;
	else if (collider1->type == front_link || collider2->type == front_link)
		character = App->player->Link;

	if (collider1->type == collider_button) {
		static bool audio = false;
		if (!audio) {
			App->audio->PlayFx(App->audio->button_sound);
			audio = true;
		}
		Button* temp = (Button*)collider1->parent;
		temp->Action();
		temp->texture_rect = temp->pressed_button;
	}

	if (collider1->type == COLLIDER_TYPE::collider_heart) {
		Heart* temp = (Heart*)collider1->parent;
		temp->Pick(App->player->Link);

	}
	
	else if (collider1->type == collider_warp) {
		Object* temp = (Object*)collider1->parent;
		temp->Action();
	}
	
	else if (collider1->type == collider_change_height) {
		ChangeHeight* temp = (ChangeHeight*)collider1->parent;
		character->ChangeLogicHeightPlayer(temp->height);

	}
	
	
	
}

void j1Object::OnCollision(Collider * collider1, Collider * collider2)
{
	Character* character = nullptr;
	if (collider1->type == collider_link || collider2->type == collider_link)
		character = App->player->Link;
	else if (collider1->type == collider_zelda || collider2->type == collider_zelda)
		character = App->player->Zelda;
	else if (collider1->type == front_zelda || collider2->type == front_zelda)
		character = App->player->Zelda;
	else if (collider1->type == front_link || collider2->type == front_link)
		character = App->player->Link;
	
	if (collider1->type == collider_jump) {
		if (character->can_walk == false && character->doing_script == false) {
			App->audio->PlayFx(App->player->Fall_Players_Audio);
			character->can_jump = true;

		}
	}
	else if (collider1->type == collider_double_button) {
		DoubleButton* temp = (DoubleButton*)collider1->parent;
		temp->characters_on++;
		temp->Action();

	}
}

void j1Object::EndCollision(Collider * collider1, Collider * collider2)
{
}


Object * j1Object::CreateChangeHeight(pugi::xml_node object, int height)
{
	ChangeHeight temp_height;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	
	temp_height.logic_height = height;
	temp_height.name = object.attribute("name").as_string();
	temp_height.rect = { x,y,w,h };
	temp_height.type = objectType::change_height;
	temp_height.active = true;

	pugi::xml_node attribute = object.child("properties").child("property");
	while (strcmp(attribute.attribute("name").as_string(), "height")) {
		attribute = attribute.next_sibling();
	}

	temp_height.height = attribute.attribute("value").as_int();
	Object* ret = new ChangeHeight(temp_height);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_change_height, (Entity*)ret, this);
	V_Objects.push_back(ret);
	return ret;
}

Object * j1Object::CreateJump(pugi::xml_node object, int height)
{
	Jump temp_jump;
	int x = object.attribute("x").as_int();
	int y = object.attribute("y").as_int();
	int w = object.attribute("width").as_int();
	int h = object.attribute("height").as_int();
	temp_jump.logic_height = height;
	temp_jump.name = object.attribute("name").as_string();
	temp_jump.rect = { x,y,w,h };
	temp_jump.type = objectType::object_jump;
	temp_jump.active = true;
	pugi::xml_node attribute = object.child("properties").child("property");
	
	Object* ret = new Jump(temp_jump);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_jump, (Entity*)ret, this);
	V_Objects.push_back(ret);
	return ret;
}

Object * j1Object::CreateJump(SDL_Rect rect, int height)
{

	Jump temp_jump;
	int x = rect.x;
	int y = rect.y;
	int w = rect.w;
	int h = rect.h;
	temp_jump.logic_height = height;
	temp_jump.name = "boss_jump";
	temp_jump.rect = { x,y,w,h };
	temp_jump.type = objectType::object_jump;
	temp_jump.active = true;


	Object* ret = new Jump(temp_jump);
	ret->collider = App->collision->AddCollider({ ret->rect }, collider_jump, (Entity*)ret, this);
	V_Objects.push_back(ret);
	return ret;
}



void Entity::LoadAnimation(const char* path)
{
	static char tmp_string[4096];
	sprintf_s(tmp_string, 4096, "%s%s", sprites_folder.c_str(), path);

	char* buf = nullptr;
	int size = App->fs->Load(tmp_string, &buf);
	pugi::xml_parse_result result = sprites_file.load_buffer(buf, size);

	if (result == NULL)
	{
		//LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		//ret = false;
	}

	pugi::xml_node info = sprites_file.child("TextureAtlas");
	char* imagepath = (char*)info.attribute("imagePath").as_string();

	entity_texture = App->tex->Load(imagepath);

	pugi::xml_node animations = info.first_child();

	char* last_name = nullptr;
	int x = animations.attribute("x").as_int();
	int y = animations.attribute("y").as_int();
	int w = animations.attribute("w").as_int();
	int h = animations.attribute("h").as_int();
	Frame anim_frame;

	int piv_x = (int)(animations.attribute("pX").as_float() *(float)w);
	int piv_y = (int)(animations.attribute("pY").as_float() * (float)h);
	Animation temp_animation;
	temp_animation.pivot.x = piv_x;
	temp_animation.pivot.y = piv_y;

	anim_frame.rect = { x,y,w,h };
	anim_frame.pivot = { piv_x,piv_y };

	char* name = (char*)animations.attribute("n").as_string();

	pugi::xml_node temp = animations;
	last_name = name;
	int i = 0;
	while (animations) {


		if (strcmp(name, last_name)) {
			temp_animation.speed = 0.05f;

			sprites_vector.push_back(temp_animation);

			//temp_animation.pivot.x = temp.attribute("pX").as_float() *(float)w;
			//temp_animation.pivot.y = temp.attribute("pY").as_float() *(float)h;

			temp_animation.Reset();

			temp_animation.last_frame = 0;
			temp_animation.PushBack(anim_frame);
			i++;
			last_name = name;
		}

		else {
			temp_animation.PushBack(anim_frame);


		}
		animations = animations.next_sibling();
		temp = animations;

		name = (char*)temp.attribute("n").as_string();
		x = temp.attribute("x").as_int();
		y = temp.attribute("y").as_int();
		w = temp.attribute("w").as_int();
		h = temp.attribute("h").as_int();

		temp_animation.pivot.x = (int)(temp.attribute("pX").as_float() *(float)w);
		temp_animation.pivot.y = (int)(temp.attribute("pY").as_float() *(float)h);

		anim_frame.rect = { x,y,w,h };
		anim_frame.pivot = { temp_animation.pivot.x, temp_animation.pivot.y };

	}
	sprites_vector.push_back(temp_animation);
}

void Entity::ChangeAnimation(int animation)
{
	//If the animation is diferent than the actual, change it
	if (last_animation != animation) {
		this->actual_animation = this->sprites_vector[animation];
		last_animation = animation;
	}
}
