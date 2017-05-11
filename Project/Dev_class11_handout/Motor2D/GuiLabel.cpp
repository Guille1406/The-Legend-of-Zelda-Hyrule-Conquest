#include "j1Gui.h"
#include "GuiLabel.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"

GuiLabel::GuiLabel(iPoint position, std::string* str, bool movable, AddGuiTo addto) : Gui(position, GuiType::gui_label, movable, addto),
LabelString(*str), font(App->font->default)
{
	str_modified = true;
	CalculateGui_Collider();
}

GuiLabel::~GuiLabel()
{

}

void GuiLabel::Draw()
{
	if (str_modified)
	{
		App->tex->UnLoad(texture_to_blit);
		if (LabelString != empty_char)
			texture_to_blit = App->font->Print(LabelString.c_str(), { (Uint8)(*color)(0), (Uint8)(*color)(1), (Uint8)(*color)(2), (Uint8)opacity }, font);
		str_modified = false;
	}
	if (this->visible)
	{
		if (LabelString != empty_char)
			App->render->Blit(texture_to_blit, position.x - App->render->camera.x, position.y - App->render->camera.y, nullptr, 1.0f, 0, INT_MAX, INT_MAX, false, opacity);

		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiLabel::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, LightSeaGreen(0), LightSeaGreen(1), LightSeaGreen(2), DEBUG_DRAW_ALPHA, true, false, false);
}

const std::string* GuiLabel::GetLabelStr() const
{
	return &LabelString;
}

void GuiLabel::EditLabelStr(std::string* newstr)
{
	LabelString = *newstr;
	CalculateGui_Collider();
	str_modified = true;
}

void GuiLabel::SetFont(_TTF_Font* newfont)
{
	font = newfont;
	CalculateGui_Collider();
	str_modified = true;
}

_TTF_Font* GuiLabel::GetFont()
{
	return font;
}

void GuiLabel::SetLabelColor(Color* newcolor)
{
	color = newcolor;
	str_modified = true;
}

void GuiLabel::Clear()
{
	LabelString.clear();
	CalculateGui_Collider();
	str_modified = true;
}

void GuiLabel::CalculateGui_Collider()
{
	int w, h = 0;
	App->font->CalcSize(LabelString.c_str(), w, h, font);
	Gui_Collider = { position.x, position.y, w, h };
}

void GuiLabel::SetOpacity(uint newopacity)
{
	if (newopacity < 0)
		opacity = 0;
	else if (newopacity > 255)
		opacity = 255;
	else
		opacity = newopacity;
	str_modified = true;
}