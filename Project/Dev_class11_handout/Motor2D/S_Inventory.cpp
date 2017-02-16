#include "S_Inventory.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "j1Scene.h"
#include "p2Log.h"

bool S_Inventory::Start()
{
	LOG("Inventory Open");
	test = new char[20];
	return false;
}


bool S_Inventory::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
		App->scene->Hide();
	}
	return false;
}

bool S_Inventory::Clean()
{
	delete test;
	LOG("Inventory Test Deleted");
	return false;
}
