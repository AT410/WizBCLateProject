/*!
@file UIAttackCommand.h
@brief UI�U���R�}���h�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIAttackCommand : public UIBase {
		// �e�I�u�W�F�N�g	
		// ���C���R�}���h
		shared_ptr<GameObject> m_parent;

		// �q�I�u�W�F�N�g
		// ���e
		vector<shared_ptr<UIAttackCommandContent>> m_childContent;
		// �I���J�[�\��
		shared_ptr<UIAttackCommandCursor> m_childCursor;

		// �I�����ꂽ�R�}���h
		bool m_bSelectAttackCommand;
		AttackCommandContent m_selectAttackContent;

		// �q�I�u�W�F�N�g�̐���
		void CreateChild();
	public:
		UIAttackCommand(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec2& size,
			Vec2& position,
			Vec2& UVPos,
			int layer,
			wstring tex,
			const shared_ptr<GameObject>& parent = nullptr);

		UIAttackCommand(const shared_ptr<Stage>& stage,
			UIData& UIdata,
			const shared_ptr<GameObject>& parent = nullptr);

		// ������
		virtual void OnCreate() override;
		// �X�V
		virtual void OnUpdate() override;

		// �I�����ꂽ�R�}���h���Ƃ̓���
		void CheckCommand();

		// �������ƕ\����\��
		void SetActiveThis(bool set);

		// �Q�b�^�[�Z�b�^�[
		// �q�I�u�W�F�N�g�̎擾
		// ���e
		// �S���̌����錩���Ȃ��iDrawActive��UpdateActive�j
		void SetActiveToChildContents(bool set);
		// �S��
		vector<shared_ptr<UIAttackCommandContent>>& GetChildContents();
		// 1����
		shared_ptr<UIAttackCommandContent> GetChildContent(int index);
		// ���e���Ƃ�1��
		shared_ptr<UIAttackCommandContent> GetChildContent(AttackCommandContent content);
		// ���e�̑I���̃��Z�b�g
		void ResetChildAttackContents();
		// �U���R�}���h�I���t���O
		bool GetSelectAttackCommand()const;
		void SetSelectAttackCommand(bool set);
		// �I�����ꂽ���e
		AttackCommandContent GetSelectAttackContent()const;
		void SetSelectAttackContent(AttackCommandContent content);
		// �J�[�\��
		shared_ptr<UIAttackCommandCursor> GetChildCursor();
	};
}

//end basecross
