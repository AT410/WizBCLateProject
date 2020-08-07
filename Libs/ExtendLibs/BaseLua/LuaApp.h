/*!
@Extention　インクルードガードBaseLua
*/
#pragma once
#include "stdafx.h"

#ifdef _BaseLua
namespace BaseLua
{
	//----------------------------------------------------------------------------
	//LuaApp
	//----------------------------------------------------------------------------
	//TODO:Luaステートの管理、実行読み込み、生成
	class LuaApp
	{
	private:
		struct LuaAppDeleter
		{
			void operator()(LuaApp *p) { delete p; }
		};

		static unique_ptr<LuaApp, LuaAppDeleter> m_instance;//<-インスタンス

		map<wstring, lua_State*> m_StateMap;				//<-ステート配列

		LuaApp();
	public:
		static unique_ptr<LuaApp, LuaAppDeleter>& CreateApp();

		static unique_ptr < LuaApp, LuaAppDeleter>& GetApp();

		static bool ChackApp();

		static void DeleteApp();

		void CreateState(const wstring& Key, const bool DefLibLoadActive = true);
		//TODO:関数のセット
		void SetFunction(const wstring& StateKey,const string&FuncName, int(*Func)(lua_State* ));
	};
}
#endif // _BaseLua
