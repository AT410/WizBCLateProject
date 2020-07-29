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

}
//end basecross
