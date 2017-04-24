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
		
	}

	~ColourBlock()
	{

	}

	void Action()
	{
		active = true;
	}
	void EndAction() {
		active = false;
	}

public:

	

};

#endif
