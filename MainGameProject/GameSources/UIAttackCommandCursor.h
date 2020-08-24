/*!
@file UIAttackCommandCursor.h
@brief UIメインコマンドのカーソルクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIAttackCommandCursor : public UIBase {
		// 親オブジェクト
		shared_ptr<GameObject> m_parent;
		// 親の親（メインコマンドウィンドウのオブジェクト）
		shared_ptr<GameObject> m_parentToMainCommand;

		// カウント
		int m_count = 0;
		// 最大カウント(enumの最後の値が最大カウント)[0を含めるため]
		int m_maxCount = AttackCommandContent::Weapon2;
		// カーソル移動クールタイム
		float m_moveCoolTime = 0.2f;
		float m_totalMoveCoolTime = 0.0f;
		// クールタイム中
		bool m_bCoolTime = false;
		// クールタイム計算
		void CalcCoolTime();

		// カーソルの移動
		void MoveCursor();
		// Aボタン
		void OnPushA();
		// Bボタン
		void OnPushB();


	public:
		UIAttackCommandCursor(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec2& size,
			Vec2& position,
			Vec2& UVPos,
			int layer,
			wstring tex,
			const shared_ptr<GameObject>& parent = nullptr);

		UIAttackCommandCursor(const shared_ptr<Stage>& stage,
			UIData& UIdata,
			const shared_ptr<GameObject>& parent = nullptr);

		// 初期化
		virtual void OnCreate() override;
		void InitPosition();
		// 更新
		virtual void OnUpdate() override;

	};
}

//end basecross
