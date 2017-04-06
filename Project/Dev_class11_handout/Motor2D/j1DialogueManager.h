#ifndef __DIALOGUE_MANAGER_H__
#define __DIALOGUE_MANAGER_H__


#include <vector>

#include "j1Module.h"
#include "p2Point.h"
#include "j1Gui.h"

class TextLine
{
public:

	TextLine(int state, std::string text);
	~TextLine();

	int state;
	std::string* line = nullptr;
};

class Dialogue
{
public:

	Dialogue(int id);
	~Dialogue();

	uint id;
	std::vector<TextLine*> texts;
};

class j1DialogueManager : public j1Module
{
public:

	j1DialogueManager();
	~j1DialogueManager();
	
	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void OnGui(Gui* ui, GuiEvent event);
	void OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments);
	void OnConsoleCVar(const CVar* cvar);
	bool BlitDialog(uint id, uint state);

private:

	int dialogueStep = 0; //Allows to order the conversarion correctly

	std::vector<Dialogue*> dialog;

	/*-- Data to load XML --*/
	std::string folder;
	std::string path;
	pugi::xml_document dialogueDataFile;
	pugi::xml_node dialogueNode;
	/*-- END --*/

	/*--- UI elements to print dialogues on screen ---*/

	/*-- END --*/

	/*---CODE TO TEST IN-GAME RESULTS ---*/
	uint id = 1;
	uint NPCstate = 0;
	/*--- END ---*/
};

#endif