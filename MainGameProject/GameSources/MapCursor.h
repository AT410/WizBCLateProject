#pragma once
#include "stdafx.h"

namespace basecross {
	enum eGameStateNum {
		choicePlayer,
		choiceAction,
		choiceWeapon,
		choiceMap,
		choiceEnemy,
		turnEnd,
	};

	class MapCursor : public ObjectBase
	{
		InputHandler<MapCursor> m_handler;

		shared_ptr<Transform> m_cursorTrans;
		vector<vector<MapData>> m_mapData;
		MapID m_choiceMapID;

		float m_moveTimer;
		float m_maxMoveTime;

		bool m_isMoveCursor;
	public:
		MapCursor(const shared_ptr<Stage>& stage,
			ObjectData objdata);

		virtual void OnCreate() override;

		virtual void OnUpdate() override;

		void MoveCursor();

		void InputStic();

		void InputCrossKey();

		void MovePos(int mapIDX, int mapIDY);

		void PushA();

	};
}
