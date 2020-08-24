/*!
@file UIMainCommand.h
@brief UIメインコマンドクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIMainCommand : public UIBase {
		// 子オブジェクト
		// 内容
		vector<shared_ptr<UICommandContent>> m_childContent;
		// 選択カーソル
		shared_ptr<UIMainCommandCursor> m_childCursor;
		// 攻撃コマンドウィンドウ
		shared_ptr<UIAttackCommand> m_childAttackCommand;

		// 攻撃コマンドがアクティブか
		bool m_bAttackCommandActive = false;
		// メインコマンド選択
		bool m_bSelectMainCommand = false;
		CommandContent m_selectMainContent;
		// 子オブジェクトの生成
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

		// 初期化
		virtual void OnCreate() override;
		// 更新
		virtual void OnUpdate() override;

		// 選択されたコマンドごとの動き
		void CheckCommand();

		// 自分ごと表示非表示
		void SetActiveThis(bool set);


		// ゲッターセッター
		// 子オブジェクトの取得
		// 内容
		// 全部の見える見えない（DrawActiveとUpdateActive）
		void SetActiveToChildContents(bool set);
		// 全部
		vector<shared_ptr<UICommandContent>>& GetChildContents();
		// 1個ずつ
		shared_ptr<UICommandContent> GetChildContent(int index);
		// 内容ごとで1個
		shared_ptr<UICommandContent> GetChildContent(CommandContent content);
		// 内容の選択のリセット
		void ResetChildMainContents();
		// カーソル
		shared_ptr<UIMainCommandCursor> GetChildCursor();
		// 攻撃コマンドアクティブフラグ
		bool GetAttackCommandActive()const;
		void SetAttackCommandActive(bool set);
		// メインコマンド選択フラグ
		bool GetSelectMainCommand()const;
		void SetSelectMainCommand(bool set);
		// 選択された内容
		CommandContent GetSelectMainContent()const;
		void SetSelectMainContent(CommandContent content);
	};
}

//end basecross
