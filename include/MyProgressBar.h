#pragma once
/*游戏中出现的所有进度条的基类，此类为一个抽象类
  资源载入条，生命值条都从此类继承，并要实现所有的纯虚函数
*/
#include<CEGUI.h>
namespace FightClub
{
	class CMyProgressBar
	{
	public:
		CMyProgressBar(void){}
	   virtual ~CMyProgressBar(void){}
	   virtual void updateProgress(float percent)=0;     //更新进度条
	   virtual void destroyProgressBar(void)=0;         //销毁进度条
	   virtual void initProgressBar(const CEGUI::String& windowName)=0;           //初始化进度条
	   /*获取当前进度条的进度
	     @mProgressBar 当前具体的进度条
	   */
	   virtual float getCurrentProgress(CEGUI::ProgressBar* mProgressBar)
	   {return mProgressBar->getProgress();}

	   virtual CEGUI::ProgressBar* getProgressBar(){return mProgressBar;}

	protected:
		CEGUI::ProgressBar* mProgressBar;
		
    };
}
