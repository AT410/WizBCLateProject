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
		Vec3 mapPos;
		int defaultMapCost;
		int nowMapCost;

		MapData(){}
		MapData(int mapState, Vec3 mapPos, int defaultMapCost, int nowMapCost):
			mapState(mapState), mapPos(mapPos), defaultMapCost(defaultMapCost), nowMapCost(nowMapCost)
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
		unsigned int charaID, jobID, Lv, Exp, HP, MaxHP, Pow, Def, MoveRange;
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

	struct JobData
	{
		unsigned int baseMaxHP, basePow, baseDef, MoveRange;

		JobData() {}
		JobData(int MaxHP, int Pow, int Def, int MoveRenge) :
			baseMaxHP(MaxHP), basePow(Pow), baseDef(Def), MoveRange(MoveRenge)
		{}
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