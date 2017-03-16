#include "j1App.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Camera.h"
#include "j1Player.h"
#include "j1Window.h"

j1Camera::j1Camera()
{
	name.create("camera");
}

j1Camera::~j1Camera()
{

}

// Called before render is available
bool j1Camera::Awake(pugi::xml_node&)
{
	LitleEllipse.ellipsecentre = { 0,0 };
	LitleEllipse.semimajoraxis = 160;
	LitleEllipse.semiminoraxis = 90;

	BigEllipse.ellipsecentre = { 0,0 };
	BigEllipse.semimajoraxis = 320;
	BigEllipse.semiminoraxis = 180;

	return true;
}

// Called before the first frame
bool j1Camera::Start()
{
	int w, h = 0;
	SDL_GetRendererOutputSize(App->render->renderer, &w, &h);
	Half_w = (int)(w * 0.5f);
	Half_h = (int)(h * 0.5f);
	return true;
}

// Called each loop iteration
bool j1Camera::PreUpdate()
{
	uint Scale = App->win->GetScale();
	App->render->camera.x = ((-1) * (int)(((App->player->Link->pos.x + App->player->Zelda->pos.x) * 0.5f) * Scale)) + Half_w;
	App->render->camera.y = ((-1) * (int)(((App->player->Link->pos.y + App->player->Zelda->pos.y) * 0.5f) * Scale)) + Half_h;
	LitleEllipse.ellipsecentre = BigEllipse.ellipsecentre = { App->render->camera.x,App->render->camera.y };

	return true;
}

// Called each loop iteration
bool j1Camera::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool j1Camera::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Camera::CleanUp()
{
	LOG("Freeing camera");
	return true;
}

void j1Camera::OnGui(Gui* ui, GuiEvent event)
{

}

void j1Camera::OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments)
{

}

void j1Camera::OnConsoleCVar(const CVar* cvar)
{

}