#include "j1InputManager.h"
#include "j1App.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1FileSystem.h"
#include "j1Input.h"
#include "j1Fonts.h"
#include "j1Audio.h"
#include "SDL\include\SDL.h"


j1InputManager::j1InputManager() : j1Module()
{
	name = "inputManager";
	
}

// Destructor
j1InputManager::~j1InputManager()
{}

// Called when before render is available
bool j1InputManager::Awake(pugi::xml_node& conf)
{
	bool ret = true;

	//Load All actions
	for (pugi::xml_node tmp = conf.child("action"); tmp != nullptr; tmp = tmp.next_sibling())
	{
		std::pair<int, INPUTEVENT> new_action;
		new_action.first = tmp.attribute("button").as_int();
		new_action.second = (INPUTEVENT)tmp.attribute("event").as_int();

		actions_link.insert(new_action);
		actions_zelda.insert(new_action);
	}

	for (pugi::xml_node tmp = conf.child("action2"); tmp != nullptr; tmp = tmp.next_sibling())
	{
		std::pair<int, INPUTEVENT> new_action;
		new_action.first = tmp.attribute("button").as_int();
		new_action.second = (INPUTEVENT)tmp.attribute("event").as_int();

		actions_link2.insert(new_action);
		actions_zelda2.insert(new_action);
		
	}


	return ret;
}

void j1InputManager::ChangeInput() {

	

	std::multimap<int, INPUTEVENT> new_action_l;
	std::multimap<int, INPUTEVENT> new_action_z;

	new_action_l = actions_link;
	new_action_z = actions_zelda;

	actions_link = actions_link2;
	actions_zelda = actions_zelda2;
	
	actions_link2 = new_action_l;
	actions_zelda2 = new_action_z;

}

// Called before all Updates
bool j1InputManager::PreUpdate()
{
	bool ret = true;
	return ret;
}

bool j1InputManager::Update(float dt)
{
	if (EventPressed(PAUSE, 0) == E_DOWN)
	{
		ChangeInputEvent(MUP);
	}

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN){
		ChangeInput();
		

	}


	return true;
}

// Called after all Updates
bool j1InputManager::PostUpdate()
{
	if (!current_action_link.empty())
		current_action_link.clear();

	if (!current_action_zelda.empty())
		current_action_zelda.clear();

	return true;
}

// Called before quitting
bool j1InputManager::CleanUp()
{
	bool ret = true;



	return ret;
}

void j1InputManager::InputDetected(int button, EVENTSTATE state, int player)
{
	if (state != EVENTSTATE::E_NOTHING)
		LOG("PLAYER = %i", player);
	if (next_input_change == false)
	{
		if (player == 1) {


			std::multimap<int, INPUTEVENT>::iterator tmp = actions_link.find(button);
			//If more than one action per button we must iterate until the end
			if (tmp != actions_link.end())
			{
				std::pair<INPUTEVENT, EVENTSTATE> new_current_action_link;
				new_current_action_link.first = (*tmp).second;
				new_current_action_link.second = state;
				current_action_link.insert(new_current_action_link);
			}
		}

		else if (player == 0) {
			std::multimap<int, INPUTEVENT>::iterator tmp = actions_zelda.find(button);
			//If more than one action per button we must iterate until the end
			if (tmp != actions_zelda.end())
			{
				std::pair<INPUTEVENT, EVENTSTATE> new_current_action_zelda;
				new_current_action_zelda.first = (*tmp).second;
				new_current_action_zelda.second = state;
				current_action_zelda.insert(new_current_action_zelda);




			}
		}
	}
	else
	{
		ChangeEventButton(button,player);
	}
}

