/*!
@file UIBase.cpp
@brief �Q�[���I�u�W�F�N�g�e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	UIBase::UIBase(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec2& size,
		Vec2& position,
		Vec2& UVPos,
		int layer,
		wstring tex) :
		GameObject(stage),
		m_rotation(rotation),
		m_size(size),
		m_position(position),
		m_UVPosition(UVPos),
		m_layer(layer),
		m_textureName(tex)
	{
		m_scale = Vec3(1.0f);
	}

	UIBase::UIBase(const shared_ptr<Stage>& stage,
		UIData& UIdata):
		GameObject(stage),
		m_rotation(UIdata.rotation),
		m_size(UIdata.size),
		m_position(UIdata.position),
		m_UVPosition(UIdata.UVPosition),
		m_layer(UIdata.layer),
		m_textureName(UIdata.texture)
	{
		m_scale = Vec3(1.0f);
	}

	void UIBase::DrawingImage(Vec2 halfSize, Vec2 texSize) {
		Col4 color(1, 1, 1, 1);

		vector<VertexPositionColorTexture> vertices = {
			{VertexPositionColorTexture(Vec3(-halfSize.x,+halfSize.y,0),color,Vec2(texSize.x,texSize.x))},
			{VertexPositionColorTexture(Vec3(+halfSize.x,+halfSize.y,0),color,Vec2(texSize.y,texSize.x))},
			{VertexPositionColorTexture(Vec3(-halfSize.x,-halfSize.y,0),color,Vec2(texSize.x,texSize.y))},
			{VertexPositionColorTexture(Vec3(+halfSize.x,-halfSize.y,0),color,Vec2(texSize.y,texSize.y))}
		};
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetPivot(0.0f, 0.0f, 0.0f);

		//�e�N�X�`���̓\��t��
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetSamplerState(SamplerState::LinearWrap);
		drawComp->SetTextureResource(m_textureName);

		this->SetAlphaActive(true);

		//���C���[�̐ݒ�
		SetDrawLayer(m_layer);
	}

	//�g�����X�t�H�[����ݒ�
	void UIBase::InitializeTransfrom() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetRotation(m_rotation);
		ptrTransform->SetPosition(m_position.x, m_position.y, 0.0f);
	}

	void UIBase::ResetTexture(wstring texStr) {
		m_textureName = texStr;
		// �e�N�X�`���̓\��t��
		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->SetSamplerState(SamplerState::LinearWrap);

		//�e�N�X�`���̎擾�A�\��t��
		drawComp->SetTextureResource(m_textureName);
	};

	void UIBase::OnCreate() {
		DrawingImage(m_size, m_UVPosition);
		InitializeTransfrom();
	}

}
//end basecross
