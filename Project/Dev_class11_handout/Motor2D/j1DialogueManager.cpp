#include "j1DialogueManager.h"
#include "j1App.h"
#include "j1FileSystem.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Input.h"
#include "j1HUD.h"
#include "j1Fonts.h"

#include "GuiImage.h"
#include "GuiLabel.h"
#include "GuiButton.h"

j1DialogueManager::j1DialogueManager() : j1Module()
{
	name = ("dialogue");
}

j1DialogueManager::~j1DialogueManager()
{
	for (std::vector<Dialogue*>::iterator item = dialogues.begin(); item != dialogues.cend(); ++item)
		RELEASE(*item);
	dialogues.clear();
	for (std::vector<DialogueInterlucutorStrRelation*>::iterator item = DialogueInterlucutorStrRelationVec.begin(); item != DialogueInterlucutorStrRelationVec.cend(); ++item)
		RELEASE(*item);
	DialogueInterlucutorStrRelationVec.clear();
	RELEASE(ActiveDialog);
	RELEASE(TextBackground);
	RELEASE(LeftCharacterLabel);
	RELEASE(RightCharacterLabel);
}

bool j1DialogueManager::Awake(pugi::xml_node& config)
{
	bool ret = false;
	LOG("Loading DialogManager");

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

		DialogueInterlucutorStrRelationVec.push_back(new DialogueInterlucutorStrRelation(&std::string("item_nullinterlucutor"), DialogueInterlucutor::item_nullinterlucutor));
		DialogueInterlucutorStrRelationVec.push_back(new DialogueInterlucutorStrRelation(&std::string("king"), DialogueInterlucutor::King));
		DialogueInterlucutorStrRelationVec.push_back(new DialogueInterlucutorStrRelation(&std::string("link"), DialogueInterlucutor::Link));
		DialogueInterlucutorStrRelationVec.push_back(new DialogueInterlucutorStrRelation(&std::string("zelda"), DialogueInterlucutor::Zelda));
		DialogueInterlucutorStrRelationVec.push_back(new DialogueInterlucutorStrRelation(&std::string("messenger"), DialogueInterlucutor::Messenger));
		DialogueInterlucutorStrRelationVec.push_back(new DialogueInterlucutorStrRelation(&std::string("ric"), DialogueInterlucutor::Ric));
		DialogueInterlucutorStrRelationVec.push_back(new DialogueInterlucutorStrRelation(&std::string("guard"), DialogueInterlucutor::Guard));

		//Allocate dialogues from XML
		AllocateDialogues(dialogue_config, &TextBackground->GetLocalPos());
	}

	ActiveDialog = new ActiveDialogue();

	return ret;
}

