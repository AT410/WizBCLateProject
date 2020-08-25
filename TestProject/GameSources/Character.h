/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class TestCube;

	class DebugTest : public GameObject
	{
	public:
		//-- 構築 --
		DebugTest(const shared_ptr<Stage>& StagePtr);

		//-- 破棄 --
		virtual ~DebugTest() {}

		//-- 初期化 --
		void OnCreate()override;

		//-- 更新処理 --
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
	private:
		weak_ptr<TestCube> m_Target;
	};

	class Test : public GameObject
	{
	public:
		//-- 構築 --
		Test(const shared_ptr<Stage>& StagePtr);
		//-- 破棄 --
		virtual ~Test() {}

		//-- 初期化 --
		void OnCreate()override;

		//-- 更新処理 --
		void OnUpdate()override;

		// -- グルーコード --
		//int l_Add(lua_State* state);
	};
}
//end basecross
