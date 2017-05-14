#include "j1DialogueManager.h"
#include "j1App.h"
#include "j1FileSystem.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Input.h"
#include "j1HUD.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1GameStartMenuBack.h"

#include "GuiImage.h"
#include "GuiLabel.h"
#include "GuiButton.h"

j1DialogueManager::j1DialogueManager() : j1Module()
{
	name = ("dialogue");
}

j1DialogueManager::~j1DialogueManager()
{
	
}

bool j1DialogueManager::Awake(pugi::xml_node& config)
{
	bool ret = true;
	LOG("Loading DialogManager");

	///Get characters atlas
	king_tex_str = config.child("king_atlas").attribute("file").as_string();
	link_tex_str = config.child("link_atlas").attribute("file").as_string();
	zelda_tex_str = config.child("zelda_atlas").attribute("file").as_string();
	messenger_tex_str = config.child("messenger_atlas").attribute("file").as_string();
	ric_tex_str = config.child("ric_atlas").attribute("file").as_string();
	ogity_tex_str = config.child("ogity_atlas").attribute("file").as_string();
	
	return ret;
}

bool j1DialogueManager::Start()
{
	bool ret = false;

	LOG("Loading DialogManager Dialogues");

	WindowRect.w = App->win->GetWindowW();
	WindowRect.h = App->win->GetWindowH();

	pugi::xml_document	config_file;
	pugi::xml_node		dialogue_config;

	char* buf = nullptr;
	int size = App->fs->Load("dialogues/Dialogues.xml", &buf);
	pugi::xml_parse_result result = config_file.load_buffer(buf, size);
	RELEASE(buf);

	if (result == NULL)
		LOG("Could not load map xml file Dialogues.xml. pugi error: %s", result.description());
	else
		dialogue_config = config_file.child("DialogueManager");

	//Set config
	if (dialogue_config.empty() == false)
		ret = true;

	if (ret == true)
	{
		//Set drawing areas and dialogue hud gui
		SDL_Rect TextBackgroundRect = { 0,94,1233,231 };
		TextBackground = App->gui->CreateImage({ 23,WindowRect.h - TextBackgroundRect.h - 11 }, &TextBackgroundRect, false, AddGuiTo::none);

		SDL_Rect LeftCharacterLabelRect = { 0,0,336,94 };
		LeftCharacterLabel = App->gui->CreateButton(iPoint(5, WindowRect.h - TextBackgroundRect.h - 11 - (int)(LeftCharacterLabelRect.h * 0.5f)), &std::string("Left Guy"), ButtonType::idle_only, &LeftCharacterLabelRect, false, AddGuiTo::none);
		LeftCharacterLabel->SetFont(App->font->ReturnofGanon36);

		SDL_Rect RightCharacterLabelRect = { 336,0,336,94 };
		RightCharacterLabel = App->gui->CreateButton(iPoint(WindowRect.w - RightCharacterLabelRect.w - 5, WindowRect.h - TextBackgroundRect.h - 11 - (int)(LeftCharacterLabelRect.h * 0.5f)), &std::string("Right Guy"), ButtonType::idle_only, &RightCharacterLabelRect, false, AddGuiTo::none);
		RightCharacterLabel->SetFont(App->font->ReturnofGanon36);

		king_tex = App->tex->Load(king_tex_str.c_str());
		link_tex = App->tex->Load(link_tex_str.c_str());
		zelda_tex = App->tex->Load(zelda_tex_str.c_str());
		messenger_tex = App->tex->Load(messenger_tex_str.c_str());
		ric_tex = App->tex->Load(ric_tex_str.c_str());
		ogity_tex = App->tex->Load(ogity_tex_str.c_str());;

		DialogueInterlucutorStrandAtlasRelationVec.push_back(new DialogueInterlucutorStrAndAtalsRelation(&std::string(""), DialogueInterlucutor::item_nullinterlucutor, nullptr));
		DialogueInterlucutorStrandAtlasRelationVec.push_back(new DialogueInterlucutorStrAndAtalsRelation(&std::string("king"), DialogueInterlucutor::King, king_tex));
		DialogueInterlucutorStrandAtlasRelationVec.push_back(new DialogueInterlucutorStrAndAtalsRelation(&std::string("link"), DialogueInterlucutor::Link, link_tex));
		DialogueInterlucutorStrandAtlasRelationVec.push_back(new DialogueInterlucutorStrAndAtalsRelation(&std::string("zelda"), DialogueInterlucutor::Zelda, zelda_tex));
		DialogueInterlucutorStrandAtlasRelationVec.push_back(new DialogueInterlucutorStrAndAtalsRelation(&std::string("messenger"), DialogueInterlucutor::Messenger, messenger_tex));
		DialogueInterlucutorStrandAtlasRelationVec.push_back(new DialogueInterlucutorStrAndAtalsRelation(&std::string("ric"), DialogueInterlucutor::Ric, ric_tex));
		DialogueInterlucutorStrandAtlasRelationVec.push_back(new DialogueInterlucutorStrAndAtalsRelation(&std::string("guard"), DialogueInterlucutor::Guard, nullptr));
		DialogueInterlucutorStrandAtlasRelationVec.push_back(new DialogueInterlucutorStrAndAtalsRelation(&std::string("ogity"), DialogueInterlucutor::Ogity, ogity_tex));

		//Allocate dialogues from XML
		AllocateDialogues(dialogue_config, &TextBackground->GetLocalPos());
	}
	ActiveDialog = new ActiveDialogue();
	return true;
}

