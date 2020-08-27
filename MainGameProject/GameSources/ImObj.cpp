#include "stdafx.h"
#include "Project.h"

#ifdef _BSImGui
namespace basecross
{
	void SystemGui::OnInit()
	{
		m_selected = -1;
		m_objWindow = ImApp::GetApp()->AddImGuiObject<ShowObjGui>();
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
			ImGui::Text(u8"更新速度\t%.3f ms", stage->GetUpdatePerformanceTime());
			ImGui::Text(u8"描画速度\t%.3f ms", stage->GetDrawPerformanceTime());
			ImGui::Text(u8"物理速度\t%.3f ms", stage->GetCollisionPerformanceTime());
			ImGui::Text(u8"検証速度\t%.3f ms", stage->GetCollisionManager()->GetMiscPerformanceTime());
			ImGui::Text(u8"判定速度\t%.3f ms", stage->GetCollisionManager()->GetCollisionCountOfTern());
			ImGui::Text(u8"物体総数\t%d", stage->GetGameObjectVec().size());
		}

		// -- オブジェクト表示 --		
		if (ImGui::TreeNode(u8"オブジェクトリスト"))
		{
			auto stage = m_stage.lock();
			if (stage) 
			{
				if (ImGui::TreeNode(u8"カメラ及びライト"))
				{

					ImGui::TreePop();
				}

				if (ImGui::TreeNode(u8"配置オブジェクト")) 
				{
					for (int n = 0; n < stage->GetGameObjectVec().size(); n++)
					{
						ImGui::PushID(n);
						auto obj = stage->GetGameObjectVec()[n];
						if (ImGui::Selectable(obj->GetTypeName().c_str(), m_selected == n))
						{
							if (m_selected == n)
							{
								m_selected = -1;
								m_objWindow->SetActiveDraw(false);
								m_objWindow->SetTarget(nullptr);
							}
							else
							{
								m_selected = n;
								m_objWindow->SetActiveDraw(true);
								m_objWindow->SetTarget(obj);
							}
						}
						ImGui::PopID();
					}
					ImGui::TreePop();
				}
			}
			else
			{
				ImGui::Text(u8"ステージがターゲットされていません。");
			}
			ImGui::TreePop();
		}
		
		ImGui::End();
	}

	void ShowObjGui::OnInit()
	{
		m_Acitive = false;
	}

	void ShowObjGui::OnGUI()
	{
		if (m_Acitive) 
		{
			ImGui::Begin(u8"オブジェクトウィンドウ", &m_Acitive);
			auto target = m_target.lock();
			if (target)
			{
				auto TransComp = target->GetComponent<Transform>();
				auto pos = TransComp->GetPosition();
				auto scal = TransComp->GetScale();
				auto rot = TransComp->GetQuaternion();


				ImGui::DragFloat3(u8"配置座標", (float*)&pos, 0.01f); // Edit 3 floats representing a color
				TransComp->SetPosition(pos);

				ImGui::DragFloat4(u8"角度", (float*)&rot, 0.01f); // Edit 3 floats representing a color
				TransComp->SetQuaternion(rot);

				ImGui::DragFloat3(u8"スケール", (float*)&scal, 0.01f); // Edit 3 floats representing a color
				TransComp->SetScale(scal);

				auto DrawComp = target->GetComponent<SmBaseDraw>(false);
				if (DrawComp)
				{
					if (ImGui::TreeNode(u8"テクスチャ情報")) 
					{
						auto TexRes = DrawComp->GetTextureResource();
						if (TexRes)
						{
							ImVec2 size;
							size.x = static_cast<float>(TexRes->GetWidth());
							size.y = static_cast<float>(TexRes->GetHeight());
							ImGui::Text(u8"テクスチャサイズ %.f×%.f", size.x, size.y);
							ImGui::SameLine();
							ImGui::Text(u8"表示サイズ %.f×%.f", size.x / 2.0f, size.y / 2.0f);
							size.x /= 2.0f;
							size.y /= 2.0f;
							ImGui::Image(TexRes->GetShaderResourceView().Get(), size);
						}
						ImGui::TreePop();
					}
				}
			}

			ImGui::End();
		}
	}
}
#endif // _BSImGui