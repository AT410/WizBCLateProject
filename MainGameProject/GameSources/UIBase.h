/*!
@file ObjectBase.h
@brief オブジェクトの親クラス
*/

#pragma once
#include "stdafx.h"
using namespace structdata;

namespace basecross {
	class UIBase : public GameObject {
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

	public:
		Vec3 m_rotation;
		Vec3 m_scale;
		Vec2 m_size;
		Vec2 m_position;
		int m_layer;
		wstring m_textureName;

		UIBase(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			int layer,
			wstring tex);

		UIBase(const shared_ptr<Stage>& stage,
			UIData& UIdata);

		//はりつけるテクスチャを指定
		void ResetTexture(wstring texStr);

		//テクスチャを張り付ける
		void DrawingImage(Vec2 halfSize, Vec2 texSize);

		//トランスフォームを設定
		void InitializeTransfrom();

		virtual void OnCreate() override;

	};
}

//end basecross
