#ifndef __j1CAMERA_H__
#define __j1CAMERA_H__

#include "j1Module.h"
#include "p2Point.h"

struct CamEllipse
{
	iPoint ellipsecentre = { 0,0 };
	uint semimajoraxis = 0;
	uint semiminoraxis = 0;

	float InsideEllipseValue(int x, int y)
	{
		return ((((x - ellipsecentre.x) * (x - ellipsecentre.x)) / (semimajoraxis * semimajoraxis)) + (((y - ellipsecentre.y) * (y - ellipsecentre.y)) / (semiminoraxis * semiminoraxis)));
	}

	bool InsideEllipse(int x, int y)
	{
		return (((((x - ellipsecentre.x) * (x - ellipsecentre.x)) / (semimajoraxis * semimajoraxis)) + (((y - ellipsecentre.y) * (y - ellipsecentre.y)) / (semiminoraxis * semiminoraxis))) <= 1);
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
	CamEllipse LitleEllipse;
	CamEllipse BigEllipse;

};

#endif // __j1CAMERA_H__