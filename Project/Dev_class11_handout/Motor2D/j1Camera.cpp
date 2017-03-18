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
	//Create the ellipses
	LitleEllipse.ellipsecentre = { 0,0 };
	LitleEllipse.semimajoraxis = 160;
	LitleEllipse.semiminoraxis = 90;

	BigEllipse.ellipsecentre = { 0,0 };
	BigEllipse.semimajoraxis = 320;
	BigEllipse.semiminoraxis = 180;

	f_border_between_ellipses = BigEllipse.InsideEllipseValue({ 0,LitleEllipse.semiminoraxis});

	return true;
}

// Called before the first frame
bool j1Camera::Start()
{
	//Get some useful variables
	App->win->scale = f_Max_scale = 2.0f;
	f_Min_scale = 1.0f;
	int w, h = 0;
	SDL_GetRendererOutputSize(App->render->renderer, &w, &h);
	i_Half_w = (int)(w * 0.5f);
	i_Half_h = (int)(h * 0.5f);
	return true;
}

// Called each loop iteration
bool j1Camera::PreUpdate()
{
	//Calculate camera centre
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) App->win->scale += 0.005;
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) App->win->scale -= 0.005;
	float Scale = App->win->GetScale();
	iPoint Centre = { 0,0 };
	Centre.x = ((-1) * (int)(((App->player->Link->pos.x + App->player->Zelda->pos.x) * 0.5f) * Scale));
	Centre.y = ((-1) * (int)(((App->player->Link->pos.y + App->player->Zelda->pos.y) * 0.5f) * Scale));
	//Camera position
	App->render->camera = { Centre.x + i_Half_w ,Centre.y + i_Half_h };
	//Ellipses centre
	LitleEllipse.ellipsecentre = BigEllipse.ellipsecentre = { Centre.x,Centre.y };
	return true;
}

// Called each loop iteration
bool j1Camera::Update(float dt)
{




	/*
	//Is inside the little ellipse
	if (LitleEllipse.InsideEllipse(App->player->Link->pos))
		App->win->scale = f_Max_scale;
	//Is out the little ellipse
	else
	{
		//Is between the big ellipse and the little one
		if (BigEllipse.InsideEllipse(App->player->Link->pos))
		{
			//Scale between f_Max_scale and f_Min_scale




		}
		//Is out the big ellipse
		else
			App->win->scale = f_Min_scale;
	}
	*/
	/*
	App->player->Link->pos;
	App->player->Zelda->pos;
	LitleEllipse.InsideEllipse();
	LitleEllipse.InsideEllipseValue();
	BigEllipse.InsideEllipse();
	BigEllipse.InsideEllipseValue();
	*/

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