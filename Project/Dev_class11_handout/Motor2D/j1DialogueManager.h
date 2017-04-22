#ifndef __DIALOGUE_MANAGER_H__
#define __DIALOGUE_MANAGER_H__

#include <vector>

#include "j1Module.h"
#include "p2Point.h"
#include "j1Gui.h"

enum DialogueID {
	//Cutscene Dialogue
	castle_intro,
	castle_sewers,
	castle_sewers_exit,

	//NPC Dialogue
	

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
	Guard,
	//NPC
	Ric,
	//None
	item_nullinterlucutor
};

enum DialogueInterlucutorPosition {
	Left,
	Right
};

struct DialogueInterlucutorStrRelation {
	DialogueInterlucutorStrRelation(std::string* str, DialogueInterlucutor enu);
	~DialogueInterlucutorStrRelation();
	std::string DialogueInterlucutorStr = empty_char;
	DialogueInterlucutor DialogueInterlucutorEnum = DialogueInterlucutor::item_nullinterlucutor;
};

struct DialogueStep
{
	DialogueStep();
	~DialogueStep();
	DialogueInterlucutor speaker = DialogueInterlucutor::item_nullinterlucutor;
	DialogueInterlucutor listener = DialogueInterlucutor::item_nullinterlucutor;
	DialogueInterlucutorPosition speaker_pos = DialogueInterlucutorPosition::Left;
	DialogueInterlucutorPosition listener_pos = DialogueInterlucutorPosition::Left;
	std::vector<std::string> lines;
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
	DialogueInterlucutor CheckInterlocutor(std::string* interlocutor_str);
	DialogueInterlucutorPosition CheckInterlocutorPosition(std::string* interlocutor_position_str);

private:

	SDL_Rect WindowRect = { 0,0,0,0 };

	std::vector<Dialogue*> dialogues;
	std::vector<DialogueInterlucutorStrRelation*> DialogueInterlucutorStrRelationVec;
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