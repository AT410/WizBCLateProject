/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace structdata;
using namespace enumdata;

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		shared_ptr<Camera> m_ptrCamera;

		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		TitleStage() :Stage() {
		}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//ゲッター・セッター


		//処理

	};


}
//end basecross

