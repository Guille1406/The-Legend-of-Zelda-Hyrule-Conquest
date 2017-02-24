#ifndef __CONSOLECOMMANDCVAR_H__
#define __CONSOLECOMMANDCVAR_H__

#include "j1Module.h"

struct Command
{
	std::string name;
	uint min_arguments = 0;
	uint max_arguments = 0;
	j1Module* listener = nullptr;
};

struct CVar
{
	union
	{
		int i;
		float f;
		bool b;
		const char* s;
	} value;

	enum
	{
		CVar_int,
		CVar_float,
		CVar_bool,
		CVar_string
	} type;

	std::string name;
	bool read_only = false;
	j1Module* listener = nullptr;

	const std::string* PrintCVar();
	bool SetValueFromString(const std::string* new_value);
};

#endif // __CONSOLECOMMANDCVAR_H__