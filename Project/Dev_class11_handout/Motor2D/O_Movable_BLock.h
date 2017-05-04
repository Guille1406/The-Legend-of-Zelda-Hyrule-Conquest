#ifndef _MOVABLEBLOCK_
#define _MOVABLEBLOCK_
#include "j1Object.h"
#include "Character.h"

class Movable_Block : public Object {
public:
	Movable_Block() {

	}
	Movable_Block(const Movable_Block& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		collider_tiles = obj.collider_tiles;
	}
	~Movable_Block() {

	}

	void Action(Character* pulling_character) {
		
		iPoint tile_pos = { rect.x / 16,rect.y / 16 };
		switch (pulling_character->character_direction) {
		case direction::up:
			if (App->object->GetLogic(logic_height, { rect.x/16 ,(rect.y-1)/16 -2 }, true) == 0) {
				rect.y--;
			}
			break;
		case direction::down:
			if (App->object->GetLogic(logic_height, { rect.x / 16 ,rect.y / 16 +4 }, true) == 0) {
				rect.y++;
			}
			break;
		case direction::left:
			if (App->object->GetLogic(logic_height, { (rect.x-1 )/ 16 -2 ,rect.y / 16 }, false) ==0) {
				rect.x--;
			}
			break;
		case direction::right:
			if (App->object->GetLogic(logic_height, { rect.x / 16 + 4,rect.y / 16 }, false) == 0) {
				rect.x++;
			}
			break;

		}
		iPoint new_tile_pos = { rect.x / 16,rect.y / 16 };
		if (tile_pos != new_tile_pos) {
			for (int i = 0; i < this->collider_tiles.size(); i++) {
				//if (App->player->loop_game_menu == false) {
					if (App->map->V_Colision[logic_height]->data != nullptr)
						App->map->V_Colision[logic_height]->data[(collider_tiles[i].y / 16) * App->map->data.width + (collider_tiles[i].x / 16)] = 0;
				//}
			}
			App->object->CreateColliders(*this);
		}
		
		this->collider->SetPos(rect.x, rect.y, logic_height);

	};
public:
	
};


#endif
