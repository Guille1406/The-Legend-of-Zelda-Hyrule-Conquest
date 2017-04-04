#ifndef __j1INPUT_H__
#define __j1INPUT_H__

#include "j1Module.h"
#include "SDL\include\SDL_gamecontroller.h"
#include<queue>

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
#define NUM_CONTROLLER_BUTTONS 15
#define NUM_CONTROLLER_AXIS 6
#define DEAD_ZONE 10000
#define MAX_GAMECONTROLLERS 2
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;

enum j1EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum j1KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP,
	KEY_NULL
};

enum j1JoystickState
{
	JOYSTICK_POSITIVE,
	JOYSTICK_NEGATIVE,
	JOYSTICK_IDDLE
};

struct GamePad
{
	SDL_GameController*	gamepad = nullptr;
	j1KeyState			controller_buttons[NUM_CONTROLLER_BUTTONS];
	j1JoystickState		controller_axis[NUM_CONTROLLER_AXIS];
	int					pad_num = -1;
	int					id = -1;


};

class j1Input : public j1Module
{

public:

	j1Input();

	// Destructor
	virtual ~j1Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Gather relevant win events
	bool GetWindowEvent(j1EventWindow ev);

	// Check key states (includes mouse and joy buttons)
	j1KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	j1KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

	//Get mouse wheel movement
	int GetMouseWheelMotion() const;


	j1KeyState GetControllerButton(int pad, int id) const;
	

	void AddController(int id);
	void RemoveController(int id);

	void ConnectGamePad(int instanceID);
	void DisconectGamePad(int instanceID);

	int NumberOfGamePads() {
		return connected_gamepads;
	}
	//get text input
	const std::string* GetInputString() const;

private:
	bool		windowEvents[WE_COUNT];
	j1KeyState*	keyboard = nullptr;
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	int			mouse_motion_x = 0;
	int			mouse_motion_y = 0;
	int			mouse_x = 0;
	int			mouse_y = 0;
	int			mouse_wheel_mov = 0;
	std::string input_text = empty_char;

	std::vector<GamePad*> gamepads;
	int			connected_gamepads = 0;
	int			gamepad_connected[MAX_GAMECONTROLLERS];
	
	

};

#endif // __j1INPUT_H__