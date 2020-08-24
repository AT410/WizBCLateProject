/*!
@Extention　インクルードガードBaseLua
*/
#pragma once
#include "stdafx.h"

#ifdef _BaseLua
namespace BaseLua
{
	class LuaFuncParam;

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

		wstring m_ActiveKey;

		lua_CFunction m_StateFunc;

		LuaApp();

		// -- エラー処理 --
		void ErrorFunction(const int ErrorCode,const string& MethodName);
	public:
		static unique_ptr<LuaApp, LuaAppDeleter>& CreateApp();

		static unique_ptr < LuaApp, LuaAppDeleter>& GetApp();

		static bool ChackApp();

		static void DeleteApp();

		void SetActiceState(const wstring& key);

		void CreateState(const wstring& Key, const bool DefLibLoadActive = true);
		//TODO:関数のセット
		void SetFunction(const wstring& StateKey,const string&FuncName, int(*Func)(lua_State* ));
		//TODO:関数実行エラー処理も
		void CallFunction(const string& FuncName, const shared_ptr<LuaFuncParam>& params, const int resultCount, shared_ptr<LuaFuncParam>& results);
		//TODO:ファイル実行エラー処理
		void DoFileFunction(const string& FileName);
	};
}
#endif // _BaseLua
