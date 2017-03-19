#ifndef __GUIINPUTTEXT_H__
#define __GUIINPUTTEXT_H__

#include "Gui.h"
#include "GuiLabel.h"
#include "j1Fonts.h"
#include "j1Timer.h"

class GuiInputText : public Gui
{
public:
	GuiInputText(iPoint position, SDL_Rect* rect, std::string* string, bool has_backgound, bool is_password, bool movable, AddGuiTo addto);
	~GuiInputText();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	void SetFont(_TTF_Font* newfont);
	void SetPassword(bool ispassword);
	void Clear();
	std::string* GetInputString();

private:
	void DebugDraw() const;
	void CreateInputTextLabel(iPoint position, std::string* str, bool movable);
	void CalculateStrWH();
	void MoveStr();
	void ShowHidePassword();

private:
	bool has_background = false;
	SDL_Rect texture_writablearea_rect = { 0,0,0,0 };
	GuiLabel* InputTextString = nullptr;
	std::string OriginalString;
	std::string string;
	std::string password_string;
	int InputTextString_w = 0;
	int InputTextString_h = 0;
	bool is_password = false;
	iPoint InputTextStringPos = { 0,0 };
	iPoint OriginalPosition = { 0,0 };
	uint previous_str_len = 0;
	uint new_str_len = 0;

	j1Timer edit_timer;
};

#endif // __GUIINPUTTEXT_H__