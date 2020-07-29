/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

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

	private:
		bool m_cosole;
		lua_State *m_state;
	};
}
//end basecross
