#include "LifeBar.h"

namespace FightClub
{
CLifeBar::CLifeBar(void)
{
	mProgressBar=0;
}


CLifeBar::~CLifeBar(void)
{
	if(mProgressBar)
	{
		delete mProgressBar;
		mProgressBar=NULL;
	}
}

void CLifeBar::updateProgress(float percent)
{
	if(mProgressBar)
		mProgressBar->setProgress(percent);
}

void CLifeBar::destroyProgressBar(void)
{
	if(mProgressBar)
		mProgressBar->destroy();
}

void CLifeBar::initProgressBar(const CEGUI::String& windowName)
{
	mProgressBar=static_cast<CEGUI::ProgressBar*>(CEGUI::WindowManager::getSingletonPtr()->getWindow(windowName));
}
}
