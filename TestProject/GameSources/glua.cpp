#include "stdafx.h"
#include "Project.h"

namespace luaTest
{
	

	int lGenerateEdit(lua_State* state)
	{
		auto key = luaL_checkstring(state, -1);

		ImApp::GetApp()->AddImGuiObject<TestGui>(key);
		return 0;
	}
}