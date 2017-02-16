#include "P_Zelda.h"

void P_Zelda::Move()
{
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		pos.y = pos.y - 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		pos.y = pos.y + 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		pos.x = pos.x - 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		pos.x = pos.x + 1;
	}

	LOG("x %i  y %i ", pos.x, pos.y);


}

void P_Zelda::Attack()
{
}
