/*!
@file ObjectBase.h
@brief �I�u�W�F�N�g�̐e�N���X
*/

#pragma once
#include "stdafx.h"
using namespace structdata;

namespace basecross {
	class ObjectBase : public GameObject {
	protected:
		vector<VertexPositionColorTexture> m_vertices;
		wstring m_textureName;
		
	public:
		Vec3 m_rotation;
		Vec3 m_scale;
		Vec3 m_position;
		int m_layer;

		ObjectBase(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position,
			int& Layer,
			wstring& Texture);

		ObjectBase(const shared_ptr<Stage>& stage,
			ObjectData& objectdata);

		virtual void OnCreate() override;

		//�Z�b�^�[
		//�͂����e�N�X�`�����w��
		void SetTexture(wstring texStr) {
			m_textureName = texStr;
			auto drawComp = AddComponent<PCTStaticDraw>();
			drawComp->SetTextureResource(m_textureName);	
		};
		
		//�e�N�X�`���𒣂�t����
		void DrawingImage(wstring texStr);

		//�e�N�X�`���𒣂�t����
		void DrawingImage(wstring texStr, Vec2 imageSize);
		
		//�g�����X�t�H�[����ݒ�
		void InitializeTransfrom();
	};

}

//end basecross