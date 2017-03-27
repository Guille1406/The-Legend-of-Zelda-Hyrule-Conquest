#ifndef __j1HUD_H__
#define __j1HUD_H__

#include "j1Module.h"
#include "SDL\include\SDL.h"

class j1HUD : public j1Module
{
public:
	j1HUD();

	~j1HUD();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void OnGui(Gui* ui, GuiEvent event);

	void OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments);

	void OnConsoleCVar(const CVar* cvar);

};

#endif // __j1HUD_H__