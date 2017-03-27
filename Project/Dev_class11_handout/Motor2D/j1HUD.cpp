#include "j1HUD.h"
#include "j1Render.h"

j1HUD::j1HUD()
{

}

j1HUD::~j1HUD()
{

}

// Called before render is available
bool j1HUD::Awake(pugi::xml_node&)
{
	return true;
}

// Called before the first frame
bool j1HUD::Start()
{
	return true;
}

// Called each loop iteration
bool j1HUD::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1HUD::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool j1HUD::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1HUD::CleanUp()
{
	return true;
}

void j1HUD::OnGui(Gui* ui, GuiEvent event)
{

}

void j1HUD::OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments)
{

}

void j1HUD::OnConsoleCVar(const CVar* cvar)
{

}