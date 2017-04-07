#include <cctype>

#include "j1Gui.h"
#include "GuiInputText.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Fonts.h"

GuiInputText::GuiInputText(iPoint position, SDL_Rect* rect, std::string* string, bool has_backgound, bool is_password, bool movable, AddGuiTo addto):
	Gui(position, GuiType::gui_inputtext, movable, addto), has_background(has_backgound), OriginalString(*string), string(*string),
	is_password(is_password), texture_writablearea_rect(*rect)
{
	Gui_Collider = { position.x, position.y, rect->w, rect->h };
	CreateInputTextLabel(position, string, movable);
	CalculateStrWH();
	password_string.clear();
	new_str_len = string->length();
	for (uint i = 0; i < new_str_len; i++)
		password_string += password_char;
	previous_str_len = new_str_len;
	edit_timer.Start();
}

GuiInputText::~GuiInputText()
{
	delete InputTextString;
}

void GuiInputText::Update(const Gui* mouse_hover, const Gui* focus)
{
	bool inside = (mouse_hover == (Gui*)this);

	if (inside == true)
	{
		std::string InputChar = *App->input->GetInputString();
		if((InputChar != empty_char) && (InputTextString_w < (Gui_Collider.w - 20)))
		{
			if (std::isalnum(InputChar[0]))
				//The way the mototr works, InputChar will always be 1 char, so only InputChar[0] is OK
			{
				string += InputChar;
				password_string += password_char;
				CalculateStrWH();
			}
		}
		if ((App->input->GetKey(SDL_SCANCODE_BACKSPACE) == j1KeyState::KEY_REPEAT) && (string != empty_char))
		{
			if (edit_timer.ReadSec() >= 0.05) {
				string.pop_back();
				password_string.pop_back();
				edit_timer.Start();
			}
			CalculateStrWH();
		}
	}
}

void GuiInputText::Draw()
{
	if (this->visible == true)
	{
		ShowHidePassword();
		//background
		if (has_background)
			App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &texture_writablearea_rect, 1.0f, 0, INT_MAX, INT_MAX, false);
		//Label
		if (OriginalPosition != position)
			MoveStr();
		if (string != empty_char)
			InputTextString->Draw();
		//Debug
		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiInputText::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, Green(0), Green(1), Green(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiInputText::SetFont(_TTF_Font* newfont)
{
	InputTextString->SetFont(newfont);
	CalculateStrWH();
}

void GuiInputText::SetPassword(bool ispassword)
{
	is_password = ispassword;
}

void GuiInputText::Clear()
{
	string.clear();
	password_string.clear();
	InputTextString->Clear();
	CalculateStrWH();
}

void GuiInputText::CreateInputTextLabel(iPoint position, std::string* str, bool movable)
{
	InputTextString = new GuiLabel(position, str, movable, AddGuiTo::none);
}

void GuiInputText::CalculateStrWH()
{
	App->font->CalcSize(string.c_str(), InputTextString_w, InputTextString_h, InputTextString->GetFont());
	MoveStr();
}

void GuiInputText::MoveStr()
{
	InputTextStringPos.x = position.x + 10;
	InputTextStringPos.y = (int)(position.y + ((Gui_Collider.h - InputTextString_h) * 0.5f));
	OriginalPosition = position;
	InputTextString->SetLocalPos(InputTextStringPos.x, InputTextStringPos.y);
}

void GuiInputText::ShowHidePassword()
{
	new_str_len = string.length();
	if (new_str_len != previous_str_len)
	{
		if (is_password)
			InputTextString->EditLabelStr(&password_string);
		else
			InputTextString->EditLabelStr(&string);
		previous_str_len = new_str_len;
	}
}

std::string* GuiInputText::GetInputString()
{
	return &string;
}