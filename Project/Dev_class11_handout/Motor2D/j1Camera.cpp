#include "j1App.h"
#include "j1Camera.h"

j1Camera::j1Camera()
{
	name.create("console");
}

j1Camera::~j1Camera()
{

}

// Called before render is available
bool j1Camera::Awake(pugi::xml_node&)
{
	return true;
}

// Called before the first frame
bool j1Camera::Start()
{
	return true;
}

// Called each loop iteration
bool j1Camera::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Camera::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool j1Camera::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Camera::CleanUp()
{
	return true;
}

void j1Camera::OnGui(Gui* ui, GuiEvent event)
{

}

void j1Camera::OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments)
{

}

void j1Camera::OnConsoleCVar(const CVar* cvar)
{

}