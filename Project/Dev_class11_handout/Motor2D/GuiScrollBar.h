#include "Gui.h"
#include "GuiButton.h"

class GuiScrollBar : public Gui
{
public:
	GuiScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, bool vertical, bool movable, AddGuiTo addto);
	GuiScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hoverorpressedtexture, bool vertical, bool movable, AddGuiTo addto);
	GuiScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hovertexture, SDL_Rect* pressedtexture, bool vertical, bool movable, AddGuiTo addto);
	~GuiScrollBar();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	void EditButtonStr(std::string* newstr);
	float GetPercentualValue() const;

private:
	void DebugDraw() const;
	void CalculateScrollMinMax(SDL_Rect* scrollbarbackground);

private:
	GuiButton* ScrollBarButton = nullptr;
	SDL_Rect scrollbarbackground;
	SDL_Rect scrollbarbar;
	iPoint ButtonWH;
	bool has_bar = true;
	bool vertical = true;
	int scroll_max_value = 0;
	int scroll_min_value = 0;
	float percentualvalue = 0.0f;

};