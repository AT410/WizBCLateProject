/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class DebugTest : public GameObject
	{
	public:
		//-- �\�z --
		DebugTest(const shared_ptr<Stage>& StagePtr);

		//-- �j�� --
		virtual ~DebugTest() {}

		//-- ������ --
		void OnCreate()override;

		//-- �X�V���� --
		void OnUpdate()override;

	private:

	};

	class TestGui :public ImGuiObject
	{
	public:
		TestGui(const string& key)
			:ImGuiObject(),m_key(key)
		{

		}

		void OnInit()override;

		void OnGUI()override;

	private:
		string m_key;
	};

	class Test : public GameObject
	{
	public:
		//-- �\�z --
		Test(const shared_ptr<Stage>& StagePtr);
		//-- �j�� --
		virtual ~Test() {}

		//-- ������ --
		void OnCreate()override;

		//-- �X�V���� --
		void OnUpdate()override;

		void OnDestroy()override;

		// -- �O���[�R�[�h --
		//int l_Add(lua_State* state);
	private:
		bool m_cosole;
		lua_State *m_state;
	};
}
//end basecross
