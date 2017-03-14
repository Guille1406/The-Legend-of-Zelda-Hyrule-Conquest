#ifndef __j1CAMERA_H__
#define __j1CAMERA_H__

#include "j1Module.h"

enum GuiEvent;
class Gui;
struct Command;
struct CVar;

class j1Camera : public j1Module
{
public:
	j1Camera();

	~j1Camera();

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

#endif // __j1CAMERA_H__