/*
	-----------------------------------------------------------------------------
	���õļ�������
	֡�������Լ������豸�ļ�����
	-----------------------------------------------------------------------------
*/

#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>

namespace FightClub
{
	// ֡������
	class IFrameListener
	{
	public:
		/**
			״̬����, ÿһ֡����
			@timeSinceLastFrame	����һ֡��ʱ��(����s)
		*/
		virtual void update(float timeSinceLastFrame ) {}

		/**
			��Ⱦ�����״̬, ÿһ֡����
			@timeSinceLastFrame	����һ֡��ʱ��(����s)
		*/
		virtual void updateAfterRender( float timeSinceLastFrame) {}
	};

	// �����̼�����
	class IKeyMouseListener : public OIS::MouseListener, public OIS::KeyListener
	{
	public:
		// ���,�����¼�
		virtual bool keyPressed( const OIS::KeyEvent &e ){ return true; }
		virtual bool keyReleased( const OIS::KeyEvent &e ){ return true; }

		virtual bool mouseMoved(const OIS::MouseEvent &e){ return true; }
		virtual bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return true; }
		virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return true; }
	};
}