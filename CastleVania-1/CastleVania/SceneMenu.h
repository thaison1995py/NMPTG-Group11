#ifndef _SCENEMENU_H_
#define _SCENEMENU_H_

#include "Scene.h"
#include "SceneMain.h"
#include "Font.h"

#define MENU_ANIMATE_STATE 5
#define MENU_MAX_OPTION 3

class SceneMenu: public Scene
{
protected:
	DWORD _localTime;
	Font* _smallFont;
	Font* _bigFont;
	int _currentSelection;
	char** _menuOption;
	void _initialize();
	void _draw();
	void _openOption();
public:
	SceneMenu(void);
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void OnKeyDown(int KeyCode);
	~SceneMenu(void);
};

#endif