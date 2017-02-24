#include <algorithm>

#include "j1Console.h"
#include "p2Log.h"
#include "Color.h"
#include "j1Input.h"
#include "j1Render.h"
#include "GuiInputText.h"
#include "j1App.h"

j1Console::j1Console()
{
	name.create("console");
}

// Destructor
j1Console::~j1Console()
{}

// Called when before render is available
bool j1Console::Awake(pugi::xml_node& conf)
{
	LOG("Awake console");
	bool ret = true;
	ConsoleModuleActive = true;
	return ret;
}

// Call before first frame
bool j1Console::Start()
{
	ConsoleBackground = { App->render->camera.x, App->render->camera.y, 768, 285 };
	ConsoleInputTextBackground = { App->render->camera.x, ConsoleBackground.h, ConsoleBackground.w, 30 };

	ConsoleInputText = App->gui->CreateInputText(iPoint(ConsoleInputTextBackground.x, ConsoleInputTextBackground.y), &ConsoleInputTextBackground, &std::string(""), false, false, false, AddGuiTo::console_purpose);
	//ConsoleInputText->SetFont();

	quit = CreateCommand(&std::string("quit"), this);
	help = CreateCommand(&std::string("help"), this);

	return true;
}

// Called before all Updates
bool j1Console::PreUpdate()
{
	iPoint NewCameraPos(App->render->camera.x, App->render->camera.y);
	if (CameraPos != NewCameraPos)
	{
		ConsoleBackground.x = -NewCameraPos.x;
		ConsoleBackground.y = -NewCameraPos.y;
		ConsoleInputTextBackground.x = -NewCameraPos.x;
		ConsoleInputTextBackground.y = -NewCameraPos.y + ConsoleBackground.h;
		CameraPos = NewCameraPos;
		//LOG("CameraPos %i %i", CameraPos.x, CameraPos.y);
	}
	return true;
}

// Called each loop iteration
bool j1Console::Update(float dt)
{
	/*
	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
		ConsoleActive = !ConsoleActive;
	*/
	if (ConsoleActive)
	{
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			std::string inputstr = *ConsoleInputText->GetInputString();
			if (inputstr != empty_char)
			{
				//Get str and analyze it
				std::transform(inputstr.begin(), inputstr.end(), inputstr.begin(), ::tolower);
				ParseInput(&inputstr);
				ConsoleInputText->Clear();
			}
		}
		int WheelMove = App->input->GetMouseWheelMotion();
		if (WheelMove)
			for (std::list<Gui*>::iterator item = LOGLabels.begin(); item != LOGLabels.cend(); ++item)
			{
				iPoint LocalItemPos = (*item)->GetLocalPos();
				(*item)->SetLocalPos(LocalItemPos.x, LocalItemPos.y + WheelMove * SCROLL_SPEED);
			}
	}
	return true;
}

// Called after all Updates
bool j1Console::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Console::CleanUp()
{
	LOG("Freeing Console");
	//LOGLabels is cleaned in j1Gui
	ConsoleModuleActive = false;
	return true;
}

void j1Console::Print_Console_Label(std::string* newlabelstr, uint tab)
{
	/*
	if (*newlabelstr != empty_char)
	{
		int XPos = 5;
		if (tab != 0)
		{
			for (int i = 0; i < tab; i++)
				XPos += 10;
		}
		if(LabelNum > 0)
		{ 
			iPoint LastLabelPos = (LOGLabels.back())->GetLocalPos();
			LOGLabels.push_back(App->gui->CreateLabel(iPoint(XPos, LastLabelPos.y + CONSOLE_FONT_SIZE), newlabelstr, false, AddGuiTo::console_purpose));
		}
		else
			LOGLabels.push_back(App->gui->CreateLabel(iPoint(XPos, 0), newlabelstr, false, AddGuiTo::console_purpose));
		LabelNum++;
	}
	*/
}

bool j1Console::IsActive() const
{
	return ConsoleActive;
}

bool j1Console::IsConsoleModuleActive() const
{
	return ConsoleModuleActive;
}

const Command* j1Console::CreateCommand(std::string* name, j1Module* listener, uint min_args, uint max_args)
{
	const Command* ret = nullptr;
	std::transform(name->begin(), name->end(), name->begin(), ::tolower);
	if ((name != nullptr) && !name->empty() && !StrExist(name))
	{
		Command com;
		com.name = *name;
		com.listener = listener;
		com.min_arguments = min_args;
		com.max_arguments = max_args;
		Commands.push_back(com);
		ret = &Commands.back();
	}
	return ret;
}

const CVar* j1Console::CreateCVar(std::string* name, std::string* string, j1Module* listener, bool read_only)
{
	const CVar* ret = nullptr;
	std::transform(name->begin(), name->end(), name->begin(), ::tolower);
	if ((name != nullptr) && !name->empty() && !StrExist(name) && (string != nullptr) && !string->empty())
	{
		std::transform(string->begin(), string->end(), string->begin(), ::tolower);
		CVar cvar;
		cvar.name = *name;
		cvar.listener = listener;
		cvar.read_only = read_only;
		cvar.type = CVar::CVar_string;
		cvar.value.s = string->c_str();
		CVars.push_back(cvar);
		ret = &CVars.back();
	}
	return ret;
}

