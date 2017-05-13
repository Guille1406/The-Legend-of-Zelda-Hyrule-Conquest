#include "Particle_Fire.h"
#include "Particle.h"
#include "j1Window.h"
#include "j1Render.h"

P_Fire::P_Fire(Arrow* element, iPoint* object, iPoint position_static, SDL_Rect initial_rect, iPoint area_, iPoint timelife_, fPoint speed_particle, Part_Direction p_direction, int num_particles, int num_textures, bool active_, Wind dir)
{
	if (element != nullptr)
	{
		pos.x = element->pos.x;
		pos.y = element->pos.y;
		arrow_to_follow = element;
		object = nullptr;
	}
	else if (object != nullptr)
	{
		pos.x = object->x;
		pos.y = object->y;
		object_follow = object;
		arrow_to_follow = nullptr;
	}
	else
	{
		pos.x = position_static.x;
		pos.y = position_static.y;
		object_follow = nullptr;
		arrow_to_follow = nullptr;
	}

	speed = speed_particle;

	if (dir != Wind::Part_Wind_NULL)
		wind_speed = true;
	else
		wind_speed = false;


	//
	area = area_;
	timelife = timelife_;
	dir_wind = dir;
	number_particles = num_particles;
	godelete = false;
	active = active_;
	n_textures = num_textures;
	size_rect = initial_rect.w;
	for (int i = 0; i < num_particles; i++)//
	{
		Particle* temp = new Particle(pos, area, timelife, speed, p_direction, initial_rect, size_rect, n_textures, true);
		particle.push_back(temp);
	}
}

P_Fire::~P_Fire()
{
	for (std::vector<Particle*>::iterator item = particle.begin(); item != particle.cend(); ++item)
		RELEASE(*item);
	particle.clear();
}

bool P_Fire::Update(float dt)
{
	if (arrow_to_follow != nullptr && object_follow == nullptr)
	{
		pos.x = arrow_to_follow->pos.x;
		pos.y = arrow_to_follow->pos.y;
	}
	else if (arrow_to_follow == nullptr && object_follow != nullptr)
	{
		Update_position(object_follow);
	}
	else
	{

	}

	MoveParticles();


	return true;
}

bool P_Fire::PostUpdate()
{
	render(pos);
	return true;
}

void P_Fire::render(fPoint pos)
{
	if (active)
	{
		//Check if the particle dead
		for (int i = 0; i < number_particles; i++)
		{
			if (particle[i]->isDead())
			{
				particle[i]->Modify(pos, area, timelife, iPoint(0, n_textures));
			}
		}
	}

	//Draw particles
	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->render();
	}
}

void P_Fire::MoveParticles()
{
	for (int i = 0; i < number_particles; i++)
	{
		float temp = App->GetDT();
		particle[i]->Move(fPoint(particle[i]->GetSpeed().x * temp, particle[i]->GetSpeed().y * temp), dir_wind, wind_speed);
	}
}

void P_Fire::Update_position(iPoint* element)
{
	pos.x = element->x ;
	//int scale = App->win->GetScale();
	//int temp = App->render->camera.y / scale;
	pos.y = element->y ;
}