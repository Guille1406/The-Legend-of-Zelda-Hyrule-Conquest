#include "P_Zelda.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "j1Player.h"

void P_Zelda::Attack()
{

}

void P_Zelda::LoadAnimation(const char * path)
{
	p2SString tmp("%s%s", sprites_folder.GetString(), path);

	char* buf = nullptr;
	int size = App->fs->Load(tmp.GetString(), &buf);
	pugi::xml_parse_result result = sprites_file.load_buffer(buf, size);

	if (result == NULL)
	{
		//LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		//ret = false;
	}

	pugi::xml_node info = sprites_file.child("TextureAtlas");
	char* imagepath = (char*)info.attribute("imagePath").as_string();

	character_texture = App->tex->Load(imagepath);

	pugi::xml_node animations = info.first_child();

	char* last_name = nullptr;
	int x = animations.attribute("x").as_int();
	int y = animations.attribute("y").as_int();
	int w = animations.attribute("w").as_int();
	int h = animations.attribute("h").as_int();
	SDL_Rect anim = { x,y,w,h };
	Animation temp_animation;

	char* name = (char*)animations.attribute("n").as_string();

	auto temp = animations;
	last_name = name;
	while (animations) {
		auto temp = animations;
		name = (char*)animations.attribute("n").as_string();
		x = temp.attribute("x").as_int();
		y = temp.attribute("y").as_int();
		w = temp.attribute("w").as_int();
		h = temp.attribute("h").as_int();
		anim = { x,y,w,h };

		if (strcmp(name, last_name)) {
			temp_animation.speed = 0.2;
			sprites_vector->push_back(temp_animation);
			temp_animation.Reset();
			temp_animation.last_frame = 0;
			temp_animation.PushBack(anim);
			last_name = name;
		}
		else {
			temp_animation.PushBack(anim);
		}
		animations = animations.next_sibling();
	}
}



player_event P_Zelda::GetEvent()
{
	SDL_Scancode UP;
	SDL_Scancode DOWN;
	SDL_Scancode LEFT;
	SDL_Scancode RIGHT;

	if (App->player->cooperative == false) {
		UP = SDL_SCANCODE_W;
		DOWN = SDL_SCANCODE_S;
		LEFT = SDL_SCANCODE_A;
		RIGHT = SDL_SCANCODE_D;

	}
	else {
		UP = SDL_SCANCODE_UP;
		DOWN = SDL_SCANCODE_DOWN;
		LEFT = SDL_SCANCODE_LEFT;
		RIGHT = SDL_SCANCODE_RIGHT;

	}
	if (App->input->GetKey(UP) == KEY_REPEAT) {
		if (App->input->GetKey(LEFT) == KEY_REPEAT) {
			movement_direction = move_up_left;
		}
		else if (App->input->GetKey(RIGHT) == KEY_REPEAT) {
			movement_direction = move_up_right;
		}
		else {
			movement_direction = move_up;

		}
		character_direction = up;
		actual_event = move;
	}

	else if (App->input->GetKey(DOWN) == KEY_REPEAT) {
		if (App->input->GetKey(LEFT) == KEY_REPEAT) {
			movement_direction = move_down_left;
		}
		else if (App->input->GetKey(RIGHT) == KEY_REPEAT) {
			movement_direction = move_down_right;
		}
		else {
			movement_direction = move_down;

		}
		character_direction = down;
		actual_event = move;
	}

	else if (App->input->GetKey(RIGHT) == KEY_REPEAT) {


		movement_direction = move_right;
		character_direction = right;
		actual_event = move;
	}
	else if (App->input->GetKey(LEFT) == KEY_REPEAT) {

		movement_direction = move_left;
		character_direction = left;
		actual_event = move;
	}
	else {
		movement_direction = move_idle;
		actual_event = idle;
	}

	return actual_event;
}