const CVar* j1Console::CreateCVar(std::string* name, float value, j1Module* listener, bool read_only)
{
	const CVar* ret = nullptr;
	std::transform(name->begin(), name->end(), name->begin(), ::tolower);
	if ((name != nullptr) && !name->empty() && !StrExist(name))
	{
		CVar cvar;
		cvar.name = *name;
		cvar.listener = listener;
		cvar.read_only = read_only;
		cvar.type = CVar::CVar_float;
		cvar.value.f = value;
		CVars.push_back(cvar);
		ret = &CVars.back();
	}
	return ret;
}

const CVar* j1Console::CreateCVar(std::string* name, int value, j1Module* listener, bool read_only)
{
	const CVar* ret = nullptr;
	std::transform(name->begin(), name->end(), name->begin(), ::tolower);
	if ((name != nullptr) && !name->empty() && !StrExist(name))
	{
		CVar cvar;
		cvar.name = *name;
		cvar.listener = listener;
		cvar.read_only = read_only;
		cvar.type = CVar::CVar_int;
		cvar.value.i = value;
		CVars.push_back(cvar);
		ret = &CVars.back();
	}
	return ret;
}

const CVar* j1Console::CreateCVar(std::string* name, bool value, j1Module* listener, bool read_only)
{
	const CVar* ret = nullptr;
	std::transform(name->begin(), name->end(), name->begin(), ::tolower);
	if ((name != nullptr) && !name->empty() && !StrExist(name))
	{
		CVar cvar;
		cvar.name = *name;
		cvar.listener = listener;
		cvar.read_only = read_only;
		cvar.type = CVar::CVar_bool;
		cvar.value.b = value;
		CVars.push_back(cvar);
		ret = &CVars.back();
	}
	return ret;
}

void j1Console::ParseInput(std::string* strtoparse)
{
	if (*strtoparse == empty_char)
		return;

	ArgumentsVect.clear();

	char* commandChunk = nullptr;
	char* separators = " ";
	char* context = nullptr;//Strtok_s variable, need it to save the state of the string he analyzes. Doesn't needed with strtok.

	commandChunk = strtok_s((char *)strtoparse->c_str(), separators, &context);

	while (commandChunk != NULL)
	{
		ArgumentsVect.push_back(std::string(commandChunk));
		commandChunk = strtok_s(NULL, separators, &context);
	}

	uint numarguments = ArgumentsVect.size() - 1;//that 1 is the command itself

	const Command* com = FindCommand(&std::string(ArgumentsVect[0].c_str()));

	if (com != nullptr && com->listener != nullptr)
	{
		if (numarguments >= com->min_arguments && numarguments <= com->max_arguments)
		{
			//now is safe to call the listener
			com->listener->OnConsoleCommand(com, ArgumentsVect);
		}
		else
			Print_Console_Label(&std::string("Command arguments num error"));
	}
	//if it's not a command, it is a cvar
	else
	{
		const CVar* var = FindCVar(&std::string(ArgumentsVect[0].c_str()));

		if (var == nullptr)
			Print_Console_Label(&std::string("Command/CVar not found"));
		else
		{
			switch (numarguments)
			{
			case 0:
			{
				//0 arguments, print it
				static char tmp_string[4096];
				sprintf_s(tmp_string, 4096, "%s: %s", var->name, ((CVar*)var)->PrintCVar()->c_str());
				Print_Console_Label(&std::string(tmp_string));
				break;
			}
			case 1:
			{
				//1 argument, set value
				if (((CVar*)var)->SetValueFromString(&ArgumentsVect[1]) == true)
				{
					if (var->listener != nullptr)
						var->listener->OnConsoleCVar(var);
				}
				break;
			}
			default:
				// not 0 or 1 argument, error
				Print_Console_Label(&std::string("CVar arguments num error"));
				break;
			}
		}
	}
	//Print_Console_Label(strtoparse);
}

const Command* j1Console::FindCommand(std::string* name)
{
	if ((name != nullptr) && !name->empty())
	{
		for (std::list<Command>::const_iterator item = Commands.begin(); item != Commands.cend(); ++item)
			if(item->name == *name)
				return &(*item);
	}
	return nullptr;
}

const CVar* j1Console::FindCVar(std::string* name)
{
	if ((name != nullptr) && !name->empty())
	{
		for (std::list<CVar>::const_iterator item = CVars.begin(); item != CVars.cend(); ++item)
			if (item->name == *name)
				return &(*item);
	}
	return nullptr;
}

bool j1Console::StrExist(std::string* name)
{
	const Command* commandExist = FindCommand(name);
	if (commandExist != nullptr)
		return true;
	const CVar* cvarExist = FindCVar(name);
	if (cvarExist != nullptr)
		return true;
	return false;
}

void j1Console::OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments)
{
	if (command == quit)
	{
		//temporal exit, will be done right when it works fine :)
		exit(0);
	}
	if (command == help)
	{
		static char tmp_string[100];
		Print_Console_Label(&std::string("Help"));
		Print_Console_Label(&std::string("Commands"), 1);
		for (std::list<Command>::const_iterator item = Commands.begin(); item != Commands.cend(); ++item)
		{
			sprintf_s(tmp_string, 100, "%s", item->name.c_str());
			Print_Console_Label(&std::string(tmp_string), 2);
		}
		Print_Console_Label(&std::string("Cvars"), 1);
		for (std::list<CVar>::const_iterator item = CVars.begin(); item != CVars.cend(); ++item)
		{
			sprintf_s(tmp_string, 100, "%s", item->name.c_str());
			Print_Console_Label(&std::string(tmp_string), 2);
		}
	}
}