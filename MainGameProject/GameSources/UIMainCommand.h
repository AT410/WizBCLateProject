/*!
@file UIMainCommand.h
@brief UI���C���R�}���h�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIMainCommand : public UIBase {
		// �q�I�u�W�F�N�g
		// ���e
		vector<shared_ptr<UICommandContent>> m_childContent;
		// �I���J�[�\��
		shared_ptr<UIMainCommandCursor> m_childCursor;
		// �U���R�}���h�E�B���h�E
		shared_ptr<UIAttackCommand> m_childAttackCommand;

		// �U���R�}���h���A�N�e�B�u��
		bool m_bAttackCommandActive = false;
		// ���C���R�}���h�I��
		bool m_bSelectMainCommand = false;
		CommandContent m_selectMainContent;
		// �q�I�u�W�F�N�g�̐���
		void CreateChild();
	public:
		UIMainCommand(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec2& size,
			Vec2& position,
			Vec2& UVPos,
			int layer,
			wstring tex);

		UIMainCommand(const shared_ptr<Stage>& stage,
			UIData& UIdata);

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
		vector<shared_ptr<UICommandContent>>& GetChildContents();
		// 1����
		shared_ptr<UICommandContent> GetChildContent(int index);
		// ���e���Ƃ�1��
		shared_ptr<UICommandContent> GetChildContent(CommandContent content);
		// ���e�̑I���̃��Z�b�g
		void ResetChildMainContents();
		// �J�[�\��
		shared_ptr<UIMainCommandCursor> GetChildCursor();
		// �U���R�}���h�A�N�e�B�u�t���O
		bool GetAttackCommandActive()const;
		void SetAttackCommandActive(bool set);
		// ���C���R�}���h�I���t���O
		bool GetSelectMainCommand()const;
		void SetSelectMainCommand(bool set);
		// �I�����ꂽ���e
		CommandContent GetSelectMainContent()const;
		void SetSelectMainContent(CommandContent content);
	};
}

//end basecross
