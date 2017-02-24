#include "j1Gui.h"
#include "GuiCheck.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"

GuiCheck::GuiCheck(iPoint position, SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3, bool movable, AddGuiTo addto):
	Gui(position, GuiType::gui_check, movable, addto), idle_texture_rect(*rect1), pressed_texture_rect(*rect2),
	check_texture_rect(*rect3), curent_state_texture(&idle_texture_rect)
{
	Gui_Collider = { position.x, position.y, rect1->w, rect1->h };
}

GuiCheck::GuiCheck(iPoint position, SDL_Rect* rect1, SDL_Rect* rect2, bool movable, AddGuiTo addto) :
	Gui(position, GuiType::gui_check, movable, addto), idle_texture_rect(*rect1), pressed_texture_rect(*rect2),
	curent_state_texture(&idle_texture_rect), bakedcheck(true)
{
	Gui_Collider = { position.x, position.y, rect1->w, rect1->h };
}

GuiCheck::~GuiCheck()
{

}

void GuiCheck::Update(const Gui* mouse_hover, const Gui* focus)
{
	bool inside = (mouse_hover == (Gui*)this);

	if ((inside == true) && (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN))
	{
		checked = !checked;
		if (checked)
			curent_state_texture = &pressed_texture_rect;
		else
			curent_state_texture = &idle_texture_rect;
	}
}

void GuiCheck::Draw()
{
	if (this->visible == true)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, curent_state_texture);
		if (checked && !bakedcheck)
			App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &check_texture_rect);
		//Debug
		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiCheck::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, Yellow(0), Yellow(1), Yellow(2), DEBUG_DRAW_ALPHA, true, false);
}

bool GuiCheck::Checked() const
{
	return checked;
}