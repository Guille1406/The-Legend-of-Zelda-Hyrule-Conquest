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

struct DialogueCharacter
{
	DialogueCharacter();
	~DialogueCharacter();
	std::string DialogueCharacter_str = empty_char;
	DialogueInterlucutor DialogueCharacter_id = DialogueInterlucutor::item_nullinterlucutor;
	DialogueInterlucutorPosition DialogueCharacter_pos = DialogueInterlucutorPosition::Left;
};

struct DialogueStep
{
	DialogueStep();
	~DialogueStep();
	DialogueCharacter* SpeakerDialogueCharacter = nullptr;
	DialogueCharacter* ListenerDialogueCharacter = nullptr;
	std::vector<GuiLabel*> lines;
};

struct Dialogue
{
	Dialogue();
	~Dialogue();
	DialogueID id = DialogueID::NullID;
	DialogueType type = DialogueType::NullType;
	std::vector<DialogueStep*> DialogueSteps;
};

struct ActiveDialogue
{
	ActiveDialogue();
	~ActiveDialogue();
	bool DialogueActive = false;
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
	void AllocateDialogues(pugi::xml_node& dialoguenode, iPoint* TextBackgroundPos);
	void CreateDialogue(pugi::xml_node& dialoguenode, iPoint* TextBackgroundPos, DialogueType type);
	bool BlitDialog(uint id, uint state);
	DialogueInterlucutor CheckInterlocutor(std::string* interlocutor_str);
	DialogueInterlucutorPosition CheckInterlocutorPosition(std::string* interlocutor_position_str);
	void DialogueNextStep();
	void SetCharacterBlit();

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