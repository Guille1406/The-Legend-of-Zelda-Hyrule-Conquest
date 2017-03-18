// ----------------------------------------------------
// j1Module.h
// Interface for all engine modules
// ----------------------------------------------------

#ifndef __j1MODULE_H__
#define __j1MODULE_H__

#include <vector>

#include "p2SString.h"
#include "PugiXml\src\pugixml.hpp"

class j1App;
enum GuiEvent;
class Gui;
struct Command;
struct CVar;
class Collider;
class j1Module
{
public:

	j1Module() : active(false)
	{}

	virtual ~j1Module()
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}

	virtual void OnGui(Gui* ui, GuiEvent event)
	{

	}

	virtual void OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments)
	{

	}

	virtual void OnConsoleCVar(const CVar* cvar)
	{

	}

	virtual void OnCollision(Collider* collider1, Collider* collider2) {
		int x = 0;

	}

	void Enable()
	{
		if (active == false)
		{
			active = true;
			Start();
		}
	}

	void Disable()
	{
		if (active == true)
		{
			active = false;
			CleanUp();
		}
	}

	virtual bool IsEnabled() {
		return active;
	}

public:

	p2SString	name;
	bool		active;

};

#endif // __j1MODULE_H__