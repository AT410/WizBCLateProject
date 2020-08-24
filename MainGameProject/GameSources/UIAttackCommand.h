/*!
@file UIAttackCommand.h
@brief UI攻撃コマンドクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIAttackCommand : public UIBase {
		// 親オブジェクト	
		// メインコマンド
		shared_ptr<GameObject> m_parent;

		// 子オブジェクト
		// 内容
		vector<shared_ptr<UIAttackCommandContent>> m_childContent;
		// 選択カーソル
		shared_ptr<UIAttackCommandCursor> m_childCursor;

		// 選択されたコマンド
		bool m_bSelectAttackCommand;
		AttackCommandContent m_selectAttackContent;

		// 子オブジェクトの生成
		void CreateChild();
	public:
		UIAttackCommand(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec2& size,
			Vec2& position,
			Vec2& UVPos,
			int layer,
			wstring tex,
			const shared_ptr<GameObject>& parent = nullptr);

		UIAttackCommand(const shared_ptr<Stage>& stage,
			UIData& UIdata,
			const shared_ptr<GameObject>& parent = nullptr);

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
		vector<shared_ptr<UIAttackCommandContent>>& GetChildContents();
		// 1個ずつ
		shared_ptr<UIAttackCommandContent> GetChildContent(int index);
		// 内容ごとで1個
		shared_ptr<UIAttackCommandContent> GetChildContent(AttackCommandContent content);
		// 内容の選択のリセット
		void ResetChildAttackContents();
		// 攻撃コマンド選択フラグ
		bool GetSelectAttackCommand()const;
		void SetSelectAttackCommand(bool set);
		// 選択された内容
		AttackCommandContent GetSelectAttackContent()const;
		void SetSelectAttackContent(AttackCommandContent content);
		// カーソル
		shared_ptr<UIAttackCommandCursor> GetChildCursor();
	};
}

//end basecross