void j1DialogueManager::AllocateDialogues(pugi::xml_node& dialoguenode, iPoint* TextBackgroundPos)
{
	//Allocate dialogues from XML
	//itereate cutscenes
	for (pugi::xml_node newcutscene = dialoguenode.child("Cutscenes").child("cutscene"); newcutscene; newcutscene = newcutscene.next_sibling("cutscene"))
	{
		dialogues.push_back(new Dialogue());
		Dialogue* newdialogue = dialogues.back();
		newdialogue->id = (DialogueID)newcutscene.attribute("enum_value").as_int(0);
		newdialogue->type = DialogueType::Cutscene;
		for (pugi::xml_node newcutscenesteps = newcutscene.child("step"); newcutscenesteps; newcutscenesteps = newcutscenesteps.next_sibling("step"))
		{
			newdialogue->DialogueSteps.push_back(new DialogueStep());
			DialogueStep* newdialoguestep = newdialogue->DialogueSteps.back();
			newdialoguestep->SpeakerDialogueCharacter = new DialogueCharacter();
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newcutscenesteps.attribute("speaker").as_string()));
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_str = std::string(newcutscenesteps.attribute("speaker").as_string());
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newcutscenesteps.attribute("speaker_pos").as_string()));
			newdialoguestep->ListenerDialogueCharacter = new DialogueCharacter();
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newcutscenesteps.attribute("listener").as_string()));
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_str = std::string(newcutscenesteps.attribute("listener").as_string());
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newcutscenesteps.attribute("listener_pos").as_string()));
			int y = 0;
			for (pugi::xml_node newcutscenesteplines = newcutscenesteps.child("line"); newcutscenesteplines; newcutscenesteplines = newcutscenesteplines.next_sibling("line"), y += 30)
			{
				newdialoguestep->lines.push_back(App->gui->CreateLabel({TextBackgroundPos->x + 60,TextBackgroundPos->y + 60 + y }, &std::string(newcutscenesteplines.child_value()), false, AddGuiTo::none));
				newdialoguestep->lines.back()->SetFont(App->font->ReturnofGanon36);
			}
		}
	}
	//itereate NPCs
	for (pugi::xml_node newnpc = dialoguenode.child("NPCs").child("npc"); newnpc; newnpc = newnpc.next_sibling("npc"))
	{
		dialogues.push_back(new Dialogue());
		Dialogue* newdialogue = dialogues.back();
		newdialogue->id = (DialogueID)newnpc.attribute("enum_value").as_int(0);
		newdialogue->type = DialogueType::Cutscene;
		for (pugi::xml_node newnpcsteps = newnpc.child("step"); newnpcsteps; newnpcsteps = newnpcsteps.next_sibling("step"))
		{
			newdialogue->DialogueSteps.push_back(new DialogueStep());
			DialogueStep* newdialoguestep = newdialogue->DialogueSteps.back();
			newdialoguestep->SpeakerDialogueCharacter = new DialogueCharacter();
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newnpcsteps.attribute("speaker").as_string()));
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_str = std::string(newnpcsteps.attribute("speaker").as_string());
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newnpcsteps.attribute("speaker_pos").as_string()));
			newdialoguestep->ListenerDialogueCharacter = new DialogueCharacter();
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newnpcsteps.attribute("listener").as_string()));
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_str = std::string(newnpcsteps.attribute("listener").as_string());
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newnpcsteps.attribute("listener_pos").as_string()));
			int y = 0;
			for (pugi::xml_node newnpcsteplines = newnpcsteps.child("line"); newnpcsteplines; newnpcsteplines = newnpcsteplines.next_sibling("line"), y += 30)
			{
				newdialoguestep->lines.push_back(App->gui->CreateLabel({ TextBackgroundPos->x + 60,TextBackgroundPos->y + 60 + y }, &std::string(newnpcsteplines.child_value()), false, AddGuiTo::none));
				newdialoguestep->lines.back()->SetFont(App->font->ReturnofGanon36);
			}
		}
	}

	//itereate items
	for (pugi::xml_node newirtem = dialoguenode.child("Items").child("item"); newirtem; newirtem = newirtem.next_sibling("item"))
	{
		dialogues.push_back(new Dialogue());
		Dialogue* newdialogue = dialogues.back();
		newdialogue->id = (DialogueID)newirtem.attribute("enum_value").as_int(0);
		newdialogue->type = DialogueType::Cutscene;
		for (pugi::xml_node newitemsteps = newirtem.child("step"); newitemsteps; newitemsteps = newitemsteps.next_sibling("step"))
		{
			newdialogue->DialogueSteps.push_back(new DialogueStep());
			DialogueStep* newdialoguestep = newdialogue->DialogueSteps.back();
			newdialoguestep->SpeakerDialogueCharacter = new DialogueCharacter();
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newitemsteps.attribute("speaker").as_string()));
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_str = std::string(newitemsteps.attribute("speaker").as_string());
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newitemsteps.attribute("speaker_pos").as_string()));
			newdialoguestep->ListenerDialogueCharacter = new DialogueCharacter();
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newitemsteps.attribute("listener").as_string()));
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_str = std::string(newitemsteps.attribute("listener").as_string());
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newitemsteps.attribute("listener_pos").as_string()));
			int y = 0;
			for (pugi::xml_node newitemsteplines = newitemsteps.child("line"); newitemsteplines; newitemsteplines = newitemsteplines.next_sibling("line"), y += 30)
			{
				newdialoguestep->lines.push_back(App->gui->CreateLabel({ TextBackgroundPos->x + 60,TextBackgroundPos->y + 60 + y }, &std::string(newitemsteplines.child_value()), false, AddGuiTo::none));
				newdialoguestep->lines.back()->SetFont(App->font->ReturnofGanon36);
			}
		}
	}
}

