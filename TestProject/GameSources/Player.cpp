/*!
@file Player.cpp
@brief ƒvƒŒƒCƒ„[‚È‚ÇÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	TestCube::TestCube(const shared_ptr<Stage>& StagePtr)
		:GameObject(StagePtr)
	{
	}

	void TestCube::OnCreate()
	{
		auto DrawRes = AddComponent<PCTStaticDraw>();
		DrawRes->SetMeshResource(L"DEFAULT_CUBE");
		DrawRes->SetEmissive(Col4(0));
		
		SetAlphaActive(true);
	}

	void TestCube::OnUpdate()
	{

	}

	void TestCube::SetMeshCol(const Col4 col)
	{
		auto DrawRes = GetComponent<PCTStaticDraw>();
		DrawRes->SetEmissive(col);
	}

	Col4 TestCube::GetMeshCol()
	{
		auto DrawRes = GetComponent<PCTStaticDraw>();
		return DrawRes->GetEmissive();
	}
}
//end basecross

