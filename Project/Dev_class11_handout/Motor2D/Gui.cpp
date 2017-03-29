#include "Gui.h"

#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"

Gui::Gui(iPoint position, GuiType type, bool movable, AddGuiTo purpose) : position(position), movable(movable), type(type), purpose(purpose)
{
	if (movable == true)
		SetDragVelocity(1.0f, 1.0f);
}

void Gui::SetLocalPos(int x, int y)
{
	position.x = Gui_Collider.x = x;
	position.y = Gui_Collider.y = y;
}

iPoint Gui::GetLocalPos() const
{
	return position;
}

void Gui::Move(int x, int y)
{
	position.x += x;
	Gui_Collider.x += x;
	position.y += y;
	Gui_Collider.y += y;
}

void Gui::SetDragVelocity(float x, float y)
{
	drag_vel.x = x;
	drag_vel.y = y;
}

fPoint Gui::GetDragVelocity() const
{
	return drag_vel;
}

void Gui::SetListener(j1Module* module)
{
	module_listener = module;
}

void Gui::SetListener(MainScene* module)
{
	scene_listener = module;
}

void Gui::SetVisible(bool visible)
{
	this->visible = visible;
}

bool Gui::PointContained(int x, int y) const
{
	return ((x >= Gui_Collider.x) && (x < (Gui_Collider.x + Gui_Collider.w)) &&
		(y >= Gui_Collider.y) && (y < (Gui_Collider.y + Gui_Collider.h)));
}

AddGuiTo Gui::GetPurpose() const
{
	return purpose;
}

bool Gui::InFOV()
{
	bool ret = (((Gui_Collider.x >= App->render->camera.x) && (Gui_Collider.x < (App->render->camera.x + App->render->camera.w)) &&
			   (Gui_Collider.y >= App->render->camera.y) && (Gui_Collider.y < (App->render->camera.y + App->render->camera.h))) ||
		       (((Gui_Collider.x + Gui_Collider.w) >= App->render->camera.x) && ((Gui_Collider.x + Gui_Collider.w) < (App->render->camera.x + App->render->camera.w)) &&
		       ((Gui_Collider.y + Gui_Collider.h) >= App->render->camera.y) && ((Gui_Collider.y + Gui_Collider.h) < (App->render->camera.y + App->render->camera.h))) &&
			   (visible == true));
	return ret;
}

void Gui::CheckInput(const Gui* mouse_hover, const Gui* focus)
{
	bool inside = (mouse_hover == this);

	j1Module* listener = nullptr;

	if (module_listener != nullptr)
	{
		listener = module_listener;
	}
	if (scene_listener != nullptr)
	{
		listener = (j1Module*)scene_listener;
	}

	if (mouse_inside != inside)
	{
		mouse_inside = inside;
		if (listener != nullptr)
			if (module_listener != nullptr)
				listener->OnGui(this, (inside) ? GuiEvent::mouse_enter : GuiEvent::mouse_leave);
			else
				((MainScene*)listener)->OnGui(this, (inside) ? GuiEvent::mouse_enter : GuiEvent::mouse_leave);
	}

	if (inside == true)
	{
		if (listener != nullptr)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_lclk_down);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_lclk_down);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_lclk_repeat);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_lclk_repeat);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_UP)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_lclk_up);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_lclk_up);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_DOWN)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_rclk_down);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_rclk_down);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_REPEAT)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_rclk_repeat);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_rclk_repeat);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_UP)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_rclk_up);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_rclk_up);
		}

		if (drag_vel.x != 0.0f || drag_vel.y != 0.0f)
		{
			iPoint drag_event_mov = { 0, 0 };
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
				App->input->GetMouseMotion(drag_event_mov.x, drag_event_mov.y);
			if ((drag_event_mov.x != 0) || (drag_event_mov.y != 0))
			{
				iPoint p = GetLocalPos();
				SetLocalPos(p.x + int(drag_event_mov.x * drag_vel.x), p.y + int(drag_event_mov.y * drag_vel.y));
			}
		}
	}

	/*
	if (focus == this && listener != nullptr)
	{
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_DOWN)
			listener->OnGui(this, GuiEvent::mouse_lclk_down);

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_REPEAT)
			listener->OnGui(this, GuiEvent::mouse_lclk_repeat);

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_UP)
			listener->OnGui(this, GuiEvent::mouse_lclk_up);
	}
	*/
}