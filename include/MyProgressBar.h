#pragma once
/*��Ϸ�г��ֵ����н������Ļ��࣬����Ϊһ��������
  ��Դ������������ֵ�����Ӵ���̳У���Ҫʵ�����еĴ��麯��
*/
#include<CEGUI.h>
namespace FightClub
{
	class CMyProgressBar
	{
	public:
		CMyProgressBar(void){}
	   virtual ~CMyProgressBar(void){}
	   virtual void updateProgress(float percent)=0;     //���½�����
	   virtual void destroyProgressBar(void)=0;         //���ٽ�����
	   virtual void initProgressBar(const CEGUI::String& windowName)=0;           //��ʼ��������
	   /*��ȡ��ǰ�������Ľ���
	     @mProgressBar ��ǰ����Ľ�����
	   */
	   virtual float getCurrentProgress(CEGUI::ProgressBar* mProgressBar)
	   {return mProgressBar->getProgress();}

	   virtual CEGUI::ProgressBar* getProgressBar(){return mProgressBar;}

	protected:
		CEGUI::ProgressBar* mProgressBar;
		
    };
}
