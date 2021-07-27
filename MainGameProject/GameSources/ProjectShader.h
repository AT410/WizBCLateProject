/*!
@file ProjectShader.h
@brief �v���W�F�N�g�Ŏg�p����V�F�[�_�[
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

