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
}