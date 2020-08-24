/*!
@file UIAttackCommand.cpp
@brief UI�U���R�}���h�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	UIAttackCommand::UIAttackCommand(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec2& size,
		Vec2& position,
		Vec2& UVPos,
		int layer,
		wstring tex,
		const shared_ptr<GameObject>& parent) :
		UIBase(stage, rotation, size, position, UVPos, layer, tex),
		m_parent(parent)
	{
		m_scale = Vec3(1.0f);
	}

	UIAttackCommand::UIAttackCommand(const shared_ptr<Stage>& stage,
		UIData& UIdata,
		const shared_ptr<GameObject>& parent):
		UIBase(stage, UIdata),
		m_parent(parent)
	{
		m_scale = Vec3(1.0f);
	}

	// �q�I�u�W�F�N�g�̐���
	void UIAttackCommand::CreateChild()
	{
		// �R�}���h���e�̐���
		auto pos = GetComponent<Transform>()->GetPosition();
		m_childContent.push_back(GetStage()->AddGameObject<UIAttackCommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f, +135.0f), Vec2(0.0f, 1.0f), 9, AttackCommandContent::Weapon1, GetThis<GameObject>()));
		m_childContent.push_back(GetStage()->AddGameObject<UIAttackCommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f,  +45.0f), Vec2(0.0f, 1.0f), 9, AttackCommandContent::Weapon2, GetThis<GameObject>()));
		SetActiveToChildContents(false);
		// �J�[�\���̐���
		auto contentPos = m_childContent[0]->GetComponent<Transform>()->GetPosition();
		m_childCursor = GetStage()->AddGameObject<UIAttackCommandCursor>(Vec3(0.0f), Vec2(85.0f, 45.0f), Vec2(contentPos.x, contentPos.y), Vec2(0.0f, 1.0f), 10, L"cursor.png", GetThis<GameObject>());
		m_childCursor->SetDrawActive(false);
		m_childCursor->SetUpdateActive(false);
	}

	// ������
	void UIAttackCommand::OnCreate() {
		// �e�̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_parent);

		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();

		CreateChild();
	}
	// �X�V
	void UIAttackCommand::OnUpdate() {
		// �I�΂ꂽ��
		if (m_bSelectAttackCommand)
		{
			CheckCommand();
		}
	}

	// �I�����ꂽ�R�}���h���Ƃ̓���
	void UIAttackCommand::CheckCommand()
	{
		// 1��݂̂̏����Ȃ̂ł����Ŏ�����Ȃ��悤�ɂ���
		m_bSelectAttackCommand = false;
		// ���e���I���ł��Ȃ����̂Ȃ�I���
		if (!GetChildContent(m_selectAttackContent)->GetCommandActive())
		{
			return;
		}
		// �I���ł��Ȃ��悤�Ɍ�����
		GetChildContent(m_selectAttackContent)->StateCommandPassive();
		// �J�[�\���𓮂��Ȃ�������(�݂��Ȃ�)
		m_childCursor->SetDrawActive(false);
		m_childCursor->SetUpdateActive(false);

		auto parent = dynamic_pointer_cast<UIMainCommand>(GetComponent<Transform>()->GetParent());
		switch (m_selectAttackContent)
		{
		case AttackCommandContent::Weapon1:
			// ���C���R�}���h�E�B���h�E�����Ȃ����ĕ���1�ōU��
			parent->SetActiveToChildContents(false);
			parent->SetDrawActive(false);
			SetActiveToChildContents(false);
			SetDrawActive(false);
			break;
		case AttackCommandContent::Weapon2:
			// ���C���R�}���h�E�B���h�E�����Ȃ����ĕ���2�ōU��
			parent->SetActiveToChildContents(false);
			parent->SetDrawActive(false);
			SetActiveToChildContents(false);
			SetDrawActive(false);
			break;
		}

	}

	// �������ƕ\����\��
	void UIAttackCommand::SetActiveThis(bool set)
	{
		// �q
		SetActiveToChildContents(set);
		m_childCursor->InitPosition();
		m_childCursor->SetDrawActive(set);
		m_childCursor->SetUpdateActive(set);
		// ����
		SetDrawActive(set);
		SetUpdateActive(set);
	}


	// �q�I�u�W�F�N�g�̎擾
	// �S���̌����錩���Ȃ��iDrawActive��UpdateActive�j
	void UIAttackCommand::SetActiveToChildContents(bool set)
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
	vector<shared_ptr<UIAttackCommandContent>>& UIAttackCommand::GetChildContents()
	{
		return m_childContent;
	}
	// 1����
	shared_ptr<UIAttackCommandContent> UIAttackCommand::GetChildContent(int index)
	{
		return m_childContent[index];
	}
	// ���e���Ƃ�1��
	shared_ptr<UIAttackCommandContent> UIAttackCommand::GetChildContent(AttackCommandContent content)
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
	void UIAttackCommand::ResetChildAttackContents()
	{
		for (auto content : m_childContent)
		{
			// �S���I���ł���悤�ɂ���
			content->StateCommandActive();
		}
	}

	// �U���R�}���h�I���t���O
	bool UIAttackCommand::GetSelectAttackCommand()const
	{
		return m_bSelectAttackCommand;
	}
	void UIAttackCommand::SetSelectAttackCommand(bool set)
	{
		m_bSelectAttackCommand = set;
	}
	// �I�����ꂽ���e
	AttackCommandContent UIAttackCommand::GetSelectAttackContent()const
	{
		return m_selectAttackContent;
	}
	void UIAttackCommand::SetSelectAttackContent(AttackCommandContent content)
	{
		m_selectAttackContent = content;
	}

	// �J�[�\��
	shared_ptr<UIAttackCommandCursor> UIAttackCommand::GetChildCursor()
	{
		return m_childCursor;
	}

}
//end basecross
