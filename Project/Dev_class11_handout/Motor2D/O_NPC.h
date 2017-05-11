#ifndef _O_NPC_
#define _O_NPC_
#include "j1Object.h"
#include"j1Render.h"
#include "Character.h"

enum NPC_Type {

	npc_ric,
	npc_enmasked,
	npc_neutral,
	npc_none
};


class O_NPC : public Object {
private:
	bool triggered = false;

public:
	O_NPC() {

	}
	O_NPC(const O_NPC& obj) {
		type = obj.type;
		//need npc_type
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		texture_rect = obj.texture_rect;
	}
	~O_NPC() {

	}
	void Active();



public:

	NPC_Type npc_type = NPC_Type::npc_none;


};


#endif
