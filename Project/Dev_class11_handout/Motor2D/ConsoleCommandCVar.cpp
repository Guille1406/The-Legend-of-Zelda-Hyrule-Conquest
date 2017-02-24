#include "ConsoleCommandCVar.h"

const std::string* CVar::PrintCVar()
{
	const std::string* ret = nullptr;

	switch (type)
	{
	case CVar::CVar_int:
		ret = &std::string("%i", value.i);
		break;
	case CVar::CVar_float:
		ret = &std::string("%0.3f", value.f);
		break;
	case CVar::CVar_bool:
		ret = value.b ? &true_str : &false_str;
		break;
	case CVar::CVar_string:
		return &std::string(value.s);
	}

	return ret;
}

bool CVar::SetValueFromString(const std::string* new_value)
{
	bool ret = false;

	switch (type)
	{
	case CVar::CVar_int:
	{
		int v = atoi(new_value->c_str());
		if (ret = (v != value.i))
			value.i = v;
		break;
	}
	case CVar::CVar_float:
	{
		float v = atof(new_value->c_str());
		if (ret = (v != value.f))
			value.f = v;
		break;
	}
	case CVar::CVar_bool:
	{
		bool v = !((new_value->c_str() == true_str) || (new_value->c_str() == false_str));
		if (ret = (v != value.b))
			value.b = v;
		break;
	}
	case CVar::CVar_string:
		if (ret = (*new_value != value.s))
			value.s = new_value->c_str();
		break;
	}
	return ret;
}