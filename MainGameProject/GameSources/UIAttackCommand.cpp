/*!
@file UIAttackCommand.cpp
@brief UI攻撃コマンドクラスの実態
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

	// 子オブジェクトの生成
	void UIAttackCommand::CreateChild()
	{
		// コマンド内容の生成
		auto pos = GetComponent<Transform>()->GetPosition();
		m_childContent.push_back(GetStage()->AddGameObject<UIAttackCommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f, +135.0f), Vec2(0.0f, 1.0f), 9, AttackCommandContent::Weapon1, GetThis<GameObject>()));
		m_childContent.push_back(GetStage()->AddGameObject<UIAttackCommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f,  +45.0f), Vec2(0.0f, 1.0f), 9, AttackCommandContent::Weapon2, GetThis<GameObject>()));
		SetActiveToChildContents(false);
		// カーソルの生成
		auto contentPos = m_childContent[0]->GetComponent<Transform>()->GetPosition();
		m_childCursor = GetStage()->AddGameObject<UIAttackCommandCursor>(Vec3(0.0f), Vec2(85.0f, 45.0f), Vec2(contentPos.x, contentPos.y), Vec2(0.0f, 1.0f), 10, L"cursor.png", GetThis<GameObject>());
		m_childCursor->SetDrawActive(false);
		m_childCursor->SetUpdateActive(false);
	}

	// 初期化
	void UIAttackCommand::OnCreate() {
		// 親の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_parent);

		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();

		CreateChild();
	}
	// 更新
	void UIAttackCommand::OnUpdate() {
		// 選ばれたら
		if (m_bSelectAttackCommand)
		{
			CheckCommand();
		}
	}

	// 選択されたコマンドごとの動き
	void UIAttackCommand::CheckCommand()
	{
		// 1回のみの処理なのでここで次入らないようにする
		m_bSelectAttackCommand = false;
		// 内容が選択できないものなら終わる
		if (!GetChildContent(m_selectAttackContent)->GetCommandActive())
		{
			return;
		}
		// 選択できないように見せる
		GetChildContent(m_selectAttackContent)->StateCommandPassive();
		// カーソルを動かなくさせる(みえない)
		m_childCursor->SetDrawActive(false);
		m_childCursor->SetUpdateActive(false);

		auto parent = dynamic_pointer_cast<UIMainCommand>(GetComponent<Transform>()->GetParent());
		switch (m_selectAttackContent)
		{
		case AttackCommandContent::Weapon1:
			// メインコマンドウィンドウ見えなくして武器1で攻撃
			parent->SetActiveToChildContents(false);
			parent->SetDrawActive(false);
			SetActiveToChildContents(false);
			SetDrawActive(false);
			break;
		case AttackCommandContent::Weapon2:
			// メインコマンドウィンドウ見えなくして武器2で攻撃
			parent->SetActiveToChildContents(false);
			parent->SetDrawActive(false);
			SetActiveToChildContents(false);
			SetDrawActive(false);
			break;
		}

	}

	// 自分ごと表示非表示
	void UIAttackCommand::SetActiveThis(bool set)
	{
		// 子
		SetActiveToChildContents(set);
		m_childCursor->InitPosition();
		m_childCursor->SetDrawActive(set);
		m_childCursor->SetUpdateActive(set);
		// 自分
		SetDrawActive(set);
		SetUpdateActive(set);
	}


	// 子オブジェクトの取得
	// 全部の見える見えない（DrawActiveとUpdateActive）
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
	// 全部
	vector<shared_ptr<UIAttackCommandContent>>& UIAttackCommand::GetChildContents()
	{
		return m_childContent;
	}
	// 1個ずつ
	shared_ptr<UIAttackCommandContent> UIAttackCommand::GetChildContent(int index)
	{
		return m_childContent[index];
	}
	// 内容ごとで1個
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
	// 内容の選択のリセット
	void UIAttackCommand::ResetChildAttackContents()
	{
		for (auto content : m_childContent)
		{
			// 全部選択できるようにする
			content->StateCommandActive();
		}
	}

	// 攻撃コマンド選択フラグ
	bool UIAttackCommand::GetSelectAttackCommand()const
	{
		return m_bSelectAttackCommand;
	}
	void UIAttackCommand::SetSelectAttackCommand(bool set)
	{
		m_bSelectAttackCommand = set;
	}
	// 選択された内容
	AttackCommandContent UIAttackCommand::GetSelectAttackContent()const
	{
		return m_selectAttackContent;
	}
	void UIAttackCommand::SetSelectAttackContent(AttackCommandContent content)
	{
		m_selectAttackContent = content;
	}

	// カーソル
	shared_ptr<UIAttackCommandCursor> UIAttackCommand::GetChildCursor()
	{
		return m_childCursor;
	}

}
//end basecross