void j1DialogueManager::AllocateDialogues(pugi::xml_node& dialoguenode, iPoint* TextBackgroundPos)
{
	//Allocate dialogues from XML
	uint sprite_id = 0;
	for (pugi::xml_node newcharacterrect = dialoguenode.child("Rects").child("rect"); newcharacterrect; newcharacterrect = newcharacterrect.next_sibling("rect"), sprite_id++)
	{
		CharaterSprite* newCharaterSprite = new CharaterSprite();
		newCharaterSprite->sprite_id = (CharaterSpriteRect_ID)sprite_id;
		newCharaterSprite->CharaterSpriteRect = { newcharacterrect.attribute("x").as_int(0) ,newcharacterrect.attribute("y").as_int(0) ,newcharacterrect.attribute("w").as_int(0) ,newcharacterrect.attribute("h").as_int(0) };
		CharaterSpritesVec.push_back(newCharaterSprite);
	}
	//itereate cutscenes
	for (pugi::xml_node newcutscene = dialoguenode.child("Cutscenes").child("cutscene"); newcutscene; newcutscene = newcutscene.next_sibling("cutscene"))
		CreateDialogue(newcutscene, TextBackgroundPos, DialogueType::Cutscene_dialoguetype);
	//itereate NPCs
	for (pugi::xml_node newnpc = dialoguenode.child("NPCs").child("npc"); newnpc; newnpc = newnpc.next_sibling("npc"))
		CreateDialogue(newnpc, TextBackgroundPos, DialogueType::NPC_dialoguetype);
	//itereate items
	for (pugi::xml_node newirtem = dialoguenode.child("Items").child("item"); newirtem; newirtem = newirtem.next_sibling("item"))
		CreateDialogue(newirtem, TextBackgroundPos, DialogueType::item_dialoguetype);
}

void j1DialogueManager::CreateDialogue(pugi::xml_node& dialoguenode, iPoint* TextBackgroundPos, DialogueType type)
{
	dialogues.push_back(new Dialogue());
	Dialogue* newdialogue = dialogues.back();
	newdialogue->id = (DialogueID)dialoguenode.attribute("enum_value").as_int();
	newdialogue->type = type;
	for (pugi::xml_node newstep = dialoguenode.child("step"); newstep; newstep = newstep.next_sibling("step"))
	{
		newdialogue->DialogueSteps.push_back(new DialogueStep());
		DialogueStep* newdialoguestep = newdialogue->DialogueSteps.back();
		newdialoguestep->SpeakerDialogueCharacter = new DialogueCharacter();
		newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newstep.attribute("speaker").as_string()));
		if(newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_id == DialogueInterlucutor::item_nullinterlucutor)
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_str = std::string("");
		else
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_str = std::string(newstep.attribute("speaker").as_string());
		newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newstep.attribute("speaker_pos").as_string()));
		newdialoguestep->SpeakerDialogueCharacter->Character_Atlas = CheckInterlocutorAtlas(newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_id);
		newdialoguestep->SpeakerDialogueCharacter->Character_Expression_Rect = CheckExpressionRect((CharaterSpriteRect_ID)newstep.attribute("speaker_expression").as_int(0));
		newdialoguestep->ListenerDialogueCharacter = new DialogueCharacter();
		newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newstep.attribute("listener").as_string()));
		if (newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_id == DialogueInterlucutor::item_nullinterlucutor)
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_str = std::string("");
		else
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_str = std::string(newstep.attribute("listener").as_string());
		newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newstep.attribute("listener_pos").as_string()));
		newdialoguestep->ListenerDialogueCharacter->Character_Atlas = CheckInterlocutorAtlas(newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_id);
		newdialoguestep->ListenerDialogueCharacter->Character_Expression_Rect = CheckExpressionRect((CharaterSpriteRect_ID)newstep.attribute("listener_expression").as_int(0));
		int y = 0;
		for (pugi::xml_node newsteplines = newstep.child("line"); newsteplines; newsteplines = newsteplines.next_sibling("line"), y += 30)
		{
			newdialoguestep->lines.push_back(App->gui->CreateLabel({ TextBackgroundPos->x + 60,TextBackgroundPos->y + 60 + y }, &std::string(newsteplines.child_value()), false, AddGuiTo::none));
			newdialoguestep->lines.back()->SetFont(App->font->ReturnofGanon36);
		}
	}
}

