/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace structdata;
using namespace enumdata;

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		shared_ptr<Camera> m_ptrCamera;

		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {
		}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//�Q�b�^�[�E�Z�b�^�[


		//����

	};


}
//end basecross

