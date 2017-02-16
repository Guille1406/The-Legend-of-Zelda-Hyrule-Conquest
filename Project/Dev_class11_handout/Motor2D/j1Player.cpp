#include "j1Player.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"

bool j1Player::Awake(pugi::xml_node&)
{
	return true;
}

bool j1Player::Start()
{
	Link = new P_Link();
	Link->pos = { 0,0 };
	Zelda = new P_Zelda();
	Zelda->pos = { 10,10 };


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
	App->render->Blit(Link->character_texture,Link->pos.x,Link->pos.y,&rect);
	App->render->Blit(Zelda->character_texture, Zelda->pos.x, Zelda->pos.y, &rect);
}

void j1Player::Move()
{ //temporal
	
		if (selected_character == Link) {
			Link->Move();
		}
		else {
			Zelda->Move();
		}
		uint x, y;
		App->win->GetWindowSize(x, y);
		App->render->camera.x = -selected_character->pos.x + x / 2 - 8;
		App->render->camera.y = -selected_character->pos.y + y / 2 - 8;
	
}

void j1Player::Change_Player()
{
}

void j1Player::Chase()
{
	
}

bool j1Player::Move_Camera()
{
	static int i = 0;
	static float rest_x;
	static float rest_y;
	int sum_x = 0;
	int sum_y = 0;
	int x = other_character->pos.x - selected_character->pos.x;
	int y = other_character->pos.y - selected_character->pos.y;

	rest_x = rest_x + x % 20;
	rest_y = rest_y + y % 20;

	if (rest_x >= 20) {
		sum_x = 1;
		rest_x = rest_x - 20;
	}
	if (rest_y >= 20) {
		sum_y = 1;
		rest_y = rest_y - 20;
	}
	App->render->camera.x = App->render->camera.x + x / 20 + sum_x;
	App->render->camera.y = App->render->camera.y + y / 20 + sum_y;

	if (i >= 20) {
		change = false;
		i = 0;
		rest_x = 0;
		rest_y = 0;
	}
	i++;
	
	return false;
}
