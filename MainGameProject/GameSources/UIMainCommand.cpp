/*!
@file UIMainCommand.cpp
@brief UI���C���R�}���h�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	UIMainCommand::UIMainCommand(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec2& size,
		Vec2& position,
		Vec2& UVPos,
		int layer,
		wstring tex) :
		UIBase(stage, rotation, size, position, UVPos, layer, tex)
	{
		m_scale = Vec3(1.0f);
	}

	UIMainCommand::UIMainCommand(const shared_ptr<Stage>& stage,
		UIData& UIdata):
		UIBase(stage, UIdata)
	{
		m_scale = Vec3(1.0f);
	}

	// �q�I�u�W�F�N�g�̐���
	void UIMainCommand::CreateChild()
	{
		// �R�}���h���e�̐���
		auto pos = GetComponent<Transform>()->GetPosition();
		m_childContent.push_back(GetStage()->AddGameObject<UICommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f, +135.0f), Vec2(0.0f, 1.0f), 6, CommandContent::Attack, GetThis<GameObject>()));
		m_childContent.push_back(GetStage()->AddGameObject<UICommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f,  +45.0f), Vec2(0.0f, 1.0f), 6, CommandContent::Move, GetThis<GameObject>()));
		m_childContent.push_back(GetStage()->AddGameObject<UICommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f,  -45.0f), Vec2(0.0f, 1.0f), 6, CommandContent::Wait, GetThis<GameObject>()));
		m_childContent.push_back(GetStage()->AddGameObject<UICommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f, -135.0f), Vec2(0.0f, 1.0f), 6, CommandContent::TurnEnd, GetThis<GameObject>()));
		// �J�[�\���̐���
		auto contentPos = m_childContent[0]->GetComponent<Transform>()->GetPosition();
		m_childCursor = GetStage()->AddGameObject<UIMainCommandCursor>(Vec3(0.0f), Vec2(85.0f, 45.0f), Vec2(contentPos.x, contentPos.y), Vec2(0.0f, 1.0f), 7, L"cursor.png", GetThis<GameObject>());
		// �U���R�}���h�E�B���h�E����
		m_childAttackCommand = GetStage()->AddGameObject<UIAttackCommand>(Vec3(0.0f), Vec2(150.0f, 200.0f), Vec2(120.0f, 100.0f), Vec2(0.0f, 1.0f), 8, L"menu.png", GetThis<GameObject>());
		m_childAttackCommand->SetDrawActive(false);
		m_childAttackCommand->SetUpdateActive(false);
	}

	// ������
	void UIMainCommand::OnCreate() {
		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();
		CreateChild();
	}
	// �X�V
	void UIMainCommand::OnUpdate() {
		if (m_bSelectMainCommand)
		{
			CheckCommand();
		}
	}

	// �I�����ꂽ�R�}���h���Ƃ̓���
	void UIMainCommand::CheckCommand()
	{
		// 1��݂̂̏����Ȃ̂ł����Ŏ�����Ȃ��悤�ɂ���
		m_bSelectMainCommand = false;
		// ���e���I���ł��Ȃ����̂Ȃ�I���
		if (!GetChildContent(m_selectMainContent)->GetCommandActive())
		{
			return;
		}

		// �I���ł��Ȃ��悤�Ɍ�����
		GetChildContent(m_selectMainContent)->StateCommandPassive();
		// ���C���̃J�[�\���𓮂��Ȃ�������(�݂��Ȃ�)
		m_childCursor->SetDrawActive(false);
		m_childCursor->SetUpdateActive(false);

		switch (m_selectMainContent)
		{
		case CommandContent::Attack:
			// �A�^�b�N�R�}���h�E�B���h�E�Ăяo��
			m_childAttackCommand->SetActiveThis(true);
			m_bAttackCommandActive = true;
			break;
		case CommandContent::Move:
			// ���C���R�}���h�E�B���h�E�����Ȃ�����̂ƈړ��̂ق��ɐ؂�ւ�
			SetActiveToChildContents(false);
			SetDrawActive(false);
			GetTypeStage<GameStage>()->SettingMoveCostMap();
			break;
		case CommandContent::Wait:
			// ���C���R�}���h�E�B���h�E�����Ȃ�����̂ƃ^�[���G���h�ȊO�����Ȃ�����
			for (auto content : m_childContent)
			{
				if (content->GetContent() != CommandContent::TurnEnd)
				{
					content->StateCommandPassive();
				}
			}
			SetActiveToChildContents(false);
			SetDrawActive(false);
			GetTypeStage<GameStage>()->WaitCharacter();
			break;
		case CommandContent::TurnEnd:
			// ���C���R�}���h�E�B���h�E�����Ȃ�����̂ƃv���C���[�؂�ւ�
			SetActiveToChildContents(false);
			SetDrawActive(false);
			GetTypeStage<GameStage>()->ChangePlayerTurn();
			break;
		}

	}

	// �������ƕ\����\��
	void UIMainCommand::SetActiveThis(bool set)
	{
		// �q
		SetActiveToChildContents(set);
		m_childCursor->SetDrawActive(set);
		m_childCursor->SetUpdateActive(set);
		// ����
		SetDrawActive(set);
		SetUpdateActive(set);
	}


	// �q�I�u�W�F�N�g�̎擾
	// �S���̌����錩���Ȃ��iDrawActive��UpdateActive�j
	void UIMainCommand::SetActiveToChildContents(bool set)
	{
		for (auto content : m_childContent)
		{
			if (content->GetDrawActive() != set) {
				content->SetDrawActive(set);
				content->SetUpdateActive(set);
			}
			else
			{
				break;
			}
		}
	}

	// �S��
	vector<shared_ptr<UICommandContent>>& UIMainCommand::GetChildContents()
	{
		return m_childContent;
	}
	// 1����
	shared_ptr<UICommandContent> UIMainCommand::GetChildContent(int index)
	{
		return m_childContent[index];
	}
	// ���e���Ƃ�1��
	shared_ptr<UICommandContent> UIMainCommand::GetChildContent(CommandContent content)
	{
		for (auto obj : m_childContent)
		{
			if (obj->GetContent() == content)
			{
				return obj;
			}
		}
		return nullptr;
	}
	// ���e�̑I���̃��Z�b�g
	void UIMainCommand::ResetChildMainContents()
	{
		for (auto content : m_childContent)
		{
			// �S���I���ł���悤�ɂ���
			content->StateCommandActive();
		}
	}

	// �J�[�\��
	shared_ptr<UIMainCommandCursor> UIMainCommand::GetChildCursor()
	{
		return m_childCursor;
	}
	// �U���R�}���h�A�N�e�B�u�t���O
	bool UIMainCommand::GetAttackCommandActive()const
	{
		return m_bAttackCommandActive;
	}
	void UIMainCommand::SetAttackCommandActive(bool set)
	{
		m_bAttackCommandActive = set;
	}
	// ���C���R�}���h�I���t���O
	bool UIMainCommand::GetSelectMainCommand()const
	{
		return m_bSelectMainCommand;
	}
	void UIMainCommand::SetSelectMainCommand(bool set)
	{
		m_bSelectMainCommand = set;
	}
	// �I�����ꂽ���e
	CommandContent UIMainCommand::GetSelectMainContent()const
	{
		return m_selectMainContent;
	}
	void UIMainCommand::SetSelectMainContent(CommandContent content)
	{
		m_selectMainContent = content;
	}

}
//end basecross
