/*
	-----------------------------------------------------------------------------
	常用的监听器：
	帧监听器以及输入设备的监听器
	-----------------------------------------------------------------------------
*/

#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>

namespace FightClub
{
	// 帧监听器
	class IFrameListener
	{
	public:
		/**
			状态更新, 每一帧调用
			@timeSinceLastFrame	自上一帧的时间(基于s)
		*/
		virtual void update(float timeSinceLastFrame ) {}

		/**
			渲染后更新状态, 每一帧调用
			@timeSinceLastFrame	自上一帧的时间(基于s)
		*/
		virtual void updateAfterRender( float timeSinceLastFrame) {}
	};

	// 鼠标键盘监听器
	class IKeyMouseListener : public OIS::MouseListener, public OIS::KeyListener
	{
	public:
		// 鼠标,键盘事件
		virtual bool keyPressed( const OIS::KeyEvent &e ){ return true; }
		virtual bool keyReleased( const OIS::KeyEvent &e ){ return true; }

		virtual bool mouseMoved(const OIS::MouseEvent &e){ return true; }
		virtual bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return true; }
		virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return true; }
	};
}