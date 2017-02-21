#include "j1Player.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"

#include <algorithm>


#define TILE_COL_ID 237
bool j1Player::Awake(pugi::xml_node&)
{
	return true;
}

bool j1Player::Start()
{
	Link = new P_Link();
	Link->pos = { 0,0 };
	Zelda = new P_Zelda();
	Zelda->pos = { 16,16 };

	//Change this for link spritesheet
	Link->character_texture = App->tex->Load("textures/map.png");

	//Change this for the zelda spritesheet
	Zelda->character_texture = Link->character_texture;
	
	selected_character = Link;
	other_character = Zelda;
	change = false;
	return true;
}

bool j1Player::PreUpdate()
{
	return true;
}

bool j1Player::Update(float dt)
{


	

	//Cambiar esto a una funcion
	uint tile_pos_x = App->player->selected_character->pos.x / 8;
	uint tile_pos_y = App->player->selected_character->pos.y / 8;


	adjacent.down.i = App->map->Colision->Get(tile_pos_x + 1, tile_pos_y + 2);
	adjacent.down.j = App->map->Colision->Get(tile_pos_x, tile_pos_y + 2);
	adjacent.up.i = App->map->Colision->Get(tile_pos_x, tile_pos_y -1);
	adjacent.up.j = App->map->Colision->Get(tile_pos_x +1, tile_pos_y -1);
	adjacent.left.i = App->map->Colision->Get(tile_pos_x -1, tile_pos_y +1);
	adjacent.left.j = App->map->Colision->Get(tile_pos_x -1, tile_pos_y);
	adjacent.right.i = App->map->Colision->Get(tile_pos_x+2, tile_pos_y);
	adjacent.right.j = App->map->Colision->Get(tile_pos_x+2, tile_pos_y +1);

	LOG("\n %i %i\n%i\t%i\n%i\t%i\n %i %i", adjacent.up.i, adjacent.up.j,adjacent.left.j,adjacent.right.i,adjacent.left.i,adjacent.right.j,adjacent.down.j,adjacent.down.i);
	//

	//Cambiar esto a una funcion
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		change = true;
		if (selected_character == Link) {
			selected_character = Zelda;
			other_character = Link;
		}
		else {
			selected_character = Link;
			other_character = Zelda;
		}
	}
	//
	
	Draw();
	if (change == true) {
		Move_Camera();
	}
	else {
		Move();
	}
	return true;
}

bool j1Player::PostUpdate()
{
	return true;
}

void j1Player::Draw()
{
	SDL_Rect rect = { 0, 0, 16, 16 };
	App->render->Blit(Link->character_texture,Link->tilepos.x*8,Link->tilepos.y*8,&rect);
	App->render->Blit(Zelda->character_texture, Zelda->tilepos.x*8, Zelda->tilepos.y*8, &rect);
}

