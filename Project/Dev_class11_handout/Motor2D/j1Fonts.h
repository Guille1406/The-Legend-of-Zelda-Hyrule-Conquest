#ifndef __j1FONTS_H__
#define __j1FONTS_H__

#include "j1Module.h"
#include "SDL\include\SDL_pixels.h"

#define DEFAULT_FONT "fonts/open_sans/OpenSans-Bold.ttf"
#define DEFAULT_FONT_SIZE 12

struct SDL_Texture;
struct _TTF_Font;

class j1Fonts : public j1Module
{
public:

	j1Fonts();

	// Destructor
	virtual ~j1Fonts();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Load Font
	_TTF_Font* const Load(const char* path, int size = 12);

	// Create a surface from text
	SDL_Texture* Print(const char* text, SDL_Color color = {255, 255, 255, 255}, _TTF_Font* font = NULL);

	bool CalcSize(const char* text, int& width, int& height, _TTF_Font* font = NULL) const;

public:

	//p2List<_TTF_Font*>	fonts;
	std::list<_TTF_Font*> fonts;
	_TTF_Font*			default = nullptr;
	_TTF_Font*			Sherwood12 = nullptr;		//Menus
	_TTF_Font*			Sherwood20 = nullptr;		//Menus
	_TTF_Font*			Sherwood28 = nullptr;		//Menus
	_TTF_Font*			Sherwood36 = nullptr;		//Menus
	_TTF_Font*			ReturnofGanon12 = nullptr;	//Text
	_TTF_Font*			ReturnofGanon20 = nullptr;	//Text
	_TTF_Font*			ReturnofGanon28 = nullptr;	//Text
};


#endif // __j1FONTS_H__