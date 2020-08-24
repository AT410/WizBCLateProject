/*!
@Extention�@�C���N���[�h�K�[�hBaseLua
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
	//TODO:Lua�X�e�[�g�̊Ǘ��A���s�ǂݍ��݁A����
	class LuaApp
	{
	private:
		struct LuaAppDeleter
		{
			void operator()(LuaApp *p) { delete p; }
		};

		static unique_ptr<LuaApp, LuaAppDeleter> m_instance;//<-�C���X�^���X

		map<wstring, lua_State*> m_StateMap;				//<-�X�e�[�g�z��

		wstring m_ActiveKey;

		lua_CFunction m_StateFunc;

		LuaApp();

		// -- �G���[���� --
		void ErrorFunction(const int ErrorCode,const string& MethodName);
	public:
		static unique_ptr<LuaApp, LuaAppDeleter>& CreateApp();

		static unique_ptr < LuaApp, LuaAppDeleter>& GetApp();

		static bool ChackApp();

		static void DeleteApp();

		void SetActiceState(const wstring& key);

		void CreateState(const wstring& Key, const bool DefLibLoadActive = true);
		//TODO:�֐��̃Z�b�g
		void SetFunction(const wstring& StateKey,const string&FuncName, int(*Func)(lua_State* ));
		//TODO:�֐����s�G���[������
		void CallFunction(const string& FuncName, const shared_ptr<LuaFuncParam>& params, const int resultCount, shared_ptr<LuaFuncParam>& results);
		//TODO:�t�@�C�����s�G���[����
		void DoFileFunction(const string& FileName);
	};
}
#endif // _BaseLua
