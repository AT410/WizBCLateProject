/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
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
		// �R���\�[�����쐬����
		AllocConsole();
		// �W�����o�͂Ɋ��蓖�Ă�
		FILE* fp = NULL;
		// �̂̃R�[�h
		//freopen("CONOUT$", "w", stdout);
		//freopen("CONIN$", "r", stdin);
		// ���݂̃R�[�h
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONIN$", "r", stdin);
		wcout << L"�e�X�g�ł���" << endl;

		luaL_openlibs(m_state);

		// Lua�t�@�C�����J���ēǂݍ���
		// �����Lua�X�e�[�g�Ɋ֐����o�^����܂�
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
