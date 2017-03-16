#include "P_Link.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "j1Player.h"
#include "j1InputManager.h"

void P_Link::Attack()
{

}

void P_Link::LoadAnimation(const char * path)
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
	
	char* name = (char*)animations.attribute("name").as_string();
	auto temp = animations;
	last_name = name;
	while (animations) {
		auto temp = animations;
		name = (char*)animations.attribute("name").as_string();
		x = temp.attribute("x").as_int();
		y = temp.attribute("y").as_int();
		w = temp.attribute("w").as_int();
		h = temp.attribute("h").as_int();
		anim = { x,y,w,h };
		
		if (strcmp(name,last_name)) {
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



player_event P_Link::GetEvent()
{

	if (doing_script == false) {

	



		 if (App->inputM->EventPressed(INPUTEVENT::MUP) == EVENTSTATE::E_REPEAT) {
			if (App->inputM->EventPressed(INPUTEVENT::MRIGHT) == EVENTSTATE::E_REPEAT) {
				movement_direction = move_up_right;
			}
			else if (App->inputM->EventPressed(INPUTEVENT::MLEFT) == EVENTSTATE::E_REPEAT) {
				movement_direction = move_up_left;
			}
			else {
				movement_direction = move_up;

			}
			character_direction = up;
			actual_event = move;
		}

		else if (App->inputM->EventPressed(INPUTEVENT::MDOWN) == EVENTSTATE::E_REPEAT) {
			if (App->inputM->EventPressed(INPUTEVENT::MLEFT) == EVENTSTATE::E_REPEAT) {
				movement_direction = move_down_left;
			}
			else if (App->inputM->EventPressed(INPUTEVENT::MRIGHT) == EVENTSTATE::E_REPEAT) {
				movement_direction = move_down_right;
			}
			else {
				movement_direction = move_down;

			}
			character_direction = down;
			actual_event = move;
		}

		else if (App->inputM->EventPressed(INPUTEVENT::MRIGHT) == EVENTSTATE::E_REPEAT) {

			movement_direction = move_right;
			character_direction = right;
			actual_event = move;
		}
		else if (App->inputM->EventPressed(INPUTEVENT::MLEFT) == EVENTSTATE::E_REPEAT) {

			movement_direction = move_left;
			character_direction = left;
			actual_event = move;
		}


		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
				movement_direction = move_up_right;
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				movement_direction = move_up_left;
			}
			else {
				movement_direction = move_up;

			}
			character_direction = up;
			actual_event = move;
		}

		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				movement_direction = move_down_left;
			}
			else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
				movement_direction = move_down_right;
			}
			else {
				movement_direction = move_down;

			}
			character_direction = down;
			actual_event = move;
		}

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

			movement_direction = move_right;
			character_direction = right;
			actual_event = move;
		}
		else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

			movement_direction = move_left;
			character_direction = left;
			actual_event = move;
		}
		else {
			movement_direction = move_idle;
			actual_event = idle;


			if (GetLogic() == 424) {
				actual_event = jump;
				doing_script = true;
				LOG("I'm Jumping :DDDD");
			}

		}
		return actual_event;
	}
}