/*!
@file UICommandContent.h
@brief UI�R�}���h���e�N���X
*/

#pragma once
#include "stdafx.h"
using namespace structdata;
using namespace enumdata;

namespace basecross {
	class UICommandContent : public UIBase {
		// �e�I�u�W�F�N�g
		shared_ptr<GameObject> m_parent;

		// ���e
		CommandContent m_content;

		// �A�N�e�B�u���ǂ���
		bool m_bCommandActive = true;

		// �A�N�e�B�u���Ɣ�A�N�e�B�u���̐F
		Col4 m_colorCommandActive = Col4(1.0f, 1.0f, 1.0f, 1.0f);// ��
		Col4 m_colorCommandPassive = Col4(0.5f, 0.5f, 0.5f, 1.0f);// �O���[

	public:
		UICommandContent(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec2& size,
			Vec2& position,
			Vec2& UVPos,
			int layer,
			CommandContent& content,
			const shared_ptr<GameObject>& parent = nullptr);

		UICommandContent(const shared_ptr<Stage>& stage,
			UIData& UIdata,
			CommandContent& content,
			const shared_ptr<GameObject>& parent = nullptr);

		virtual void OnCreate() override;

		// ���e�ʂ̃e�N�X�`���Z�b�g
		void SetTexture(CommandContent content);

		// �X�e�[�g
		// �A�N�e�B�u
		void StateCommandActive();
		// ��A�N�e�B�u(�����Ȃ����Ƃ𕪂���₷��)
		void StateCommandPassive();

		// �Z�b�^�[�Q�b�^�[
		// �A�N�e�B�u��
		void SetCommandActive(bool set);
		bool GetCommandActive()const;
		// ���e
		CommandContent GetContent()const;
	};
}

//end basecross
