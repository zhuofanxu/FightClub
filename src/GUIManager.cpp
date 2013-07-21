/*
-----------------------------------------------------------------------------
This source file is part of TankWar
This is a 3D tank war game, use ogre for render, support singleplayer and multiplayer.
For the latest info, see http://flyingpig.isgreat.org or https://sourceforge.net/projects/tankwar3d

Copyright (c) 2000-2010

Usage of this program is free for non-commercial use and licensed under the
the terms of the MIT License.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "GUIManager.h"
//#include "Util.h"

namespace FightClub
{
  CEGUI::MouseButton MB_OISToCEGUI(OIS::MouseButtonID buttonID)
	{
		 switch (buttonID)
		 {
         case OIS::MB_Left:
             return CEGUI::LeftButton;
             break;
         case OIS::MB_Right:
             return CEGUI::RightButton;
             break;
         case OIS::MB_Middle:
             return CEGUI::MiddleButton;
             break;
         default:
             return CEGUI::LeftButton;
		  }
	}

	// 鼠标类型名称
	const std::string MOUSE_CURSOR[3] = {"CursorOn", "CursorFire", "CursorNormal"};

	GUIManager::GUIManager() : mpGUISystem(0),  mpGUIRenderer(0){}


	GUIManager::~GUIManager()
	{

	}

	void GUIManager::destroy()
	{
		//SAFE_DELETE(mpGUISystem);
		//SAFE_DELETE(mpGUIRenderer);
	}

	//void GUIManager::setTargetSceneManager(Ogre::SceneManager* mgr)
	//{
	//	//mpGUIRenderer->setRenderingEnabled(true);
	//}

	void GUIManager::init()
	{
		if (!mpGUIRenderer)
		{
			mpGUIRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

#ifdef _DEBUG
			CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);
#endif

			// set the default resource groups to be used
			CEGUI::Imageset::setDefaultResourceGroup("imagesets");
			CEGUI::Font::setDefaultResourceGroup("fonts");
			CEGUI::Scheme::setDefaultResourceGroup("schemes");
			CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
			CEGUI::WindowManager::setDefaultResourceGroup("layouts");
			CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

			// setup default group for validation schemas
			CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
			if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
				parser->setProperty("SchemaDefaultResourceGroup", "schemas");


			CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

			// 加载GUI主题并设置默认参数
			CEGUI::SchemeManager::getSingleton().create("VanillaSkin.scheme");
			CEGUI::SchemeManager::getSingleton().create("WindowsLook.scheme");
			//CEGUI::SchemeManager::getSingleton().create("TankWar.scheme");
			CEGUI::SchemeManager::getSingleton().create("OgreTray.scheme");

			

			CEGUI::System &sys = CEGUI::System::getSingleton();
			//sys.setDefaultFont("BlueHighway-10");
			sys.setDefaultTooltip("WindowsLook/Tooltip");
			sys.setDefaultMouseCursor("TaharezLook","MouseArrow");
			//setCursorType(CURSOR_NORMAL);
			showGUICursor(true);
		}
	}

	CEGUI::Window* GUIManager::getWindow(const std::string &windowName)
	{
		return getWindowManager()->getWindow(windowName);
		//return CEGUI::WindowManager::getSingletonPtr()->getWindow(windowName);
	}

	CEGUI::Window* GUIManager::createWindow(const std::string &type, const std::string &name)
	{
		return getWindowManager()->createWindow(type, name);
	}

	bool GUIManager::loadWindow(const std::string &windowName)
	{
		bool flag = false;
		// 检测给定layout的文件是否加载,没有加载则加载
		if(!getWindowManager()->isWindowPresent(windowName))
		{
			// 从 .layout脚本文件读取一个UI布局设计，并将其放置到GUI资源组中。
			CEGUI::Window *editorGuiSheet = getWindowManager()->loadWindowLayout(windowName + ".layout");
			// 接下来我们告诉CEGUI显示哪份UI布局。当然我们可以随时更换显示的UI布局。
			CEGUI::System &sys = CEGUI::System::getSingleton();
			sys.setGUISheet(editorGuiSheet);
			//getSingletonPtr()->getGUISystem()->setGUISheet(editorGuiSheet);
			editorGuiSheet->setVisible(true);
			editorGuiSheet->setMousePassThroughEnabled(true);

			flag = true;
		}
		else
		{	
			assert(0);
			//// 如果已经加载则直接显示
			//CEGUI::Window *window = getWindowManager()->getWindow(windowName);
			//getSingletonPtr()->getGUISystem()->setGUISheet(window);
			//window->show();
		}

		return flag;
	}

	void GUIManager::changeSize(float width, float height) 
	{ 
		// 更新CEGUI窗口大小, 同步鼠标显示范围, 来解决CEGUI鼠标范围与系统鼠标范围一致
		mpGUIRenderer->setDisplaySize(CEGUI::Size(width, height)); 

		// 确保UI重新绘制并显示
		//		说明, 当窗口大小发生改变的时候, UI会消失, 调用mpGUISystem->signalRedraw();
		// 来重新绘制并显示UI
		CEGUI::System &guiSys = CEGUI::System::getSingleton();
		guiSys.signalRedraw();
	}

	void GUIManager::update( float timeSinceLastFrame )
	{
		CEGUI::System &sys = CEGUI::System::getSingleton();
		sys.injectTimePulse(timeSinceLastFrame / 1000);
	}

	void GUIManager::showGUICursor(bool enable)
	{
		if (enable)
			CEGUI::MouseCursor::getSingletonPtr()->show();
		else
			CEGUI::MouseCursor::getSingletonPtr()->hide();

		::ShowCursor(!enable);
	}

	void GUIManager::setCursorType(CURSOR_TYPE cursor)
	{
		CEGUI::System &guiSys = CEGUI::System::getSingleton();
		///guiSys.setDefaultMouseCursor("NormalImageSet", MOUSE_CURSOR[cursor]);
	}

	void GUIManager::destoryWindow(const std::string &windowName)
	{
		getWindowManager()->destroyWindow(windowName);
	}
	void GUIManager::hideWindow(const std::string &windowName)
	{
		getWindowManager()->getWindow(windowName)->hide();
	}
	void GUIManager::createImageset(const std::string& name, const std::string& filename)
	{
		CEGUI::ImagesetManager::getSingleton().createFromImageFile(name, filename);
		//setProperty("Image", "set:Root/StaticImage image:full_image");
	}



	void GUIManager::subscribeEvent(const CEGUI::String& windowName, const CEGUI::String &eventName, 
		const CEGUI::Event::Subscriber &subscriber)
	{
		CEGUI::WindowManager::getSingleton().getWindow(CEGUI::String(windowName))->subscribeEvent(eventName,subscriber);
	}

	void GUIManager::setProperty(const std::string &windowName, const std::string& PropName, const std::string& PropValue)
	{
		getWindow(windowName)->setProperty(PropName, PropValue);
	}

	}