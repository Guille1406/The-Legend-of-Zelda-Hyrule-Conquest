#pragma once
#ifndef _P_EXPLOSION_H_
#define _P_EXPLOSION_H_

#include "ParticleManager.h"
/*
#include "SceneElements.h"

class Particle;

class P_Explosion
{
public:
	P_Explosion(SceneElement* element, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, Explosion_Type type, iPoint perimeter, iPoint timelife, fPoint speed, Part_Direction p_direction, int num_particles, int num_textures);
	~P_Explosion();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void MoveParticles();

public:
	std::vector<Particle*> particle;
	SceneElement* arrow_to_follow = nullptr;
	//Num of particles
	int number_particles = 0;
	Explosion_Type type_explosion = Explosion_Type::NOTHING;
	//test
	iPoint* object_follow = nullptr;

	//timelife
	iPoint timelife = { 0,0 };

	//position
	fPoint pos = { 0.0f,0.0f };
	int size_rect = 0;
	int n_textures = 0;

	//velocity
	fPoint speed = { 0.0f,0.0f };
	bool active = false;

	bool godelete = false;

};
*/
#endif /*_P_EXPLOSION_H_*/