DialogueInterlucutor j1DialogueManager::CheckInterlocutor(std::string* interlocutor_str)
{
	for (std::vector<DialogueInterlucutorStrAndAtalsRelation*>::iterator item = DialogueInterlucutorStrandAtlasRelationVec.begin(); item != DialogueInterlucutorStrandAtlasRelationVec.cend(); ++item)
		if ((*item)->DialogueInterlucutorStr == *interlocutor_str)
			return (*item)->DialogueInterlucutorEnum;
	return DialogueInterlucutor::item_nullinterlucutor;
}

DialogueInterlucutorPosition j1DialogueManager::CheckInterlocutorPosition(std::string* interlocutor_position_str)
{
	if(*interlocutor_position_str == right_str)
		return DialogueInterlucutorPosition::Right;
	return DialogueInterlucutorPosition::Left;
}

SDL_Texture* j1DialogueManager::CheckInterlocutorAtlas(DialogueInterlucutor interlocutor_enu)
{
	for (std::vector<DialogueInterlucutorStrAndAtalsRelation*>::iterator item = DialogueInterlucutorStrandAtlasRelationVec.begin(); item != DialogueInterlucutorStrandAtlasRelationVec.cend(); ++item)
		if ((*item)->DialogueInterlucutorEnum == interlocutor_enu)
			return (*item)->DialogueInterlucutorAtlas;
	return nullptr;
}

SDL_Rect j1DialogueManager::CheckExpressionRect(CharaterSpriteRect_ID id)
{
	for (std::vector<CharaterSprite*>::iterator item = CharaterSpritesVec.begin(); item != CharaterSpritesVec.cend(); ++item)
		if ((*item)->sprite_id == id)
			return (*item)->CharaterSpriteRect;
	return { 0,0,0,0 };
}

bool j1DialogueManager::PreUpdate()
{
	return true;
}

