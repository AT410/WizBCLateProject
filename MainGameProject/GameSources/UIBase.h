/*!
@file ObjectBase.h
@brief �I�u�W�F�N�g�̐e�N���X
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

		//�͂����e�N�X�`�����w��
		void ResetTexture(wstring texStr);

		//�e�N�X�`���𒣂�t����
		void DrawingImage(Vec2 halfSize, Vec2 texSize);

		//�g�����X�t�H�[����ݒ�
		void InitializeTransfrom();

		virtual void OnCreate() override;

	};
}

//end basecross
