#include "j1Enemy.h"
#include"Green_Enemy.h"
#include"j1Collision.h"
bool j1Enemy::Start()
{
	return true;
}

bool j1Enemy::PreUpdate()
{
	return true;
}

bool j1Enemy::Update(float)
{
	return true;
}

bool j1Enemy::PostUpdate()
{
	return true;
}

bool j1Enemy::CleanUp()
{
	return true;
}

Green_Enemy * j1Enemy::Create_GreenEnemy(char* type_name, pugi::xml_node object)
{
	Green_Enemy* ret = nullptr;
	if (!strcmp(type_name, "green enemy")) {
	
		SDL_Rect rect={ 150,150,50,50 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, this);
		ret->logic_height = 1;
		ret->active = true;
		//problems with constructors
		//ret = new Green_Enemy(ret);
	}

	return ret;
}
