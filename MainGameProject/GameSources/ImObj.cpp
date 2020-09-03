#include "stdafx.h"
#include "Project.h"

#ifdef _BSImGui
namespace basecross
{
	void SystemGui::OnInit()
	{
		m_selected = -1;
		m_example = false;
		m_objWindow = ImApp::GetApp()->AddImGuiObject<ShowObjGui>(u8"�I�u�W�F�N�g�E�B���h�E");
		m_MapTipWindow = ImApp::GetApp()->AddImGuiObject<MapGui>(u8"�ڍ׃E�B���h�E");
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

		// -- ���݈ʒu�̏ڍו\�� --
		string buttonstr = m_example == true ? u8"����" : u8"�ڍ�";
		if (ImGui::Button(buttonstr.c_str()))
		{
			m_example = !m_example;
			m_MapTipWindow->SetActiveDraw(m_example);
			// -- ���݃J�[�\���������Ă���f�[�^�����o�� --

		}

		// -- �I�u�W�F�N�g�\�� --		
		if (ImGui::TreeNode(u8"�I�u�W�F�N�g���X�g"))
		{
			auto stage = m_stage.lock();
			if (stage) 
			{
				if (ImGui::TreeNode(u8"�J�����y�у��C�g"))
				{

					ImGui::TreePop();
				}

				if (ImGui::TreeNode(u8"�z�u�I�u�W�F�N�g")) 
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
				ImGui::Text(u8"�X�e�[�W���^�[�Q�b�g����Ă��܂���B");
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
			ImGui::Begin(m_windowName.c_str());
			auto target = m_target.lock();
			if (target)
			{
				auto TransComp = target->GetComponent<Transform>();
				auto pos = TransComp->GetPosition();
				auto scal = TransComp->GetScale();
				auto rot = TransComp->GetQuaternion();


				ImGui::DragFloat3(u8"�z�u���W", (float*)&pos, 0.01f); // Edit 3 floats representing a color
				TransComp->SetPosition(pos);

				ImGui::DragFloat4(u8"�p�x", (float*)&rot, 0.01f); // Edit 3 floats representing a color
				TransComp->SetQuaternion(rot);

				ImGui::DragFloat3(u8"�X�P�[��", (float*)&scal, 0.01f); // Edit 3 floats representing a color
				TransComp->SetScale(scal);

				auto DrawComp = target->GetComponent<SmBaseDraw>(false);
				if (DrawComp)
				{
					if (ImGui::TreeNode(u8"�e�N�X�`�����")) 
					{
						auto TexRes = DrawComp->GetTextureResource();
						if (TexRes)
						{
							ImVec2 size;
							size.x = static_cast<float>(TexRes->GetWidth());
							size.y = static_cast<float>(TexRes->GetHeight());
							ImGui::Text(u8"�e�N�X�`���T�C�Y %.f�~%.f", size.x, size.y);
							ImGui::SameLine();
							ImGui::Text(u8"�\���T�C�Y %.f�~%.f", size.x / 2.0f, size.y / 2.0f);
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

	//----------------------------------------------------------------------------
	//MapGui
	//----------------------------------------------------------------------------
	void MapGui::OnInit()
	{

	}

	void MapGui::OnGUI()
	{
		if (m_Acitive)
		{
			auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage(false);
			if (stage)
			{
				auto gamestage = dynamic_pointer_cast<GameStage>(stage);
				if (gamestage == nullptr)
					return;

				auto ptr = m_Controll.lock();
				if (ptr == nullptr)
				{
					ptr = gamestage->GetSharedGameObject<MapCursor>(L"Cursor");
				}

				ImGui::Begin(m_windowName.c_str());
				auto id = ptr->GetID();
				auto mapdata = gamestage->GetMapData(id);

				// -- �}�b�v�f�[�^ --
				ImGui::Text(u8"�W���}�b�v�R�X�g�F\t%d", mapdata.defaultMapCost);
				ImGui::Text(u8"���݂̃}�b�v�R�X�g:\t%d", mapdata.nowMapCost);

				string statestr;
				switch (mapdata.mapState)
				{
				case eXMLMapStateNum::Normal:
					statestr = u8"NORMAL";
					break;
				case eXMLMapStateNum::Forest:
					statestr = u8"FOREST";
					break;
				case eXMLMapStateNum::NotAvailable:
					statestr = u8"NotAvailable";
					break;
				case eXMLMapStateNum::Player1Chara:
					statestr = u8"Player1";
					break;
				case eXMLMapStateNum::Player2Chara:
					statestr = u8"Player2";
					break;
				case eXMLMapStateNum::Player3Chara:
					statestr = u8"Player3";
					break;
				case eXMLMapStateNum::Player4Chara:
					statestr = u8"Player4";
					break;
				default:
					statestr = u8"MissingState";
					break;
				}

				string result = u8"�}�b�v�X�e�[�g:\t" + statestr;
				ImGui::Text(result.c_str());
				ImGui::End();
			}
		}
	}
}
#endif // _BSImGui