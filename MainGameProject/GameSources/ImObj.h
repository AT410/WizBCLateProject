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
	};
}
#endif // _BSImGui