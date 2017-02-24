#ifndef __GUIVIEWPORT_H__
#define __GUIVIEWPORT_H__

#include "Gui.h"

class GuiViewport : public Gui
{
	//Things inside viewport didn't update :), by now...
public:
	GuiViewport(SDL_Rect* rect, bool movable, AddGuiTo addto);
	~GuiViewport();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	void push_back_item(Gui* newitem);

private:
	void DebugDraw() const;

private:
	SDL_Rect viewport_rect;
	std::list<Gui*> ViewportElements;
	iPoint OriginalPosition;

};

#endif // __GUIVIEWPORT_H__