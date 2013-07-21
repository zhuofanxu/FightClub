#pragma once
/*
-----------------------------------------------------------------------------
游戏界面管理类
-----------------------------------------------------------------------------
*/

#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include <RendererModules\Ogre\CEGUIOgreRenderer.h>
#include <CEGUI.h>
#include <Ogre.h>

#include "SingletonT.h"
#include "Common.h"
namespace FightClub
{


	/**
	将OIS鼠标转换成CEGUI鼠标
	@buttonID	OIS鼠标枚举
	*/
	

	// 鼠标类型
	enum CURSOR_TYPE
	{
		CURSOR_ON				= 0,		// 手指型
		CURSOR_FIRE				= 1,		// 攻击型
		CURSOR_NORMAL		= 2,		// 普通型
	};
	CEGUI::MouseButton MB_OISToCEGUI(OIS::MouseButtonID buttonID);
	/**
	GUI管理系统,负责GUI界面的加载,事件和管理
	*/
	class GUIManager : public SingletonT<GUIManager>, public IFrameListener
	{
		SINGLETON_DEFINE(GUIManager)

	public:
		
		virtual ~GUIManager();

		// 释放资源
		void destroy();

		/**
		初始化GUI,只在第一次调用有效
		@rendweWindow		渲染窗口
		@sceneManager		GUI显示的场景
		*/
		void init();

		///*
		//每当转换场景的时候, 如果当前场景的SceneManager不是同一个的话, 需要更改GUI
		//依附的场景管理器, 这是需要调用此函数来更新, 例如MenuState转换到GameState
		//@mgr	设置当前GUI依附的场景管理器
		//*/
		//void setTargetSceneManager(Ogre::SceneManager* mgr);

		inline CEGUI::OgreRenderer* getGUIRender() { return mpGUIRenderer; }
		// 获取当前GUI的根Window
		inline CEGUI::Window* getGUISheet() 
		{
			//assert(0&&"CEGUI::Window* getGUISheet");
			CEGUI::System &sys = CEGUI::System::getSingleton();

			return sys.getGUISheet(); 
		}

		// 注入CEGUI鼠标事件
		inline bool injectMouseButtonDown(CEGUI::MouseButton id) 
		{ 
			CEGUI::System &sys = CEGUI::System::getSingleton();
			return sys.injectMouseButtonDown(id);
		}
		inline bool injectMouseButtonUp(CEGUI::MouseButton id) 
		{
			CEGUI::System &sys = CEGUI::System::getSingleton();
			return sys.injectMouseButtonUp(id); 
		}
		// 注入CEGUI鼠标移动事件, 时时更新鼠标位置, 可能频繁调用, 故内联之
		inline bool injectMouseMove(float xRel, float yRel, float xAbs, float yAbs)
		{
			//static CEGUI::MouseCursor* mouse = CEGUI::MouseCursor::getSingletonPtr();
			//mouse->setPosition(CEGUI::Point(xAbs, yAbs));
			CEGUI::System &sys = CEGUI::System::getSingleton();

			sys.injectMouseMove(xRel, yRel);
			return sys.injectMousePosition(xAbs, yAbs);
		}

		/**
		当窗口更新大小后调用
		@width	更改窗口后渲染窗口的宽度
		@height	更改窗口后渲染窗口的高度
		*/
		void changeSize(float width, float height);

		void update( float timeSinceLastFrame );

		/**
		注册CEGUI控件事件
		@windowName	要注册事件的控件名称
		@eventName		注册的控件事件
		@subscriber			事件触发时的回调函数
		*/
		static void subscribeEvent(const CEGUI::String& windowName, 
			const CEGUI::String &eventName, 
			const CEGUI::Event::Subscriber &subscriber);

		// 获取GUI窗口管理器
		static CEGUI::WindowManager* getWindowManager() { return CEGUI::WindowManager::getSingletonPtr(); }

		/**
		创建WIndow控件
		@type		窗口类型
		@name	窗口名称, 必须全局唯一
		*/
		static CEGUI::Window* createWindow(const std::string &type, const std::string &name);

		/**
		获取Window
		@name 要获取窗口控件的名称
		*/
		static CEGUI::Window* getWindow(const std::string &windowName);

		// 给指定窗口设定属性
		static void setProperty(const std::string &windowName, const std::string& name, 
			const std::string& value);

		/**
		根据图片构造Imageset
		@name		创建的Imageset名称, 全局唯一
		@filename	创建Imageset的图片名称
		*/
		static void createImageset(const std::string& name, const std::string& filename);

		/**
		加载UI布局,加载后设置为当前UI
		注意 : 保证布局文件和Root名称相同:Root name = Window, Window.layout
		如果layout未加载则返回true, 如果layout已经加载则返回false
		@windowName	加载的layout文件名称
		*/
		static bool loadWindow(const std::string &windowName);

		/**
		销毁窗口
		@windowName	要销毁的窗口控件的名称
		*/
		static void destoryWindow(const std::string &windowName);
		static void hideWindow(const std::string &windowName);
		// 显示/隐藏GUI鼠标
		static void showGUICursor(bool enable);
		// 设置鼠标样式
		static void setCursorType(CURSOR_TYPE cursor);

	private:
		GUIManager();

	private:
		CEGUI::OgreRenderer			*mpGUIRenderer;
		CEGUI::System				*mpGUISystem;

	};
#endif
	}

