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
		shared_ptr<ShowObjGui> m_MapTipWindow;
		int m_selected;

		bool m_example;
	};

	//----------------------------------------------------------------------------
	//オブジェクトImGui
	//----------------------------------------------------------------------------
	class ShowObjGui : public ImGuiObject
	{
	public:
		ShowObjGui(const string& name)
			:m_windowName(name)
		{}

		void OnInit()override;

		void OnGUI()override;

		void SetTarget(const shared_ptr<GameObject>& obj) { m_target = obj; }

		void SetActiveDraw(const bool Active) { m_Acitive = Active; }

	protected:
		string m_windowName;
		weak_ptr<GameObject> m_target;
		bool m_Acitive;
	};

	//----------------------------------------------------------------------------
	//MapImGui
	//----------------------------------------------------------------------------
	class MapGui:public ShowObjGui
	{
	public:
		void OnInit()override;

		void OnGUI()override;

	private:

	};
}
#endif // _BSImGui