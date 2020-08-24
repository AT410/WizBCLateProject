/*!
@file UIAttackCommandContent.cpp
@brief UI攻撃コマンド内容クラスの実態
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

	// 初期化
	void UIAttackCommandContent::OnCreate() {
		// 親の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_parent);

		// トランスフォーム、テクスチャの設定
		SetTexture(m_content);
		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();
		StateCommandActive();
	}

	// 内容ごとのテクスチャの設定
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

	// ステート
	// アクティブ
	void UIAttackCommandContent::StateCommandActive()
	{
		m_bCommandActive = true;
		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->SetDiffuse(m_colorCommandActive);
	}
	// 非アクティブ(押せないことを分かりやすく)
	void UIAttackCommandContent::StateCommandPassive()
	{
		m_bCommandActive = false;
		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->SetDiffuse(m_colorCommandPassive);

	}

	// セッターゲッター
	// アクティブか
	void UIAttackCommandContent::SetCommandActive(bool set)
	{
		m_bCommandActive = set;
	}
	bool UIAttackCommandContent::GetCommandActive()const
	{
		return m_bCommandActive;
	}
	// 内容
	AttackCommandContent UIAttackCommandContent::GetContent()const
	{
		return m_content;
	}

}
//end basecross
