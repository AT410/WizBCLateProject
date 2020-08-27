#pragma once
#include "stdafx.h"

#ifdef _BSImGui
namespace basecross
{
	class ShowObjGui;

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
		shared_ptr<ShowObjGui> m_objWindow;
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

		void SetTarget(const shared_ptr<GameObject>& obj) { m_target = obj; }

		void SetActiveDraw(const bool Active) { m_Acitive = Active; }

	private:
		weak_ptr<GameObject> m_target;
		bool m_Acitive;
	};
}
#endif // _BSImGui