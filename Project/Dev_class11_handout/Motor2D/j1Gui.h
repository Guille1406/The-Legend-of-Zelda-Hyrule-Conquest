#ifndef __j1GUI_H__
#define __j1GUI_H__

#include <list>

#include "j1Module.h"
#include "Gui.h"

#define CURSOR_WIDTH 2
#define DEBUG_DRAW_ALPHA 80

class Gui;
class GuiImage;
class GuiLabel;
class GuiButton;
class GuiCheck;
class GuiBar;
class GuiScrollBar;
class GuiInputText;
class GuiWindow;
class GuiViewport;

class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	GuiImage* CreateImage(iPoint position, SDL_Rect* rect, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiLabel* CreateLabel(iPoint position, std::string* str, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiButton* CreateButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* idletexture, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiButton* CreateButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hoverorpressedtexture, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiButton* CreateButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hovertexture, SDL_Rect* pressedtexture, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiCheck* CreateCheck(iPoint position, SDL_Rect* idletexture, SDL_Rect* checkedtexture, SDL_Rect* checktexture, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiCheck* CreateCheck(iPoint position, SDL_Rect* idletexture, SDL_Rect* checkedtexturewithbakedcheck, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiBar* CreateBar(iPoint position, BarType type, SDL_Rect* colorbar, int min_value, int max_value, Color* bar_color, int bar_color_alpha = 255, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	//x and y of colorbar are the offset of the bar from bartexture rect
	GuiBar* CreateBar(iPoint position, BarType type, SDL_Rect* bartexture, SDL_Rect* colorbar, int min_value, int max_value, Color* bar_color, int bar_color_alpha = 255, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	//vertical = true, vertical scrollbar, vertical = false, horitzontal scrollbar
	GuiScrollBar* CreateScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, bool vertical = true, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiScrollBar* CreateScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hoverorpressedtexture, bool vertical = true, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiScrollBar* CreateScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hovertexture, SDL_Rect* pressedtexture, bool vertical = true, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	//if has_backgound=true, rect is the rect of the texture of the background, else, rect is the writable area
	GuiInputText* CreateInputText(iPoint position, SDL_Rect* rect, std::string* string, bool has_backgound = false, bool is_password = false, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	//if has_backgound=true, rect is the rect of the texture of the background, else, rect is the window collision area
	GuiWindow* CreateGuiWindow(iPoint position, SDL_Rect* rect, bool has_background = false, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);
	//rect x,y is position, w,h width and heith of the viewport
	GuiViewport* CreateViewport(SDL_Rect* rect, bool movable = false, AddGuiTo addto = AddGuiTo::regular_purpose);

	SDL_Texture* GetAtlas();

	bool Gui_DebugDraw_isactive()
	{
		return Gui_DebugDraw;
	}

private:
	const Gui* FindMouseHover();
	bool CanInteract(Gui* ui) const;
	void push_back_gui(Gui* gui, AddGuiTo addto);
	bool InFOV(Gui* gui);

private:
	bool Gui_DebugDraw = false;

	SDL_Texture* atlas;
	std::string atlas_file_name;

	std::list<Gui*> GuiElements;
	std::list<Gui*> ConsoleElements;

};

#endif // __j1GUI_H__