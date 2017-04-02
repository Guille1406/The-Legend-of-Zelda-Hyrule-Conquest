#ifndef __j1CAMERA_H__
#define __j1CAMERA_H__

#include <vector>

#include "j1Module.h"
#include "p2Point.h"
#include "j1Gui.h"


struct CamEllipse
{
	iPoint ellipsecentre = { 0,0 };
	int semimajoraxis = 0;
	int semiminoraxis = 0;

	float InsideEllipseValue(iPoint point)
	{
		return (((float)((point.x - ellipsecentre.x) * (point.x - ellipsecentre.x)) / (float)(semimajoraxis * semimajoraxis)) + ((float)((point.y - ellipsecentre.y) * (point.y - ellipsecentre.y)) / (float)(semiminoraxis * semiminoraxis)));
	}

	bool InsideEllipse(iPoint point)
	{
		return (InsideEllipseValue(point) <= 1.0f);
	}
};

enum GuiEvent;
class Gui;
struct Command;
struct CVar;

class j1Camera : public j1Module
{
public:
	j1Camera();

	~j1Camera();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void OnGui(Gui* ui, GuiEvent event);

	void OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments);

	void OnConsoleCVar(const CVar* cvar);

private:
	float		f_Max_scale = 0.0f;
	float		f_Min_scale = 0.0f;
	int			i_Half_w = 0;
	int			i_Half_h = 0;
	CamEllipse	LitleEllipse;
	CamEllipse  BigEllipse;
	float		f_border_between_ellipses = 0.0f;

	//Debug performance info
	bool f_DebugPerformanceData = false;
	std::vector<GuiLabel*> DebugPerformanceData;
	SDL_Rect DebugPerformanceData_Rect = { 0,0,0,0 };

};

#endif // __j1CAMERA_H__