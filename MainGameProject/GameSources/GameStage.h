/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
using namespace structdata;

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {

		shared_ptr<Camera> m_ptrCamera;
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
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		GameStage() :Stage() {
			m_maxPlayerNum = 4;
		}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//ゲッター・セッター
		vector<vector<MapData>> GetMapData() { return m_mapData; };
		MapData GetMapData(MapID mapID) { return m_mapData[mapID.y][mapID.x]; };
		void SetMapData(vector<vector<MapData>> set) { m_mapData = set; };
		//マップコストを設定
		void SetMapDataCost(MapID mapID, int nowMapCost) { m_mapData[mapID.y][mapID.x].nowMapCost = nowMapCost; };
		//マップコストをリセットする
		void ResetMapDataCost(MapID mapID) {
			m_mapData[mapID.y][mapID.x].nowMapCost =
				m_mapData[mapID.y][mapID.x].defaultMapCost;};

		int GetMaxPlayerNum() { return m_maxPlayerNum; };
		void SetCharactorMapID(vector<vector<MapID>> mapID) { m_charactorMapID = mapID; };
		MapID GetCharactorMapID(int playerID, int playerNum) { return m_charactorMapID[playerID][playerNum]; };

		void UpDateCameraPos(Vec2 at);
	};


}
//end basecross

