#include "j1Gui.h"
#include "GuiImage.h"
#include "j1App.h"
#include "j1Render.h"

GuiImage::GuiImage(iPoint position, SDL_Rect* rect, bool movable, AddGuiTo addto) : Gui(position, GuiType::gui_image, movable, addto), 
texture_rect(*rect)
{
	Gui_Collider = { position.x, position.y, rect->w, rect->h };
}

GuiImage::~GuiImage()
{

}

void GuiImage::Draw()
{
	if (this->visible == true)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &texture_rect);
		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiImage::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, Lime(0), Lime(1), Lime(2), DEBUG_DRAW_ALPHA, true, false);
}