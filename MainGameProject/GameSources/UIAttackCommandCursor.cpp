/*!
@file UIMainCommandCursor.cpp
@brief UI���C���R�}���h�̃J�[�\���N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	UIAttackCommandCursor::UIAttackCommandCursor(const shared_ptr<Stage>& stage,
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

	UIAttackCommandCursor::UIAttackCommandCursor(const shared_ptr<Stage>& stage,
		UIData& UIdata,
		const shared_ptr<GameObject>& parent):
		UIBase(stage, UIdata),
		m_parent(parent)
	{
		m_scale = Vec3(1.0f);
	}

	// ������
	// �ʒu�̏�����
	void UIAttackCommandCursor::InitPosition()
	{
		auto parent = dynamic_pointer_cast<UIAttackCommand>(GetComponent<Transform>()->GetParent());
		GetComponent<Transform>()->SetPosition(parent->GetChildContent(AttackCommandContent::Weapon1)->GetComponent<Transform>()->GetPosition());
		m_count = 0;
	}

	void UIAttackCommandCursor::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_parent);
		m_parentToMainCommand = m_parent->GetComponent<Transform>()->GetParent();

		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();

	}
	// �X�V
	void UIAttackCommandCursor::OnUpdate() {
		//auto parent = dynamic_pointer_cast<UIMainCommand>(GetComponent<Transform>()->GetParent());
		//if (parent->GetSelectMainCommand())return;
		// �J�[�\���̈ړ�
		MoveCursor();
		OnPushA();
		OnPushB();
	}

	// �J�[�\���̈ړ�
	void UIAttackCommandCursor::MoveCursor()
	{
		// �N�[���^�C�����Ȃ�v�Z���ċA��
		if (m_bCoolTime)
		{
			CalcCoolTime();
			return;
		}

		// �R���g���[���[�̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		float thumbLY = 0;
		if (cntlVec.bConnected)
		{
			thumbLY = cntlVec.fThumbLY;
		}
		//�\�����������Ɖ��Ɉړ�
		if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			m_count++;
			if (m_count >= m_maxCount)
			{
				m_count = m_maxCount;
			}
			m_bCoolTime = true;
		}
		//�\�����������Ə�Ɉړ�
		if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			m_count--;
			if (m_count <= 0)
			{
				m_count = 0;
			}
			m_bCoolTime = true;
		}
		// �X���Ă�����
		if (thumbLY != 0.0f) {
			if (thumbLY < -0.1f)
			{
				m_count++;
				if (m_count >= m_maxCount)
				{
					m_count = m_maxCount;
				}
			}
			else if (thumbLY > 0.1f)
			{
				m_count--;
				if (m_count <= 0)
				{
					m_count = 0;
				}
			}
			m_bCoolTime = true;
		}
		else
		{
			if (m_bCoolTime) {
				m_bCoolTime = false;
			}
		}
		auto parent = dynamic_pointer_cast<UIAttackCommand>(GetComponent<Transform>()->GetParent());
		//auto contentPos = parent->GetChildContent((AttackCommandContent)m_count)->GetComponent<Transform>()->GetPosition();
		auto contentPos = parent->GetChildContent(m_count)->GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(contentPos);
	}
	// A�{�^��
	void UIAttackCommandCursor::OnPushA()
	{
		// �R���g���[���[�̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A)
		{
			auto parent = dynamic_pointer_cast<UIAttackCommand>(GetComponent<Transform>()->GetParent());
			//parent->GetChildContent(m_count)->StateCommandPassive();
			parent->SetSelectAttackCommand(true);
			parent->SetSelectAttackContent((AttackCommandContent)m_count);
		}
	}
	// B�{�^��
	void UIAttackCommandCursor::OnPushB()
	{
		// �R���g���[���[�̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			// �ЂƂO�̃R�}���h�I���ɖ߂�
			auto mainCommand = dynamic_pointer_cast<UIMainCommand>(m_parentToMainCommand);
			mainCommand->SetSelectMainCommand(false);
			mainCommand->GetChildContent(mainCommand->GetSelectMainContent())->StateCommandActive();
			mainCommand->GetChildCursor()->SetDrawActive(true);
			mainCommand->GetChildCursor()->SetUpdateActive(true);
			auto parent = dynamic_pointer_cast<UIAttackCommand>(m_parent);
			parent->SetActiveThis(false);
		}

	}

	// �N�[���^�C���v�Z
	void UIAttackCommandCursor::CalcCoolTime()
	{
		m_totalMoveCoolTime += App::GetApp()->GetElapsedTime();
		if (m_totalMoveCoolTime >= m_moveCoolTime)
		{
			// �N�[���^�C���I���
			m_totalMoveCoolTime = 0.0f;
			m_bCoolTime = false;
		}
	}

}
//end basecross
