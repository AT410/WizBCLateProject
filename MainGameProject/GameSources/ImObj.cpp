#include "stdafx.h"
#include "Project.h"

#ifdef _BSImGui
namespace basecross
{
	void SystemGui::OnInit()
	{

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

		ImGui::Begin(u8"システム情報");
		auto &style = ImGui::GetStyle();
		ImGui::SliderFloat(u8"透明度", &style.Alpha, 0.5f, 1.0f);
		ImGui::Text(u8"実効速度 平均 %.3f ms/frame (%.1f FPS)", 
			1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("ElapsedTime\t%.3f ms", App::GetApp()->GetElapsedTime());
		auto stage = m_stage.lock();
		if (stage)
		{
			ImGui::Text("UpdatePerformance\t%.3f ms", stage->GetUpdatePerformanceTime());
			ImGui::Text("DrawPerformance\t%.3f ms", stage->GetDrawPerformanceTime());
			ImGui::Text("CollisionPerform\t%.3f ms", stage->GetCollisionPerformanceTime());
			ImGui::Text("ColMiscPerform\t%.3f ms", stage->GetCollisionManager()->GetMiscPerformanceTime());
			ImGui::Text("CollisionCountOfTern\t%.3f ms", stage->GetCollisionManager()->GetCollisionCountOfTern());
			ImGui::Text("ObjectCount\t%d", stage->GetGameObjectVec().size());
		}

		ImGui::End();
	}
}
#endif // _BSImGui