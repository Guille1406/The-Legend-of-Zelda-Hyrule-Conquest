#include <math.h>

#include "p2Log.h"
#include "j1GameStartMenuBack.h"
#include "S_MainMenu.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Gui.h"
#include "GuiButton.h"

j1GameStartMenuBackground::j1GameStartMenuBackground()
{
	name.create("gamestartmenubackground");
}

j1GameStartMenuBackground::~j1GameStartMenuBackground()
{

}

// Called before render is available
bool j1GameStartMenuBackground::Awake(pugi::xml_node& conf)
{
	LOG("Loading Game Start Menu Background atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1GameStartMenuBackground::Start()
{
	atlas = App->tex->Load(atlas_file_name.c_str());

	Background_Initial_pos = App->win->GetWindowH() - background.h;

	Background_timer.Start();

	return true;
}

// Called each loop iteration
bool j1GameStartMenuBackground::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1GameStartMenuBackground::Update(float dt)
{
	//Blit background
	int Background_Y_Pos = -App->render->camera.y + Background_Initial_pos + Background_pos;
	App->render->Blit(App->gui->GetAtlas(), -App->render->camera.x + 1, Background_Y_Pos, &background, 1.0f, 0, INT_MAX, INT_MAX, false);
	//Blit background
	if (Background_Y_Pos < -1)
	{
		if (Background_timer.Read() > Background_speed)
		{
			Background_pos += 2;
			Background_timer.Start();
		}
	}
	else
		if (!((S_MainMenu*)App->scene->GetActiveScene())->visibility)
		{
			((S_MainMenu*)App->scene->GetActiveScene())->campaign->SetVisible(true);
			((S_MainMenu*)App->scene->GetActiveScene())->campaign->SetOpacity(startmenuopacity);
			((S_MainMenu*)App->scene->GetActiveScene())->options->SetVisible(true);
			((S_MainMenu*)App->scene->GetActiveScene())->options->SetOpacity(startmenuopacity);
			((S_MainMenu*)App->scene->GetActiveScene())->credits->SetVisible(true);
			((S_MainMenu*)App->scene->GetActiveScene())->credits->SetOpacity(startmenuopacity);
			((S_MainMenu*)App->scene->GetActiveScene())->quit->SetVisible(true);
			((S_MainMenu*)App->scene->GetActiveScene())->quit->SetOpacity(startmenuopacity);
			((S_MainMenu*)App->scene->GetActiveScene())->visibility = true;
			MainMenuOpacity_timer.Start();
		}
		else
		{
			if ((MainMenuOpacity_timer.Read() > 10) && (startmenuopacity < 255))
			{
				startmenuopacity += 5;
				if (startmenuopacity > 255)
					startmenuopacity = 255;
				((S_MainMenu*)App->scene->GetActiveScene())->campaign->SetOpacity(startmenuopacity);
				((S_MainMenu*)App->scene->GetActiveScene())->options->SetOpacity(startmenuopacity);
				((S_MainMenu*)App->scene->GetActiveScene())->credits->SetOpacity(startmenuopacity);
				((S_MainMenu*)App->scene->GetActiveScene())->quit->SetOpacity(startmenuopacity);
				((S_MainMenu*)App->scene->GetActiveScene())->titleopacity = startmenuopacity;
			}
		}

	return true;
}

// Called each loop iteration
bool j1GameStartMenuBackground::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1GameStartMenuBackground::CleanUp()
{
	return true;
}