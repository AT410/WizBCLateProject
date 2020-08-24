#include "stdafx.h"

#ifdef _BaseLua
namespace BaseLua
{
	// -- インスタンス宣言 --
	unique_ptr<LuaApp, LuaApp::LuaAppDeleter> LuaApp::m_instance;

	LuaApp::LuaApp()
		:m_ActiveKey(L""), m_StateFunc(NULL)
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
				throw(LuaException(L"LuaAppが作成されていません。", 
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
		try {
			// -- ステートの確認 --
			if (m_StateMap.find(Key) != m_StateMap.end())
			{
				throw(LuaException(L"対象のステートが作成されています。",
					L"file:LuaApp.cpp",
					L"Method:LuaApp::CreateState"));
			}

			lua_State *state = luaL_newstate();

			if (DefLibLoadActive)
			{
				luaL_openlibs(state);
			}
			m_ActiveKey = Key;

			if (m_StateFunc == NULL)
			{
				lua_getglobal(state, "debug");
				if (!lua_isnil(state, -1))
				{
					lua_getfield(state, -1, "traceback");
					m_StateFunc = lua_tocfunction(state, -1);
					lua_pop(state, 1);
				}
				lua_pop(state, 1);
			}

			m_StateMap[Key] = state;
		}
		catch (...)
		{
			throw;
		}
	}

	void LuaApp::SetActiceState(const wstring& key)
	{
		try 
		{
			// -- ステートの確認 --
			if (m_StateMap.find(key) == m_StateMap.end())
			{
				throw(LuaException(L"対象のステートが作成されていません。",
					L"file:LuaApp.cpp",
					L"Method:LuaApp::SetFunction"));
			}

			m_ActiveKey = key;

		}
		catch (...)
		{
			throw;
		}
	}

	// -- Luaに関数を流す --
	void LuaApp::SetFunction(const wstring&key, const string&FuncName, int(*Func)(lua_State*))
	{
		try {
			// -- ステートの確認 --
			if (m_StateMap.find(key) == m_StateMap.end())
			{
				throw(LuaException(L"対象のステートが作成されていません。",
					L"file:LuaApp.cpp",
					L"Method:LuaApp::SetFunction"));
			}
			auto &state = m_StateMap[key];
			lua_register(state, FuncName.c_str(), Func);
		}
		catch (...)
		{
			throw;
		}
	}

	void LuaApp::CallFunction(const string& FuncName,
		const shared_ptr<LuaFuncParam>& params, const int resultCount, shared_ptr<LuaFuncParam>& results)
	{
		try
		{
			auto &state = m_StateMap[m_ActiveKey];
			
			// -- 先頭のサイズを保持 --
			int top = lua_gettop(state);

			// -- エラー関数を積む --
			lua_pushcfunction(state, m_StateFunc);
			lua_getglobal(state, FuncName.c_str());//<-関数を積む

			// -- 引数設定 --
			for (auto param : params->GetItems())
			{
				switch (param.GetType())
				{
				case LuaParamType::Nil:
					lua_pushnil(state);
					break;
				case LuaParamType::String:
					lua_pushstring(state, param.GetStr().c_str());
					break;
				case LuaParamType::Number:
					lua_pushinteger(state, param.GetNumber());
					break;
				case LuaParamType::Boolean:
					lua_pushboolean(state, param.GetFlag());
					break;
				default:
					break;
				}
			}
			// -- 関数実行 --
			int ret = lua_pcall(state, params->Count(), resultCount, -2);

			if (ret != 0)
			{
				auto ErrorStr = lua_tostring(state, -1);
				
				ErrorFunction(ret, "CallFunction\n"+string(ErrorStr));
				lua_settop(state, top);
				return;
			}
			else 
			{
				for (int i = 0; i < resultCount; i++) 
				{
					switch (lua_type(state, -1))
					{
					case LUA_TNUMBER:
						int num = lua_tointeger(state, -1);
						results->SetNumber(num);
						lua_pop(state, 1);
						break;
					}
				}
				lua_settop(state, top);
				return;
			}
		}
		catch (...)
		{
			throw;
		}
	}

	void LuaApp::DoFileFunction(const string& FuncName)
	{
		try
		{
			auto &state = m_StateMap[m_ActiveKey];

			if (luaL_dofile(state, FuncName.c_str()))
			{
				auto ErrorStr = lua_tostring(state, -1);
				MessageBoxA(0, ErrorStr, 0, 0);
				lua_close(state);
				return;
			}
		}
		catch (...)
		{
			throw;
		}
	}

	void LuaApp::ErrorFunction(const int ErrorCode,const string& MethodName)
	{
		string ErrorMsg = "";

		switch (ErrorCode)
		{
		case LUA_ERRSYNTAX:	//<-構文エラー
			ErrorMsg += "Lua構文エラー";
			ErrorMsg += "file:LuaApp.cpp";
			ErrorMsg += "Method:LuaApp::" + MethodName;
			break;
		case LUA_ERRMEM:	//<-メモリ割り当てエラー
			ErrorMsg += "メモリの割り当てに失敗しました";
			ErrorMsg += "file:LuaApp.cpp";
			ErrorMsg += "Method:LuaApp::" + MethodName;
			break;
		case LUA_ERRFILE:	//<-ファイルエラー
			ErrorMsg += "対象のファイル読み込めません";
			ErrorMsg += "file:LuaApp.cpp";
			ErrorMsg += "Method:LuaApp::" + MethodName;
			break;
		case LUA_ERRRUN:	//関数実行時エラー
			ErrorMsg += "関数の実行に失敗しました";
			ErrorMsg += "file:LuaApp.cpp";
			ErrorMsg += "Method:LuaApp::" + MethodName;
			break;
		case LUA_ERRERR:	//エラー関数中実行エラー
			ErrorMsg += "エラー関数実行エラー";
			ErrorMsg += "file:LuaApp.cpp";
			ErrorMsg += "Method:LuaApp::" + MethodName;
			break;
		default:
			return;
		}

		MessageBoxA(0, ErrorMsg.c_str(), 0, 0);
	}
}
#endif // _BaseLua
