#ifndef _INVENTORY_
#define _INVENTORY_

#include "MainScene.h"



class S_Inventory : public MainScene {
public:
	~S_Inventory() {};


	bool Start();
	bool Update(); 
	bool Clean();

public:
	int x = 0;
	char* test;
};

#endif