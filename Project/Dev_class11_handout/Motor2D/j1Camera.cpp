#include "j1App.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Camera.h"
#include "j1Player.h"
#include "j1Window.h"
#include "Color.h"

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
	LitleEllipse.semimajoraxis = (int)(320);
	LitleEllipse.semiminoraxis = (int)(180);

	BigEllipse.ellipsecentre = { 0,0 };
	BigEllipse.semimajoraxis = (int)(640);
	BigEllipse.semiminoraxis = (int)(360);

	f_border_between_ellipses = BigEllipse.InsideEllipseValue({ 0,LitleEllipse.semiminoraxis});

	DebugPerformanceData_Rect = { App->render->camera.x,App->render->camera.y,20,20 };

	return true;
}

// Called before the first frame
bool j1Camera::Start()
{
	//Get some useful variables
	f_Max_scale = App->win->scale;
	f_Min_scale = f_Max_scale - 1.0f;
	if (f_Min_scale <= 0.0f)
		f_Min_scale = 0.8f;
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
	Centre.x = ((-1) * (int)((((float)(App->player->Link->pos.x + App->player->Zelda->pos.x)) * 0.5f) * Scale));
	Centre.y = ((-1) * (int)((((float)(App->player->Link->pos.y + App->player->Zelda->pos.y)) * 0.5f) * Scale));
	//Camera position
	App->render->camera.x = Centre.x + i_Half_w;
	App->render->camera.y = Centre.y + i_Half_h;
	//Ellipses centre
	LitleEllipse.ellipsecentre = BigEllipse.ellipsecentre = { (int)(App->render->camera.x - Centre.x * Scale), (int)(App->render->camera.y - Centre.y * Scale) };
	return true;
}

// Called each loop iteration
bool j1Camera::Update(float dt)
{
	iPoint LinkPos = { 0,0 };
	LinkPos = App->render->WorldToScreen(App->player->Link->pos.x, App->player->Link->pos.y);
	//Is inside the little ellipse
	if (LitleEllipse.InsideEllipse(LinkPos))
		App->win->scale = f_Max_scale;
	//Is out the little ellipse
	else
	{
		//Is between the big ellipse and the little one
		if (BigEllipse.InsideEllipse(LinkPos))
		{
			//Scale between f_Max_scale and f_Min_scale
			float f_percentual_value = (((float)(BigEllipse.InsideEllipseValue(LinkPos) - f_border_between_ellipses)) / ((float)(1.0f - f_border_between_ellipses))) * 100.0f;
			float f_invert_percentual_value = 100.0f - f_percentual_value;
			if (f_invert_percentual_value < 0.0f)
				f_invert_percentual_value = 0.0f;
			else if (f_invert_percentual_value > 100.0f)
				f_invert_percentual_value = 100.0f;
			App->win->scale = (((f_Max_scale - f_Min_scale) * f_invert_percentual_value) / (100.0f)) + f_Min_scale;
		}
		//Is out the big ellipse
		else
			App->win->scale = f_Min_scale;
	}

	//Some ellipses debug draw for testing
	/*
	//Little ellipse
	//Centre
	App->render->DrawCircle(LitleEllipse.ellipsecentre.x, LitleEllipse.ellipsecentre.y, 5, 0, 0, 255);
	//Axis
	App->render->DrawCircle(LitleEllipse.ellipsecentre.x + LitleEllipse.semimajoraxis, LitleEllipse.ellipsecentre.y, 5, 0, 0, 255);
	App->render->DrawCircle(LitleEllipse.ellipsecentre.x - LitleEllipse.semimajoraxis, LitleEllipse.ellipsecentre.y, 5, 0, 0, 255);
	App->render->DrawCircle(LitleEllipse.ellipsecentre.x, LitleEllipse.ellipsecentre.y + LitleEllipse.semiminoraxis, 5, 0, 0, 255);
	App->render->DrawCircle(LitleEllipse.ellipsecentre.x, LitleEllipse.ellipsecentre.y - LitleEllipse.semiminoraxis, 5, 0, 0, 255);

	//Big ellipse
	App->render->DrawCircle(BigEllipse.ellipsecentre.x, BigEllipse.ellipsecentre.y, 10, 255,0,0);
	//Axis
	App->render->DrawCircle(BigEllipse.ellipsecentre.x + BigEllipse.semimajoraxis, BigEllipse.ellipsecentre.y, 10, 255, 0, 0);
	App->render->DrawCircle(BigEllipse.ellipsecentre.x - BigEllipse.semimajoraxis, BigEllipse.ellipsecentre.y, 10, 255, 0, 0);
	App->render->DrawCircle(BigEllipse.ellipsecentre.x, BigEllipse.ellipsecentre.y + BigEllipse.semiminoraxis, 10, 255, 0, 0);
	App->render->DrawCircle(BigEllipse.ellipsecentre.x, BigEllipse.ellipsecentre.y - BigEllipse.semiminoraxis, 10, 255, 0, 0);
	*/

	//WIP
	//Here we will do a debug window with perdformance data
	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last Frame Ms: %u Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %lu ",
		App->avg_fps, App->last_frame_ms, App->frames_on_last_update, App->dt, App->seconds_since_startup, App->frame_count);
	App->win->SetTitle(title);

	App->render->DrawQuad(DebugPerformanceData_Rect, Blue(0), Blue(1), Blue(2), 80, true, true, false);

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