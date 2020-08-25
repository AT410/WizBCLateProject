/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class TestCube : public GameObject
	{
	public:
		//-- �\�z --
		TestCube(const shared_ptr<Stage>& StagePtr);

		//-- �j�� --
		virtual ~TestCube() {}

		//-- ������ --
		void OnCreate()override;

		//-- �X�V���� --
		void OnUpdate()override;

		void SetMeshCol(const Col4 col);

		Col4 GetMeshCol();

	private:

	};

}
//end basecross

