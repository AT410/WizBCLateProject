/*!
@file ObjectBase.cpp
@brief ゲームオブジェクト親クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ObjectBase::ObjectBase(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec3& position,
		int& layer,
		wstring& texture) :
	GameObject(stage),
		m_rotation(rotation),
		m_scale(scale),
		m_position(position),
		m_layer(layer),
		m_textureName(texture)
	{}

	ObjectBase::ObjectBase(const shared_ptr<Stage>& stage,
		ObjectData& objectdata) :
		GameObject(stage),
		m_rotation(objectdata.rotation),
		m_scale(objectdata.scale),
		m_position(objectdata.position),
		m_layer(objectdata.layer),
		m_textureName(objectdata.texture)
	{}

	void ObjectBase::OnCreate() {
		DrawingImage(m_textureName);
		InitializeTransfrom();
	}

	void ObjectBase::DrawingImage(wstring texStr) {
		Col4 color(1, 1, 1, 1);
		Vec2 tipSize = Vec2(1.0f, 1.0f);

		m_vertices =
		{
			{Vec3(-1.0f,+1.0f,0.0f),color,Vec2(0		,0)},
			{Vec3(+1.0f,+1.0f,0.0f),color,Vec2(tipSize.x,0)},
			{Vec3(-1.0f,-1.0f,0.0f),color,Vec2(0		,tipSize.y)},
			{Vec3(+1.0f,-1.0f,0.0f),color,Vec2(tipSize.x,tipSize.y)},
		};

		vector<uint16_t> indices =
		{
			0,1,2,
			2,1,3,
		};

		auto drawComp = AddComponent<PCTStaticDraw>();
		drawComp->CreateOriginalMesh<VertexPositionColorTexture>(m_vertices, indices);
		drawComp->SetOriginalMeshUse(true);

		//テクスチャの取得、貼り付け
		auto &app = App::GetApp();
		auto texDir = app->GetDataDirWString();

		//アルファ値を有効にする
		m_textureName = texStr;
		drawComp->SetTextureResource(m_textureName);
		this->SetAlphaActive(true);

		SetDrawLayer(m_layer);
	}

	//画像サイズを変えられる描画処理
	void ObjectBase::DrawingImage(wstring texStr, Vec2 imageSize) {
		m_textureName = texStr;
		Col4 color(1, 1, 1, 1);
		float maxTipSize = 1.0f;
		float mimTipSize = 0.0f;

		m_vertices =
		{
			{Vec3(-imageSize.x,+imageSize.y,0.0f),color,Vec2(mimTipSize,mimTipSize)},
			{Vec3(+imageSize.x,+imageSize.y,0.0f),color,Vec2(maxTipSize,mimTipSize)},
			{Vec3(-imageSize.x,-imageSize.y,0.0f),color,Vec2(mimTipSize,maxTipSize)},
			{Vec3(+imageSize.x,-imageSize.y,0.0f),color,Vec2(maxTipSize,maxTipSize)},
		};

		vector<uint16_t> indices =
		{
			0,1,2,
			2,1,3,
		};

		auto drawComp = AddComponent<PCTStaticDraw>();
		//テクスチャがループするように設定
		drawComp->SetSamplerState(SamplerState::PointWrap);
		drawComp->CreateOriginalMesh<VertexPositionColorTexture>(m_vertices, indices);
		drawComp->SetOriginalMeshUse(true);

		//テクスチャの取得、貼り付け
		auto &app = App::GetApp();
		auto texDir = app->GetDataDirWString();

		//アルファ値を有効にする
		drawComp->SetTextureResource(m_textureName);
		this->SetAlphaActive(true);

		SetDrawLayer(m_layer);
	}

	void ObjectBase::InitializeTransfrom() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetRotation(m_rotation);
		ptrTransform->SetPosition(m_position);
	}

}
//end basecross
