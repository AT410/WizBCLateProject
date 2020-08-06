
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			wstring mediaPath;
			App::GetApp()->GetDataDirectory(mediaPath);
			App::GetApp()->RegisterTexture(L"TestTex", mediaPath + L"TexMask.png");

			// -- フォントを読み込む --
			auto fontRes = make_shared<FontResources>();

			wstring path;
			App::GetApp()->GetDataDirectory(path);
			path += L"fonts/";

			fontRes->AddFontFile(path + L"001Shirokuma-Regular.otf");
			fontRes->AddFontFile(path + L"AiharaHudemojiKaisho3.00.ttf");
			fontRes->AddFontFile(path + L"AiharaHudemojiKaisho3.ttf");
			fontRes->AddFontFile(path + L"memoir.otf");
			fontRes->AddFontFile(path + L"Zomzi.TTF");

			App::GetApp()->SetFontResources(fontRes);
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
			
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
