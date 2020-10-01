#pragma once
#include "stdafx.h"

namespace structdata {
	struct ObjectData
	{
		Vec3 position, rotation, scale;
		int layer;
		wstring texture;

		ObjectData(){}
		ObjectData(Vec3 pos, Vec3 rot, Vec3 sca, int layer, wstring texture):
			position(pos), rotation(rot), scale(sca), layer(layer), texture(texture)
		{}
	};

	struct UIData
	{
		Vec2 position;
		Vec3 rotation;
		Vec2 size;
		Vec2 UVPosition;
		int layer;
		wstring texture;

		UIData(){}
		UIData(Vec2 pos, Vec3 rot, Vec2 size, Vec2 UVPos, int layer, wstring texture) :
			position(pos), rotation(rot), size(size), UVPosition(UVPos),layer(layer), texture(texture)
		{}
	};

	struct MapData
	{
		int mapState;
		int defaultMapState;
		Vec3 mapPos;
		int nowMapCost;
		int defaultMapCost;

		MapData(){}
		MapData(int defaultMapState, Vec3 mapPos, int defaultMapCost):
			mapState(defaultMapState), defaultMapState(defaultMapState), mapPos(mapPos), nowMapCost(defaultMapCost), defaultMapCost(defaultMapCost)
		{}
	};

	struct MapID
	{
		int x, y;
		Vec2 mapPos;
		MapID(){}
		MapID(int x, int y):
			x(x),y(y), mapPos((float)x,(float)y)
		{}
	};

	struct CharactorData
	{
		int HP;
		unsigned int charaID, jobID, Lv, Exp, MaxHP, Pow, Def, MoveRange;
		bool isDed = false;
		vector<unsigned int> weaponID;

		CharactorData() {}
		CharactorData(int charaID, int jobID, int Lv, int Exp, int MaxHP, int Pow, int Def, int MoveRenge, vector<unsigned int> weaponID):
			charaID(charaID), jobID(jobID), Lv(Lv), Exp(Exp), HP(MaxHP),
			MaxHP(MaxHP), Pow(Pow), Def(Def), MoveRange(MoveRenge), weaponID(weaponID)
		{}
	};

	struct CharactorCommandData
	{
		bool isAttacked, isMoved, isWaiting;

		CharactorCommandData() {}
		CharactorCommandData(bool isAttacked, bool isMoved, bool isWaiting) :
			isAttacked(isAttacked), isMoved(isMoved), isWaiting(isWaiting) {}
	};

	struct JobValueData
	{
		unsigned int baseHP, basePow, baseDef, moveRange;

		JobValueData() {}
		JobValueData(int HP, int Pow, int Def, int moveRenge) :
			baseHP(HP), basePow(Pow), baseDef(Def), moveRange(moveRenge)
		{}
	};

	struct CharactorValueData
	{
		unsigned int baseHP, basePow, baseDef, moveRange;

		CharactorValueData() {}
		CharactorValueData(int HP, int Pow, int Def) :
			baseHP(HP), basePow(Pow), baseDef(Def)
		{}
	};

	struct SavePlayerData
	{
		unsigned int jobID, Lv, Exp;
		vector<unsigned int> weaponID;

		SavePlayerData() {};
		SavePlayerData(int jobID, int Lv, int Exp, vector<unsigned int> weaponID) :
			jobID(jobID), Lv(Lv), Exp(Exp), weaponID(weaponID){}
	};

	struct WeaponData
	{
		unsigned int weponID, weponPow, weponDef, AttackRange;
		int weaponTag;

		WeaponData(){}
		WeaponData(int weponID, int weponPow, int weponDef, int AttackRange, int weaponTag):
		weponID(weponID), weponPow(weponPow), weponDef(weponDef), AttackRange(AttackRange), weaponTag(weaponTag){}
	};
}