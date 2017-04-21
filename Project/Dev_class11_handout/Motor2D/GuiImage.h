#ifndef __GUIIMAGE_H__
#define __GUIIMAGE_H__

#include "Gui.h"

class GuiImage : public Gui
{
public:
	GuiImage(iPoint position, SDL_Rect* rect, bool movable, AddGuiTo addto);
	~GuiImage();

	void Draw();
	void DrawWithAlternativeAtlas(SDL_Texture* alternativeatlas);
	void SetOpacity(uint newopacity);

private:
	void SubDrawFunction(SDL_Texture* atlas);
	void DebugDraw() const;

private:
	SDL_Rect texture_rect = { 0,0,0,0 };

};

#endif // __GUIIMAGE_H__