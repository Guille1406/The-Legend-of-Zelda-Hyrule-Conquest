#include "j1DialogueManager.h"
#include "j1App.h"
#include "j1FileSystem.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Input.h"
#include "j1HUD.h"
#include "j1Fonts.h"

#include "GuiImage.h"
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
		//Allocate dialogues from XML
		AllocateDialogues(dialogue_config);

		//Set drawing areas and dialogue hud gui
		SDL_Rect TextBackgroundRect = { 0,94,1233,231 };
		TextBackground = App->gui->CreateImage({ 23,WindowRect.h - TextBackgroundRect.h - 11 }, &TextBackgroundRect, false, AddGuiTo::none);

		SDL_Rect LeftCharacterLabelRect = { 0,0,336,94 };
		LeftCharacterLabel = App->gui->CreateButton(iPoint(5, WindowRect.h - TextBackgroundRect.h - 11 - (int)(LeftCharacterLabelRect.h * 0.5f)), &std::string("Left Guy"), ButtonType::idle_only, &LeftCharacterLabelRect, false, AddGuiTo::none);
		LeftCharacterLabel->SetFont(App->font->ReturnofGanon36);

		SDL_Rect RightCharacterLabelRect = { 336,0,336,94 };
		RightCharacterLabel = App->gui->CreateButton(iPoint(WindowRect.w - RightCharacterLabelRect.w - 5, WindowRect.h - TextBackgroundRect.h - 11 - (int)(LeftCharacterLabelRect.h * 0.5f)), &std::string("Right Guy"), ButtonType::idle_only, &RightCharacterLabelRect, false, AddGuiTo::none);
		RightCharacterLabel->SetFont(App->font->ReturnofGanon36);
	}

	ActiveDialog = new ActiveDialogue();

	return ret;
}

void j1DialogueManager::AllocateDialogues(pugi::xml_node& dialoguenode)
{
	//Allocate dialogues from XML
	//itereate cutscenes
	for (pugi::xml_node newcutscene = dialoguenode.child("Cutscenes").child("cutscene"); newcutscene; newcutscene = newcutscene.next_sibling("cutscene"))
	{
		dialogues.push_back(new Dialogue());
		Dialogue* newdialogue = dialogues.back();
		newdialogue->id = (DialogueID)newcutscene.attribute("enum_value").as_int(0);
		for (pugi::xml_node newcutscenesteps = newcutscene.child("step"); newcutscenesteps; newcutscenesteps = newcutscenesteps.next_sibling("step"))
		{
			newdialogue->DialogueSteps.push_back(new DialogueStep());
			DialogueStep* newdialoguestep = newdialogue->DialogueSteps.back();
			newdialoguestep->listener = CheckInterlocutor(&std::string(newcutscenesteps.attribute("listener").as_string()));
			newdialoguestep->listener_pos = CheckInterlocutorPosition(&std::string(newcutscenesteps.attribute("listener_pos").as_string()));
			newdialoguestep->speaker = CheckInterlocutor(&std::string(newcutscenesteps.attribute("speaker").as_string()));
			newdialoguestep->speaker_pos = CheckInterlocutorPosition(&std::string(newcutscenesteps.attribute("speaker_pos").as_string()));
			for (pugi::xml_node newcutscenesteplines = newcutscenesteps.child("line"); newcutscenesteplines; newcutscenesteplines = newcutscenesteplines.next_sibling("line"))
			{
				newdialoguestep->lines.push_back(std::string(newcutscenesteplines.child_value()));
			}
		}
	}
	//itereate NPCs

	//itereate items
}

DialogueInterlucutor j1DialogueManager::CheckInterlocutor(std::string* interlocutor_str)
{
	return DialogueInterlucutor::item_nullinterlucutor;
}

DialogueInterlucutorPosition j1DialogueManager::CheckInterlocutorPosition(std::string* interlocutor_position_str)
{
	return DialogueInterlucutorPosition::Left;
}

bool j1DialogueManager::Start()
{
	/*
	dialogueNode = dialogueDataFile.child("npcs");
	// Allocate memory
	int i = 0;
	for (pugi::xml_node npc = dialogueNode.child("npc"); npc != NULL; npc = npc.next_sibling(), i++)
	{
		//Allocate Dialog with his ID and State
		Dialogue* tmp = new Dialogue(npc.attribute("id").as_int());
		dialog.push_back(tmp);

		//Allocate text
		for (pugi::xml_node dialogue = npc.child("dialogue"); dialogue != NULL; dialogue = dialogue.next_sibling())
			for (pugi::xml_node text = dialogue.child("text"); text != NULL; text = text.next_sibling("text"))
			{
				DialogueStep* tmp = new DialogueStep(dialogue.attribute("state").as_int(), text.attribute("value").as_string());
				dialog[i]->texts.push_back(tmp);
			}
	}
	*/
	//Prepare UI to print
	
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
		ActiveDialog->id = DialogueID::NullID;
	//Test code end

	if (ActiveDialog->id == DialogueID::NullID)
		return true;

	//Blit Dark background
	App->render->DrawQuad(WindowRect, Black(0), Black(1), Black(2), 80, true, false, false);

	//Blit text background and Name labels
	TextBackground->DrawWithAlternativeAtlas(App->hud->GetAtlas());
	LeftCharacterLabel->DrawWithAlternativeAtlas(App->hud->GetAtlas());
	RightCharacterLabel->DrawWithAlternativeAtlas(App->hud->GetAtlas());

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
	ActiveDialog->id = id;
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