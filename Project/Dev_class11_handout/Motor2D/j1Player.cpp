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
	return true;
}

bool j1Player::PreUpdate()
{
	return true;
}

bool j1Player::Update(float dt)
{
	
	if (selected_character == Link) {
		Link->Move();
	}
	else {
		Zelda->Move();
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (selected_character == Link)selected_character = Zelda;
		else selected_character = Link;
	}
	
	Draw();
	Move();
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
	uint x, y;
	App->win->GetWindowSize(x, y);
	App->render->camera.x = -selected_character->pos.x + x/2 - 8;
	App->render->camera.y = -selected_character->pos.y + y/2 - 8;

}

void j1Player::Change_Player()
{
}

void j1Player::Chase()
{
}
