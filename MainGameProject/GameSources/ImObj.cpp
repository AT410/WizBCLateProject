#include "stdafx.h"
#include "Project.h"

#ifdef _BSImGui
namespace basecross
{
	void SystemGui::OnInit()
	{
		m_selected = -1;
	}

	void SystemGui::OnGUI()
	{
		if (m_stage.lock() == nullptr)
		{
			auto &stage = App::GetApp()->GetScene<Scene>()->GetActiveStage(false);
			if (stage == nullptr)
				return;
			stage->SetCollisionPerformanceActive(true);
			stage->SetUpdatePerformanceActive(true);
			stage->SetDrawPerformanceActive(true);

			m_stage = stage;
		}

		ImGui::Begin(u8"�V�X�e�����");
		auto &style = ImGui::GetStyle();
		ImGui::SliderFloat(u8"�����x", &style.Alpha, 0.5f, 1.0f);
		ImGui::Text(u8"�������x ���� %.3f ms/frame (%.1f FPS)", 
			1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("ElapsedTime\t%.3f ms", App::GetApp()->GetElapsedTime());
		auto stage = m_stage.lock();
		if (stage)
		{
			ImGui::Text(u8"�X�V���x\t%.3f ms", stage->GetUpdatePerformanceTime());
			ImGui::Text(u8"�`�摬�x\t%.3f ms", stage->GetDrawPerformanceTime());
			ImGui::Text(u8"�������x\t%.3f ms", stage->GetCollisionPerformanceTime());
			ImGui::Text(u8"���ؑ��x\t%.3f ms", stage->GetCollisionManager()->GetMiscPerformanceTime());
			ImGui::Text(u8"���葬�x\t%.3f ms", stage->GetCollisionManager()->GetCollisionCountOfTern());
			ImGui::Text(u8"���̑���\t%d", stage->GetGameObjectVec().size());
		}

		// -- �I�u�W�F�N�g�\�� --		
		if (ImGui::TreeNode(u8"�I�u�W�F�N�g���X�g"))
		{
			for (int n = 1; n < 5; n++)
			{
				if (ImGui::Selectable("Object", m_selected == n, ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowDoubleClick))
				{
					if (m_selected == n)
					{
						m_selected = -1;
					}
					else
					{
						m_selected = n;
					}

				}
			}

			ImGui::TreePop();
		}
		
		ImGui::End();
	}

	void ShowObjGui::OnInit()
	{

	}

	void ShowObjGui::OnGUI()
	{

	}
}
#endif // _BSImGui