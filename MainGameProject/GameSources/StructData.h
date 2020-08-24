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
		Vec3 mapPos;
		int defaultMapCost;
		int nowMapCost;

		MapData(){}
		MapData(Vec3 mapPos, int defaultMapCost, int nowMapCost):
			mapPos(mapPos), defaultMapCost(defaultMapCost), nowMapCost(nowMapCost)
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
		unsigned int charaID, jobID, Lv, Exp, HP, Pow, Def, MoveRange, AttackRange;

		CharactorData() {}
		CharactorData(int charaID, int jobID, int Lv, int Exp, int HP, int Pow, int Def, int MoveRenge, int AttackRange):
			charaID(charaID), jobID(jobID), Lv(Lv), Exp(Exp), HP(HP), Pow(Pow), Def(Def), MoveRange(MoveRenge), AttackRange(AttackRange)
		{};
	};

	struct CharactorCommandData
	{
		bool isAttacked, isMoved, isWaiting;

		CharactorCommandData() {}
		CharactorCommandData(bool isAttacked, bool isMoved, bool isWaiting):
		isAttacked(isAttacked), isMoved(isMoved), isWaiting(isWaiting) {}
	};

	struct LevelUPBonus
	{

	};
}