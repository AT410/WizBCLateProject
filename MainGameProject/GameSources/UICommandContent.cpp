/*!
@file UICommandContent.cpp
@brief UI�R�}���h���e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	UICommandContent::UICommandContent(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec2& size,
		Vec2& position,
		Vec2& UVPos,
		int layer,
		CommandContent& content,
		const shared_ptr<GameObject>& parent) :
		UIBase(stage, rotation, size, position, UVPos, layer, L""),
		m_content(content),
		m_parent(parent)
	{
		m_scale = Vec3(1.0f);
	}

	UICommandContent::UICommandContent(const shared_ptr<Stage>& stage,
		UIData& UIdata,
		CommandContent& content,
		const shared_ptr<GameObject>& parent) :
		UIBase(stage, UIdata),
		m_content(content),
		m_parent(parent)
	{
		m_scale = Vec3(1.0f);
	}

	void UICommandContent::OnCreate() {
		// �e�̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_parent);

		SetTexture(m_content);
		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();
		StateCommandActive();
	}

	void UICommandContent::SetTexture(CommandContent content)
	{
		switch (content)
		{
		case CommandContent::Attack:
			m_textureName = L"attack.png";
			break;
		case CommandContent::Move:
			m_textureName = L"move.png";
			break;
		case CommandContent::Wait:
			m_textureName = L"wait.png";
			break;
		case CommandContent::TurnEnd:
			m_textureName = L"turnEnd.png";
			break;
		}
	}

	// �X�e�[�g
	// �A�N�e�B�u
	void UICommandContent::StateCommandActive()
	{
		m_bCommandActive = true;
		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->SetDiffuse(m_colorCommandActive);
	}
	// ��A�N�e�B�u(�����Ȃ����Ƃ𕪂���₷��)
	void UICommandContent::StateCommandPassive()
	{
		m_bCommandActive = false;
		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->SetDiffuse(m_colorCommandPassive);

	}

	// �Z�b�^�[�Q�b�^�[
	// �A�N�e�B�u��
	void UICommandContent::SetCommandActive(bool set)
	{
		m_bCommandActive = set;
	}
	bool UICommandContent::GetCommandActive()const
	{
		return m_bCommandActive;
	}
	// ���e
	CommandContent UICommandContent::GetContent()const
	{
		return m_content;
	}

}
//end basecross
