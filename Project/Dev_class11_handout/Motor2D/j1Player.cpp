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

	Link->Link_Sprite = App->tex->Load("textures/map.png");

	
	return true;
}

bool j1Player::PreUpdate()
{
	return true;
}

bool j1Player::Update(float dt)
{
	Link->Move();
	
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
	App->render->Blit(Link->Link_Sprite,Link->pos.x,Link->pos.y,&rect);

}

void j1Player::Move()
{ //temporal
	uint x, y;
	App->win->GetWindowSize(x, y);
	App->render->camera.x = -Link->pos.x + x/2 - 8;
	App->render->camera.y = -Link->pos.y + y/2 - 8;

}

void j1Player::Change_Player()
{
}

void j1Player::Chase()
{
}
