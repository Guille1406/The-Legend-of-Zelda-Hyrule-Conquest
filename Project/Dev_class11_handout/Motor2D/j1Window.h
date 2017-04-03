#ifndef __j1WINDOW_H__
#define __j1WINDOW_H__

#include "j1Module.h"

struct SDL_Window;
struct SDL_Surface;

class j1Window : public j1Module
{
public:

	j1Window();

	// Destructor
	virtual ~j1Window();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Changae title
	void SetTitle(const char* new_title);

	// Retrive window size
	void GetWindowSize(uint& width, uint& height) const;

	uint GetWindowW() const;
	uint GetWindowWHalf() const;

	uint GetWindowH() const;
	uint GetWindowHHalf() const;

	// Retrieve window scale
	float GetScale() const;

public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface =nullptr;
	float		scale = 0.0f;
private:
	std::string	title = empty_char;
	uint		width = 0;
	uint		width_half = 0;
	uint		height = 0;
	uint		height_half = 0;
	
};

#endif // __j1WINDOW_H__