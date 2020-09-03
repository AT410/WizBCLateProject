/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -50.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		m_ptrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(m_ptrCamera);
		m_ptrCamera->SetEye(eye);
		m_ptrCamera->SetAt(at);

		//カメラの遠近法を切る
		m_ptrCamera->SetPers(false);

		//仮の値を設定
		float width = 3.2 * 12;
		float height = 2.0 * 12;

		//カメラが映す範囲を設定
		m_ptrCamera->SetWidth(width);
		m_ptrCamera->SetHeight(height);
		//視野角を設定
		m_ptrCamera->SetFovY(1.0f);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			auto charaObjData = structdata::ObjectData(Vec3(0.0f), Vec3(0.0f), Vec3(1.0f),1, L"tx_Cursor.png");
			auto uiData = structdata::UIData(Vec2(0.0f), Vec3(0.0f), Vec2(150.0f, 200.0f), Vec2(0.0f, 1.0f), 5, L"menu.png");

			//描画の確認用に画像を生成
			//AddGameObject<ObjectBase>(charaObjData);

			AddGameObject<MapCreator>();

			AddGameObject<MapCursor>(charaObjData);

#ifdef _BSImGui
			ImApp::GetApp()->AddImGuiObject<SystemGui>();
#endif // _BSImGui

			CreateCharactor();

			for (int i = 0; i < 50; i++) {
				auto objData = ObjectData(
					Vec3(0.0f),
					Vec3(0.0f), Vec3(0.5f), 1, L"tx_MovingRange.png");
				m_actionRangeObj.push_back(AddGameObject<ObjectBase>(objData));
				m_actionRangeObj[i]->SetDrawActive(false);
			}

			m_ptrUIMainCommand = AddGameObject<UIMainCommand>(uiData);
			m_ptrUIMainCommand->SetActiveThis(false);

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		m_handler.PushHandle(GetThis<GameStage>());
		VisibleUIMainCommand();
	}

	void GameStage::VisibleUIMainCommand(){
		if (m_gameStateNum == eGameStateNum::choiceAction) {
			if (!m_ptrUIMainCommand->GetDrawActive()) {
				m_ptrUIMainCommand->SetActiveThis(true);
			}
		}
	}

	void GameStage::UpDateCameraPos(Vec2 at) {
		Vec3 setCameraEye = Vec3(at.x, at.y, m_ptrCamera->GetEye().z);
		Vec3 setCameraAt = Vec3(at.x, at.y, m_ptrCamera->GetAt().z);

		m_ptrCamera->SetEye(setCameraEye);
		m_ptrCamera->SetAt(setCameraAt);
	}

	void GameStage::CreateCharactor() {
		for (int i = 0; i < m_charactorMapID.size(); i++) {
			m_charactorObj.push_back(vector<shared_ptr<Character>>());
			m_charactorData.push_back(vector<CharactorData>());
			m_charactorCommandData.push_back(vector<CharactorCommandData>());
			for (int j = 0; j < m_charactorMapID[i].size(); j++) {
				vector<unsigned int> weaponID = { 0,2 };
				CharactorData charaData = CharactorData(1, 1, 5, 1, 2, 5, 4, 3, weaponID);
				CharactorCommandData charaComData = CharactorCommandData(false, false, false);
				m_charactorData[i].push_back(charaData);
				m_charactorCommandData[i].push_back(charaComData);

				auto setPos = m_mapData[m_charactorMapID[i][j].y][m_charactorMapID[i][j].x].mapPos;
				auto objData = ObjectData(
					setPos,
					Vec3(0.0f), Vec3(0.5f), 2, L"kaizoku_viking.png");
				m_charactorObj[i].push_back(AddGameObject<Character>(objData));
			}
		}
	}

	void GameStage::ChangeGameStateNum(eGameStateNum gameState) {
		m_gameStateNum = gameState;

	}

	void GameStage::ConfirmationCharacter() {
		//ChangeGameStateNum(eGameStateNum::choiceAction);
		m_gameStateNum = eGameStateNum::choiceAction;
		m_ptrUIMainCommand->GetChildContent(CommandContent::Attack)->StateCommandPassive();
		m_ptrUIMainCommand->GetChildContent(CommandContent::Move)->StateCommandPassive();
		m_ptrUIMainCommand->GetChildContent(CommandContent::Wait)->StateCommandPassive();

		for (int i = 0; i < m_charactorMapID[m_playerTurnNum].size(); i++) {
			if (m_charactorMapID[m_playerTurnNum][i].mapPos == m_choiceMapID.mapPos) {
				if (m_charactorData[m_playerTurnNum][i].isDed == true) {
					return;
				}

				m_choiceCharactorID = i;
				//MessageBox(0, L"", L"", 0);

				if (!m_charactorCommandData[m_playerTurnNum][i].isAttacked) {
					m_ptrUIMainCommand->GetChildContent(CommandContent::Attack)->StateCommandActive();
				}
				if (!m_charactorCommandData[m_playerTurnNum][i].isMoved) {
					m_ptrUIMainCommand->GetChildContent(CommandContent::Move)->StateCommandActive();
				}
				if (!m_charactorCommandData[m_playerTurnNum][i].isWaiting) {
					m_ptrUIMainCommand->GetChildContent(CommandContent::Wait)->StateCommandActive();
				}
				return;
			}
		}
	}

	void GameStage::ConfirmationMove() {
		if (m_mapData[m_choiceMapID.y][m_choiceMapID.x].nowMapCost != eXMLMapStateNum::NotAvailable) {
			for (int i = 0; i < m_canActionMapID.size(); i++) {
				if (m_canActionMapID[i].mapPos == m_choiceMapID.mapPos) {
					m_charactorMapID[m_playerTurnNum][m_choiceCharactorID] = m_choiceMapID;
					m_charactorObj[m_playerTurnNum][m_choiceCharactorID]->MoveCharacter(m_mapData[m_choiceMapID.y][m_choiceMapID.x].mapPos);
					InvisibleActionRangeObj();
					m_charactorCommandData[m_playerTurnNum][m_choiceCharactorID].isMoved = true;
					m_gameStateNum = eGameStateNum::choicePlayer;
					return;
				}
			}
		}
	}

	void GameStage::ConfirmationAttack() {
		for (int i = 0; i < m_canActionMapID.size(); i++) {
			if (m_choiceMapID.mapPos == m_canActionMapID[i].mapPos) {
				for (int i = 0; i < m_charactorMapID.size(); i++) {
					if (i != m_playerTurnNum) {
						SerchCharactor(i);
					}
				}
			}
		}
	}

	void GameStage::SerchCharactor(int playerNum) {
		for (int i = 0; i < m_charactorMapID[playerNum].size(); i++) {
			if (m_choiceMapID.mapPos == m_charactorMapID[playerNum][i].mapPos) {
				if (m_charactorData[playerNum][i].isDed) {
					return;
				}

				m_choiceEnemyID = playerNum;
				m_choiceEnemyCharaID = i;
				m_charactorCommandData[m_playerTurnNum][m_choiceCharactorID].isAttacked = true;

				InvisibleActionRangeObj();

				DamageCalculation(m_charactorData[playerNum][i]);
				m_gameStateNum = eGameStateNum::choicePlayer;
			}
		}
	}

	//HPを減らす処理
	//void GameStage::

	//ダメージ計算
	void GameStage::DamageCalculation(CharactorData& enemyData) {
		//MessageBox(0, L"ダメージ処理", L"", 0);

		auto playerWeapon = m_weaponData[m_choiceWeaponID];
		auto enemyWeapon = m_weaponData[0];

		auto charactorData = m_charactorData[m_playerTurnNum][m_choiceCharactorID];

		float weekBunus = 1.5f;

		float pow = ((float)charactorData.Lv * 2 / 5.0f) + (float)charactorData.Pow + playerWeapon.weponPow;
		float def = (float)enemyData.Def / 2 + enemyWeapon.weponDef;
		float damage = pow - def;

		if (playerWeapon.weaponTag != enemyWeapon.weaponTag) {
			if (playerWeapon.weaponTag == (int)eWeaponTag::Sword) {
				if (enemyWeapon.weaponTag == eWeaponTag::Spear) {
					MessageBox(0, L"ダメージUP", L"", 0);
					damage = damage * weekBunus;
				}
				else {
					MessageBox(0, L"ダメージDOWN", L"", 0);
					damage = damage * 0.5f;
				}
			}
			else if (playerWeapon.weaponTag == eWeaponTag::Spear) {
				if (enemyWeapon.weaponTag == eWeaponTag::Bow) {
					MessageBox(0, L"ダメージUP", L"", 0);
					damage = damage * weekBunus;
				}
				else {
					MessageBox(0, L"ダメージDOWN", L"", 0);
					damage = damage * 0.5f;
				}
			}
			else if (playerWeapon.weaponTag == eWeaponTag::Bow) {
				if (enemyWeapon.weaponTag == eWeaponTag::Sword) {
					MessageBox(0, L"ダメージUP", L"", 0);
					damage = damage * weekBunus;
				}
				else {
					MessageBox(0, L"ダメージDOWN", L"", 0);
					damage = damage * 0.5f;
				}
			}
		}

		if (damage > 0) {
			enemyData.HP = enemyData.HP - (unsigned int)damage;
		}
		else {
			srand((unsigned int)time(NULL));
			m_charactorData[m_playerTurnNum][m_choiceCharactorID].HP = enemyData.HP - rand() % 2 + 1;
		}

		CheckPlayerHP(enemyData);
	}

	void GameStage::CheckPlayerHP(CharactorData& enemyData) {
		if (enemyData.HP <= 0) {
			//やられたプレイヤーを非表示にする
			enemyData.isDed = true;
			m_charactorObj[m_choiceEnemyID][m_choiceEnemyCharaID]->DestroyCharacter();
			ResetMapState(m_choiceMapID);
		}
	}

	void GameStage::CreateCanAcionMapID(int actionCost) {
		m_mapData[m_choiceMapID.y][m_choiceMapID.x].nowMapCost = actionCost++;
		m_canActionMapID.push_back(m_choiceMapID);

		MapSearch4(m_choiceMapID, actionCost);
	}

	void GameStage::MapSearch4(MapID mapID, int actionCost) {
		if (mapID.x >= 0 && mapID.y >= 0 && mapID.x < m_mapData[0].size() && mapID.y < m_mapData.size()) {
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
		//マップのサイズからはみ出していたら終了
		if (mapID.mapPos.x < 0 || mapID.y < 0 ||
			mapID.x >= m_mapData[0].size() || mapID.y >= m_mapData.size()) {
			return;
		}

		//アクションコストが小さい場合は終了
		if (actionCost < m_mapData[mapID.y][mapID.x].nowMapCost) {
			return;
		}
		
		actionCost = actionCost + m_mapData[mapID.y][mapID.x].defaultMapCost;

		if (0 <= m_mapData[mapID.y][mapID.x].nowMapCost){
			m_mapData[mapID.y][mapID.x].nowMapCost = actionCost;
			MapSearch4(mapID, actionCost);
			return;
		}

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
		for (int i = 0; i < m_canActionMapID.size(); i++) {
			m_mapData[m_canActionMapID[i].y][m_canActionMapID[i].x].nowMapCost = m_mapData[m_canActionMapID[i].y][m_canActionMapID[i].x].defaultMapCost;
		}

		m_canActionMapID.clear();
	}

	void GameStage::SettingMoveCostMap() {
		for (int i = 0; i < m_charactorMapID.size(); i++) {
			for (int j = 0; j < m_charactorMapID[i].size(); j++) {

			}
		}

		auto moveCost = m_charactorData[m_playerTurnNum][m_choiceCharactorID].MoveRange;
		//MessageBox(0, L"", L"", 0);
		CreateCanAcionMapID(moveCost);
		m_gameStateNum = eGameStateNum::choiceMap;

		//MessageBox(0, L"", L"", 0);
		for (int i = 0; i < m_canActionMapID.size(); i++) {
			auto objData = ObjectData(
				Vec3(m_mapData[m_canActionMapID[i].y][m_canActionMapID[i].x].mapPos.x, m_mapData[m_canActionMapID[i].y][m_canActionMapID[i].x].mapPos.y, 0.0f),
				Vec3(0.0f), Vec3(0.5f), 2, L"tx_MovingRange.png");

			auto trans = m_actionRangeObj[i]->GetComponent<Transform>();
			trans->SetPosition(objData.position);
			trans->SetScale(objData.scale);
			trans->SetRotation(objData.rotation);
			m_actionRangeObj[i]->DrawingImage(objData.texture);
			m_actionRangeObj[i]->SetDrawActive(true);
		}
	}

	void GameStage::SettingAttackCostMap(AttackCommandContent setWeapon) {
		for (int i = 0; i < m_charactorMapID.size(); i++) {
			for (int j = 0; j < m_charactorMapID[i].size(); j++) {
				if (m_charactorMapID[i][j].x == m_choiceMapID.x &&
					m_charactorMapID[i][j].y == m_choiceMapID.y) {
					//return;
				}
			}
		}

		m_choiceWeaponID = m_charactorData[m_playerTurnNum][m_choiceCharactorID].weaponID[setWeapon];
		auto attackCost = m_weaponData[m_choiceWeaponID].AttackRange;
		CreateCanAcionMapID(attackCost);

		for (int i = 0; i < m_canActionMapID.size(); i++) {
			auto objData = ObjectData(
				Vec3(m_mapData[m_canActionMapID[i].y][m_canActionMapID[i].x].mapPos.x, m_mapData[m_canActionMapID[i].y][m_canActionMapID[i].x].mapPos.y, 0.0f),
				Vec3(0.0f), Vec3(0.5f), 2, L"tx_AttackRange.png");

			auto trans = m_actionRangeObj[i]->GetComponent<Transform>();
			trans->SetPosition(objData.position);
			trans->SetScale(objData.scale);
			trans->SetRotation(objData.rotation);
			m_actionRangeObj[i]->DrawingImage(objData.texture);
			m_actionRangeObj[i]->SetDrawActive(true);
		}

		m_gameStateNum = eGameStateNum::choiceEnemy;
	}

	void GameStage::WaitCharacter() {
		m_charactorCommandData[m_playerTurnNum][m_choiceCharactorID].isAttacked = true;
		m_charactorCommandData[m_playerTurnNum][m_choiceCharactorID].isMoved = true;
		m_charactorCommandData[m_playerTurnNum][m_choiceCharactorID].isWaiting = true;
	}

	void GameStage::InvisibleActionRangeObj() {
		for (int i = 0; i < m_canActionMapID.size(); i++) {
			m_actionRangeObj[i]->SetDrawActive(false);
		}

		ResetCanActionMapID();
	}

	void GameStage::ChangePlayerTurn() {
		MessageBox(0, L"次のプレイヤーのターン", L"ターン終了", 0);
		m_gameStateNum = eGameStateNum::changePlayer;
		for (int i = 0; i < m_charactorCommandData[m_playerTurnNum].size(); i++) {
			m_charactorCommandData[m_playerTurnNum][i].isAttacked = false;
			m_charactorCommandData[m_playerTurnNum][i].isMoved = false;
			m_charactorCommandData[m_playerTurnNum][i].isWaiting = false;
		}
		
		m_playerTurnNum++;

		if (m_playerTurnNum >= m_maxPlayerNum) {
			m_playerTurnNum = 0;
		}
		m_gameStateNum = eGameStateNum::choicePlayer;
		m_ptrUIMainCommand->GetChildContent(CommandContent::TurnEnd)->StateCommandActive();
	}

	void GameStage::OnPushB() {
		if (m_gameStateNum == eGameStateNum::choiceEnemy || m_gameStateNum == eGameStateNum::choiceMap)
		{
			InvisibleActionRangeObj();
			m_gameStateNum = eGameStateNum::choicePlayer;
		}
	}

}
//end basecross
