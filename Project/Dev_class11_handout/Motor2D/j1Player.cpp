#include "j1Player.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Pathfinding.h"
#include <algorithm>


#define TILE_COL_ID 237
bool j1Player::Awake(pugi::xml_node& config)
{
	Link = new P_Link();
	Zelda = new P_Zelda();

	Link->sprites_vector = new std::vector<Animation>;
	Zelda->sprites_vector = new std::vector<Animation>;
	Link->sprites_folder.create(config.child("folder").child_value());
	Zelda->sprites_folder.create(config.child("folder").child_value());
	return true;
}

bool j1Player::Start()
{
	
	Link->pos = { 0,0 };

	Zelda->pos = { 16,16 };

	//Change this for link spritesheet
	Link->character_texture = App->tex->Load("textures/map.png");

	//Change this for the zelda spritesheet
	Zelda->character_texture = Link->character_texture;
	

	Link->LoadAnimation("sprites/Link_Sprites.xml");
	Zelda->LoadAnimation("sprites/Link_Sprites.xml");

	Link->actual_animation = Link->sprites_vector[0][animation_idle_down];
	Zelda->actual_animation = Zelda->sprites_vector[0][animation_idle_down];
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


	GetAdjacents(Link);
	GetAdjacents(Zelda);
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) { 
		cooperative = !cooperative; 
		selected_character = Link;
		other_character = Zelda;
	}

	if (cooperative == true) {
		Move(Link, dt);
		Move(Zelda,dt);

	}
	else {



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
			Move(selected_character, dt);
		}


		/////////////  TEMP
		static bool pathfinding_active = true;
		if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
			pathfinding_active = !pathfinding_active;
		}
		if (pathfinding_active == true) {
			App->pathfinding->CreatePath(other_character->tilepos, selected_character->tilepos);
			chase = true;
		}

		int dist = 0;
		dist = sqrt((selected_character->tilepos.x - other_character->tilepos.x)* (selected_character->tilepos.x - other_character->tilepos.x) + (selected_character->tilepos.y - other_character->tilepos.y)*(selected_character->tilepos.y - other_character->tilepos.y));

		if (chase == true && dist > 3 && pathfinding_active == true) {
			App->pathfinding->Move(other_character, selected_character);
			if (other_character->tilepos == selected_character->tilepos || App->pathfinding->GetLastPath()->Count() == 0) {
				chase = false;
				App->pathfinding->DeletePath();
			}
		}
		else {
			//TEMP
			other_character->ChangeAnimation(animation_idle_down);
		}
		

	}

	Link->tilepos.x = Link->pos.x / 8;
	Link->tilepos.y = Link->pos.y / 8;
	Zelda->tilepos.x = Zelda->pos.x / 8;
	Zelda->tilepos.y = Zelda->pos.y / 8;

	
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
	App->render->Blit(Link->character_texture, Link->pos.x - 6 , Link->pos.y - 12, &Link->actual_animation.GetCurrentFrame());
	App->render->Blit(Zelda->character_texture, Zelda->pos.x - 6, Zelda->pos.y - 12 , &Zelda->actual_animation.GetCurrentFrame());
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
	int x = other_character->pos.x * App->win->GetScale() - selected_character->pos.x * App->win->GetScale();
	int y = other_character->pos.y * App->win->GetScale() - selected_character->pos.y * App->win->GetScale();

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

void j1Player::GetAdjacents(Character* character)
{

	Character* Selected_Character = Link;
	if (character == Link) {
		Selected_Character = Link;
	}
	else if (character == Zelda) {
		Selected_Character = Zelda;
	}
	uint tile_pos_x = (Selected_Character->pos.x+3) / 8;
	uint tile_pos_y = (Selected_Character->pos.y +3) / 8;

	adjacent_tiles adjacent;
	

	adjacent.down.i = App->map->Colision->Get(tile_pos_x + 1, tile_pos_y + 2);
	adjacent.down.j = App->map->Colision->Get(tile_pos_x, tile_pos_y + 2);
	adjacent.up.i = App->map->Colision->Get(tile_pos_x, tile_pos_y - 1);
	adjacent.up.j = App->map->Colision->Get(tile_pos_x + 1, tile_pos_y - 1);
	adjacent.left.i = App->map->Colision->Get(tile_pos_x - 1, tile_pos_y + 1);
	adjacent.left.j = App->map->Colision->Get(tile_pos_x - 1, tile_pos_y);
	adjacent.right.i = App->map->Colision->Get(tile_pos_x + 2, tile_pos_y);
	adjacent.right.j = App->map->Colision->Get(tile_pos_x + 2, tile_pos_y + 1);


	if (character == Link) {
		adjacent_link = adjacent;
	}
	else if (character == Zelda) {
		adjacent_zelda = adjacent;
	}
}

