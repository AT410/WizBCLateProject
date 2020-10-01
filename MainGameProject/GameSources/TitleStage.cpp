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
	void TitleStage::CreateViewLight() {
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



	void TitleStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

#ifdef _BSImGui
			ImApp::GetApp()->AddImGuiObject<SystemGui>();
#endif // _BSImGui

		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {

	}

}
//end basecross
