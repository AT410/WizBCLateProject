/*!
@file ProjectShader.h
@brief プロジェクトで使用するシェーダー
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	
	struct GameBuffer
	{
		Mat4x4 World;

		Mat4x4 View;

		Mat4x4 Projection;

		Col4 Diffuse;

		Col4 Emissive;
	};

	DECLARE_DX11_CONSTANT_BUFFER(GBuffer, GameBuffer);
}
//end basecross

