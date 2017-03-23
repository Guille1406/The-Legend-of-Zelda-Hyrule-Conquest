#include "j1Gui.h"
#include "GuiViewport.h"
#include "j1App.h"
#include "j1Render.h"

GuiViewport::GuiViewport(SDL_Rect* rect, bool movable, AddGuiTo addto) : Gui(iPoint(rect->x, rect->y), GuiType::gui_viewport, movable, addto),
	viewport_rect(*rect)
{
	Gui_Collider = { rect->x, rect->y, rect->w, rect->h };
	OriginalPosition = position;
}

GuiViewport::~GuiViewport()
{

}

void GuiViewport::Update(const Gui* mouse_hover, const Gui* focus)
{
	if (OriginalPosition != position)
	{
		viewport_rect.x = position.x;
		viewport_rect.y = position.y;
		OriginalPosition = position;
	}
}

void GuiViewport::Draw()
{
	if (this->visible == true)
	{
		//Viewport items
		SDL_RenderSetViewport(App->render->renderer, &viewport_rect);
		for (std::list<Gui*>::iterator item = ViewportElements.begin(); item != ViewportElements.cend(); ++item)
			(*item)->Draw();
		SDL_RenderSetViewport(App->render->renderer, NULL);
		//Border
		App->render->DrawQuad(viewport_rect, White(0), White(1), White(2), 255, false, false);
		//Debug
		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiViewport::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, Blue(0), Blue(1), Blue(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiViewport::push_back_item(Gui* newitem)
{
	ViewportElements.push_back(newitem);
}