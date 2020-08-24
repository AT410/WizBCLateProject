#pragma once
#include "stdafx.h"

namespace enumdata {
	// コマンドの種類（Attack:攻撃,Move:移動,Wait:待機,TurnEnd:ターン終了）
	enum CommandContent{ Attack, Move, Wait, TurnEnd};

	// 攻撃コマンドの種類(武器)
	enum AttackCommandContent{ Weapon1, Weapon2 };

}