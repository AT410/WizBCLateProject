#pragma once
#include "stdafx.h"

namespace basecross {
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

		void InputKey();

		void InputCrossKey();

		void MovePos(int mapIDX, int mapIDY);

		void OnPushA();

		void OnPushB() {};

		MapID GetID() { return m_choiceMapID; }
	};
}
