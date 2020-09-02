/*!
@file GameStage.h
@brief ƒQ[ƒ€ƒXƒe[ƒW
*/

#pragma once
#include "stdafx.h"
using namespace structdata;
using namespace enumdata;

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ƒQ[ƒ€ƒXƒe[ƒWƒNƒ‰ƒX
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
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		GameStage() :Stage() {
			m_maxPlayerNum = 4;
		}
		virtual ~GameStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//ƒQƒbƒ^[EƒZƒbƒ^[
		vector<vector<MapData>> GetMapData() { return m_mapData; };
		MapData GetMapData(MapID mapID) { return m_mapData[mapID.y][mapID.x]; };
		void SetMapData(vector<vector<MapData>> set) { m_mapData = set; };
		//ƒ}ƒbƒvƒRƒXƒg‚ğİ’è
		void SetMapDataCost(MapID mapID, int nowMapCost) { m_mapData[mapID.y][mapID.x].nowMapCost = nowMapCost; };
		//ƒ}ƒbƒvƒRƒXƒg‚ğƒŠƒZƒbƒg‚·‚é
		void ResetMapDataCost(MapID mapID) {
			m_mapData[mapID.y][mapID.x].nowMapCost =
				m_mapData[mapID.y][mapID.x].defaultMapCost;};

		int GetMaxPlayerNum() { return m_maxPlayerNum; };
		void SetCharactorMapID(vector<vector<MapID>> mapID) { m_charactorMapID = mapID; };
		MapID GetCharactorMapID(int playerID, int playerNum) { return m_charactorMapID[playerID][playerNum]; };
		unsigned int GetGameStateNum() { return m_gameStateNum; };
		void SetChoiceMapID(MapID choiceID) { m_choiceMapID = choiceID; };

		//ï¿½ï¿½ï¿½ï¿½
		void VisibleUIMainCommand();

		void UpDateCameraPos(Vec2 at);

		void CreateCharactor();

		void ChangeGameStateNum(eGameStateNum gameState);

		void ConfirmationCharacter();
		//ˆÚ“®‚Å‚«‚é‚©Šm”F‚·‚é
		void ConfirmationMove();

		void ConfirmationAttack();

		void DamageCalculation(CharactorData& enemyData);

		void CheckPlayerHP(CharactorData& enemyData);

		void SerchCharactor(int playerNum);

		void CreateCanAcionMapID(int actionCost);
		//
		void MapSearch4(MapID mapID, int actionCost);
		//ƒ}ƒbƒv‚ğƒT[ƒ`‚·‚é
		void MapSearch(MapID mapID, int actionCost);
		//‘‚«Š·‚¦‚½ƒ}ƒbƒvƒRƒXƒg‚ğƒŠƒZƒbƒg‚·‚é
		void ResetCanActionMapID();

		void SettingMoveCostMap();

		void SettingAttackCostMap();

		void WaitCharacter();

		void InvisibleActionRangeObj();

		void ChangePlayerTurn();

		void OnPushA() {};

		void OnPushB();
	};


}
//end basecross

