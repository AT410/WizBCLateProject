/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;

		void OnDestroy()override;
	};

	class GameStage2 : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		GameStage2() :Stage() {}
		virtual ~GameStage2() {}
		//初期化
		virtual void OnCreate();
	};


}
//end basecross

