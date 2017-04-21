#ifndef __DIALOGUE_MANAGER_H__
#define __DIALOGUE_MANAGER_H__

#include <vector>

#include "j1Module.h"
#include "p2Point.h"
#include "j1Gui.h"

enum DialogueID {
	//Cutscene Dialogue


	//NPC Dialogue


	//Item Dialogue


	NullID
};

class DialogueStep
{
public:

	DialogueStep(int state, std::string text);
	~DialogueStep();

	uint state = 0;
	std::vector<std::string*> lines;
};

class Dialogue
{
public:

	Dialogue(int id);
	~Dialogue();

	uint id = 0;
	std::vector<DialogueStep*> DialogueSteps;
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
	void ActivateDialogue(DialogueID id);

private:
	bool BlitDialog(uint id, uint state);

private:

	int dialogueStep = 0; //Allows to order the conversarion correctly

	std::vector<Dialogue*> dialogue;

	std::string folder = empty_char;
	std::string path = empty_char;
	pugi::xml_document dialogueDataFile;
	pugi::xml_node dialogueNode;

	std::vector<GuiLabel*> Labels;

	uint id = 0;
	uint NPCstate = 0;

	DialogueID ActiveDialogue = DialogueID::NullID;
};

#endif