void j1Player::Move()
{ 
	enum key_state {
		up,
		down,
		left,
		right,
		left_up,
		left_down,
		right_up,
		right_down,
		idle
	};

	key_state state =idle;
	// HAY QUE INTENTAR QUE ESTO NO SEA TAN HARD CODE
	//ADEMAS HAY ALGUNOS BUGS :S


	p2Point<int> pos = selected_character->pos;

	selected_character->tilepos.x = pos.x / 8;
	selected_character->tilepos.y = pos.y / 8;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			state = left_up;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			state = right_up;
		}
		else {
			state = up;
		}
	}

	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			state = left_down;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			state = right_down;
		}
		else {
			state = down;
		}
	}

	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
	
		
			state = right;
		}
	 else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				
			state = left;
		}
	 else state = idle;

	 if (state == left_up) {
		 int a = 0;
	 }

	 switch (state) {
	 case up: 
		 if (adjacent.up.i != TILE_COL_ID && adjacent.up.j != TILE_COL_ID)
			 selected_character->pos.y = pos.y - 1;
		 else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j != TILE_COL_ID) {
			 pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
			 selected_character->pos.y = pos.y - 1;
			 selected_character->pos.x = pos.x + 1;
		 }
		 else if (adjacent.up.i != TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			 pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
			 selected_character->pos.y = pos.y - 1;
			 selected_character->pos.x = pos.x - 1;
		 }
		 break;

	 case down:
		 if (adjacent.down.i != TILE_COL_ID && adjacent.down.j != TILE_COL_ID)
			 selected_character->pos.y = pos.y + 1;
		 else if (adjacent.down.i == TILE_COL_ID && adjacent.down.j != TILE_COL_ID) {
			 pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
			 selected_character->pos.y = pos.y + 1;
			 selected_character->pos.x = pos.x - 1;
		 }
		 else if (adjacent.down.i != TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			 pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
			 selected_character->pos.y = pos.y + 1;
			 selected_character->pos.x = pos.x + 1;
		 }
		 break;

	 case left:
		 if (adjacent.left.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID)
			 selected_character->pos.x = pos.x - 1;
		 else if (adjacent.left.i == TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			 pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
			 selected_character->pos.x = pos.x - 1;
			 selected_character->pos.y = pos.y - 1;
		 }
		 else if (adjacent.left.i != TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {

			 pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
			 selected_character->pos.y = pos.y + 1;
			 selected_character->pos.x = pos.x - 1;
		 }
		 break;
	 case right:
		 if (adjacent.right.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID)
			 selected_character->pos.x = pos.x + 1;
		 else if (adjacent.right.i == TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			 pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
			 selected_character->pos.y = pos.y + 1;
			 selected_character->pos.x = pos.x + 1;
		 }
		 else if (adjacent.right.i != TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			 pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
			 selected_character->pos.y = pos.y - 1;
			 selected_character->pos.x = pos.x + 1;
		 }
		 break;

	 case left_up:
		 if (adjacent.up.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID ) {
			
		 }

		 else if (adjacent.up.i == TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			 selected_character->pos.x = pos.x - 1;
		 }
		 else if (adjacent.up.i != TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			 selected_character->pos.y = pos.y - 1;
		 }
		 else if (adjacent.up.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID){
			selected_character->pos.x = pos.x - 1;
			selected_character->pos.y = pos.y - 1;
	 }
		 break;
	 
	 case right_up:
		 if (adjacent.up.j == TILE_COL_ID && adjacent.right.i== TILE_COL_ID) {

		 }

		 else if (adjacent.up.j == TILE_COL_ID && adjacent.right.i != TILE_COL_ID) {
			 selected_character->pos.x = pos.x + 1;
		 }
		 else if (adjacent.up.j != TILE_COL_ID && adjacent.right.i == TILE_COL_ID) {
			 selected_character->pos.y = pos.y - 1;
		 }
		 else if (adjacent.up.j != TILE_COL_ID && adjacent.right.i != TILE_COL_ID) {
			 selected_character->pos.x = pos.x + 1;
			 selected_character->pos.y = pos.y - 1;
		 }
		 break;
	 case left_down:
	
		 if (adjacent.down.j == TILE_COL_ID && adjacent.left.i == TILE_COL_ID) {

		 }

		 else if (adjacent.down.j == TILE_COL_ID && adjacent.left.i != TILE_COL_ID) {
			 selected_character->pos.x = pos.x - 1;
		 }
		 else if (adjacent.down.j != TILE_COL_ID && adjacent.left.i == TILE_COL_ID) {
			 selected_character->pos.y = pos.y + 1;
		 }
		 else if (adjacent.down.j != TILE_COL_ID && adjacent.left.i != TILE_COL_ID) {
			 selected_character->pos.x = pos.x - 1;
			 selected_character->pos.y = pos.y + 1;
		 }
		 break;

	 case right_down:
		 if (adjacent.down.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {

		 }

		 else if (adjacent.down.i == TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			 selected_character->pos.x = pos.x + 1;
		 }
		 else if (adjacent.down.i != TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			 selected_character->pos.y = pos.y + 1;
		 }
		 else if (adjacent.down.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			 selected_character->pos.x = pos.x + 1;
			 selected_character->pos.y = pos.y + 1;
		 }
		 break;
	 }
	



		uint x, y;
		App->win->GetWindowSize(x, y);
		App->render->camera.x = -selected_character->pos.x*3 + x / 2 - 8;
		App->render->camera.y = -selected_character->pos.y*3 + y / 2 - 8;
	
}

void j1Player::Change_Player()
{
}

void j1Player::Chase()
{
	
}

bool j1Player::Move_Camera()
{

	int mult = -1;
	static int i = 0;
	
	//Time between character change
	const int time = 20;

	static float rest_x;
	static float rest_y;
	int sum_x = 0;
	int sum_y = 0;
	int x = other_character->pos.x*3 - selected_character->pos.x*3;
	int y = other_character->pos.y*3 - selected_character->pos.y*3;

	if (x > 0)mult = 1;

	rest_x = rest_x + x % time;
	rest_y = rest_y + y % time;

	if (mult * rest_x >= time) {
		sum_x = mult;
		rest_x = rest_x - time * mult;
	}

	mult = -1;
	if (y > 0)mult = 1;

	if (mult * rest_y >= time) {
		sum_y = mult;
		rest_y = rest_y - time * mult;
	}
	App->render->camera.x = App->render->camera.x + x / time + sum_x;
	App->render->camera.y = App->render->camera.y + y / time + sum_y;
	if (i >= time) {
		change = false;
		i = 0;
		rest_x = 0;
		rest_y = 0;
	}
	i++;
	
	return false;
}
