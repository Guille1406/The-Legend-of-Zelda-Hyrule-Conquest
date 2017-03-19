#ifndef __j1CONSOLE_H__
#define __j1CONSOLE_H__

#include <vector>

#include "j1App.h"
#include "j1Module.h"
#include "j1Gui.h"
#include "ConsoleCommandCVar.h"

#define CONSOLE_ALPHA 175
#define SCROLL_SPEED 50
#define CONSOLE_FONT_SIZE 12

class GuiLabel;
class GuiInputText;

class j1Console : public j1Module
{
	friend class j1Gui;
public:

	j1Console();

	// Destructor
	virtual ~j1Console();

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

	void Print_Console_Label(std::string* newlabelstr, uint tab = 0);
	bool IsActive() const;
	bool IsConsoleModuleActive() const;

	//Create Commands
	const Command* CreateCommand(std::string* name, j1Module* listener, uint min_args = 0, uint max_args = 0);

	//Create CVars
	const CVar* CreateCVar(std::string* name, std::string* string, j1Module* listener, bool read_only = false);
	const CVar* CreateCVar(std::string* name, float value, j1Module* listener, bool read_only = false);
	const CVar* CreateCVar(std::string* name, int value, j1Module* listener, bool read_only = false);
	const CVar* CreateCVar(std::string* name, bool value, j1Module* listener, bool read_only = false);

	void OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments);

private:
	const Command* FindCommand(std::string* name);
	const CVar* FindCVar(std::string* name);
	bool StrExist(std::string* name);
	void ParseInput(std::string* strtoparse);

private:
	bool ConsoleActive = false;
	bool ConsoleModuleActive = false;
	SDL_Rect ConsoleBackground = { 0,0,0,0 };
	SDL_Rect ConsoleInputTextBackground = { 0,0,0,0 };

	GuiInputText* ConsoleInputText = nullptr;
	std::list<Gui*> LOGLabels;
	uint LabelNum = 0;

	std::list<Command> Commands;
	std::list<CVar> CVars;
	std::vector<std::string> ArgumentsVect;

	iPoint CameraPos = { 0,0 };

	const Command* quit = nullptr;
	const Command* help = nullptr;
};

#endif // __j1CONSOLE_H__