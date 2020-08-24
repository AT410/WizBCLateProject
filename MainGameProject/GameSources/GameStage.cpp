/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -50.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		m_ptrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(m_ptrCamera);
		m_ptrCamera->SetEye(eye);
		m_ptrCamera->SetAt(at);

		//�J�����̉��ߖ@��؂�
		m_ptrCamera->SetPers(false);

		//���̒l��ݒ�
		float width = 3.2 * 12;
		float height = 2.0 * 12;

		//�J�������f���͈͂�ݒ�
		m_ptrCamera->SetWidth(width);
		m_ptrCamera->SetHeight(height);
		//����p��ݒ�
		m_ptrCamera->SetFovY(1.0f);

		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			auto charaObjData = structdata::ObjectData(Vec3(0.0f), Vec3(1.0f), Vec3(0.0f),0, L"thumbnail.png");

			//�`��̊m�F�p�ɉ摜�𐶐�
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