DialogueInterlucutor j1DialogueManager::CheckInterlocutor(std::string* interlocutor_str)
{
	for (std::vector<DialogueInterlucutorStrRelation*>::iterator item = DialogueInterlucutorStrRelationVec.begin(); item != DialogueInterlucutorStrRelationVec.cend(); ++item)
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

bool j1DialogueManager::Start()
{
	return true;
}

bool j1DialogueManager::PreUpdate()
{
	return true;
}

bool j1DialogueManager::Update(float dt)
{
	//Test code
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		App->dialoguemanager->ActivateDialogue(DialogueID::castle_intro);
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		ActiveDialog->DialogueActive = false;
	//Test code end

	if (!ActiveDialog->DialogueActive)
		return true;

	//Blit Dark background
	App->render->DrawQuad(WindowRect, Black(0), Black(1), Black(2), 80, true, false, false);

	//Blit text background and Name labels
	TextBackground->DrawWithAlternativeAtlas(App->hud->GetAtlas());
	LeftCharacterLabel->DrawWithAlternativeAtlas(App->hud->GetAtlas());
	RightCharacterLabel->DrawWithAlternativeAtlas(App->hud->GetAtlas());

	//Blit text
	for (std::vector<GuiLabel*>::iterator item = ActiveDialog->ActiveDialogueStepPtr->lines.begin(); item != ActiveDialog->ActiveDialogueStepPtr->lines.cend(); ++item)
		(*item)->Draw();

	if ((App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_DOWN) || (App->input->GetControllerButton(0, 0) == j1KeyState::KEY_DOWN))
		DialogueNextStep();

	return true;
}

bool j1DialogueManager::PostUpdate()
{
	return true;
}

bool j1DialogueManager::CleanUp()
{
	return true;
}

bool j1DialogueManager::BlitDialog(uint id, uint state)
{
	/*
	//Find the correct ID
	for (uint i = 0; i < dialogue.size(); i++)
		if (dialogue[i]->id == id)
			for (uint j = 0; (j + dialogueStep) < dialogue[i]->DialogueSteps.size(); j++) //Search correct text inside Dialogue
				if (dialogue[i]->DialogueSteps[dialogueStep + j]->state == state)
				{
					//for (uint k = 0; k < dialog[i]->texts[dialogueStep + j]->lines.size(); k++)
					//text_on_screen->Set_String((char*)dialog[i]->texts[dialogueStep+j]->line->c_str());
					return true;
				}
	*/
	return false;
}

void j1DialogueManager::ActivateDialogue(DialogueID id)
{
	ActiveDialog->DialogueActive = true;
	for (std::vector<Dialogue*>::iterator item = dialogues.begin(); item != dialogues.cend(); ++item)
		if ((*item)->id == id)
		{
			ActiveDialog->ActiveDialoguePtr = *item;
			ActiveDialog->ActiveDialogueStepPtr = (*item)->DialogueSteps.front();
			SetCharacterBlit();
		}
}

void j1DialogueManager::DialogueNextStep()
{
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
				ActiveDialog->ActiveDialoguePtr = nullptr;
				ActiveDialog->ActiveDialogueStepPtr = nullptr;
			}
			return;
		}
}

void j1DialogueManager::SetCharacterBlit()
{
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

DialogueInterlucutorStrRelation::DialogueInterlucutorStrRelation(std::string* str, DialogueInterlucutor enu) : DialogueInterlucutorStr(*str), DialogueInterlucutorEnum(enu)
{

}

DialogueInterlucutorStrRelation::~DialogueInterlucutorStrRelation()
{

}

DialogueCharacter::DialogueCharacter()
{

}

DialogueCharacter::~DialogueCharacter()
{

}