#pragma once
#include "MyProgressBar.h"
namespace FightClub
{
class CLifeBar :public CMyProgressBar
	
{
public:
	CLifeBar(void);
	~CLifeBar(void);
	virtual void updateProgress(float percent);
	virtual void destroyProgressBar(void);
	virtual void initProgressBar(const CEGUI::String& windowName);

};
}
