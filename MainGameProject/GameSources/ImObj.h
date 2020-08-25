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
		int m_selected;
	};

	//----------------------------------------------------------------------------
	//�I�u�W�F�N�gImGui
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