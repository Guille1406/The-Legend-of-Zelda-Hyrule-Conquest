#include "j1App.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Camera.h"
#include "j1Player.h"
#include "j1Window.h"
#include "Color.h"
#include "GuiLabel.h"

j1Camera::j1Camera()
{
	name = "camera";
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

	DebugPerformanceData_Rect = { 0,0,260,150 };

	return true;
}

// Called before the first frame
bool j1Camera::Start()
{
	//Get some useful variables
	f_Max_scale = App->win->scale;
	f_Min_scale = f_Max_scale - 0.3f;
	if (f_Min_scale < 0.8f)
		f_Min_scale = 0.8f;
	int w = 0, h = 0;
	SDL_GetRendererOutputSize(App->render->renderer, &w, &h);
	i_Half_w = (int)(w * 0.5f);
	i_Half_h = (int)(h * 0.5f);

	//Fill up debug performance data vector
	for (int i = 0, pos = App->win->GetWindowH() - DebugPerformanceData_Rect.h + 6; i < 9; i++, pos += 15) //9, number of debug strings
		DebugPerformanceData.push_back(App->gui->CreateLabel({ 10,pos }, &std::string(""), false, AddGuiTo::none));
	DebugPerformanceData[6]->EditLabelStr(&std::string("Press F9 to toggle this window visibility."));
	DebugPerformanceData[6]->SetLabelColor(&Yellow);
	DebugPerformanceData[7]->EditLabelStr(&std::string("Press F10 to report a bug."));
	DebugPerformanceData[7]->SetLabelColor(&Yellow);
	DebugPerformanceData[8]->EditLabelStr(&std::string("Press F11 to take a screenshot."));
	DebugPerformanceData[8]->SetLabelColor(&Yellow);

	return true;
}

// Called each loop iteration
bool j1Camera::PreUpdate()
{
	if (Cam_move_paused)
		return true;

	//Calculate camera centre
	float Scale = App->win->GetScale();
	iPoint Centre = { 0,0 };
	Centre.x = (int)((((float)(App->player->Link->pos.x + App->player->Zelda->pos.x)) * 0.5f));
	Centre.y = (int)((((float)(App->player->Link->pos.y + App->player->Zelda->pos.y)) * 0.5f));
	
	//Camera position
	App->render->camera.x = (int)(-Centre.x * Scale + i_Half_w);
	App->render->camera.y = (int)(-Centre.y * Scale + i_Half_h);

	if(App->render->camera.x >= 0)
		App->render->camera.x = 0;
	if (-App->render->camera.x >= App->map->data.width * App->map->data.tile_width * Scale - App->render->camera.w)
		App->render->camera.x = (int)(-(App->map->data.width * App->map->data.tile_width * Scale - App->render->camera.w));

	if (App->render->camera.y >= 0)
		App->render->camera.y = 0;
	if (-App->render->camera.y >= App->map->data.height * App->map->data.tile_height * Scale - App->render->camera.h)
		App->render->camera.y = (int)(-(App->map->data.height * App->map->data.tile_height * Scale - App->render->camera.h));

	//Ellipss centre
	iPoint CentrePos = { 0,0 };
	CentrePos = App->render->WorldToScreen(Centre.x, Centre.y);
	LitleEllipse.ellipsecentre = BigEllipse.ellipsecentre = { (int)(CentrePos.x), (int)(CentrePos.y) };

	//Debug Performance Data
	DebugPerformanceData_Rect.x = -App->render->camera.x;
	DebugPerformanceData_Rect.y = -App->render->camera.y + App->win->GetWindowH() - DebugPerformanceData_Rect.h;
	return true;
}

// Called each loop iteration
bool j1Camera::Update(float dt)
{
	if (Cam_move_paused)
		return true;

	iPoint LinkPos = { 0,0 };
	LinkPos = App->render->WorldToScreen(App->player->Link->pos.x, App->player->Link->pos.y);
	/**/
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

	App->win->scale = floor(App->win->scale * 1000 + 0.5f) * 0.001;

	/**/

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
	//Centre
	App->render->DrawCircle(BigEllipse.ellipsecentre.x, BigEllipse.ellipsecentre.y, 10, 255, 0, 0);
	//Axis
	App->render->DrawCircle(BigEllipse.ellipsecentre.x + BigEllipse.semimajoraxis, BigEllipse.ellipsecentre.y, 10, 255, 0, 0);
	App->render->DrawCircle(BigEllipse.ellipsecentre.x - BigEllipse.semimajoraxis, BigEllipse.ellipsecentre.y, 10, 255, 0, 0);
	App->render->DrawCircle(BigEllipse.ellipsecentre.x, BigEllipse.ellipsecentre.y + BigEllipse.semiminoraxis, 10, 255, 0, 0);
	App->render->DrawCircle(BigEllipse.ellipsecentre.x, BigEllipse.ellipsecentre.y - BigEllipse.semiminoraxis, 10, 255, 0, 0);
	*/

	//Debug window with perdformance data
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		f_DebugPerformanceData = !f_DebugPerformanceData;

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		ShellExecute(NULL, "open", "https://github.com/Guille1406/The-Legend-of-Zelda-Hyrule-Conquest/issues", NULL, NULL, SW_SHOWMAXIMIZED);

	if (f_DebugPerformanceData)
	{
		App->render->DrawQuad(DebugPerformanceData_Rect, Blue(0), Blue(1), Blue(2), 150, true, true, false);

		for (uint i = 0; i < DebugPerformanceData.size(); i++)
		{
			switch (i)
			{
			case 0:
				static char AvFPS[25];
				sprintf_s(AvFPS, 25, "Av.FPS: %.2f", App->avg_fps);
				DebugPerformanceData[i]->EditLabelStr(&std::string(AvFPS));
				break;
			case 1:
				static char LastFrameMs[25];
				sprintf_s(LastFrameMs, 25, "Last Frame Ms: %u", App->last_frame_ms);
				DebugPerformanceData[i]->EditLabelStr(&std::string(LastFrameMs));
				break;
			case 2:
				static char Lastsecframes[25];
				sprintf_s(Lastsecframes, 25, "Last sec frames: %i", App->frames_on_last_update);
				DebugPerformanceData[i]->EditLabelStr(&std::string(Lastsecframes));
				break;
			case 3:
				static char Lastdt[25];
				sprintf_s(Lastdt, 25, "Last dt: %.3f", App->dt);
				DebugPerformanceData[i]->EditLabelStr(&std::string(Lastdt));
				break;
			case 4:
				static char Timesincestartup[100];
				sprintf_s(Timesincestartup, 100, "Time since startup: %.3f", App->seconds_since_startup);
				DebugPerformanceData[i]->EditLabelStr(&std::string(Timesincestartup));
				break;
			case 5:
				static char FrameCount[100];
				sprintf_s(FrameCount, 100, "Frame Count: %lu", App->frame_count);
				DebugPerformanceData[i]->EditLabelStr(&std::string(FrameCount));
				break;
			}
			DebugPerformanceData[i]->Draw();
		}
	}

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

	for (std::vector<GuiLabel*>::iterator item = DebugPerformanceData.begin(); item != DebugPerformanceData.cend(); ++item)
		RELEASE(*item);

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

void j1Camera::PauseCamMovement()
{
	Cam_move_paused = true;
}

void j1Camera::ResumeCamMovement()
{
	Cam_move_paused = false;
}