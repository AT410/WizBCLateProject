/*!
@file MapCursor.cpp
@brief ゲームオブジェクト親クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MapCursor::MapCursor(const shared_ptr<Stage>& stage,
		ObjectData objdata) :
		ObjectBase(stage, objdata)

	{
		m_maxMoveTime = 0.3;
	}

	void MapCursor::OnCreate() {
		DrawingImage(L"thumbnail.png");
		InitializeTransfrom();
		m_cursorTrans = GetComponent<Transform>();

		m_mapData = GetTypeStage<GameStage>()->GetMapData();

		m_cursorTrans->SetPosition(m_mapData[0][0].mapPos);
	}

	void MapCursor::OnUpdate() {
		m_handler.PushHandle(GetThis<MapCursor>());
		MoveCursor();
	}

	void MapCursor::MoveCursor() {
		unsigned int playerNum = 0;
		auto contr = App::GetApp()->GetInputDevice().GetControlerVec()[playerNum];
		float inputSticNum = 0.8f;
		bool isInputStic =
			contr.fThumbLX >= inputSticNum || contr.fThumbLX <= -inputSticNum ||
			contr.fThumbLY >= inputSticNum || contr.fThumbLY <= -inputSticNum;
		bool isInputButton =
			contr.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP || contr.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN ||
			contr.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT || contr.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;

		if (GetTypeStage<GameStage>()->GetGameStateNum() != (int)eGameStateNum::choiceAction) {
			if (isInputStic || isInputButton)
			{
				InputStic();
			}
			else {
				m_moveTimer = 0;
			}
		}
	}

	void MapCursor::InputStic() {
		unsigned int playerNum = 0;
		auto contr = App::GetApp()->GetInputDevice().GetControlerVec()[playerNum];
		float inputSticNum = 0.8f;

		//右に動く
		if (contr.fThumbLX >= inputSticNum) {
			MovePos(m_choiceMapID.x + 1, m_choiceMapID.y);
		}
		//左に動く
		if (contr.fThumbLX <= -inputSticNum) {
			MovePos(m_choiceMapID.x - 1, m_choiceMapID.y);
		}
		//上に動く
		if (contr.fThumbLY >= inputSticNum) {
			MovePos(m_choiceMapID.x, m_choiceMapID.y - 1);
		}
		//下に動く
		if (contr.fThumbLY <= -inputSticNum) {
			MovePos(m_choiceMapID.x, m_choiceMapID.y + 1);
		}
	}

	void MapCursor::MovePos(int mapIDX, int mapIDY) {
		bool isCheckMapCulam = mapIDX < m_mapData.size() && mapIDX >= 0;
		bool isCheckMapRow = mapIDY < m_mapData[0].size() && mapIDY >= 0;

		if (m_moveTimer == 0.0f) {
			m_isMoveCursor = true;
		}

		if (m_moveTimer > m_maxMoveTime) {
			m_isMoveCursor = true;
			m_moveTimer = 0.1f;
		}
		else {
			m_moveTimer += App::GetApp()->GetElapsedTime();
		}

		if (m_isMoveCursor) {
			if (isCheckMapCulam && isCheckMapRow) {
				m_cursorTrans->SetPosition(m_mapData[mapIDY][mapIDX].mapPos);
				m_choiceMapID = MapID(mapIDX, mapIDY);
				m_isMoveCursor = false;
			}
		}
	}

	void MapCursor::PushA() {
		if (GetTypeStage<GameStage>()->GetGameStateNum() == (int)eGameStateNum::choicePlayer) {
			GetTypeStage<GameStage>()->SetChoiceMapID(m_choiceMapID);
			GetTypeStage<GameStage>()->ConfirmationCharacter();
		}

		if (GetTypeStage<GameStage>()->GetGameStateNum() == (int)eGameStateNum::choiceMap) {
			GetTypeStage<GameStage>()->SetChoiceMapID(m_choiceMapID);
			GetTypeStage<GameStage>()->ConfirmationMove();
		}

		if (GetTypeStage<GameStage>()->GetGameStateNum() == (int)eGameStateNum::choiceEnemy) {
			GetTypeStage<GameStage>()->SetChoiceMapID(m_choiceMapID);
			GetTypeStage<GameStage>()->ConfirmationAttack();
		}
	}
}