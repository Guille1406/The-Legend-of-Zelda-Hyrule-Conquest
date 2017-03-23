#include "j1Gui.h"
#include "GuiScrollBar.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"

GuiScrollBar::GuiScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, 
	SDL_Rect* idletexture, bool vertical, bool movable, AddGuiTo addto) :
	Gui(position, GuiType::gui_scrollbar, movable, addto), scrollbarbackground(*scrollbarbackground), scrollbarbar(*scrollbarbar), vertical(vertical)
{
	Gui_Collider = { position.x, position.y, scrollbarbackground->w, scrollbarbackground->h };
	ScrollBarButton = new GuiButton(position, bottonstr, type, idletexture, true, AddGuiTo::none);
	ButtonWH.x = idletexture->w;
	ButtonWH.y = idletexture->h;
	if (scrollbarbar != nullptr)
		has_bar = true;
	CalculateScrollMinMax(scrollbarbackground);
}

GuiScrollBar::GuiScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, 
	SDL_Rect* idletexture, SDL_Rect* hoverorpressedtexture, bool vertical, bool movable, AddGuiTo addto) :
	Gui(position, GuiType::gui_scrollbar, movable, addto), scrollbarbackground(*scrollbarbackground), scrollbarbar(*scrollbarbar), vertical(vertical)
{
	Gui_Collider = { position.x, position.y, scrollbarbackground->w, scrollbarbackground->h };
	ScrollBarButton = new GuiButton(position, bottonstr, type, idletexture, hoverorpressedtexture, true, AddGuiTo::none);
	ButtonWH.x = idletexture->w;
	ButtonWH.y = idletexture->h;
	if (scrollbarbar != nullptr)
		has_bar = true;
	CalculateScrollMinMax(scrollbarbackground);
}

GuiScrollBar::GuiScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, 
	SDL_Rect* idletexture, SDL_Rect* hovertexture, SDL_Rect* pressedtexture, bool vertical, bool movable, AddGuiTo addto) :
	Gui(position, GuiType::gui_scrollbar, movable, addto), scrollbarbackground(*scrollbarbackground), scrollbarbar(*scrollbarbar), vertical(vertical)
{
	Gui_Collider = { position.x, position.y, scrollbarbackground->w, scrollbarbackground->h };
	ScrollBarButton = new GuiButton(position, bottonstr, type, idletexture, hovertexture, pressedtexture, true, AddGuiTo::none);
	ButtonWH.x = idletexture->w;
	ButtonWH.y = idletexture->h;
	if (scrollbarbar != nullptr)
		has_bar = true;
	CalculateScrollMinMax(scrollbarbackground);
}

GuiScrollBar::~GuiScrollBar()
{
	delete ScrollBarButton;
}

void GuiScrollBar::CalculateScrollMinMax(SDL_Rect* scrollbarbackground)
{
	if(vertical)
	{
		scroll_max_value = position.y + scrollbarbackground->h - ButtonWH.y;
		scroll_min_value = position.y;
	}
	else
	{
		scroll_max_value = position.x + scrollbarbackground->w - ButtonWH.x;
		scroll_min_value = position.x;
	}
}

void GuiScrollBar::Update(const Gui* mouse_hover, const Gui* focus)
{
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	if (((Gui*)ScrollBarButton)->PointContained(mouse.x, mouse.y))
	{
		ScrollBarButton->Update(ScrollBarButton, focus);
		fPoint button_drag_vel = ScrollBarButton->GetDragVelocity();
		if (button_drag_vel.x != 0.0f || button_drag_vel.y != 0.0f)
		{
			iPoint drag_event_mov = { 0, 0 };
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
				App->input->GetMouseMotion(drag_event_mov.x, drag_event_mov.y);
			iPoint p = ScrollBarButton->GetLocalPos();
			if (vertical)
			{
				int newY = p.y + int(drag_event_mov.y * button_drag_vel.y);
				if ((newY >= position.y) && (newY <= (position.y + scrollbarbackground.h - ButtonWH.y)))
				{
					ScrollBarButton->SetLocalPos(p.x, newY);
					//Calculate bar percentual value
					percentualvalue = (((float)(newY - scroll_min_value)) / ((float)(scroll_max_value - scroll_min_value))) * 100.0f;
				}
				LOG("Vertical Bar Value: %.2f", percentualvalue);
			}
			else
			{
				int newX = p.x + int(drag_event_mov.x * button_drag_vel.x);
				if ((newX >= position.x) && (newX <= (position.x + scrollbarbackground.w - ButtonWH.x)))
				{
					ScrollBarButton->SetLocalPos(newX, p.y);
					//Calculate bar percentual value
					percentualvalue = (((float)(newX - scroll_min_value)) / ((float)(scroll_max_value - scroll_min_value))) * 100.0f;
				}
				LOG("Horitzontal Bar Value: %.2f", percentualvalue);
			}
		}
	}
	else
		ScrollBarButton->Update(mouse_hover, focus);
}

void GuiScrollBar::Draw()
{
	if (this->visible == true)
	{
		//Background
		App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &scrollbarbackground, 1.0f, 0, INT_MAX, INT_MAX, false);
		//Bar
		//App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &scrollbarbar, 1.0f, 0, INT_MAX, INT_MAX, false);
		//Button
		ScrollBarButton->Draw();
		//Debug
		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiScrollBar::EditButtonStr(std::string* newstr)
{
	ScrollBarButton->EditButtonStr(newstr);
}

void GuiScrollBar::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, Cyan(0), Cyan(1), Cyan(2), DEBUG_DRAW_ALPHA, true, false, false);
}

float GuiScrollBar::GetPercentualValue() const
{
	return percentualvalue;
}