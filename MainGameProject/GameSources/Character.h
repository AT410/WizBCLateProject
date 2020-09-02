/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Character : public ObjectBase {

	public:
		Character(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position,
			int& Layer,
			wstring& Texture);

		Character(const shared_ptr<Stage>& stage,
			ObjectData& objectdata);

		virtual void OnCreate() override;

		void DestroyCharacter();

		void MoveCharacter(Vec3 pos);
	};

}
//end basecross
