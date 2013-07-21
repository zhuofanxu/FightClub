#include"MyResourceListener.h"
namespace FightClub
{
CMyResourceListener::CMyResourceListener()
{
	m_Currentcount=0;
	m_Allcount=0;
    mResourceBar=new CResourceLoadBar();
}
void CMyResourceListener::resourceLoadEnded(void)
{
	m_Currentcount++;
	mResourceBar->updateProgress(m_Currentcount/m_Allcount);
	if(mResourceBar->getCurrentProgress(mResourceBar->getProgressBar())>=0.99)
		mResourceBar->destroyProgressBar();
}

void CMyResourceListener::worldGeometryStageEnded(void)
{
	m_Currentcount++;
	mResourceBar->updateProgress(m_Currentcount/m_Allcount);
	if(mResourceBar->getCurrentProgress(mResourceBar->getProgressBar())>=0.99)
		mResourceBar->destroyProgressBar();
}
}