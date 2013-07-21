#pragma once
#include"MyProgressBar.h"
namespace FightClub
{
class CResourceLoadBar :public CMyProgressBar
	
{
public:
	CResourceLoadBar(void);
	~CResourceLoadBar(void);

	virtual void updateProgress(float percent);
	virtual void destroyProgressBar(void);
	virtual void initProgressBar(const CEGUI::String& windowName);
};

}