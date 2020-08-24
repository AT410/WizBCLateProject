/*!
@file UICommandContent.h
@brief UIコマンド内容クラス
*/

#pragma once
#include "stdafx.h"
using namespace structdata;
using namespace enumdata;

namespace basecross {
	class UICommandContent : public UIBase {
		// 親オブジェクト
		shared_ptr<GameObject> m_parent;

		// 内容
		CommandContent m_content;

		// アクティブかどうか
		bool m_bCommandActive = true;

		// アクティブ中と非アクティブ中の色
		Col4 m_colorCommandActive = Col4(1.0f, 1.0f, 1.0f, 1.0f);// 白
		Col4 m_colorCommandPassive = Col4(0.5f, 0.5f, 0.5f, 1.0f);// グレー

	public:
		UICommandContent(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec2& size,
			Vec2& position,
			Vec2& UVPos,
			int layer,
			CommandContent& content,
			const shared_ptr<GameObject>& parent = nullptr);

		UICommandContent(const shared_ptr<Stage>& stage,
			UIData& UIdata,
			CommandContent& content,
			const shared_ptr<GameObject>& parent = nullptr);

		virtual void OnCreate() override;

		// 内容別のテクスチャセット
		void SetTexture(CommandContent content);

		// ステート
		// アクティブ
		void StateCommandActive();
		// 非アクティブ(押せないことを分かりやすく)
		void StateCommandPassive();

		// セッターゲッター
		// アクティブか
		void SetCommandActive(bool set);
		bool GetCommandActive()const;
		// 内容
		CommandContent GetContent()const;
	};
}

//end basecross
