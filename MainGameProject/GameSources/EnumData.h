#pragma once
#include "stdafx.h"

namespace enumdata {
	// �R�}���h�̎�ށiAttack:�U��,Move:�ړ�,Wait:�ҋ@,TurnEnd:�^�[���I���j
	enum CommandContent{ Attack, Move, Wait, TurnEnd};

	// �U���R�}���h�̎��(����)
	enum AttackCommandContent{ Weapon1, Weapon2 };

	//�Q�[���̃X�e�[�g�p
	enum eGameStateNum {
		choicePlayer,	//�v���C���[�I��
		choiceAction,	//�R�}���h�I��
		choiceWeapon,	//����I��
		choiceMap,		//�}�b�v�I��
		choiceEnemy,	//�G�I��
		turnEnd,		//�^�[���G���h
	};

}