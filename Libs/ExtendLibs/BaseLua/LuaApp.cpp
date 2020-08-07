#include "stdafx.h"

#ifdef _BaseLua
namespace BaseLua
{
	// -- インスタンス宣言 --
	unique_ptr<LuaApp, LuaApp::LuaAppDeleter> LuaApp::m_instance;

	LuaApp::LuaApp()
	{

	}

	unique_ptr<LuaApp, LuaApp::LuaAppDeleter>& LuaApp::CreateApp()
	{
		try
		{
			if (m_instance.get() == 0)
			{
				m_instance.reset(new LuaApp());
			}
			return m_instance;
		}
		catch (...)
		{
			throw;
		}
	}

	unique_ptr<LuaApp, LuaApp::LuaAppDeleter>& LuaApp::GetApp()
	{
		try 
		{
			if (m_instance.get() == 0)
			{
				throw(basecross::BaseException(L"LuaAppが作成されていません。", 
					L"file:LuaApp.cpp", 
					L"Method:LuaApp::GetApp"));
			}
			return m_instance;
		}
		catch (...)
		{
			throw;
		}
	}

	bool LuaApp::ChackApp()
	{
		if (m_instance == 0)
		{
			return false;
		}
		return true;
	}

	void LuaApp::DeleteApp()
	{
		if (m_instance != 0)
		{
			m_instance.reset();
		}
	}

	void LuaApp::CreateState(const wstring& Key, const bool DefLibLoadActive)
	{
		// -- ステートの確認 --
		if (m_StateMap.find(Key) != m_StateMap.end())
		{
			throw(basecross::BaseException(L"対象のステートが作成されています。",
				L"file:LuaApp.cpp",
				L"Method:LuaApp::CreateState"));
		}

		lua_State *state = luaL_newstate();

		if (DefLibLoadActive)
		{
			luaL_openlibs(state);
		}

	}

	// -- Luaに関数を流す --
	void LuaApp::SetFunction(const wstring&key, const string&FuncName, int(*Func)(lua_State*))
	{
		// -- ステートの確認 --
		if (m_StateMap.find(key) == m_StateMap.end())
		{
			throw(basecross::BaseException(L"対象のステートが作成されていません。",
				L"file:LuaApp.cpp",
				L"Method:LuaApp::SetFunction"));
		}
		auto &state = m_StateMap[key];
		lua_register(state, FuncName.c_str(), Func);
	}
}
#endif // _BaseLua
