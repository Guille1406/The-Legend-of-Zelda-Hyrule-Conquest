#pragma once
#ifndef _P_FIREWORK_H_
#define _P_FIREWORK_H_

#include "ParticleManager.h"
/*
#include "SceneElements.h"

#define MULITFIREWORK 4

class Particle;

class P_Firework
{
public:
	P_Firework(SceneElement* element, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint timelife, fPoint speed, Part_Direction p_direction, int num_particles, int num_textures, iPoint next_textures, iPoint last_textures);
	~P_Firework();

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
	int number_multifirework = 0;

	//iPoint object
	iPoint* object_follow = nullptr;

	//timelife
	iPoint timelife = { 0,0 };


	//textures
	iPoint next_textures = { 0,0 };
	iPoint last_textures = { 0,0 };

	//position
	fPoint pos = { 0.0f,0.0f };
	int size_rect = 0;
	int n_textures = 0;

	SDL_Rect i_rect = { 0,0,0,0 };

	//velocity
	fPoint speed = { 0.0f,0.0f };

	bool godelete = false;

};
*/
#endif /*_P_FIREWORK_H_*/