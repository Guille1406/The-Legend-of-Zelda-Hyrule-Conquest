#ifndef __DIALOGUE_MANAGER_H__
#define __DIALOGUE_MANAGER_H__

#include <vector>

#include "j1Module.h"
#include "p2Point.h"
#include "j1Gui.h"

enum DialogueID {
	//Cutscene Dialogue


	//NPC Dialogue
	Ric_test,

	//Item Dialogue


	NullID
};

enum DialogueType {
	Cutscene,
	NPC,
	item,
	NullType
};

enum DialogueInterlucutor {
	//Cutscene/NPC
	Link,
	Zelda,
	Messenger,
	King,
	//NPC
	Ric,
	//None
	item
};

enum DialogueInterlucutorPosition {
	Left,
	Right
};

struct DialogueStep
{
	DialogueStep();
	~DialogueStep();
	DialogueInterlucutor speaker = DialogueInterlucutor::item;
	DialogueInterlucutor listener = DialogueInterlucutor::item;
	DialogueInterlucutorPosition speaker_pos = DialogueInterlucutorPosition::Left;
	DialogueInterlucutorPosition listener_pos = DialogueInterlucutorPosition::Left;
	std::vector<std::string*> lines;
};

struct Dialogue
{
	Dialogue();
	~Dialogue();
	DialogueID id = DialogueID::NullID;
	std::vector<DialogueStep*> DialogueSteps;
};

struct ActiveDialogue
{
	ActiveDialogue();
	~ActiveDialogue();
	DialogueID id = DialogueID::NullID;
	DialogueType type = DialogueType::NullType;
	Dialogue* ActiveDialoguePtr = nullptr;
	DialogueStep* ActiveDialogueStepPtr = nullptr;
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
	void AllocateDialogues(pugi::xml_node& dialoguenode);
	bool BlitDialog(uint id, uint state);

private:

	SDL_Rect WindowRect = { 0,0,0,0 };

	std::vector<Dialogue*> dialogues;
	ActiveDialogue* ActiveDialog = nullptr;

	std::string folder = empty_char;
	std::string path = empty_char;
	pugi::xml_document dialogueDataFile;
	pugi::xml_node dialogueNode;

	GuiImage* TextBackground = nullptr;
	GuiButton* LeftCharacterLabel = nullptr;
	GuiButton* RightCharacterLabel = nullptr;
};

#endif