/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -50.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		m_ptrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(m_ptrCamera);
		m_ptrCamera->SetEye(eye);
		m_ptrCamera->SetAt(at);

		//�J�����̉��ߖ@��؂�
		m_ptrCamera->SetPers(false);

		//���̒l��ݒ�
		float width = 3.2 * 12;
		float height = 2.0 * 12;

		//�J�������f���͈͂�ݒ�
		m_ptrCamera->SetWidth(width);
		m_ptrCamera->SetHeight(height);
		//����p��ݒ�
		m_ptrCamera->SetFovY(1.0f);

		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			auto charaObjData = structdata::ObjectData(Vec3(0.0f), Vec3(1.0f), Vec3(0.0f),0, L"thumbnail.png");
			auto uiData = structdata::UIData(Vec2(0.0f), Vec3(0.0f), Vec2(150.0f, 200.0f), Vec2(0.0f, 1.0f), 5, L"menu.png");

			//�`��̊m�F�p�ɉ摜�𐶐�
			AddGameObject<ObjectBase>(charaObjData);

			AddGameObject<MapCreator>();
			AddGameObject<UIMainCommand>(uiData);

#ifdef _BSImGui
			ImApp::GetApp()->AddImGuiObject<SystemGui>();
#endif // _BSImGui

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {

	}

	void GameStage::UpDateCameraPos(Vec2 at) {
		Vec3 setCameraEye = Vec3(at.x, at.y, m_ptrCamera->GetEye().z);
		Vec3 setCameraAt = Vec3(at.x, at.y, m_ptrCamera->GetAt().z);

		m_ptrCamera->SetEye(setCameraEye);
		m_ptrCamera->SetAt(setCameraAt);
	}

	void GameStage::ChangeGameStateNum(eGameStateNum gameState) {
		m_gameStateNum = gameState;
	}

	void GameStage::ConfirmationCharacter() {
		for (int i = 0; i < m_charactorMapID[m_playerTurnNum].size(); i++) {
			if (m_charactorMapID[m_playerTurnNum][i].mapPos == m_choiceMapID.mapPos) {
				m_choiceCharactorID = i;
				//m_charactorCommandData;
				MessageBox(0, L"�E�L�E��E��E��E��E�N�E�^�E�[�E��E��E��E��E��E�", L"�E�L�E��E��E��E��E�N�E�^�E�[�E�ԍ��E�F"+ i, 0);
				//�E�L�E��E��E��E��E�N�E�^�E�[�E�̃R�E�}�E��E��E�h�E�I�E��E��E�Ԃɂ��E��E�
				SettingMoveCostMap();
				return;
			}
		}
	}

	void GameStage::ConfirmationMove() {
		if (m_mapData[m_choiceMapID.y][m_choiceMapID.x].nowMapCost != eXMLMapStateNum::NotAvailable) {
			for (int i = 0; i < m_canActionMapID.size(); i++) {
				if (m_canActionMapID[i].mapPos == m_choiceMapID.mapPos) {
					m_charactorMapID[m_playerTurnNum][m_choiceCharactorID] = m_choiceMapID;
					m_charactorCommandData[m_playerTurnNum][m_choiceCharactorID].isMoved = true;
					ResetCanActionMapID();
					return;
				}
			}
		}
	}

	void GameStage::ConfirmationAttack() {
		for (int i = 0; i < m_charactorMapID.size(); i++) {
			if (i != m_playerTurnNum) {
				SerchCharactor(i);
			}
		}
	}

	void GameStage::SerchCharactor(int playerNum) {
		for (int i = 0; i < m_charactorMapID[playerNum].size(); i++) {
			if (m_choiceMapID.mapPos == m_charactorMapID[playerNum][i].mapPos) {
				//�E�U�E��E��E�\
				m_charactorCommandData[m_playerTurnNum][m_choiceCharactorID].isAttacked = true;
			}
		}
	}

	void GameStage::CreateCanAcionMapID(int actionCost) {
		m_mapData[m_choiceMapID.y][m_choiceMapID.x].nowMapCost = actionCost;
		m_canActionMapID.push_back(m_choiceMapID);

		MapSearch4(m_choiceMapID, actionCost);
	}

	void GameStage::MapSearch4(MapID mapID, int actionCost) {
		if (mapID.x > 0 && mapID.y > 0 && mapID.x < m_mapData[0].size(), mapID.y < m_mapData.size()) {
			auto searchMapID = MapID(mapID.x, mapID.y -1);
			MapSearch(searchMapID, actionCost);

			searchMapID = MapID(mapID.x - 1, mapID.y);
			MapSearch(searchMapID, actionCost);

			searchMapID = MapID(mapID.x + 1, mapID.y );
			MapSearch(searchMapID, actionCost);

			searchMapID = MapID(mapID.x, mapID.y + 1);
			MapSearch(searchMapID, actionCost);
		}
	}

	void GameStage::MapSearch(MapID mapID, int actionCost) {
		if (mapID.mapPos.x < 0 || mapID.y < 0 ||
			mapID.x >= m_mapData[0].size() || mapID.y >= m_mapData.size()) {
			return;
		}

		if (actionCost <= m_mapData[mapID.y][mapID.x].nowMapCost) {
			return;
		}
		
		//�E�R�E�X�E�g�E�}�E�b�E�v�E��E��E�X�E�V�E��E��E��E�Ă��E��E�Ȃ�}�E�b�E�vID�E��E�ǉ��E��E��E�Ȃ�
		if (0 < m_mapData[mapID.y][mapID.x].nowMapCost){
			m_mapData[mapID.y][mapID.x].nowMapCost = actionCost;
			MapSearch4(mapID, actionCost);
			return;
		}

		actionCost = actionCost + m_mapData[mapID.y][mapID.x].nowMapCost;

		if (actionCost > 0) {
			m_mapData[mapID.y][mapID.x].nowMapCost = actionCost;
			m_canActionMapID.push_back(mapID);
			MapSearch4(mapID, actionCost);
		}
		else {
			actionCost = 0;
		}
	}

	void GameStage::ResetCanActionMapID() {
		for each (auto mapData in m_mapData)
		{
			mapData[0].nowMapCost = mapData[0].defaultMapCost;
		}

		m_canActionMapID.clear();
	}

	void GameStage::SettingMoveCostMap() {
		for (int i = 0; i < m_charactorMapID.size(); i++) {
			for (int j = 0; j < m_charactorMapID[i].size(); j++) {

			}
		}

		auto moveCost = m_charactorData[m_playerTurnNum][m_choiceCharactorID].MoveRange;
		MessageBox(0, L"�E�}�E�b�E�v�E�R�E�X�E�g�E��E�", L"�E�}�E�b�E�v", 0);
		CreateCanAcionMapID(moveCost);
		m_gameStateNum = eGameStateNum::choiceMap;

		MessageBox(0, L"�E�ړ��E�͈�", L"�E��E��E��E�", 0);
		for (int i = 0; i < m_canActionMapID.size(); i++) {
			auto objData = ObjectData(
				Vec3(m_mapData[m_canActionMapID[i].mapPos.y][m_canActionMapID[i].mapPos.x].mapPos.x, m_mapData[m_canActionMapID[i].mapPos.y][m_canActionMapID[i].mapPos.x].mapPos.y, 0.0f),
				Vec3(0.0f), Vec3(0.5f), 2, L"thumbnail.png");
			AddGameObject<ObjectBase>(objData);
		}
	}

	void GameStage::SettingAttackCostMap() {
		for (int i = 0; i < m_charactorMapID.size(); i++) {
			for (int j = 0; j < m_charactorMapID[i].size(); j++) {
				if (m_charactorMapID[i][j].x == m_choiceMapID.x &&
					m_charactorMapID[i][j].y == m_choiceMapID.y) {
					//�E�I�E��E�ł��E�Ȃ�
					return;
				}
			}
		}
		auto moveCost = m_charactorData[m_playerTurnNum][m_choiceCharactorID].MoveRange;
		CreateCanAcionMapID(moveCost);
		m_gameStateNum = eGameStateNum::choiceEnemy;

		for (int i = 0; i < m_canActionMapID.size(); i++) {
			auto objData = ObjectData(
				Vec3(m_canActionMapID[i].mapPos.x, m_canActionMapID[i].mapPos.y, 0.0f),
				Vec3(0.0f), Vec3(0.5f), 0, L"thumbnail.png");
			AddGameObject<ObjectBase>(objData);
		}
	}
}
//end basecross
