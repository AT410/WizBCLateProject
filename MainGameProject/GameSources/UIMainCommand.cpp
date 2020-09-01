/*!
@file UIMainCommand.cpp
@brief UIメインコマンドクラスの実態
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

	// 子オブジェクトの生成
	void UIMainCommand::CreateChild()
	{
		// コマンド内容の生成
		auto pos = GetComponent<Transform>()->GetPosition();
		m_childContent.push_back(GetStage()->AddGameObject<UICommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f, +135.0f), Vec2(0.0f, 1.0f), 6, CommandContent::Attack, GetThis<GameObject>()));
		m_childContent.push_back(GetStage()->AddGameObject<UICommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f,  +45.0f), Vec2(0.0f, 1.0f), 6, CommandContent::Move, GetThis<GameObject>()));
		m_childContent.push_back(GetStage()->AddGameObject<UICommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f,  -45.0f), Vec2(0.0f, 1.0f), 6, CommandContent::Wait, GetThis<GameObject>()));
		m_childContent.push_back(GetStage()->AddGameObject<UICommandContent>(Vec3(0.0f), Vec2(75.0f, 35.0f), Vec2(0.0f, -135.0f), Vec2(0.0f, 1.0f), 6, CommandContent::TurnEnd, GetThis<GameObject>()));
		// カーソルの生成
		auto contentPos = m_childContent[0]->GetComponent<Transform>()->GetPosition();
		m_childCursor = GetStage()->AddGameObject<UIMainCommandCursor>(Vec3(0.0f), Vec2(85.0f, 45.0f), Vec2(contentPos.x, contentPos.y), Vec2(0.0f, 1.0f), 7, L"cursor.png", GetThis<GameObject>());
		// 攻撃コマンドウィンドウ生成
		m_childAttackCommand = GetStage()->AddGameObject<UIAttackCommand>(Vec3(0.0f), Vec2(150.0f, 200.0f), Vec2(120.0f, 100.0f), Vec2(0.0f, 1.0f), 8, L"menu.png", GetThis<GameObject>());
		m_childAttackCommand->SetDrawActive(false);
		m_childAttackCommand->SetUpdateActive(false);
	}

	// 初期化
	void UIMainCommand::OnCreate() {
		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();
		CreateChild();
	}
	// 更新
	void UIMainCommand::OnUpdate() {
		if (m_bSelectMainCommand)
		{
			CheckCommand();
		}
	}

	// 選択されたコマンドごとの動き
	void UIMainCommand::CheckCommand()
	{
		// 1回のみの処理なのでここで次入らないようにする
		m_bSelectMainCommand = false;
		// 内容が選択できないものなら終わる
		if (!GetChildContent(m_selectMainContent)->GetCommandActive())
		{
			return;
		}

		// 選択できないように見せる
		GetChildContent(m_selectMainContent)->StateCommandPassive();
		// メインのカーソルを動かなくさせる(みえない)
		m_childCursor->SetDrawActive(false);
		m_childCursor->SetUpdateActive(false);

		switch (m_selectMainContent)
		{
		case CommandContent::Attack:
			// アタックコマンドウィンドウ呼び出し
			m_childAttackCommand->SetActiveThis(true);
			m_bAttackCommandActive = true;
			break;
		case CommandContent::Move:
			// メインコマンドウィンドウ見えなくするのと移動のほうに切り替え
			SetActiveToChildContents(false);
			SetDrawActive(false);
			GetTypeStage<GameStage>()->SettingMoveCostMap();
			break;
		case CommandContent::Wait:
			// メインコマンドウィンドウ見えなくするのとターンエンド以外押せなくする
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
			// メインコマンドウィンドウ見えなくするのとプレイヤー切り替え
			SetActiveToChildContents(false);
			SetDrawActive(false);
			GetTypeStage<GameStage>()->ChangePlayerTurn();
			break;
		}

	}

	// 自分ごと表示非表示
	void UIMainCommand::SetActiveThis(bool set)
	{
		// 子
		SetActiveToChildContents(set);
		m_childCursor->SetDrawActive(set);
		m_childCursor->SetUpdateActive(set);
		// 自分
		SetDrawActive(set);
		SetUpdateActive(set);
	}


	// 子オブジェクトの取得
	// 全部の見える見えない（DrawActiveとUpdateActive）
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

	// 全部
	vector<shared_ptr<UICommandContent>>& UIMainCommand::GetChildContents()
	{
		return m_childContent;
	}
	// 1個ずつ
	shared_ptr<UICommandContent> UIMainCommand::GetChildContent(int index)
	{
		return m_childContent[index];
	}
	// 内容ごとで1個
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
	// 内容の選択のリセット
	void UIMainCommand::ResetChildMainContents()
	{
		for (auto content : m_childContent)
		{
			// 全部選択できるようにする
			content->StateCommandActive();
		}
	}

	// カーソル
	shared_ptr<UIMainCommandCursor> UIMainCommand::GetChildCursor()
	{
		return m_childCursor;
	}
	// 攻撃コマンドアクティブフラグ
	bool UIMainCommand::GetAttackCommandActive()const
	{
		return m_bAttackCommandActive;
	}
	void UIMainCommand::SetAttackCommandActive(bool set)
	{
		m_bAttackCommandActive = set;
	}
	// メインコマンド選択フラグ
	bool UIMainCommand::GetSelectMainCommand()const
	{
		return m_bSelectMainCommand;
	}
	void UIMainCommand::SetSelectMainCommand(bool set)
	{
		m_bSelectMainCommand = set;
	}
	// 選択された内容
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
