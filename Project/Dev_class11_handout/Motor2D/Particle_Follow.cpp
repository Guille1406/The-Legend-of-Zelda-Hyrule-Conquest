#include "Particle_Follow.h"
#include "Particle.h"
#include "j1Player.h"
#include "j1Window.h"
#include "j1Render.h"
/*
P_Follow::P_Follow(SceneElement* element, iPoint* object, SDL_Rect initial_rect, iPoint area_, iPoint timelife_, int num_textures, int num_particles, bool active_, bool mouse)
{
	//TODO 3:---------------------------------------------------------------------------------------
	//Check if entity (element) is different from nullptr
	//Then set the position of the entity and the pointer iPoint (object) to nullptr and entity pointer has created in .h
	if (element != nullptr)
	{
		pos.x = element->position.x;
		pos.y = element->position.y;
		element_to_follow = element;
		object_follow = nullptr;
	}
	//Otherwise, do it backwards. //element == nullptr and position = object ------
	else
	{
		pos.x = object->x;
		pos.y = object->y;
		object_follow = object;
		element_to_follow = nullptr;
	}
	//--------------------------------------------------------------------------------------------
	area = area_;
	number_particles = num_particles;
	godelete = false;
	isMouse = mouse;
	active = active_;
	timelife = timelife_;
	n_textures = num_textures;
	size_rect = initial_rect.w;
	for (int i = 0; i < num_particles; i++)//
	{
		//TODO 4: ------------------------------------------------------------------------------
		//In this TODO we need open Particle.h and see the constructor
		//Create a new Particle and pushback in vector.
		//TIPS: Speed = fPoint(0,0) // Part_Direction = P_NON
		Particle* temp = new Particle(pos, area, timelife, fPoint(0,0), Part_Direction::Part_Direc_NULL, initial_rect, size_rect, num_textures, active_);
		particle.push_back(temp);
		//-------------------------------------------------------------------------------
	}
}

P_Follow::~P_Follow()
{
}

bool P_Follow::Update(float dt)
{
	//TODO 5:-------------------------------------------------------------
	//Here we have to Update the position.
	//Check if the entity is diferent nullptr. On the contrary, use Update_position(iPoint* pos);
	if (element_to_follow != nullptr)
	{
		pos.x = element_to_follow->position.x;
		pos.y = element_to_follow->position.y;
	}
	else
	{
		Update_position(object_follow);
	}

	//-------------------------------------------------------------------------------
	return true;
}

bool P_Follow::PostUpdate()
{
	render(pos);
	return true;
}

void P_Follow::render(fPoint pos)
{
	if (active)
	{
		//TODO 6: ---------------------------------------------------------------------------
		//Iterate the filled vector, First Comprovated if the particle is Dead, and then use particle[i]->Modify();
		//TIPS: Use number_particles!! // iPoint num_tex -> (0, n_textures)!
		for (int i = 0; i < number_particles; i++)
		{
			if (particle[i]->isDead())
			{
				particle[i]->Modify(pos, area, timelife, iPoint(0, n_textures));
			}
		}
		//---------------------------------------------------------------------------
	}

	//TODO 7: -------------------------------------------------------------------
	//Draw particles
	//Iterate the filled vector, Call the functioon render();
	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->render();
	}
	//-------------------------------------------------------------------------------
}

void P_Follow::Update_position(iPoint* element)
{
	if (isMouse == false)
	{
		pos.x = element->x;
		pos.y = element->y;
	}
	else
	{
		pos.x = element->x - App->render->camera.x / 2;
		pos.y = element->y - App->render->camera.y / 2;
	}

	LOG("%i - %i", element->x, element->y);
}
*/