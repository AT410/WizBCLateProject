/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

using namespace structdata;
using namespace enumdata;

namespace basecross{
	class Character : public ObjectBase {
		bool m_isDed;
		unsigned int m_choiceWeaponID;
		CharactorData m_charactorData;
		CharactorCommandData m_charactorCommandData;

	public:
		Character(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position,
			int& Layer,
			wstring& Texture);

		Character(const shared_ptr<Stage>& stage,
			ObjectData& objectData, CharactorData& charactorData,
			CharactorCommandData& charactorCommandData);

		virtual void OnCreate() override;

		unsigned int GetChoiceWeaponID() { return m_choiceWeaponID; };
		void SetChoiceWeaponID(unsigned int set) { m_choiceWeaponID = set; };


		void DestroyCharacter();

		void MoveCharacter(Vec3 pos);
	};

}
//end basecross
