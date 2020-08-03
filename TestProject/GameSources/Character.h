/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

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
		string m_key;
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

		void OnDestroy()override;

		// -- グルーコード --
		//int l_Add(lua_State* state);
	private:
		bool m_cosole;
		lua_State *m_state;
	};
}
//end basecross
