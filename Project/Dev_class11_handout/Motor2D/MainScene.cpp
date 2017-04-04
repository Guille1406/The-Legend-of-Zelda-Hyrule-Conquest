#include "j1Scene.h"
#include "MainScene.h"

void MainScene::MenuInput(std::vector<GuiButton*>* buttons)
{
	if (this == App->scene->GetActiveScene())
	{
		if ((App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) || (App->input->GetControllerButton(0, 11) == KEY_DOWN))
		{
			std::vector<GuiButton*>::iterator focused_button = std::find(buttons->begin(), buttons->end(), App->gui->GetFocus());
			if ((*focused_button) != buttons->front())
			{
				focused_button--;
				App->gui->SetFocus((*(focused_button)));
			}
		}

		if ((App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) || (App->input->GetControllerButton(0, 12) == KEY_DOWN))
		{
			std::vector<GuiButton*>::iterator focused_button = std::find(buttons->begin(), buttons->end(), App->gui->GetFocus());
			if ((*focused_button) != buttons->back())
			{
				focused_button++;
				App->gui->SetFocus((*(focused_button)));
			}
		}
	}
}