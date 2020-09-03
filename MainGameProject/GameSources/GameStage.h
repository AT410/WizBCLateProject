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
		InputHandler<GameStage> m_handler;
		shared_ptr<Camera> m_ptrCamera;
		shared_ptr<UIMainCommand> m_ptrUIMainCommand;

		vector<vector<MapData>> m_mapData;
		vector<vector<MapID>> m_charactorMapID;
		vector<MapID> m_canActionMapID;
		vector<vector<shared_ptr<Character>>> m_charactorObj;
		vector <vector<CharactorData>> m_charactorData;
		vector<vector<CharactorCommandData>> m_charactorCommandData;
		vector<WeaponData> m_weaponData = {
			WeaponData(eWeaponID::normalSword,	3, 2, 1, eWeaponTag::Sword),
			WeaponData(eWeaponID::normalSpear,	4, 0, 2, eWeaponTag::Spear),
			WeaponData(eWeaponID::normalBow,	2, 0, 4, eWeaponTag::Bow),
		};

		vector<shared_ptr<ObjectBase>> m_actionRangeObj;
		MapID m_choiceMapID;
		MapID m_beforeMapID;
		unsigned int m_choiceWeaponID;
		int m_choiceEnemyID;
		int m_choiceEnemyCharaID;

		vector<unsigned int> m_orderOfAction;

		unsigned int m_gameStateNum;
		unsigned int m_playerTurnNum;
		unsigned int m_choiceCharactorID;
		unsigned int m_maxPlayerNum;
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {
			m_maxPlayerNum = 4;
			m_playerTurnNum = eGameStateNum::choicePlayer;
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

		void ResetMapState(MapID mapID) {
			m_mapData[mapID.y][mapID.x].mapState =
				m_mapData[mapID.y][mapID.x].defaultMapState;
		};

		int GetMaxPlayerNum() { return m_maxPlayerNum; };
		void SetCharactorMapID(vector<vector<MapID>> mapID) { m_charactorMapID = mapID; };
		MapID GetCharactorMapID(int playerID, int playerNum) { return m_charactorMapID[playerID][playerNum]; };
		void SetGameStateNum(eGameStateNum set) { m_gameStateNum = set; };
		unsigned int GetGameStateNum() { return m_gameStateNum; };
		void SetChoiceMapID(MapID choiceID) { 
			m_beforeMapID = m_choiceMapID;
			m_choiceMapID = choiceID; };
		void SetChoiceWeaponID(eWeaponID set) { m_choiceWeaponID = set; };


		//����
		void VisibleUIMainCommand();

		void UpDateCameraPos(Vec2 at);

		void CreateCharactor();

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

		void SettingAttackCostMap(AttackCommandContent setWeapon);

		void WaitCharacter();

		void InvisibleActionRangeObj();

		void ChangePlayerTurn();

		void OnPushA() {};

		void OnPushB();
	};


}
//end basecross

