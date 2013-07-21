#include "ResourceLoadBar.h"
namespace FightClub
{

CResourceLoadBar::CResourceLoadBar(void)
{
	mProgressBar=0;
}


CResourceLoadBar::~CResourceLoadBar(void)
{
	if(mProgressBar)
	{
		delete mProgressBar;
		mProgressBar=NULL;
	}
}

void CResourceLoadBar::initProgressBar(const CEGUI::String& windowName)
{
	  mProgressBar=static_cast<CEGUI::ProgressBar*>(CEGUI::WindowManager::getSingletonPtr()->getWindow(windowName));
}
void CResourceLoadBar::updateProgress(float percent)
{
	if(mProgressBar)
		mProgressBar->setProgress(percent);
}

void CResourceLoadBar::destroyProgressBar(void)
{
	if(mProgressBar)
		mProgressBar->destroy();
}
}