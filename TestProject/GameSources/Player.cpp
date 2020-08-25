/*!
@file Player.cpp
@brief ÉvÉåÉCÉÑÅ[Ç»Ç«é¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	TestCube::TestCube(const shared_ptr<Stage>& StagePtr,const string& name)
		:GameObject(StagePtr),m_name(name)
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

