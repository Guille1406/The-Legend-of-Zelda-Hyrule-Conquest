#ifndef __GUIBAR_H__
#define __GUIBAR_H__

#include "Gui.h"
#include "Color.h"

class GuiBar : public Gui
{
public:
	GuiBar(iPoint position, BarType type, SDL_Rect* rect1, int max_value, int min_value, Color* bar_color, int bar_color_alpha, bool movable, AddGuiTo addto);
	GuiBar(iPoint position, BarType type, SDL_Rect* rect1, SDL_Rect* rect2, int max_value, int min_value, Color* bar_color, int bar_color_alpha, bool movable, AddGuiTo addto);
	~GuiBar();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	void SetValue(int newvalue);
	void EditValue(int valuevariation);

private:
	void DebugDraw() const;
	void NormalizeValue();

private:
	BarType type = BarType::unknown;
	int value = 0;
	int pastvalue = 0;
	int max_value = 0;
	int min_value = 0;
	Color* bar_color;
	int bar_color_alpha = 255;
	bool has_background = false;
	SDL_Rect background_texture_rect = { 0,0,0,0 };
	SDL_Rect bar_rect = { 0,0,0,0 };
	SDL_Rect original_bar_rect = { 0,0,0,0 };

};

#endif // __GUIBAR_H__