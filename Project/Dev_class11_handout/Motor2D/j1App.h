#ifndef __j1APP_H__
#define __j1APP_H__

#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"

#include<list>
#include<string>

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1FileSystem;
class j1Scene;
class j1Map;
class j1Pathfinding;
class j1Fonts;
class j1Gui;
class j1Console;
class j1Player;
class j1FadeToBlack;
class j1Camera;
class j1InputManager;
class j1Collision;
class j1Object;
class j1Enemy;
class j1HUD;
class j1GameStartMenuBackground;
class j1DialogueManager;
class ParticleManager;

enum SaveLoadType {
	Module,
	Scene,
	Menu,
	NullSaveLoadType
};

class j1App
{
	friend class j1Camera;
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;

	void LoadGame(const char* file);
	void SaveGame(const char* file) const;
	void LoadGameModules(const char* file);
	void SaveGameModules(const char* file) const;
	void LoadGameScenes(const char* file);
	void SaveGameScenes(const char* file) const;
	void LoadGameMenus(const char* file);
	void SaveGameMenus(const char* file) const;
	void GetSaveGames(std::list<std::string>& list_to_fill) const;

	void WantToQuit();

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;
	bool SaveLoadIterate(pugi::xml_node& root);

public:

	// Modules
	j1Window*			win = nullptr;
	j1Input*			input = nullptr;
	j1Render*			render = nullptr;
	j1Textures*			tex = nullptr;
	j1Audio*			audio = nullptr;
	j1Scene*			scene = nullptr;
	j1FileSystem*		fs = nullptr;
	j1Map*				map = nullptr;
	j1Pathfinding*		pathfinding = nullptr;
	j1Fonts*			font = nullptr;
	j1Gui*				gui = nullptr;
	j1Player*			player = nullptr;
	j1Console*			console = nullptr;
	j1FadeToBlack*		fadetoblack = nullptr;
	j1Camera*			camera = nullptr;
	j1InputManager*		inputM = nullptr;
	j1Collision*		collision = nullptr;
	j1Object*			object = nullptr;
	j1Enemy*			enemy = nullptr;
	j1HUD*				hud = nullptr;
	j1GameStartMenuBackground* startmenuback = nullptr;
	j1DialogueManager*	dialoguemanager = nullptr;
	ParticleManager*	particlemanager = nullptr;

private:
	std::list<j1Module*> modules;
	int					argc = 0;
	char**				args = nullptr;

	std::string		title = empty_char;
	std::string		organization;

	mutable SaveLoadType WantTo_SaveLoadType = SaveLoadType::NullSaveLoadType;
	mutable bool		want_to_save = false;
	bool				want_to_load = false;
	std::string			load_game = empty_char;
	mutable std::string	save_game = empty_char;

	j1PerfTimer			ptimer;
	unsigned int long	frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float				dt = 0.0f;
	int					capped_ms = -1;

	float				avg_fps = 0.0f;
	float				seconds_since_startup = 0.0f;
	uint32				last_frame_ms = 0;
	uint32				frames_on_last_update = 0;

	bool				wanttoquit = false;
};

extern j1App* App;

#endif