
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			wstring mediaPath;
			App::GetApp()->GetDataDirectory(mediaPath);
			App::GetApp()->RegisterTexture(L"TestTex", mediaPath + L"TexMask.png");

			// -- �t�H���g��ǂݍ��� --
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
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