bool j1DialogueManager::Update(float dt)
{
	/*
	//Test code
	//Different dialogues
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		App->dialoguemanager->ActivateDialogue(DialogueID::castle_1_dialogue);
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		App->dialoguemanager->ActivateDialogue(DialogueID::castle_2_dialogue);
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		App->dialoguemanager->ActivateDialogue(DialogueID::castle_3_dialogue);
	//Pause/resume dialogue
	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
		PauseActiveDialogue();
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		ResumeActiveDialogue();
	//Test code end
	*/

	if (!ActiveDialog->DialogueActive || ActiveDialog->DialoguePaused || App->startmenuback->InGameMenuVisible())
		return true;

	//Blit Dark background
	App->render->DrawQuad(WindowRect, Black(0), Black(1), Black(2), 80, true, false, false);

	//Blit Characters
	if(ActiveDialog->ActiveDialogueStepPtr->ListenerDialogueCharacter->DialogueCharacter_pos == DialogueInterlucutorPosition::Left)
		App->render->Blit(ActiveDialog->ActiveDialogueStepPtr->ListenerDialogueCharacter->Character_Atlas, 0 - App->render->camera.x, 0 - App->render->camera.y, &ActiveDialog->ActiveDialogueStepPtr->ListenerDialogueCharacter->Character_Expression_Rect, 1.0f, 0, INT_MAX, INT_MAX, false, 123, SDL_RendererFlip::SDL_FLIP_NONE);
	else
		App->render->Blit(ActiveDialog->ActiveDialogueStepPtr->ListenerDialogueCharacter->Character_Atlas, 1280 - ActiveDialog->ActiveDialogueStepPtr->ListenerDialogueCharacter->Character_Expression_Rect.w - App->render->camera.x, 0 - App->render->camera.y, &ActiveDialog->ActiveDialogueStepPtr->ListenerDialogueCharacter->Character_Expression_Rect, 1.0f, 0, INT_MAX, INT_MAX, false, 123, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);

	if (ActiveDialog->ActiveDialogueStepPtr->SpeakerDialogueCharacter->DialogueCharacter_pos == DialogueInterlucutorPosition::Left)
		App->render->Blit(ActiveDialog->ActiveDialogueStepPtr->SpeakerDialogueCharacter->Character_Atlas, 0 - App->render->camera.x, 0 - App->render->camera.y, &ActiveDialog->ActiveDialogueStepPtr->SpeakerDialogueCharacter->Character_Expression_Rect, 1.0f, 0, INT_MAX, INT_MAX, false, 255, SDL_RendererFlip::SDL_FLIP_NONE);
	else
		App->render->Blit(ActiveDialog->ActiveDialogueStepPtr->SpeakerDialogueCharacter->Character_Atlas, 1280 - ActiveDialog->ActiveDialogueStepPtr->SpeakerDialogueCharacter->Character_Expression_Rect.w - App->render->camera.x, 0 - App->render->camera.y, &ActiveDialog->ActiveDialogueStepPtr->SpeakerDialogueCharacter->Character_Expression_Rect, 1.0f, 0, INT_MAX, INT_MAX, false, 255, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);

	//Blit text background and Name labels
	TextBackground->DrawWithAlternativeAtlas(App->hud->GetAtlas());
	if(*LeftCharacterLabel->GetLabelStr() != empty_char)
		LeftCharacterLabel->DrawWithAlternativeAtlas(App->hud->GetAtlas());
	if (*RightCharacterLabel->GetLabelStr() != empty_char)
		RightCharacterLabel->DrawWithAlternativeAtlas(App->hud->GetAtlas());

	//Blit text
	for (std::vector<GuiLabel*>::iterator item = ActiveDialog->ActiveDialogueStepPtr->lines.begin(); item != ActiveDialog->ActiveDialogueStepPtr->lines.cend(); ++item)
		(*item)->Draw();

	if ((App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_DOWN) || (App->input->GetControllerButton(0, 0) == j1KeyState::KEY_DOWN) || (App->input->GetControllerButton(1, 0) == j1KeyState::KEY_DOWN))
		DialogueNextStep();

	return true;
}

bool j1DialogueManager::PostUpdate()
{
	return true;
}

bool j1DialogueManager::CleanUp()
{
	for (std::vector<Dialogue*>::iterator item = dialogues.begin(); item != dialogues.cend(); ++item)
		RELEASE(*item);
	dialogues.clear();
	for (std::vector<DialogueInterlucutorStrAndAtalsRelation*>::iterator item = DialogueInterlucutorStrandAtlasRelationVec.begin(); item != DialogueInterlucutorStrandAtlasRelationVec.cend(); ++item)
		RELEASE(*item);
	DialogueInterlucutorStrandAtlasRelationVec.clear();
	for (std::vector<CharaterSprite*>::iterator item = CharaterSpritesVec.begin(); item != CharaterSpritesVec.cend(); ++item)
		RELEASE(*item);
	CharaterSpritesVec.clear();
	RELEASE(ActiveDialog);
	RELEASE(TextBackground);
	RELEASE(LeftCharacterLabel);
	RELEASE(RightCharacterLabel);

	App->tex->UnLoad(king_tex);
	App->tex->UnLoad(link_tex);
	App->tex->UnLoad(zelda_tex);
	App->tex->UnLoad(messenger_tex);
	App->tex->UnLoad(ric_tex);
	App->tex->UnLoad(ogity_tex);
	
	return true;
}

void j1DialogueManager::ActivateDialogue(DialogueID id)
{
	ActiveDialog->DialogueActive = true;
	ActiveDialog->DialoguePaused = false;
	for (std::vector<Dialogue*>::iterator item = dialogues.begin(); item != dialogues.cend(); ++item)
		if ((*item)->id == id)
		{
			ActiveDialog->ActiveDialoguePtr = *item;
			ActiveDialog->ActiveDialogueStepPtr = (*item)->DialogueSteps.front();
			SetCharacterBlit();
		}
}

void j1DialogueManager::PauseActiveDialogue()
{
	if(ActiveDialog != nullptr)
		if(ActiveDialog->DialogueActive == true)
			ActiveDialog->DialoguePaused = true;
}

