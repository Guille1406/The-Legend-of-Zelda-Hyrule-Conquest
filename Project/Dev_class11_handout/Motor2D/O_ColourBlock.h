#ifndef _COLOURBLOCK_
#define _COLOURBLOCK_

#include "j1Object.h"
#include"j1Render.h"


class ColourBlock : public Object {
private:
	bool triggered = false;

public:
	ColourBlock()
	{

	}

	ColourBlock(const ColourBlock& obj)
	{
		type = obj.type;
		rect = obj.rect;
		active = false;
		name = obj.name;
		logic_height = obj.logic_height;
		if (strcmp(name.c_str(), "blue") == 0)
			texture_rect = rect_blue_block;
		if (strcmp(name.c_str(), "orange") == 0)
			texture_rect = rect_yellow_block;
		if (strcmp(name.c_str(), "green") == 0)
			texture_rect = rect_green_block;
		if (strcmp(name.c_str(), "red") == 0)
			texture_rect = rect_red_block;
		
	}

	~ColourBlock()
	{

	}

	void Action()
	{
		active = true;
		can_dissapear = false;
	}
	void EndAction() {
		block_delay.Start();
		can_dissapear = true;
		//active = false;
	}

public:

	j1Timer block_delay;
	bool can_dissapear = false;

};

#endif
