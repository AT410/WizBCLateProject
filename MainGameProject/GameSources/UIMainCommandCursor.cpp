/*!
@file UIMainCommandCursor.cpp
@brief UIメインコマンドのカーソルクラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	UIMainCommandCursor::UIMainCommandCursor(const shared_ptr<Stage>& stage,
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

	UIMainCommandCursor::UIMainCommandCursor(const shared_ptr<Stage>& stage,
		UIData& UIdata,
		const shared_ptr<GameObject>& parent):
		UIBase(stage, UIdata),
		m_parent(parent)
	{
		m_scale = Vec3(1.0f);
	}

	// 初期化
	// 位置の初期化
	void UIMainCommandCursor::InitPosition()
	{
		auto parent = dynamic_pointer_cast<UIMainCommand>(GetComponent<Transform>()->GetParent());
		GetComponent<Transform>()->SetPosition(parent->GetChildContent(CommandContent::Attack)->GetComponent<Transform>()->GetPosition());
		m_count = 0;
	}

	// 初期化
	void UIMainCommandCursor::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_parent);

		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();

	}
	// 更新
	void UIMainCommandCursor::OnUpdate() {
		//auto parent = dynamic_pointer_cast<UIMainCommand>(GetComponent<Transform>()->GetParent());
		//if (parent->GetSelectMainCommand())return;
		// 入力
		m_handler.PushHandle(GetThis<UIMainCommandCursor>());
		// カーソルの移動
		MoveCursor();
	}

	// カーソルの移動
	void UIMainCommandCursor::MoveCursor()
	{
		// クールタイム中なら計算して帰る
		if (m_bCoolTime)
		{
			CalcCoolTime();
			return;
		}

		// コントローラーの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		float thumbLY = 0;
		if (cntlVec.bConnected)
		{
			thumbLY = cntlVec.fThumbLY;
		}
		//十字↓を押すと下に移動
		if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			m_count++;
			if (m_count >= m_maxCount)
			{
				m_count = m_maxCount;
			}
			m_bCoolTime = true;
		}
		//十字↑を押すと上に移動
		if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			m_count--;
			if (m_count <= 0)
			{
				m_count = 0;
			}
			m_bCoolTime = true;
		}

		// 傾いていたら
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
		auto parent = dynamic_pointer_cast<UIMainCommand>(GetComponent<Transform>()->GetParent());
		//auto contentPos = parent->GetChildContent((CommandContent)m_count)->GetComponent<Transform>()->GetPosition();
		auto contentPos = parent->GetChildContent(m_count)->GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(contentPos);
	}
	// Aボタン
	void UIMainCommandCursor::OnPushA()
	{
		if (GetTypeStage<GameStage>()->GetGameStateNum() == eGameStateNum::choiceAction) {
			auto parent = dynamic_pointer_cast<UIMainCommand>(GetComponent<Transform>()->GetParent());
			parent->SetSelectMainCommand(true);
			parent->SetSelectMainContent((CommandContent)m_count);

		}
	}
	// Bボタン
	void UIMainCommandCursor::OnPushB()
	{
		auto parent = dynamic_pointer_cast<UIMainCommand>(GetComponent<Transform>()->GetParent());
		parent->SetActiveThis(false);
		GetTypeStage<GameStage>()->SetGameStateNum(eGameStateNum::choicePlayer);
	}

	// クールタイム計算
	void UIMainCommandCursor::CalcCoolTime()
	{
		m_totalMoveCoolTime += App::GetApp()->GetElapsedTime();
		if (m_totalMoveCoolTime >= m_moveCoolTime)
		{
			// クールタイム終わり
			m_totalMoveCoolTime = 0.0f;
			m_bCoolTime = false;
		}
	}

}
//end basecross
