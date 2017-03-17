#ifndef _ENTITY_
#define _ENTITY_
#include "j1App.h"
#include "j1Module.h"


class j1Entity : public j1Module {

public:
	j1Entity() {};
	~j1Entity() {};

	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

	void LoadEntities();

public: 

	
};


#endif