/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Character::Character(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec3& position,
		int& Layer,
		wstring& Texture):
	ObjectBase(stage, rotation, scale, position, Layer, Texture)
	{}

	Character::Character(const shared_ptr<Stage>& stage,
		ObjectData& objectData, CharactorData& charactorData,
		CharactorCommandData& charactorCommandData):
	ObjectBase(stage, objectData), m_charactorData(charactorData), 
		m_charactorCommandData(charactorCommandData)
	{} 

	void Character::OnCreate() {
		DrawingImage(m_textureName);
		InitializeTransfrom();
	}

	void Character::DestroyCharacter() {
		SetDrawActive(false);
	}

	void Character::MoveCharacter(Vec3 pos) {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetPosition(pos);
	}

}
//end basecross