void j1InputManager::JoystickDetected(int axis, JSTATE state, int player)
{

	std::pair<INPUTEVENT, EVENTSTATE>	new_current_action_link;
	std::pair<INPUTEVENT, EVENTSTATE>	new_current_action_zelda;
	if (player == 1) {
		switch (axis)
		{
		case SDL_CONTROLLER_AXIS_LEFTX:
			if (state == J_POSITIVE)
			{
				new_current_action_link.first = MRIGHT;
				new_current_action_link.second = E_REPEAT;
				current_action_link.insert(new_current_action_link);
			}
			else
			{
				new_current_action_link.first = MLEFT;
				new_current_action_link.second = E_REPEAT;
				current_action_link.insert(new_current_action_link);
			}
			break;

		case SDL_CONTROLLER_AXIS_LEFTY:

			if (state == J_POSITIVE)
			{
				new_current_action_link.first = MDOWN;
				new_current_action_link.second = E_REPEAT;
				current_action_link.insert(new_current_action_link);
			}
			else
			{
				new_current_action_link.first = MUP;
				new_current_action_link.second = E_REPEAT;
				current_action_link.insert(new_current_action_link);
			}
			break;


		}


	}
	else if (player == 0) {

		switch (axis)
		{
		case SDL_CONTROLLER_AXIS_LEFTX:
			if (state == J_POSITIVE)
			{
				new_current_action_zelda.first = MRIGHT;
				new_current_action_zelda.second = E_REPEAT;
				current_action_zelda.insert(new_current_action_zelda);
			}
			else
			{
				new_current_action_zelda.first = MLEFT;
				new_current_action_zelda.second = E_REPEAT;
				current_action_zelda.insert(new_current_action_zelda);
			}
			break;

		case SDL_CONTROLLER_AXIS_LEFTY:

			if (state == J_POSITIVE)
			{
				new_current_action_zelda.first = MDOWN;
				new_current_action_zelda.second = E_REPEAT;
				current_action_zelda.insert(new_current_action_zelda);
			}
			else
			{
				new_current_action_zelda.first = MUP;
				new_current_action_zelda.second = E_REPEAT;
				current_action_zelda.insert(new_current_action_zelda);
			}
			break;

		}
	}
}

void j1InputManager::ChangeInputEvent(INPUTEVENT change_ev)
{
	next_input_change = true;
	event_to_change = change_ev;
}

bool j1InputManager::ChangeEventButton(int new_button,int id)
{
	bool ret = false;

	//Look if the new button is actually asigned
	std::multimap<int, INPUTEVENT>::iterator tmp = actions_link.find(new_button);
	std::multimap<int, INPUTEVENT>::iterator tmp_1 = actions_zelda.find(new_button);
	if (id == 1) {
		if (tmp != actions_link.end())
		{
			LOG("This button is actually in another action");
			return ret;
		}

		//Look for the event to erase it
		tmp = actions_link.begin();
		while ((*tmp).second != event_to_change)
			tmp++;
		actions_link.erase(tmp);

		//This is the event with the new button
		std::pair<int, INPUTEVENT> event_changed;
		event_changed.first = new_button;
		event_changed.second = event_to_change;
		actions_link.insert(event_changed);

		//Reset the variables
		next_input_change = false;
		event_to_change = NO_EVENT;

		ret = true;
	}

	if (id == 0) {
		if (tmp_1 != actions_zelda.end())
		{
			LOG("This button is actually in another action");
			return ret;
		}

		//Look for the event to erase it
		tmp_1 = actions_zelda.begin();
		while ((*tmp_1).second != event_to_change)
			tmp_1++;
		actions_zelda.erase(tmp_1);

		//This is the event with the new button
		std::pair<int, INPUTEVENT> event_changed;
		event_changed.first = new_button;
		event_changed.second = event_to_change;
		actions_zelda.insert(event_changed);

		//Reset the variables
		next_input_change = false;
		event_to_change = NO_EVENT;

		ret = true;



	}

	return ret;
}

EVENTSTATE j1InputManager::EventPressed(INPUTEVENT action, int player) const
{
	if (player == 1) {

		std::multimap<INPUTEVENT, EVENTSTATE>::const_iterator tmp = current_action_link.find(action);

		if (tmp != current_action_link.end())
			return tmp->second;

	}
	else if (player == 0)
	{
		std::multimap<INPUTEVENT, EVENTSTATE>::const_iterator tmp = current_action_zelda.find(action);

		if (tmp != current_action_zelda.end())
			return tmp->second;
	}

	return E_NOTHING;
}








