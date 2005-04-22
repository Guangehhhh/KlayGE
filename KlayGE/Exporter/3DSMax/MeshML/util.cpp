#include <max.h>
#include <bipexp.h>

#include "util.hpp"

std::string tstr_to_str(std::basic_string<TCHAR> const & tstr)
{
#ifdef UNICODE
	std::vector<char> temp(wcstombs(NULL, tstr.c_str(), 0));
	wcstombs(&temp[0], tstr.c_str(), temp.size());
	return std::string(temp.begin(), temp.end());
#else
	return tstr;
#endif
}

bool is_mesh(INode* node)
{
	if (NULL == node)
	{
		return false;
	}

	ObjectState os = node->EvalWorldState(0);
	if (NULL == os.obj)
	{
		return false;
	}

	if (os.obj->SuperClassID() == GEOMOBJECT_CLASS_ID)
	{
		if (os.obj->ClassID() != Class_ID(TARGET_CLASS_ID, 0))
		{
            return true;
		}
	}
	
	return false;
}

bool is_bone(INode* node)
{
	if (NULL == node)
	{
		return false;
	}

	ObjectState os = node->EvalWorldState(0);
	if (NULL == os.obj)
	{
		return false;
	}

	if (os.obj->SuperClassID() == HELPER_CLASS_ID)
	{
		return true;
	}

	Control* ctl = node->GetTMController();
	if ((ctl->ClassID() == BIPSLAVE_CONTROL_CLASS_ID)
		|| (ctl->ClassID() == BIPBODY_CONTROL_CLASS_ID))
	{
		return true;
	}

	return false;
}
