#include "j1Gui.h"
#include "GuiButton.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Fonts.h"

GuiButton::GuiButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* rect1, bool movable, AddGuiTo addto) :
	Gui(position, GuiType::gui_button, movable, addto), button_type(type), idle_texture_rect(*rect1),
	curent_state_texture(&idle_texture_rect)
{
	Gui_Collider = { position.x, position.y, rect1->w, rect1->h };
	CalculateStrWH(str);
	CreateButtonLabel(ButtonStringPos, str, movable);
}

GuiButton::GuiButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* rect1, SDL_Rect* rect2, bool movable, AddGuiTo addto) :
	Gui(position, GuiType::gui_button, movable, addto), button_type(type), idle_texture_rect(*rect1),
	curent_state_texture(&idle_texture_rect)
{
	if (type == ButtonType::idle_hover)
		hover_texture_rect = *rect2;
	else
		pressed_texture_rect = *rect2;
	Gui_Collider = { position.x, position.y, rect1->w, rect1->h };
	CalculateStrWH(str);
	CreateButtonLabel(ButtonStringPos, str, movable);
}

GuiButton::GuiButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3, bool movable, AddGuiTo addto) :
	Gui(position, GuiType::gui_button, movable, addto), button_type(type), idle_texture_rect(*rect1),
	hover_texture_rect(*rect2), pressed_texture_rect(*rect3), curent_state_texture(&idle_texture_rect)
{
	Gui_Collider = { position.x, position.y, rect1->w, rect1->h };
	CalculateStrWH(str);
	CreateButtonLabel(ButtonStringPos, str, movable);
}

GuiButton::~GuiButton()
{
	delete ButtonString;
}

void GuiButton::Update(const Gui* mouse_hover, const Gui* focus)
{
	bool inside = (mouse_hover == (Gui*)this);

	if ((inside == true) || (focus == this))
	{
		switch (button_type)
		{
		case ButtonType::idle_hover:
			curent_state_texture = &hover_texture_rect;
			break;
		case ButtonType::idle_pressed:
			curent_state_texture = &idle_texture_rect;
			if ((App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN) || (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT))
				curent_state_texture = &pressed_texture_rect;
			break;
		case ButtonType::idle_hover_pressed:
			curent_state_texture = &hover_texture_rect;
			if ((App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN) || (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT))
				curent_state_texture = &pressed_texture_rect;
			break;
		}
	}
	else
	{
		curent_state_texture = &idle_texture_rect;
	}
	if (OriginalPosition != position)
	{
		CenterStr();
		ButtonString->SetLocalPos(ButtonStringPos.x, ButtonStringPos.y);
	}
}

void GuiButton::Draw()
{
	SubDrawFunction(App->gui->GetAtlas());
}

void GuiButton::DrawWithAlternativeAtlas(SDL_Texture* alternativeatlas)
{
	SubDrawFunction(alternativeatlas);
}

void GuiButton::SubDrawFunction(SDL_Texture* atlas)
{
	if (this->visible == true)
	{
		//Button
		App->render->Blit(atlas, position.x - App->render->camera.x, position.y - App->render->camera.y, curent_state_texture, 1.0f, 0, INT_MAX, INT_MAX, false, opacity);
		//Label
		ButtonString->Draw();
		//Debug
		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiButton::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, Orange(0), Orange(1), Orange(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiButton::CreateButtonLabel(iPoint position, std::string* str, bool movable)
{
	ButtonString = new GuiLabel(position, str, movable, AddGuiTo::none);
}

void GuiButton::EditButtonStr(std::string* newstr)
{
	ButtonString->EditLabelStr(newstr);
	CalculateStrWH(newstr);
}

void GuiButton::SetButtonColor(Color* newcolor)
{
	ButtonString->SetLabelColor(newcolor);
}

void GuiButton::SetFont(_TTF_Font* newfont)
{
	ButtonString->SetFont(newfont);
	CalculateStrWH(ButtonString->GetLabelStr());
}

void GuiButton::CalculateStrWH(const std::string* str)
{
	if(ButtonString != nullptr)
		App->font->CalcSize(str->c_str(), ButtonString_w, ButtonString_h, ButtonString->GetFont());
	else
		App->font->CalcSize(str->c_str(), ButtonString_w, ButtonString_h);
	CenterStr();
}

void GuiButton::CenterStr()
{
	ButtonStringPos.x = (int)(position.x + ((Gui_Collider.w - ButtonString_w) * 0.5f));
	ButtonStringPos.y = (int)(position.y + ((Gui_Collider.h - ButtonString_h) * 0.5f));
	if (ButtonString != nullptr)
		ButtonString->SetLocalPos(ButtonStringPos.x, ButtonStringPos.y);
	OriginalPosition = position;
}

void GuiButton::SetOpacity(uint newopacity)
{
	if (newopacity < 0)
		opacity = 0;
	else if (newopacity > 255)
		opacity = 255;
	else
	opacity = newopacity;
	ButtonString->SetOpacity(opacity);
}