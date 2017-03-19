#ifndef __GUICHECK_H__
#define __GUICHECK_H__

#include "Gui.h"

class GuiCheck : public Gui
{
public:
	GuiCheck(iPoint position, SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3, bool movable, AddGuiTo addto);
	GuiCheck(iPoint position, SDL_Rect* rect1, SDL_Rect* rect2, bool movable, AddGuiTo addto);
	~GuiCheck();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	bool Checked() const;

private:
	void DebugDraw() const;

private:
	bool bakedcheck = false;
	bool checked = false;
	SDL_Rect* curent_state_texture = nullptr;
	SDL_Rect idle_texture_rect = { 0,0,0,0 };
	SDL_Rect pressed_texture_rect = { 0,0,0,0 };
	SDL_Rect check_texture_rect = { 0,0,0,0 };

};

#endif // __GUICHECK_H__