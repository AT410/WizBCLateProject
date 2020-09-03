/*!
@file MapCreator.cpp
@brief マップ作製オブジェクトの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MapCreator::MapCreator(const shared_ptr<Stage>& stage):
		GameObject(stage)
	{
		m_cellSize = 2.0f;
	}

	void MapCreator::OnCreate() {
		ReadXML();
		CreateBGObj();
	}

	void MapCreator::ReadXML() {
		//読み込むXMLデータのパスを取得
		wstring DataDir;
		wstring stageNode = L"EditorSetting/MapData";
		ATL::CComBSTR stageStr = L"Header";

		//読み込むXMLデータを指定
		App::GetApp()->GetDataDirectory(DataDir);
		m_XmlDocReader.reset(new XmlDocReader(DataDir + L"MapData/" + m_xmlName + L".xml"));

		//読み込むノードを取得
		auto mapNode = m_XmlDocReader->GetSelectNodes(stageNode.c_str());
		wstring name;

		//ノードの数を取得
		auto nodeLen = m_XmlDocReader->GetLength(mapNode);

		//指定のノードを探す
		for (int i = 0; i < nodeLen; i++) {
			auto readItem = m_XmlDocReader->GetItem(mapNode, (long)i);
			name = m_XmlDocReader->GetAttribute(readItem, L"Header");
			if (name == m_selectStageStr) {
				//Layerノードの中身を見る
				m_mapColumn = stoi(m_XmlDocReader->GetAttribute(readItem, L"Columns"));
				m_mapRow = stoi(m_XmlDocReader->GetAttribute(readItem, L"Rows"));
				ReadLayer(readItem, stageNode);
				break;
			}
		}
	}

	void MapCreator::ReadLayer(IXMLDOMNodePtr nodePtr, wstring nodeStr) {
		IXMLDOMNodeListPtr nextNodePtr;
			
		nodePtr->get_childNodes(&nextNodePtr);
		auto nodeLen = m_XmlDocReader->GetLength(nextNodePtr);

		for (int i = 0; i < nodeLen; i++) {
			//マップデータ読み込み
			IXMLDOMNodeListPtr saveNodePtr;
			auto node = m_XmlDocReader->GetItem(nextNodePtr, (long)i);
			node->get_childNodes(&saveNodePtr);
			ReadCellMap(saveNodePtr, i);
		}
	}

	void MapCreator::ReadCellMap(IXMLDOMNodeListPtr nodePtr, int num) {
		switch (num)
		{
		case (int)eXMLLayerNum::BG:
			SaveBGMapData(nodePtr);
			break;

		case (int)eXMLLayerNum::Obj:
			SaveObjMapData(nodePtr);
			break;

		case (int)eXMLLayerNum::Chara:
			SaveCharaMapData(nodePtr);
			break;

		default:
			break;
		}
	}

	void MapCreator::SaveBGMapData(IXMLDOMNodeListPtr nodePtr) {	
		int maxLan = m_XmlDocReader->GetLength(nodePtr);
		CreateMapData(maxLan);

		for (int i = 0; i < maxLan; i++) {
			auto item = m_XmlDocReader->GetItem(nodePtr, i);
			MapID mapID = MapID(stoi(m_XmlDocReader->GetAttribute(item, L"X")),
				stoi(m_XmlDocReader->GetAttribute(item, L"Y")));

			//原点が中心になるように生成位置を調整
			Vec2 createStartPos = Vec2((float)-(m_cellSize * m_mapColumn / 2 - m_cellSize / 2)
				, (float)(m_cellSize * m_mapColumn / 2 - m_cellSize / 2));

			Vec3 mapPos =
				Vec3(createStartPos.x + (mapID.x * m_cellSize), createStartPos.y + (mapID.y * -m_cellSize), 0.0f);
			int index = stoi(m_XmlDocReader->GetAttribute(item, L"Index"));

			switch (index)
			{
			case (int)eXMLMapStateNum::Normal:
				m_mapData[mapID.y][mapID.x] = MapData(index, mapPos, -1);
				break;

			case (int)eXMLMapStateNum::Forest:
				m_mapData[mapID.y][mapID.x] = MapData(index, mapPos, -2);
				break;

			default:
				break;
			}
		}
	}

	void MapCreator::SaveObjMapData(IXMLDOMNodeListPtr nodePtr) {

	}

	void MapCreator::SaveCharaMapData(IXMLDOMNodeListPtr nodePtr) {
		int maxLan = m_XmlDocReader->GetLength(nodePtr);

		for (int i = 0; i < 4; i++) {
			m_charactorMapID.push_back(vector<MapID>());
		}

		for (int i = 0; i < maxLan; i++) {
			auto item = m_XmlDocReader->GetItem(nodePtr, i);
			int index = stoi(m_XmlDocReader->GetAttribute(item, L"Index"));

			MapID mapID = MapID(stoi(m_XmlDocReader->GetAttribute(item, L"X")),
				stoi(m_XmlDocReader->GetAttribute(item, L"Y")));

			switch (index)
			{
			case (int)eXMLMapStateNum::Player1Chara:
				m_charactorMapID[(int)ePlayerID::Player1].push_back(mapID);
				m_mapData[mapID.y][mapID.x].mapState = eXMLMapStateNum::Player1Chara;
				break;
			case (int)eXMLMapStateNum::Player2Chara:
				m_charactorMapID[(int)ePlayerID::Player2].push_back(mapID);
				m_mapData[mapID.y][mapID.x].mapState = eXMLMapStateNum::Player2Chara;
				break;
			case (int)eXMLMapStateNum::Player3Chara:
				m_charactorMapID[(int)ePlayerID::Player3].push_back(mapID);
				m_mapData[mapID.y][mapID.x].mapState = eXMLMapStateNum::Player3Chara;
				break;
			case (int)eXMLMapStateNum::Player4Chara:
				m_charactorMapID[(int)ePlayerID::Player4].push_back(mapID);
				m_mapData[mapID.y][mapID.x].mapState = eXMLMapStateNum::Player4Chara;
				break;
			default:
				break;
			}			
		}
		GetTypeStage<GameStage>()->SetCharactorMapID(m_charactorMapID);
		GetTypeStage<GameStage>()->SetMapData(m_mapData);
	}

	void MapCreator::CreateMapData(int maxLan){
		for (int i = 0; i < m_mapRow; i++) {
			m_mapData.push_back(vector<MapData>());
			for (int j = 0; j < m_mapColumn; j++) {
				int roopCount = i * m_mapRow + j;
				if (maxLan < roopCount) {
					break;
				}
				m_mapData[i].push_back(MapData());
			}
		}
	}

	void MapCreator::CreateBGObj() {
		for (int i = 0; i < m_mapRow; i++) {
			for (int j = 0; j < m_mapColumn; j++) {
				auto objData = ObjectData(
					Vec3(m_mapData[j][i].mapPos.x, m_mapData[j][i].mapPos.y, 0.0f),
					Vec3(0.0f), Vec3(0.5f), 0, L"sand1.jpg");

				switch (m_mapData[j][i].defaultMapState)
				{
				case (int)eXMLMapStateNum::Normal:
					objData = ObjectData(
						Vec3(m_mapData[j][i].mapPos.x, m_mapData[j][i].mapPos.y, 0.0f),
						Vec3(0.0f), Vec3(1.0f), 0, L"sand1.jpg");
					break;

				case (int)eXMLMapStateNum::Forest:
					objData = ObjectData(
						Vec3(m_mapData[j][i].mapPos.x, m_mapData[j][i].mapPos.y, 0.0f),
						Vec3(0.0f), Vec3(1.0f), 0, L"thumbnail.png");
					break;
				default:
					break;
				}

				GetStage()->AddGameObject<ObjectBase>(objData);
			}
		}
	}

}
//end basecross

