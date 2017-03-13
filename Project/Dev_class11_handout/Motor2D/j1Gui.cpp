#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Console.h"
#include "j1Gui.h"
#include "GuiImage.h"
#include "GuiLabel.h"
#include "GuiButton.h"
#include "GuiCheck.h"
#include "GuiBar.h"
#include "GuiScrollBar.h"
#include "GuiInputText.h"
#include "GuiWindow.h"
#include "GuiViewport.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.c_str());
	
	return true;
}

// Called before all Updates
bool j1Gui::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		Gui_DebugDraw = !Gui_DebugDraw;

	// Update all guis
	std::list<Gui*>* list_to_iterate = nullptr;
	if (App->console->IsActive())
		list_to_iterate = &ConsoleElements;
	else
		list_to_iterate = &GuiElements;

	const Gui* mouse_hover = FindMouseHover();
	for (std::list<Gui*>::iterator item = list_to_iterate->begin(); item != list_to_iterate->cend(); ++item)
	{
		(*item)->CheckInput(mouse_hover, nullptr);
		(*item)->Update(mouse_hover, nullptr);
	}
	return true;
}

// Called each loop iteration
bool j1Gui::Update(float dt)
{
	// Draw all guis
	for (std::list<Gui*>::iterator item = GuiElements.begin(); item != GuiElements.cend(); ++item)
		if((*item)->GetPurpose() != AddGuiTo::viewport_purpose)
			(*item)->Draw();
	if (App->console->IsActive())
	{
		App->render->DrawQuad(App->console->ConsoleBackground, Black(0), Black(1), Black(2), CONSOLE_ALPHA, true, true, false);
		App->render->DrawQuad(App->console->ConsoleInputTextBackground, Gray(0), Gray(1), Gray(2), CONSOLE_ALPHA, true, true, false);
		for (std::list<Gui*>::iterator item = ConsoleElements.begin(); item != ConsoleElements.cend(); ++item)
		{
			if (((*item)->type == GuiType::gui_label) && (InFOV(*item)))
			{
				SDL_Rect ViewportRect = { 0,0,App->console->ConsoleBackground.w,App->console->ConsoleBackground.h };
				SDL_RenderSetViewport(App->render->renderer, &ViewportRect);
				(*item)->Draw();
				SDL_RenderSetViewport(App->render->renderer, NULL);
			}
			if ((*item)->type == GuiType::gui_inputtext)
				(*item)->Draw();
		}
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (std::list<Gui*>::iterator item = GuiElements.begin(); item != GuiElements.cend(); ++item)
		RELEASE(*item);
	GuiElements.clear();

	for (std::list<Gui*>::iterator item = ConsoleElements.begin(); item != ConsoleElements.cend(); ++item)
		RELEASE(*item);
	ConsoleElements.clear();

	return true;
}

// const getter for atlas
/*
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}
*/

SDL_Texture* j1Gui::GetAtlas()
{
	return atlas;
}

const Gui* j1Gui::FindMouseHover()
{
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	std::list<Gui*>* list_to_iterate = nullptr;
	if (App->console->IsActive())
		list_to_iterate = &ConsoleElements;
	else
		list_to_iterate = &GuiElements;

	for (std::list<Gui*>::const_reverse_iterator item = list_to_iterate->rbegin(); item != list_to_iterate->crend(); ++item)
	{
		if ((list_to_iterate == &ConsoleElements) && ((*item)->type == GuiType::gui_label))
			continue;
		else
			if (CanInteract(*item) == true)
				if ((*item)->PointContained(mouse.x, mouse.y))
					return *item;
	}

	return nullptr;
}

bool j1Gui::CanInteract(Gui* ui) const
{
	//return ui->movable && ui->visible;
	return ui->visible;
}

void j1Gui::push_back_gui(Gui* gui, AddGuiTo addto)
{
	switch (addto)
	{
	case AddGuiTo::regular_purpose:
		GuiElements.push_back(gui);
		break;
	case AddGuiTo::console_purpose:
		ConsoleElements.push_back(gui);
		break;
	case AddGuiTo::none:
	case AddGuiTo::viewport_purpose:
		break;
	}
}

bool j1Gui::InFOV(Gui* gui)
{
	return gui->InFOV();
}

// Gui Creators ---------------------------------------------------

GuiImage* j1Gui::CreateImage(iPoint position, SDL_Rect* rect, bool movable, AddGuiTo addto)
{
	GuiImage* ret = nullptr;
	ret = new GuiImage(position, rect, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiLabel* j1Gui::CreateLabel(iPoint position, std::string* str, bool movable, AddGuiTo addto)
{
	GuiLabel* ret = nullptr;
	ret = new GuiLabel(position, str, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiButton* j1Gui::CreateButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* rect1, bool movable, AddGuiTo addto)
{
	GuiButton* ret = nullptr;
	if(type == ButtonType::idle_only)
		ret = new GuiButton(position, str, type, rect1, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiButton* j1Gui::CreateButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* rect1, SDL_Rect* rect2, bool movable, AddGuiTo addto)
{
	GuiButton* ret = nullptr;
	if ((type == ButtonType::idle_hover) || (type == ButtonType::idle_pressed))
		ret = new GuiButton(position, str, type, rect1, rect2, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiButton* j1Gui::CreateButton(iPoint position, std::string* str, ButtonType type, SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3, bool movable, AddGuiTo addto)
{
	GuiButton* ret = nullptr;
	if (type == ButtonType::idle_hover_pressed)
		ret = new GuiButton(position, str, type, rect1, rect2, rect3, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiCheck* j1Gui::CreateCheck(iPoint position, SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3, bool movable, AddGuiTo addto)
{
	GuiCheck* ret = nullptr;
	ret = new GuiCheck(position, rect1, rect2, rect3, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiCheck* j1Gui::CreateCheck(iPoint position, SDL_Rect* rect1, SDL_Rect* rect2, bool movable, AddGuiTo addto)
{
	GuiCheck* ret = nullptr;
	ret = new GuiCheck(position, rect1, rect2, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiBar* j1Gui::CreateBar(iPoint position, BarType type, SDL_Rect* rect1, int min_value, int max_value, Color* bar_color, int bar_color_alpha, bool movable, AddGuiTo addto)
{
	GuiBar* ret = nullptr;
	ret = new GuiBar(position, type, rect1, max_value, min_value, bar_color, bar_color_alpha, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiBar* j1Gui::CreateBar(iPoint position, BarType type, SDL_Rect* rect1, SDL_Rect* rect2, int min_value, int max_value, Color* bar_color, int bar_color_alpha, bool movable, AddGuiTo addto)
{
	GuiBar* ret = nullptr;
	ret = new GuiBar(position, type, rect1, rect2, max_value, min_value, bar_color, bar_color_alpha, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiScrollBar* j1Gui::CreateScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, bool vertical, bool movable, AddGuiTo addto)
{
	GuiScrollBar* ret = nullptr;
	ret = new GuiScrollBar(position, scrollbarbackground, scrollbarbar, bottonstr, type, idletexture, vertical, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiScrollBar* j1Gui::CreateScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hoverorpressedtexture, bool vertical, bool movable, AddGuiTo addto)
{
	GuiScrollBar* ret = nullptr;
	ret = new GuiScrollBar(position, scrollbarbackground, scrollbarbar, bottonstr, type, idletexture, hoverorpressedtexture, vertical, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiScrollBar* j1Gui::CreateScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hovertexture, SDL_Rect* pressedtexture, bool vertical, bool movable, AddGuiTo addto)
{
	GuiScrollBar* ret = nullptr;
	ret = new GuiScrollBar(position, scrollbarbackground, scrollbarbar, bottonstr, type, idletexture, hovertexture, pressedtexture, vertical, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiInputText* j1Gui::CreateInputText(iPoint position, SDL_Rect* rect, std::string* string, bool has_backgound, bool is_password, bool movable, AddGuiTo addto)
{
	GuiInputText* ret = nullptr;
	ret = new GuiInputText(position, rect, string, has_backgound, is_password, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiWindow* j1Gui::CreateGuiWindow(iPoint position, SDL_Rect* rect, bool has_background, bool movable, AddGuiTo addto)
{
	GuiWindow* ret = nullptr;
	ret = new GuiWindow(position, rect, has_background, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiViewport* j1Gui::CreateViewport(SDL_Rect* rect, bool movable, AddGuiTo addto)
{
	GuiViewport* ret = nullptr;
	ret = new GuiViewport(rect, movable, addto);
	push_back_gui(ret, addto);
	return ret;
}