#ifndef _BLOCK_
#define _BLOCK_
#include "j1Object.h"
#include "Character.h"

class Block : public Object {
public:
	Block() {

	}
	Block(const Block& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		collider_tiles = obj.collider_tiles;
		collider_tiles = obj.collider_tiles;
		texture_rect = rect_block;
	}
	~Block() {

	}

	void Action() {


	};
public:

};


#endif
