#pragma once
#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "j1Module.h"
#include "j1Scene.h"
#include "P_Zelda.h"

#define MAX_TIMELIFE 255
#define NORMAL_SPEED_Y 180

enum Wind {
	Part_Wind_UP,
	Part_Wind_DOWN,
	Part_Wind_LEFT,
	Part_Wind_RIGHT,
	Part_Wind_NULL
};

enum Part_Direction {
	Part_Direc_UP,
	Part_Direc_DOWN,
	Part_Direc_LEFT,
	Part_Direc_RIGHT,
	Part_Direc_RANDOM_X,
	Part_Direc_RANDOM_Y,
	Part_Direc_RANDOM,
	Part_Direc_RANDOM_FIREWORK,
	Part_Direc_NULL
};

enum Explosion_Type {
	CIRCLE,
	SEMICIRCLE,
	CROSS,
	RANDOM,
	NOTHING
};

class P_Follow;
class P_Fire;
class P_Explosion;
class P_Firework;

class ParticleManager : public j1Module
{
public:

	ParticleManager();

	// Destructor
	~ParticleManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//FUNCTIONS TO CREATE

	//Create & Delete Follow Group
	/*
	void CreateFollow_P(SceneElement* arrow_to_follow, iPoint* object_follow, SDL_Rect initial_rect, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, int num_textures = 4, int num_particles = 20, bool active_ = false, bool isMouse = false);
	bool DeleteFollow_p(P_Follow* group);
	*/
	//Create & DeleteFire Group
	void CreateFire_Particle(Arrow* arrow_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, Part_Direction p_direction = Part_Direction::Part_Direc_NULL, int num_particles = 20, int num_textures = 4, bool active_ = false, Wind dir = Wind::Part_Wind_NULL);
	bool DeleteFire_p(P_Fire* group);
	/*
	//Create & Delete Explosion Group
	void CreateExplosion_Particle(SceneElement* arrow_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, Explosion_Type type, iPoint perimeter = { 20, 20 }, iPoint timelife = { 20,10 }, fPoint speed = { 0,0 }, Part_Direction p_direction = Part_Direction::Part_Direc_NULL, int num_particles = 20, int num_textures = 4);
	bool DeleteExplosion_p(P_Explosion* group);

	//Create & Delete Firework Group
	void CreateFirework_Particle(SceneElement* arrow_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, Part_Direction p_direction = Part_Direction::Part_Direc_NULL, int num_particles = 20, int num_textures = 4, iPoint next_textures = { 0, 4 }, iPoint last_textures = { 0, 4 });
	bool DeleteFirework_p(P_Firework* group);
	/**/

public:

	std::list<P_Follow*> Group_Follow;
	std::list<P_Fire*> Group_Fire;
	std::list<P_Explosion*> Group_Explosion;
	std::list<P_Firework*> Group_Firework;

	SDL_Texture* atlas_particle = nullptr;
};

#endif // __PARTICLESYSTEM_H__