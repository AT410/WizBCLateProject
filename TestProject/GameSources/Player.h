/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class TestCube : public GameObject
	{
	public:
		//-- 構築 --
		TestCube(const shared_ptr<Stage>& StagePtr);

		//-- 破棄 --
		virtual ~TestCube() {}

		//-- 初期化 --
		void OnCreate()override;

		//-- 更新処理 --
		void OnUpdate()override;

		void SetMeshCol(const Col4 col);

		Col4 GetMeshCol();

	private:

	};

}
//end basecross

