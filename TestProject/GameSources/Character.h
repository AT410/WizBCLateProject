/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class TestCube;

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
		float f = 0.0f;
		int counter = 0;
		string m_key;
	};

	class ObjGui :public ImGuiObject
	{
	public:
		ObjGui(shared_ptr<TestCube> obj) 
		{
			m_Target = obj;
		}

		void OnInit()override;

		void OnGUI()override;

		void ChangeTarget(const shared_ptr<TestCube>& obj)
		{
			m_Target = obj;
		}

	private:
		weak_ptr<TestCube> m_Target;
	};

	class ObjOwner :public ImGuiObject
	{
	public:
		ObjOwner(const shared_ptr<ObjGui>& obj) 
		{
			m_wiget = obj;
		}

		void OnInit()override;

		void OnGUI()override;

	private:
		int m_objCount;
		weak_ptr<ObjGui> m_wiget;
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

		// -- �O���[�R�[�h --
		//int l_Add(lua_State* state);
	};
}
//end basecross
