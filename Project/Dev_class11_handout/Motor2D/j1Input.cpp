#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1InputManager.h"
#include "SDL/include/SDL.h"

#define MAX_KEYS 300

j1Input::j1Input() : j1Module()
{
	name.create("input");

	keyboard = new j1KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(j1KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(j1KeyState) * NUM_MOUSE_BUTTONS);
	//memset(controller_axis, JOYSTICK_IDDLE, sizeof(j1JoystickState)* NUM_CONTROLLER_AXIS);
	memset(gamepad_connected, -1, sizeof(int)*MAX_GAMECONTROLLERS);
}

// Destructor
j1Input::~j1Input()
{
	delete[] keyboard;
}

// Called before render is available
bool j1Input::Awake(pugi::xml_node& config)
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	for (uint i = 0; i < NUM_CONTROLLER_BUTTONS; i++)
		prev_state[i] = j1KeyState::KEY_IDLE;

	return ret;
}

// Called before the first frame
bool j1Input::Start()

{
	
	SDL_StartTextInput();
	return true;
}

// Called each loop iteration
bool j1Input::PreUpdate()
{
	static SDL_Event event;

	//				Gamepad				//

	

	for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end(); it++) {

		for (int i = 0; i < NUM_CONTROLLER_BUTTONS; ++i) {

			if (prev_state[i] == j1KeyState::KEY_IDLE) {
				if ((*it)->controller_buttons[i] == j1KeyState::KEY_DOWN)
					App->inputM->InputDetected(i, EVENTSTATE::E_DOWN, (*it)->id);
					prev_state[i] = j1KeyState::KEY_DOWN;
			}

			if (prev_state[i] == j1KeyState::KEY_DOWN || prev_state[i] == j1KeyState::KEY_REPEAT) {
				if ((*it)->controller_buttons[i] == j1KeyState::KEY_DOWN) {
					(*it)->controller_buttons[i] = j1KeyState::KEY_REPEAT;
					App->inputM->InputDetected(i, EVENTSTATE::E_REPEAT, (*it)->id);
				}
				if ((*it)->controller_buttons[i] == j1KeyState::KEY_IDLE) {
					(*it)->controller_buttons[i] = j1KeyState::KEY_UP;
					prev_state[i] = j1KeyState::KEY_UP;
					App->inputM->InputDetected(i, EVENTSTATE::E_UP, (*it)->id);
				}



			}


			for (int i = 0; i < NUM_CONTROLLER_AXIS; ++i)
			{

				if ((*it)->controller_axis[i] == j1JoystickState::JOYSTICK_NEGATIVE)
					App->inputM->JoystickDetected(i, JSTATE::J_NEGATIVE, (*it)->id);


				if ((*it)->controller_axis[i] == j1JoystickState::JOYSTICK_POSITIVE)
					App->inputM->JoystickDetected(i, JSTATE::J_POSITIVE, (*it)->id);

			}
		}
	}
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	mouse_motion_x = 0;
	mouse_motion_y = 0;
	mouse_wheel_mov = 0;
	input_text.clear();

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for(int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if(mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if(mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{

		case SDL_CONTROLLERDEVICEADDED:
			AddController(event.cdevice.which);
			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			RemoveController(event.cdevice.which);
			break;





		case SDL_CONTROLLERAXISMOTION:
		{
			for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end(); it++)
			{
				if ((*it)->id == event.cbutton.which) {
					if (event.caxis.value < -DEAD_ZONE)
						(*it)->controller_axis[event.caxis.axis] = j1JoystickState::JOYSTICK_NEGATIVE;

					else
					{
						if (event.caxis.value > DEAD_ZONE)
							(*it)->controller_axis[event.caxis.axis] = j1JoystickState::JOYSTICK_POSITIVE;

						else (*it)->controller_axis[event.caxis.axis] = j1JoystickState::JOYSTICK_IDDLE;
					}
				}
			}}

		break;

		case SDL_CONTROLLERBUTTONDOWN:
		{
			for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end(); it++)
			{
				if ((*it)->id == event.cbutton.which)
				{
					LOG("BOTON: %i", event.cbutton.button);
					if ((*it)->controller_buttons[event.cbutton.button] = KEY_DOWN) {
						App->inputM->InputDetected(event.cbutton.button, EVENTSTATE::E_DOWN, (*it)->id);
					}
					if ((*it)->controller_buttons[event.cbutton.button] = KEY_REPEAT) {
						App->inputM->InputDetected(event.cbutton.button, EVENTSTATE::E_REPEAT, (*it)->id);
					}
				}
			}}
		break;

		// el problema esta aqui//
		case SDL_CONTROLLERBUTTONUP:
		{
			for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end(); it++)
			{
				if ((*it)->id == event.cbutton.which)
				{
					(*it)->controller_buttons[event.cbutton.button] == KEY_UP;
					App->inputM->InputDetected(event.cbutton.button, EVENTSTATE::E_UP, (*it)->id);
				}
			}
		}
		break;






		case SDL_QUIT:
			windowEvents[WE_QUIT] = true;
			SDL_StopTextInput();
			break;

		case SDL_TEXTINPUT:
			input_text = event.text.text;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
				//case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				windowEvents[WE_HIDE] = true;
				break;

				//case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				windowEvents[WE_SHOW] = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouse_buttons[event.button.button - 1] = KEY_DOWN;
			//LOG("Mouse button %d down", event.button.button-1);
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_buttons[event.button.button - 1] = KEY_UP;
			//LOG("Mouse button %d up", event.button.button-1);
			break;

		case SDL_MOUSEWHEEL:
			mouse_wheel_mov = event.wheel.y;
			break;

		case SDL_MOUSEMOTION:
			/*
			int scale = App->win->GetScale();
			mouse_motion_x = event.motion.xrel / scale;
			mouse_motion_y = event.motion.yrel / scale;
			mouse_x = event.motion.x / scale;
			mouse_y = event.motion.y / scale;
			*/
			mouse_motion_x = event.motion.xrel;
			mouse_motion_y = event.motion.yrel;
			mouse_x = event.motion.x;
			mouse_y = event.motion.y;
			//LOG("Mouse motion x %d y %d", mouse_motion_x, mouse_motion_y);
			break;

	//			gamepad			//
		


		}
	}
	return true;
}

