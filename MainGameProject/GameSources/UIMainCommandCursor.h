/*!
@file UIMainCommandCursor.h
@brief UI���C���R�}���h�̃J�[�\���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIMainCommandCursor : public UIBase {
		// �e�I�u�W�F�N�g
		shared_ptr<GameObject> m_parent;

		// �J�E���g
		int m_count = 0;
		// �ő�J�E���g(enum�̍Ō�̒l���ő�J�E���g)
		int m_maxCount = (int)CommandContent::TurnEnd;
		// �J�[�\���ړ��N�[���^�C��
		float m_moveCoolTime = 0.2f;
		float m_totalMoveCoolTime = 0.0f;
		// �N�[���^�C����
		bool m_bCoolTime = false;
		// �N�[���^�C���v�Z
		void CalcCoolTime();

		// �J�[�\���̈ړ�
		void MoveCursor();
		// A�{�^��
		void OnPushA();
		// B�{�^��
		void OnPushB();


	public:
		UIMainCommandCursor(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec2& size,
			Vec2& position,
			Vec2& UVPos,
			int layer,
			wstring tex,
			const shared_ptr<GameObject>& parent = nullptr);

		UIMainCommandCursor(const shared_ptr<Stage>& stage,
			UIData& UIdata,
			const shared_ptr<GameObject>& parent = nullptr);

		// ������
		virtual void OnCreate() override;
		void InitPosition();
		// �X�V
		virtual void OnUpdate() override;

	};
}

//end basecross
