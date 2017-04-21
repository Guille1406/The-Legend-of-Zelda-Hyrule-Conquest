#include "j1DialogueManager.h"
#include "j1App.h"
#include "j1FileSystem.h"

#include "j1Input.h"

j1DialogueManager::j1DialogueManager() : j1Module()
{
	name = ("dialogue");
}

j1DialogueManager::~j1DialogueManager()
{
	dialogues.clear();
}

bool j1DialogueManager::Awake(pugi::xml_node& config)
{
	bool ret = false;
	LOG("Loading DialogManager");

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

	}

	/*
	//Dialogue quad {0,94,1233,231}
	//Left label {0,0,336,94}
	//Right label {0337,336,94}
	*/

	return ret;
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
	if (ActiveDialogue == DialogueID::NullID)
		return true;
	/*--- CODE TO TEST RESULTS IN-GAME ---*/
	/*
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		dialogueStep = 0;
		if (id == 0)
			id = 1;
		else
			id = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		dialogueStep = 0;
		if (NPCstate == 0)
			NPCstate = 1;
		else
			NPCstate = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		dialogueStep = 0;
	*/
	/*--- END ---*/
	/*
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		dialogueStep++;
	*/
	//BlitDialog(id, NPCstate); //Calls Blit function
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
	ActiveDialogue = id;
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
	for (std::vector<std::string*>::iterator item = lines.begin(); item != lines.cend(); ++item)
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