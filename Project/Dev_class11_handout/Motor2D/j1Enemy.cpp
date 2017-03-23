#include "j1Enemy.h"

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

Enemy * j1Enemy::CreateEnemy(char *, pugi::xml_node)
{
	return new Enemy();
}
