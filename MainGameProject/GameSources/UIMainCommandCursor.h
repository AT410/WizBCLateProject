/*!
@file UIMainCommandCursor.h
@brief UIメインコマンドのカーソルクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIMainCommandCursor : public UIBase {
		// 親オブジェクト
		shared_ptr<GameObject> m_parent;

		// カウント
		int m_count = 0;
		// 最大カウント(enumの最後の値が最大カウント)
		int m_maxCount = (int)CommandContent::TurnEnd;
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
		UIMainCommandCursor(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec2& size,
			Vec2& position,
			Vec2& UVPos,
			int layer,
			wstring tex,
			const shared_ptr<GameObject>& parent = nullptr);

		UIMainCommandCursor(const shared_ptr<Stage>& stage,
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
