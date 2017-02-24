#ifndef __GUIIMAGE_H__
#define __GUIIMAGE_H__

#include "Gui.h"

class GuiImage : public Gui
{
public:
	GuiImage(iPoint position, SDL_Rect* rect, bool movable, AddGuiTo addto);
	~GuiImage();

	void Draw();

private:
	void DebugDraw() const;

private:
	SDL_Rect texture_rect;

};

#endif // __GUIIMAGE_H__