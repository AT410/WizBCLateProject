/*!
@file MapCreator.h
@brief マップの作成
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum eXMLLayerNum {
		BG = 0,
		Obj = 1,
		Chara = 2
	};

	enum eXMLMapStateNum {
		NotAvailable = -1,
		Normal = 0,
		Forest = 1,
		Player1Chara = 2,
		Player2Chara = 3,
		Player3Chara = 4,
		Player4Chara = 5
	};

	enum ePlayerID {
		Player1,
		Player2,
		Player3,
		Player4
	};

	class MapCreator : public GameObject {
		unique_ptr<XmlDocReader> m_XmlDocReader;
		//背景作成用のデータ
		vector<vector<wstring>> m_mapTexStr;
		vector<vector<MapData>> m_mapData;
		//オブジェクト作成用のデータ
		vector<vector<MapID>> m_objMapPos;
		//キャラクター作成用のデータ : m_objMapPos[PlayerID][CharactorNum]
		vector<vector<MapID>> m_charactorMapID;
		
		wstring m_selectStageStr = L"Map1";
		wstring m_xmlName = L"TestMap01";
		int m_mapColumn;
		int m_mapRow;

		float m_cellSize;

	public:
		MapCreator(const shared_ptr<Stage>& stage);

		virtual void OnCreate() override;

		void ReadXML();

		void ReadLayer(IXMLDOMNodePtr nodePtr, wstring nodeStr);

		void ReadCellMap(IXMLDOMNodeListPtr nodePtr, int num);

		void SaveBGMapData(IXMLDOMNodeListPtr nodePtr);

		void SaveObjMapData(IXMLDOMNodeListPtr nodePtr);

		void SaveCharaMapData(IXMLDOMNodeListPtr nodePtr);

		void CreateMapData(int maxLan);

		void CreateBGObj();
	};

}
//end basecross

