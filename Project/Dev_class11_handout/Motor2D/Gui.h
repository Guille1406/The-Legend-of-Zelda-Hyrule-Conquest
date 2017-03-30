#ifndef __GUI_H__
#define __GUI_H__

#include "p2Log.h"
#include "j1Module.h"
#include "MainScene.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "Color.h"

enum GuiType
{
	gui_image,
	gui_button,
	gui_check,
	gui_inputtext,
	gui_label,
	gui_bar,
	gui_scrollbar,
	gui_window,
	gui_viewport,
	undefined
};

enum GuiEvent
{
	mouse_enter,
	mouse_leave,
	mouse_lclk_down,
	mouse_lclk_repeat,
	mouse_lclk_up,
	mouse_rclk_down,
	mouse_rclk_repeat,
	mouse_rclk_up,
	gain_focus,
	lost_focus,

	/*
	listening_ends,
	input_changed,
	input_submit,
	value_changed
	*/

	none_event
};

enum AddGuiTo
{
	regular_purpose,
	console_purpose,
	viewport_purpose,
	none
};

enum ButtonType
{
	idle_only,
	idle_hover,
	idle_pressed,
	idle_hover_pressed,
	undef
};

enum BarType
{
	vertical_up,
	vertical_down,
	horitzontal_left,
	horitzontal_right,
	unknown
};

class MainScene;

class Gui
{
	friend class j1Gui;
public:
	Gui(iPoint position, GuiType type, bool movable, AddGuiTo purpose);
	virtual ~Gui()
	{

	}
	virtual void Update(const Gui* mouse_hover, const Gui* focus)
	{

	}
	virtual void Draw()
	{

	}
	virtual void DebugDraw() const
	{

	}
	void SetLocalPos(int x, int y);
	iPoint GetLocalPos() const;
	void Move(int x, int y);
	void SetDragVelocity(float x, float y);
	fPoint GetDragVelocity() const;
	void SetListener(j1Module* module);
	void SetListener(MainScene* module);
	void SetVisible(bool visible);
	bool PointContained(int x, int y) const;
	void CheckInput(const Gui* mouse_hover, const Gui* focus);
	AddGuiTo GetPurpose() const;
	bool InFOV();

	void Focusable(bool value)
	{
		can_focus = value;
	}

	const j1Module* GetModuleListener() const
	{
		return module_listener;
	}

	const MainScene* GetSceneListener() const
	{
		return scene_listener;
	}

protected:
	AddGuiTo purpose;
	fPoint drag_vel = { 0.0f, 0.0f };
	iPoint position = { 0,0 };
	j1Module* module_listener = nullptr;
	MainScene* scene_listener = nullptr;
	GuiType type = GuiType::undefined;
	bool visible = true;
	bool movable = false;
	bool mouse_inside = false;
	SDL_Rect Gui_Collider = { 0,0,0,0 };
	uint opacity = 255;
	bool can_focus = false;
};

#endif // __GUI_H__