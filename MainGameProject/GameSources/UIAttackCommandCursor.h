/*!
@file UIAttackCommandCursor.h
@brief UI���C���R�}���h�̃J�[�\���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIAttackCommandCursor : public UIBase {
		// �e�I�u�W�F�N�g
		shared_ptr<GameObject> m_parent;
		// �e�̐e�i���C���R�}���h�E�B���h�E�̃I�u�W�F�N�g�j
		shared_ptr<GameObject> m_parentToMainCommand;

		// �J�E���g
		int m_count = 0;
		// �ő�J�E���g(enum�̍Ō�̒l���ő�J�E���g)[0���܂߂邽��]
		int m_maxCount = AttackCommandContent::Weapon2;
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
		UIAttackCommandCursor(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec2& size,
			Vec2& position,
			Vec2& UVPos,
			int layer,
			wstring tex,
			const shared_ptr<GameObject>& parent = nullptr);

		UIAttackCommandCursor(const shared_ptr<Stage>& stage,
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
