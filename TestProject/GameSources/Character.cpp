/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	Test::Test(const shared_ptr<Stage>& StagePtr)
		:GameObject(StagePtr),m_cosole(false)
	{
		m_state = luaL_newstate();
	}

	void Test::OnCreate()
	{
		// コンソールを作成する
		AllocConsole();
		// 標準入出力に割り当てる
		FILE* fp = NULL;
		// 昔のコード
		//freopen("CONOUT$", "w", stdout);
		//freopen("CONIN$", "r", stdin);
		// 現在のコード
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONIN$", "r", stdin);
		wcout << L"テストですよ" << endl;

		luaL_openlibs(m_state);

		// Luaファイルを開いて読み込み
		// これでLuaステートに関数が登録されます
		//if (luaL_dofile(m_state, "test.lua")) 
		//{
		//	printf("%s\n", lua_tostring(m_state, lua_gettop(m_state)));
		//	lua_close(m_state);
		//	return;
		//}

		lua_pushboolean(m_state, 1);
		lua_pushnumber(m_state, 100.0);
		lua_pushstring(m_state, "Marupeke");
		
		

		int ret= luaL_dostring(m_state, "print('hello lua script!!')");;
		if (ret != 0)
		{
			cout << "Error:" << lua_tostring(m_state, -1) << endl;
			lua_pop(m_state, 1);
		}

		cout << "Test:" << lua_tostring(m_state, -1) << endl;

		FreeConsole();


		m_cosole = true;
	}

	void Test::OnUpdate()
	{
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_RETURN]&&m_cosole)
		{
			FreeConsole();
			m_cosole = false;
		}
	}

	void Test::OnDestroy()
	{
		lua_close(m_state);
	}
}
//end basecross
