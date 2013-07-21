#pragma once
#include "state.h"
namespace FightClub
{
class COlGameState :
	public State
{
public:

	void    createLight(void);
	void    createCamera(void);
	COlGameState(void);
	~COlGameState(void);
	virtual void enter(void);                          //进入网络游戏状态
	virtual void pause(void);                         //网络版游戏暂停状态
	virtual void resume(void);                       //恢复网络游戏状态
	virtual void exit(void);                        //离开网络游戏状态

	/*更改窗口大小之后调用, 负责本状态对窗口更改后的处理
			@width	更改窗口大小后的渲染窗口宽度
			@height	更改窗口大小后的渲染窗口高度*/
	virtual void changeSize(int width, int height);
};
}
