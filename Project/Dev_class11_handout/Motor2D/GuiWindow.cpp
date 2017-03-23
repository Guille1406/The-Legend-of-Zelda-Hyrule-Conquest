#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1Input.h"
#include "GuiWindow.h"

GuiWindow::GuiWindow(iPoint position, SDL_Rect* rect, bool has_background, bool movable, AddGuiTo addto) : Gui(position, GuiType::gui_window, movable, addto),
	background_rect(*rect), has_background(has_background)
{
	Gui_Collider = { position.x, position.y, rect->w, rect->h };
}

GuiWindow::~GuiWindow()
{
	//WindowElements is released in the general cleanup loop
}

void GuiWindow::Update(const Gui* mouse_hover, const Gui* focus)
{
	if (OriginalPosition != position)
	{
		iPoint drag_event_mov = { 0, 0 };
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
			App->input->GetMouseMotion(drag_event_mov.x, drag_event_mov.y);

		iPoint item_local_pos;
		fPoint item_drag_vel;
		for (std::list<Gui*>::iterator item = WindowElements.begin(); item != WindowElements.cend(); ++item)
		{
			item_drag_vel = (*item)->GetDragVelocity();
			if (item_drag_vel.x != 0.0f || item_drag_vel.y != 0.0f)
			{
				item_local_pos = (*item)->GetLocalPos();
				(*item)->SetLocalPos(item_local_pos.x + int(drag_event_mov.x * drag_vel.x), item_local_pos.y + int(drag_event_mov.y * drag_vel.y));
			}
		}
		OriginalPosition = position;
	}
}

void GuiWindow::Draw()
{
	if (this->visible == true)
	{
		if (has_background)
			App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &background_rect, 1.0f, 0, INT_MAX, INT_MAX, false);
		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiWindow::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, DarkBlue(0), DarkBlue(1), DarkBlue(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiWindow::push_back_item(Gui* newitem)
{
	WindowElements.push_back(newitem);
}