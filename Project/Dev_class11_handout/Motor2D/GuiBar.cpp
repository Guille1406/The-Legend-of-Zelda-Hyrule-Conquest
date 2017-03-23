#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "GuiBar.h"

GuiBar::GuiBar(iPoint position, BarType type, SDL_Rect* rect1, int max_value, int min_value, Color* bar_color, int bar_color_alpha, bool movable, AddGuiTo addto) :
	Gui(position, GuiType::gui_bar, movable, addto), type(type), value(max_value), pastvalue(max_value), max_value(max_value), min_value(min_value), bar_color(bar_color),
	bar_color_alpha(bar_color_alpha), bar_rect(*rect1), has_background(false), original_bar_rect(*rect1)
{
	Gui_Collider = { position.x, position.y, rect1->w, rect1->h };
}

GuiBar::GuiBar(iPoint position, BarType type, SDL_Rect* rect1, SDL_Rect* rect2, int max_value, int min_value, Color* bar_color, int bar_color_alpha, bool movable, AddGuiTo addto) :
	Gui(position, GuiType::gui_bar, movable, addto), type(type), value(max_value), pastvalue(max_value), max_value(max_value), min_value(min_value), bar_color(bar_color),
	bar_color_alpha(bar_color_alpha), background_texture_rect(*rect1), bar_rect(*rect2), has_background(true), original_bar_rect(*rect2)
{
	Gui_Collider = { position.x, position.y, rect1->w, rect1->h };
	bar_rect.x += position.x;
	bar_rect.y += position.y;
}

GuiBar::~GuiBar()
{

}

void GuiBar::Update(const Gui* mouse_hover, const Gui* focus)
{
	if (value != pastvalue)
	{
		int beforeh = 0;
		int beforew = 0;
		switch (type)
		{
		case BarType::vertical_up:
			beforeh = bar_rect.h;
			bar_rect.h = ((abs(min_value) + value) * original_bar_rect.h) / (max_value + abs(min_value));
			bar_rect.y += (beforeh - bar_rect.h);
			break;
		case BarType::vertical_down:
			bar_rect.h = ((abs(min_value) + value) * original_bar_rect.h) / (max_value + abs(min_value));
			break;
		case BarType::horitzontal_left:
			beforew = bar_rect.w;
			bar_rect.w = ((abs(min_value) + value) * original_bar_rect.w) / (max_value + abs(min_value));
			bar_rect.x += (beforew - bar_rect.w);
			break;
		case BarType::horitzontal_right:
			bar_rect.w = ((abs(min_value) + value) * original_bar_rect.w) / (max_value + abs(min_value));
			break;
		}
		pastvalue = value;
	}
	/*
	if ((bar_rect.x != (position.x + original_bar_rect.x)) || (bar_rect.y != (position.y + original_bar_rect.y)))
	{
		bar_rect.x = position.x + original_bar_rect.x;
		bar_rect.y = position.y + original_bar_rect.y;
	}
	*/
}

void GuiBar::Draw()
{
	if (this->visible == true)
	{
		if(has_background)
			App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &background_texture_rect, 1.0f, 0, INT_MAX, INT_MAX, false);
		if(value > min_value)
			App->render->DrawQuad(bar_rect, (*bar_color)(0), (*bar_color)(1), (*bar_color)(2), bar_color_alpha, true, false);
		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiBar::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, Red(0), Red(1), Red(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiBar::SetValue(int newvalue)
{
	value = newvalue;
	NormalizeValue();
}

void GuiBar::EditValue(int valuevariation)
{
	value += valuevariation;
	NormalizeValue();
}

void GuiBar::NormalizeValue()
{
	if (value < min_value)
		value = min_value;
	if (value > max_value)
		value = max_value;
}