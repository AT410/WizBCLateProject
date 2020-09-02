/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
using namespace structdata;
using namespace enumdata;

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {

		shared_ptr<Camera> m_ptrCamera;
		shared_ptr<UIMainCommand> m_ptrUIMainCommand;

		vector<vector<MapData>> m_mapData;
		vector<vector<MapID>> m_charactorMapID;
		vector<MapID> m_canActionMapID;
		vector <vector<CharactorData>> m_charactorData;
		vector<vector<CharactorCommandData>> m_charactorCommandData;

		MapID m_choiceMapID;

		unsigned int m_gameStateNum;
		unsigned int m_playerTurnNum;
		unsigned int m_choiceCharactorID;
		int m_maxPlayerNum;
		float time;
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {
			m_maxPlayerNum = 4;
		}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//�Q�b�^�[�E�Z�b�^�[
		vector<vector<MapData>> GetMapData() { return m_mapData; };
		MapData GetMapData(MapID mapID) { return m_mapData[mapID.y][mapID.x]; };
		void SetMapData(vector<vector<MapData>> set) { m_mapData = set; };
		//�}�b�v�R�X�g��ݒ�
		void SetMapDataCost(MapID mapID, int nowMapCost) { m_mapData[mapID.y][mapID.x].nowMapCost = nowMapCost; };
		//�}�b�v�R�X�g�����Z�b�g����
		void ResetMapDataCost(MapID mapID) {
			m_mapData[mapID.y][mapID.x].nowMapCost =
				m_mapData[mapID.y][mapID.x].defaultMapCost;};

		int GetMaxPlayerNum() { return m_maxPlayerNum; };
		void SetCharactorMapID(vector<vector<MapID>> mapID) { m_charactorMapID = mapID; };
		MapID GetCharactorMapID(int playerID, int playerNum) { return m_charactorMapID[playerID][playerNum]; };
		unsigned int GetGameStateNum() { return m_gameStateNum; };
		void SetChoiceMapID(MapID choiceID) { m_choiceMapID = choiceID; };

		void UpDateCameraPos(Vec2 at);

		void ChangeGameStateNum(eGameStateNum gameState);

		void ConfirmationCharacter();
		//�ړ��ł��邩�m�F����
		void ConfirmationMove();

		void ConfirmationAttack();

		void DamageCalculation(CharactorData& enemyData);

		void CheckPlayerHP(CharactorData& enemyData);

		void SerchCharactor(int playerNum);

		void CreateCanAcionMapID(int actionCost);
		//
		void MapSearch4(MapID mapID, int actionCost);
		//�}�b�v���T�[�`����
		void MapSearch(MapID mapID, int actionCost);
		//�����������}�b�v�R�X�g�����Z�b�g����
		void ResetCanActionMapID();

		void SettingMoveCostMap();

		void SettingAttackCostMap();

		void WaitCharacter();

		void ChangePlayerTurn();

		void OnPushA() {};

		void OnPushB();
	};


}
//end basecross

