#ifndef _O_NPC_
#define _O_NPC_
#include "j1Object.h"
#include"j1Render.h"
#include "Character.h"


struct navi_save {
	int link_containters=0;
	int link_hearts = 0;
	Scene_ID id_scene = Scene_ID::NullScene;
	iPoint Link_Pos = { 0,0 };
	iPoint Zelda_Pos = { 0,0 };
	bool blocks_out_save = false;
	bool heart_1_picked = false;
	bool heart_2_picked = false;
	bool heart_3_picked = false;
	bool heart_4_picked = false;
	std::vector<bool>cutscenes_showed;

};

enum NPC_Type {

	npc_ric,
	npc_enmasked,
	npc_neutral,
	npc_navi,
	npc_none
};

enum NPC_direcction {

	npc_up,
	npc_right,
	npc_left,
	npc_down,
	npc_none_direction
};


class O_NPC : public Object {
private:
	bool triggered = false;

public:
	O_NPC() {

	}
	O_NPC(const O_NPC& obj) {
		type = obj.type;
		npc_type = obj.npc_type;
		dialogue_id_npc = obj.dialogue_id_npc;
		//need npc_type
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		texture_rect = obj.texture_rect;
		object_animation = obj.object_animation;
		object_animation.speed = 0.1;
	}
	~O_NPC() {

	}
	void Active() {
		if (npc_type!= NPC_Type::npc_navi) {
			App->dialoguemanager->ActivateDialogue(dialogue_id_npc);
		}
		else {

		}
	}



public:
	DialogueID dialogue_id_npc = DialogueID::NullID_dialogue;
	NPC_Type npc_type = NPC_Type::npc_none;


};


#endif
