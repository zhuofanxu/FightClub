#pragma once
#include<OgreResourceGroupManager.h>
#include"ResourceLoadBar.h"
namespace FightClub
{
	class CMyResourceListener : public Ogre::ResourceGroupListener
	{
	private:
	    float m_Allcount;           
	    float m_Currentcount;  
		CResourceLoadBar* mResourceBar;
	public:
		CMyResourceListener();
		virtual void resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount){}
		virtual void scriptParseStarted(const Ogre::String& scriptName, bool& skipThisScript){}
		virtual void scriptParseEnded(const Ogre::String& scriptName, bool skipped) {}
		virtual void resourceGroupScriptingEnded(const Ogre::String& groupName){}
		virtual void resourceGroupPrepareStarted(const Ogre::String& groupName, size_t resourceCount) { m_Allcount=resourceCount;}
        virtual void resourcePrepareStarted(const Ogre::ResourcePtr& resource){}
        virtual void resourcePrepareEnded(void) {}
        virtual void worldGeometryPrepareStageStarted(const Ogre::String& description){}
		virtual void worldGeometryPrepareStageEnded(void) {}
        virtual void resourceGroupPrepareEnded(const Ogre::String& groupName){}
        virtual void resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount){}
		virtual void resourceLoadEnded(void);	
		virtual void worldGeometryStageEnded(void);
		virtual void resourceLoadStarted(const Ogre::ResourcePtr& resource) {}
		virtual void worldGeometryStageStarted(const Ogre::String& description) {}
        virtual void resourceGroupLoadEnded(const Ogre::String& groupName) {}
	  };
}
