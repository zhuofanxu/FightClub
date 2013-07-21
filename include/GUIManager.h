#pragma once
/*
-----------------------------------------------------------------------------
��Ϸ���������
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
	��OIS���ת����CEGUI���
	@buttonID	OIS���ö��
	*/
	

	// �������
	enum CURSOR_TYPE
	{
		CURSOR_ON				= 0,		// ��ָ��
		CURSOR_FIRE				= 1,		// ������
		CURSOR_NORMAL		= 2,		// ��ͨ��
	};
	CEGUI::MouseButton MB_OISToCEGUI(OIS::MouseButtonID buttonID);
	/**
	GUI����ϵͳ,����GUI����ļ���,�¼��͹���
	*/
	class GUIManager : public SingletonT<GUIManager>, public IFrameListener
	{
		SINGLETON_DEFINE(GUIManager)

	public:
		
		virtual ~GUIManager();

		// �ͷ���Դ
		void destroy();

		/**
		��ʼ��GUI,ֻ�ڵ�һ�ε�����Ч
		@rendweWindow		��Ⱦ����
		@sceneManager		GUI��ʾ�ĳ���
		*/
		void init();

		///*
		//ÿ��ת��������ʱ��, �����ǰ������SceneManager����ͬһ���Ļ�, ��Ҫ����GUI
		//�����ĳ���������, ������Ҫ���ô˺���������, ����MenuStateת����GameState
		//@mgr	���õ�ǰGUI�����ĳ���������
		//*/
		//void setTargetSceneManager(Ogre::SceneManager* mgr);

		inline CEGUI::OgreRenderer* getGUIRender() { return mpGUIRenderer; }
		// ��ȡ��ǰGUI�ĸ�Window
		inline CEGUI::Window* getGUISheet() 
		{
			//assert(0&&"CEGUI::Window* getGUISheet");
			CEGUI::System &sys = CEGUI::System::getSingleton();

			return sys.getGUISheet(); 
		}

		// ע��CEGUI����¼�
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
		// ע��CEGUI����ƶ��¼�, ʱʱ�������λ��, ����Ƶ������, ������֮
		inline bool injectMouseMove(float xRel, float yRel, float xAbs, float yAbs)
		{
			//static CEGUI::MouseCursor* mouse = CEGUI::MouseCursor::getSingletonPtr();
			//mouse->setPosition(CEGUI::Point(xAbs, yAbs));
			CEGUI::System &sys = CEGUI::System::getSingleton();

			sys.injectMouseMove(xRel, yRel);
			return sys.injectMousePosition(xAbs, yAbs);
		}

		/**
		�����ڸ��´�С�����
		@width	���Ĵ��ں���Ⱦ���ڵĿ��
		@height	���Ĵ��ں���Ⱦ���ڵĸ߶�
		*/
		void changeSize(float width, float height);

		void update( float timeSinceLastFrame );

		/**
		ע��CEGUI�ؼ��¼�
		@windowName	Ҫע���¼��Ŀؼ�����
		@eventName		ע��Ŀؼ��¼�
		@subscriber			�¼�����ʱ�Ļص�����
		*/
		static void subscribeEvent(const CEGUI::String& windowName, 
			const CEGUI::String &eventName, 
			const CEGUI::Event::Subscriber &subscriber);

		// ��ȡGUI���ڹ�����
		static CEGUI::WindowManager* getWindowManager() { return CEGUI::WindowManager::getSingletonPtr(); }

		/**
		����WIndow�ؼ�
		@type		��������
		@name	��������, ����ȫ��Ψһ
		*/
		static CEGUI::Window* createWindow(const std::string &type, const std::string &name);

		/**
		��ȡWindow
		@name Ҫ��ȡ���ڿؼ�������
		*/
		static CEGUI::Window* getWindow(const std::string &windowName);

		// ��ָ�������趨����
		static void setProperty(const std::string &windowName, const std::string& name, 
			const std::string& value);

		/**
		����ͼƬ����Imageset
		@name		������Imageset����, ȫ��Ψһ
		@filename	����Imageset��ͼƬ����
		*/
		static void createImageset(const std::string& name, const std::string& filename);

		/**
		����UI����,���غ�����Ϊ��ǰUI
		ע�� : ��֤�����ļ���Root������ͬ:Root name = Window, Window.layout
		���layoutδ�����򷵻�true, ���layout�Ѿ������򷵻�false
		@windowName	���ص�layout�ļ�����
		*/
		static bool loadWindow(const std::string &windowName);

		/**
		���ٴ���
		@windowName	Ҫ���ٵĴ��ڿؼ�������
		*/
		static void destoryWindow(const std::string &windowName);
		static void hideWindow(const std::string &windowName);
		// ��ʾ/����GUI���
		static void showGUICursor(bool enable);
		// ���������ʽ
		static void setCursorType(CURSOR_TYPE cursor);

	private:
		GUIManager();

	private:
		CEGUI::OgreRenderer			*mpGUIRenderer;
		CEGUI::System				*mpGUISystem;

	};
#endif
	}

