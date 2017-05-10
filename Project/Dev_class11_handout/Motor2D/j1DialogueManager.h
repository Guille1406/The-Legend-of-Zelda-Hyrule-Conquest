#ifndef __DIALOGUE_MANAGER_H__
#define __DIALOGUE_MANAGER_H__

#include <vector>

#include "j1Module.h"
#include "p2Point.h"
#include "j1Gui.h"

enum DialogueID {
	//Cutscene Dialogue
	castle_room_dialogue,
	castle_1_dialogue,
	castle_2_dialogue,
	castle_3_dialogue,
	castle_sewers_1_dialogue,
	castle_sewers_2_dialogue,
	village_dialogue,
	house_1_dialogue,
	house_2_dialogue,
	house_3_dialogue,
	forest_1_dialogue,
	forest_2_dialogue,
	truth_1_dialogue,
	truth_2_dialogue,
	truth_3_dialogue,
	truth_4_dialogue,
	truth_5_dialogue,
	castle_doors_dialogue,
	castle_yard_1_dialogue,
	castle_yard_2_dialogue,
	castle_yard_3_dialogue,
	castle_yard_4_dialogue,
	castle_yard_5_dialogue,

	//NPC Dialogue
	ric_with_link_dialogue,
	ric_with_zelda_dialogue,
	npc_1_with_link_dialogue,
	npc_1_with_zelda_dialogue,
	npc_2_with_link_dialogue,
	npc_2_with_zelda_dialogue,

	NullID_dialogue
};

enum DialogueType {
	Cutscene_dialoguetype,
	NPC_dialoguetype,
	item_dialoguetype,
	NullType
};

enum DialogueInterlucutor {
	//Cutscene/NPC
	Link,
	Zelda,
	Messenger,
	King,
	Guard,
	Ogity,
	//NPC
	Ric,
	//None
	item_nullinterlucutor
};

enum DialogueInterlucutorPosition {
	Left,
	Right
};

struct DialogueInterlucutorStrAndAtalsRelation {
	DialogueInterlucutorStrAndAtalsRelation(std::string* str, DialogueInterlucutor enu, SDL_Texture* atlas);
	~DialogueInterlucutorStrAndAtalsRelation();
	std::string DialogueInterlucutorStr = empty_char;
	DialogueInterlucutor DialogueInterlucutorEnum = DialogueInterlucutor::item_nullinterlucutor;
	SDL_Texture* DialogueInterlucutorAtlas = nullptr;
};

struct DialogueCharacter
{
	DialogueCharacter();
	~DialogueCharacter();
	std::string DialogueCharacter_str = empty_char;
	DialogueInterlucutor DialogueCharacter_id = DialogueInterlucutor::item_nullinterlucutor;
	DialogueInterlucutorPosition DialogueCharacter_pos = DialogueInterlucutorPosition::Left;
	SDL_Texture* Character_Atlas = nullptr;
	SDL_Rect Character_Expression_Rect = { 0,0,0,0 };
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
	DialogueID id = DialogueID::NullID_dialogue;
	DialogueType type = DialogueType::NullType;
	std::vector<DialogueStep*> DialogueSteps;
};

struct ActiveDialogue
{
	ActiveDialogue();
	~ActiveDialogue();
	bool DialogueActive = false;
	bool DialoguePaused = false;
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
	void PauseActiveDialogue();
	void ResumeActiveDialogue();
	uint GetActiveDialogueStep();

	const ActiveDialogue* GetActiveDialogue()const 
	{
		return ActiveDialog;
	}

private:
	void AllocateDialogues(pugi::xml_node& dialoguenode, iPoint* TextBackgroundPos);
	void CreateDialogue(pugi::xml_node& dialoguenode, iPoint* TextBackgroundPos, DialogueType type);
	DialogueInterlucutor CheckInterlocutor(std::string* interlocutor_str);
	DialogueInterlucutorPosition CheckInterlocutorPosition(std::string* interlocutor_position_str);
	SDL_Texture* CheckInterlocutorAtlas(DialogueInterlucutor interlocutor_enu);
	void DialogueNextStep();
	void SetCharacterBlit();

private:

	SDL_Rect WindowRect = { 0,0,0,0 };

	std::vector<Dialogue*> dialogues;
	std::vector<DialogueInterlucutorStrAndAtalsRelation*> DialogueInterlucutorStrandAtlasRelationVec;
	ActiveDialogue* ActiveDialog = nullptr;

	std::string folder = empty_char;
	std::string path = empty_char;
	pugi::xml_document dialogueDataFile;
	pugi::xml_node dialogueNode;

	GuiImage* TextBackground = nullptr;
	GuiButton* LeftCharacterLabel = nullptr;
	GuiButton* RightCharacterLabel = nullptr;

	SDL_Texture* king_tex = nullptr;
	SDL_Texture* link_tex = nullptr;
	SDL_Texture* zelda_tex = nullptr;
	SDL_Texture* messenger_tex = nullptr;
	SDL_Texture* ric_tex = nullptr;
	SDL_Texture* ogity_tex = nullptr;

	std::string king_tex_str = empty_char;
	std::string link_tex_str = empty_char;
	std::string zelda_tex_str = empty_char;
	std::string messenger_tex_str = empty_char;
	std::string ric_tex_str = empty_char;
	std::string ogity_tex_str = empty_char;

};

#endif