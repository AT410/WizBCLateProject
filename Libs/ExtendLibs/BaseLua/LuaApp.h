/*!
@Extention�@�C���N���[�h�K�[�hBaseLua
*/
#pragma once
#include "stdafx.h"

#ifdef _BaseLua
namespace BaseLua
{
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

		LuaApp();
	public:
		static unique_ptr<LuaApp, LuaAppDeleter>& CreateApp();

		static unique_ptr < LuaApp, LuaAppDeleter>& GetApp();

		static bool ChackApp();

		static void DeleteApp();

		void CreateState(const wstring& Key, const bool DefLibLoadActive = true);
		//TODO:�֐��̃Z�b�g
		void SetFunction(const wstring& StateKey,const string&FuncName, int(*Func)(lua_State* ));
	};
}
#endif // _BaseLua
