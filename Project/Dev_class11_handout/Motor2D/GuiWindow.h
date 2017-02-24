#ifndef __GUIWINDOW_H__
#define __GUIWINDOW_H__

#include "Gui.h"

class GuiWindow : public Gui
{
public:
	GuiWindow(iPoint position, SDL_Rect* rect, bool has_background, bool movable, AddGuiTo addto);
	~GuiWindow();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	void push_back_item(Gui* newitem);

private:
	void DebugDraw() const;

private:
	bool has_background = false;
	SDL_Rect background_rect;
	std::list<Gui*> WindowElements;
	iPoint OriginalPosition;

};

#endif // __GUIWINDOW_H__