// Called before quitting
bool j1Input::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool j1Input::GetWindowEvent(j1EventWindow ev)
{
	return windowEvents[ev];
}

void j1Input::GetMousePosition(int& x, int& y)
{
	x = mouse_x;
	y = mouse_y;
}

void j1Input::GetMouseMotion(int& x, int& y)
{
	x = mouse_motion_x;
	y = mouse_motion_y;
}

int j1Input::GetMouseWheelMotion() const
{
	return mouse_wheel_mov;
}

const std::string* j1Input::GetInputString() const
{
	return &input_text;

}

j1KeyState j1Input::GetControllerButton(int pad, int id) const
{
	for (std::vector<GamePad*>::const_iterator it = gamepads.begin(); it != gamepads.end(); it++)
	{
		if ((*it)->id == gamepad_connected[pad]) {
			return (*it)->controller_buttons[id];
		}
	}
	return KEY_NULL;
}


void j1Input::AddController(int id)
{
	if (SDL_IsGameController(id) && connected_gamepads < MAX_GAMECONTROLLERS)
	{
		SDL_GameController *pad = SDL_GameControllerOpen(id);

		if (pad)
		{
			SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
			int instanceID = SDL_JoystickInstanceID(joy);
			GamePad* new_pad = new GamePad();
			new_pad->id = instanceID;
			ConnectGamePad(instanceID);
			memset(new_pad->controller_buttons, KEY_IDLE, sizeof(j1KeyState)*NUM_CONTROLLER_BUTTONS);
			memset(new_pad->controller_axis, JOYSTICK_IDDLE, sizeof(j1JoystickState)* NUM_CONTROLLER_AXIS);
			new_pad->gamepad = pad;
			new_pad->pad_num = connected_gamepads;
			gamepads.push_back(new_pad);
			connected_gamepads++;
		}
	}
}


void j1Input::RemoveController(int id)
{
	for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end() && gamepads.size()>0; it++)
	{
		if ((*it)->id == id)
		{
			DisconectGamePad(id);
			SDL_GameControllerClose((*it)->gamepad);
			RELEASE(*it);
			gamepads.erase(it);
			connected_gamepads--;
			break;
		}
	}
}

void j1Input::ConnectGamePad(int instanceID)
{
	for (int i = 0; i < MAX_GAMECONTROLLERS; i++) {
		if (gamepad_connected[i] == -1)
		{
			gamepad_connected[i] = instanceID;
			break;
		}
	}
}

void j1Input::DisconectGamePad(int instanceID)
{
	for (int i = 0; i < MAX_GAMECONTROLLERS; i++) {
		if (gamepad_connected[i] == instanceID)
		{
			gamepad_connected[i] = -1;
			break;
		}
	}
}