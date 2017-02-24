#include "j1Player.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Pathfinding.h"
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

	GetAdjacents();
	
	//


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

	if (change == true) {
		Move_Camera();
	}
	else {
		Move();
	}


/////////////  TEMP
	static bool temp = true;
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		temp = !temp;
	}
	if (temp == true) {
		App->pathfinding->CreatePath(other_character->tilepos, selected_character->tilepos);
		chase = true;
	}

	int dist = 0;
	dist = sqrt((selected_character->tilepos.x - other_character->tilepos.x)* (selected_character->tilepos.x - other_character->tilepos.x) + (selected_character->tilepos.y - other_character->tilepos.y)*(selected_character->tilepos.y - other_character->tilepos.y));

	if (chase == true && dist > 3 && temp==true) {
		App->pathfinding->Move(other_character, selected_character);
		if (other_character->tilepos == selected_character->tilepos || App->pathfinding->GetLastPath()->Count() == 0) {
			chase = false;
			App->pathfinding->DeletePath();
		}
	}


	/////
	Draw();
	
	return true;
}

bool j1Player::PostUpdate()
{
	return true;
}

void j1Player::Draw()
{
	SDL_Rect rect = { 0, 0, 16, 16 };
	App->render->Blit(Link->character_texture, Link->pos.x , Link->pos.y, &rect);
	App->render->Blit(Zelda->character_texture, Zelda->pos.x, Zelda->pos.y, &rect);
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
	int x = other_character->pos.x * App->win->GetScale(); - selected_character->pos.x * App->win->GetScale();
	int y = other_character->pos.y * App->win->GetScale(); - selected_character->pos.y * App->win->GetScale();

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

void j1Player::GetAdjacents()
{
	uint tile_pos_x = (App->player->selected_character->pos.x+3) / 8;
	uint tile_pos_y = (App->player->selected_character->pos.y +3) / 8;


	adjacent.down.i = App->map->Colision->Get(tile_pos_x + 1, tile_pos_y + 2);
	adjacent.down.j = App->map->Colision->Get(tile_pos_x, tile_pos_y + 2);
	adjacent.up.i = App->map->Colision->Get(tile_pos_x, tile_pos_y - 1);
	adjacent.up.j = App->map->Colision->Get(tile_pos_x + 1, tile_pos_y - 1);
	adjacent.left.i = App->map->Colision->Get(tile_pos_x - 1, tile_pos_y + 1);
	adjacent.left.j = App->map->Colision->Get(tile_pos_x - 1, tile_pos_y);
	adjacent.right.i = App->map->Colision->Get(tile_pos_x + 2, tile_pos_y);
	adjacent.right.j = App->map->Colision->Get(tile_pos_x + 2, tile_pos_y + 1);

}
