#pragma once
#include "stdafx.h"

namespace enumdata {
	// コマンドの種類（Attack:攻撃,Move:移動,Wait:待機,TurnEnd:ターン終了）
	enum CommandContent{ Attack, Move, Wait, TurnEnd};

	// 攻撃コマンドの種類(武器)
	enum AttackCommandContent{ Weapon1, Weapon2 };

	//ゲームのステート用
	enum eGameStateNum {
		choicePlayer,	//プレイヤー選択
		choiceAction,	//コマンド選択
		choiceWeapon,	//武器選択
		choiceMap,		//マップ選択
		choiceEnemy,	//敵選択
		turnEnd,		//ターンエンド
	};

}