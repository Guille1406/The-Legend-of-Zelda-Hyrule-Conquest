#pragma once
#ifndef _P_FIRE_H_
#define _P_FIRE_H_

#include "ParticleManager.h"
/*
#include "SceneElements.h"

class Particle;

class P_Fire
{
public:
	P_Fire(SceneElement* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint area, iPoint timelife, fPoint speed, Part_Direction p_direction, int num_particles, int num_textures, bool active_, Wind dir);

	~P_Fire();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void Update_position(iPoint* pos);

	void MoveParticles();

public:
	std::vector<Particle*> particle;
	SceneElement* element_to_follow = nullptr;
	//Num of particles
	int number_particles = 0;

	//test
	iPoint* object_follow = nullptr;

	//wind
	Wind dir_wind = Wind::Part_Wind_NULL;
	bool wind_speed = false;
	iPoint timelife = { 0,0 };

	//position
	fPoint pos = { 0.0f,0.0f };
	int size_rect = 0;
	int n_textures = 0;
	iPoint area = { 0,0 };

	//velocity
	fPoint speed = { 0.0f,0.0f };
	bool active = false;

	bool godelete = false;

};
*/
#endif /*_P_FIRE_H_*/