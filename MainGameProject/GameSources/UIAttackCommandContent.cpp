/*!
@file UIAttackCommandContent.cpp
@brief UI�U���R�}���h���e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	UIAttackCommandContent::UIAttackCommandContent(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec2& size,
		Vec2& position,
		Vec2& UVPos,
		int layer,
		AttackCommandContent& content,
		const shared_ptr<GameObject>& parent) :
		UIBase(stage, rotation, size, position, UVPos, layer, L""),
		m_content(content),
		m_parent(parent)
	{
		m_scale = Vec3(1.0f);
	}

	UIAttackCommandContent::UIAttackCommandContent(const shared_ptr<Stage>& stage,
		UIData& UIdata,
		AttackCommandContent& content,
		const shared_ptr<GameObject>& parent) :
		UIBase(stage, UIdata),
		m_content(content),
		m_parent(parent)
	{
		m_scale = Vec3(1.0f);
	}

	// ������
	void UIAttackCommandContent::OnCreate() {
		// �e�̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_parent);

		// �g�����X�t�H�[���A�e�N�X�`���̐ݒ�
		SetTexture(m_content);
		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();
		StateCommandActive();
	}

	// ���e���Ƃ̃e�N�X�`���̐ݒ�
	void UIAttackCommandContent::SetTexture(AttackCommandContent content)
	{
		switch (content)
		{
		case AttackCommandContent::Weapon1:
			m_textureName = L"wait.png";
			break;
		case AttackCommandContent::Weapon2:
			m_textureName = L"turnEnd.png";
			break;
		}
	}

	// �X�e�[�g
	// �A�N�e�B�u
	void UIAttackCommandContent::StateCommandActive()
	{
		m_bCommandActive = true;
		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->SetDiffuse(m_colorCommandActive);
	}
	// ��A�N�e�B�u(�����Ȃ����Ƃ𕪂���₷��)
	void UIAttackCommandContent::StateCommandPassive()
	{
		m_bCommandActive = false;
		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->SetDiffuse(m_colorCommandPassive);

	}

	// �Z�b�^�[�Q�b�^�[
	// �A�N�e�B�u��
	void UIAttackCommandContent::SetCommandActive(bool set)
	{
		m_bCommandActive = set;
	}
	bool UIAttackCommandContent::GetCommandActive()const
	{
		return m_bCommandActive;
	}
	// ���e
	AttackCommandContent UIAttackCommandContent::GetContent()const
	{
		return m_content;
	}

}
//end basecross
