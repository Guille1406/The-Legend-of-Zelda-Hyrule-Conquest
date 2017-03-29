#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "Gui.h"
#include "GuiLabel.h"

enum ButtonState
{
	Idle_Button,
	Hover_Button,
	Pressed_Button
};

class GuiButton : public Gui
{
public:
	GuiButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* rect1, bool movable, AddGuiTo addto);
	GuiButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* rect1, SDL_Rect* rect2, bool movable, AddGuiTo addto);
	GuiButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3, bool movable, AddGuiTo addto);
	~GuiButton();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	void EditButtonStr(std::string* newstr);
	void SetFont(_TTF_Font* newfont);
	void SetButtonColor(Color* newcolor);
	void SetOpacity(uint newopacity);

private:
	void CreateButtonLabel(iPoint position, std::string* str, bool movable);
	void DebugDraw() const;
	void CalculateStrWH(const std::string* str);
	void CenterStr();

private:
	GuiLabel* ButtonString = nullptr;
	int ButtonString_w = 0;
	int ButtonString_h = 0;
	iPoint ButtonStringPos = { 0,0 };
	iPoint OriginalPosition = { 0,0 };
	ButtonType button_type = ButtonType::undef;
	ButtonState Button_State = ButtonState::Idle_Button;
	SDL_Rect* curent_state_texture = nullptr;
	SDL_Rect idle_texture_rect = { 0,0,0,0 };
	SDL_Rect hover_texture_rect = { 0,0,0,0 };
	SDL_Rect pressed_texture_rect = { 0,0,0,0 };
	uint opacity = 255;

};

#endif // __GUIBUTTON_H__