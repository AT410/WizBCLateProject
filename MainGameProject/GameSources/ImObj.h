#pragma once
#include "stdafx.h"

#ifdef _BSImGui
namespace basecross
{
	//----------------------------------------------------------------------------
	//システム表示を行う
	//----------------------------------------------------------------------------
	class SystemGui : public ImGuiObject
	{
	public:
		SystemGui(){}

		void OnInit()override;

		void OnGUI()override;

	private:
		weak_ptr<Stage> m_stage;
		int m_selected;
	};

	//----------------------------------------------------------------------------
	//オブジェクトImGui
	//----------------------------------------------------------------------------
	class ShowObjGui : public ImGuiObject
	{
	public:
		ShowObjGui(){}

		void OnInit()override;

		void OnGUI()override;
	private:
		weak_ptr<GameObject> m_target;
	};
}
#endif // _BSImGui