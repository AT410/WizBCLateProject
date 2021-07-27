/*!
@breif　プロジェクト定義の描画機能
*/
#pragma once
#include "stdafx.h"

namespace basecross
{
	class MapTipDraw :public SmBaseDraw
	{
	public:
		explicit MapTipDraw(const shared_ptr<GameObject>& GameObjectPtr);

		~MapTipDraw();

		void OnCreate()override;

		void OnDraw()override;

	private:
		struct Impl;
		unique_ptr<Impl> m_pImpl;
	};
}