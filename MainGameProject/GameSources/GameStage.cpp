/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -50.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		m_ptrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(m_ptrCamera);
		m_ptrCamera->SetEye(eye);
		m_ptrCamera->SetAt(at);

		//カメラの遠近法を切る
		m_ptrCamera->SetPers(false);

		//仮の値を設定
		float width = 3.2 * 12;
		float height = 2.0 * 12;

		//カメラが映す範囲を設定
		m_ptrCamera->SetWidth(width);
		m_ptrCamera->SetHeight(height);
		//視野角を設定
		m_ptrCamera->SetFovY(1.0f);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			auto charaObjData = structdata::ObjectData(Vec3(0.0f), Vec3(1.0f), Vec3(0.0f),0, L"thumbnail.png");

			//描画の確認用に画像を生成
			AddGameObject<ObjectBase>(charaObjData);
			AddGameObject<MapCreator>();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {

	}

	void GameStage::UpDateCameraPos(Vec2 at) {
		Vec3 setCameraEye = Vec3(at.x, at.y, m_ptrCamera->GetEye().z);
		Vec3 setCameraAt = Vec3(at.x, at.y, m_ptrCamera->GetAt().z);

		m_ptrCamera->SetEye(setCameraEye);
		m_ptrCamera->SetAt(setCameraAt);
	}

}
//end basecross
