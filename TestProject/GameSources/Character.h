/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class DebugTest : public GameObject
	{
	public:
		//-- �\�z --
		DebugTest(const shared_ptr<Stage>& StagePtr);

		//-- �j�� --
		virtual ~DebugTest() {}

		//-- ������ --
		void OnCreate()override;

		//-- �X�V���� --
		void OnUpdate()override;

	private:

	};

}
//end basecross
