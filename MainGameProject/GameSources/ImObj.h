#pragma once
#include "stdafx.h"

#ifdef _BSImGui
namespace basecross
{
	//----------------------------------------------------------------------------
	//�V�X�e���\�����s��
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