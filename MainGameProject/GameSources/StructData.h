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
		Vec3 position, rotation, scale;
		int layer;
		wstring texture;

		UIData(){}
		UIData(Vec3 pos, Vec3 rot, Vec3 sca, int layer, wstring texture) :
			position(pos), rotation(rot), scale(sca), layer(layer), texture(texture)
		{}
	};
}