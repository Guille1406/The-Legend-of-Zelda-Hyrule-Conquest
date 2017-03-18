#include"j1Collision.h"
#include"j1App.h"
#include"j1Player.h"
#include"j1Render.h"
j1Collision::j1Collision()
{
	//for (uint i = 0; i < colliders.size(); ++i)
		//colliders[i] = nullptr;

	matrix[collider_link][collider_zelda] = true;
	matrix[collider_zelda][collider_link] = true;
	matrix[collider_button][collider_link] = true;
	matrix[collider_link][collider_button] = true;
	matrix[collider_link][collider_change_height] = true;
	matrix[collider_change_height][collider_link] = true;
	matrix[collider_zelda][collider_change_height] = true;
	matrix[collider_change_height][collider_zelda] = true;
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::Start()
{

	// CHANGE THIS
	/*matrix_colliders.push_back(App->player->Link->allow_collision);
	matrix_colliders.push_back(App->player->Zelda->allow_collision);

	matrix_colliders.push_back(App->player->Zelda->allow_collision);
	matrix_colliders.push_back(App->player->Zelda->allow_collision);
	matrix_colliders.push_back(App->player->Zelda->allow_collision);
	matrix_colliders.push_back(App->player->Zelda->allow_collision);*/
	return true;
}

bool j1Collision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < colliders.size(); ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
	
	return true;
	}




// Called before render is available
bool j1Collision::Update(float dt)
{
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < colliders.size(); ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
				{
				
					c1->callback->OnCollision(c1, c2);
						//App->render->Blit(App->player->graphics, App->player->PreviousPos.x, App->player->PreviousPos.y-1, &(App->player->current_animation->GetCurrentFrame()));

				}


				if (matrix[c2->type][c1->type] && c2->callback)
				{
					c2->callback->OnCollision(c2, c1);
				}
				
			}
		}
	}

	DebugDraw();

	return true;
}

void j1Collision::DebugDraw()
{

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < colliders.size(); ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case collider_link: // green
			App->render->DrawQuad(colliders[i]->rect, 12, 198, 0, alpha);
			break;
		case collider_zelda: // pink
			App->render->DrawQuad(colliders[i]->rect, 245, 25, 219, alpha);
			break;
		case collider_chest: 
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, 255);
			break;
		case collider_button:
			App->render->DrawQuad(colliders[i]->rect, 150, 65, 255, 255);
			break;
		}
	}
}

// Called before quitting
bool j1Collision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < colliders.size(); ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type,Entity* parent, j1Module* callback)
{
	Collider* ret = nullptr;
	
			ret = new Collider(rect, type, parent, callback);
			colliders.push_back(ret);

	return ret;
}

bool j1Collision::EraseCollider(Collider* collider)
{
	if (collider != nullptr)
	{
		// we still search for it in case we received a dangling pointer
		for (uint i = 0; i < colliders.size(); ++i)
		{
			if (colliders[i] == collider)
			{
				collider->to_delete = true;
				break;
			}
		}
	}


	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}