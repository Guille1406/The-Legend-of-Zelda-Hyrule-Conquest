#ifndef _FIRE_PARTICLES_
#define _FIRE_PARTICLES_
#include "j1Object.h"
#include "Character.h"
#include <time.h>

class Fire_Particles : public Object {
public:
	Fire_Particles() {

	}
	Fire_Particles(const Fire_Particles& obj) {
		rect = obj.rect;
		type = obj.type;
		active = obj.active;
		name = obj.name;
		active = true;
		logic_height = obj.logic_height;
		collider_tiles = obj.collider_tiles;
		big_particle_fire = obj.big_particle_fire;
		direction = obj.direction;
	}
	~Fire_Particles() {

	}

	void Action() {

	};
public:
	bool big_particle_fire;
	int direction;
};


#endif