void j1DialogueManager::ResumeActiveDialogue()
{
	if (ActiveDialog != nullptr)
	{
		DialogueNextStep();
		if (ActiveDialog->DialogueActive == true)
			ActiveDialog->DialoguePaused = false;
	}
}

uint j1DialogueManager::GetActiveDialogueStep()
{
	uint ret = 0;
	if(ActiveDialog != nullptr)
		for (std::vector<DialogueStep*>::iterator item = ActiveDialog->ActiveDialoguePtr->DialogueSteps.begin(); item != ActiveDialog->ActiveDialoguePtr->DialogueSteps.cend(); ++item, ret++)
			if ((*item) == ActiveDialog->ActiveDialogueStepPtr)
				return ret;

	return ret;
}

void j1DialogueManager::DialogueNextStep()
{
	if (ActiveDialog != nullptr)
		for (std::vector<DialogueStep*>::iterator item = ActiveDialog->ActiveDialoguePtr->DialogueSteps.begin(); item != ActiveDialog->ActiveDialoguePtr->DialogueSteps.cend(); ++item)
			if ((*item) == ActiveDialog->ActiveDialogueStepPtr)
			{
				if ((*item) != ActiveDialog->ActiveDialoguePtr->DialogueSteps.back())
				{
					ActiveDialog->ActiveDialogueStepPtr = *(++item);
					SetCharacterBlit();
				}
				else //if it the last step, quit and clean
				{
					ActiveDialog->DialogueActive = false;
					ActiveDialog->DialoguePaused = false;
					ActiveDialog->ActiveDialoguePtr = nullptr;
					ActiveDialog->ActiveDialogueStepPtr = nullptr;
				}
				return;
			}
}

void j1DialogueManager::SetCharacterBlit()
{
	if (ActiveDialog == nullptr)
		return;
	if (ActiveDialog->ActiveDialogueStepPtr->ListenerDialogueCharacter->DialogueCharacter_pos == DialogueInterlucutorPosition::Left)
		LeftCharacterLabel->EditButtonStr(&ActiveDialog->ActiveDialogueStepPtr->ListenerDialogueCharacter->DialogueCharacter_str);
	else
		RightCharacterLabel->EditButtonStr(&ActiveDialog->ActiveDialogueStepPtr->ListenerDialogueCharacter->DialogueCharacter_str);
	if (ActiveDialog->ActiveDialogueStepPtr->SpeakerDialogueCharacter->DialogueCharacter_pos == DialogueInterlucutorPosition::Left)
		LeftCharacterLabel->EditButtonStr(&ActiveDialog->ActiveDialogueStepPtr->SpeakerDialogueCharacter->DialogueCharacter_str);
	else
		RightCharacterLabel->EditButtonStr(&ActiveDialog->ActiveDialogueStepPtr->SpeakerDialogueCharacter->DialogueCharacter_str);
}

void j1DialogueManager::OnGui(Gui* ui, GuiEvent event)
{

}

void j1DialogueManager::OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments)
{

}

void j1DialogueManager::OnConsoleCVar(const CVar* cvar)
{

}

DialogueStep::DialogueStep()
{

}

DialogueStep::~DialogueStep()
{
	delete SpeakerDialogueCharacter;
	delete ListenerDialogueCharacter;
	for (std::vector<GuiLabel*>::iterator item = lines.begin(); item != lines.cend(); ++item)
		RELEASE(*item);
	lines.clear();
}

Dialogue::Dialogue()
{

}

Dialogue::~Dialogue()
{
	for (std::vector<DialogueStep*>::iterator item = DialogueSteps.begin(); item != DialogueSteps.cend(); ++item)
		RELEASE(*item);
	DialogueSteps.clear();
}

ActiveDialogue::ActiveDialogue()
{

}

ActiveDialogue::~ActiveDialogue()
{

}

DialogueInterlucutorStrAndAtalsRelation::DialogueInterlucutorStrAndAtalsRelation(std::string* str, DialogueInterlucutor enu, SDL_Texture* atlas) : 
	DialogueInterlucutorStr(*str), DialogueInterlucutorEnum(enu), DialogueInterlucutorAtlas(atlas)
{

}

DialogueInterlucutorStrAndAtalsRelation::~DialogueInterlucutorStrAndAtalsRelation()
{

}

DialogueCharacter::DialogueCharacter()
{

}

DialogueCharacter::~DialogueCharacter()
{

}

CharaterSprite::CharaterSprite()
{

}

CharaterSprite::~CharaterSprite()
{

}