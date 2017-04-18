#include "j1DialogueManager.h"
#include "j1App.h"
#include "j1FileSystem.h"

#include "j1Input.h"

Dialogue::Dialogue(int id) : id(id)
{

}

Dialogue::~Dialogue()
{
	texts.clear();
}

DialogueStep::DialogueStep(int NPCstate, std::string text) : state(NPCstate)
{

}

DialogueStep::~DialogueStep()
{

}

j1DialogueManager::j1DialogueManager() : j1Module()
{
	name = ("dialogue");
}

j1DialogueManager::~j1DialogueManager()
{
	dialog.clear();
}

bool j1DialogueManager::Awake(pugi::xml_node& config)
{
	LOG("Loading DialogManager");
	/*
	folder = config.child("dialogues").attribute("folder").as_string();
	path = config.child("dialogues").first_child().attribute("file").as_string();

	std::string tmp = folder + path;

	char* buf;
	int size = App->fs->Load(tmp.c_str(), &buf);
	pugi::xml_parse_result result = dialogueDataFile.load_buffer(buf, size);

	RELEASE(buf);

	if (result == NULL)
	{
		LOG("Could not load gui xml file %s. pugi error: %s", dialogueDataFile, result.description());
		return false;
	}
	*/
	return true;
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
	if (hidden)
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
	BlitDialog(id, NPCstate); //Calls Blit function
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

void j1DialogueManager::OnGui(Gui* ui, GuiEvent event)
{

}

void j1DialogueManager::OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments)
{

}

void j1DialogueManager::OnConsoleCVar(const CVar* cvar)
{

}

bool j1DialogueManager::BlitDialog(uint id, uint state)
{
	//Find the correct ID
	for (uint i = 0; i < dialog.size(); i++)
		if (dialog[i]->id == id)
			for (uint j = 0; (j + dialogueStep) < dialog[i]->texts.size(); j++) //Search correct text inside Dialogue
				if (dialog[i]->texts[dialogueStep + j]->state == state)
				{
					//for (uint k = 0; k < dialog[i]->texts[dialogueStep + j]->lines.size(); k++)
					//text_on_screen->Set_String((char*)dialog[i]->texts[dialogueStep+j]->line->c_str());
					return true;
				}
	return false;
}

void j1DialogueManager::DialogueShown(bool visible)
{
	hidden = visible;
}