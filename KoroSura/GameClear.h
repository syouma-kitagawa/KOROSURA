#ifndef GAMECLEAR_H
#define GAMECLEAR_H

#include<d3dx9.h>
#include"ObjectBase.h"

class GameClear : public ObjectBase
{
public:
	GameClear();
	virtual~GameClear();

	virtual void Update();
	virtual void Draw();
private:
	const int kPngWidth = 8192;
	const int kPngHeight = 1024;

	const D3DXVECTOR2 kStageClearPos = D3DXVECTOR2(800.0f, 200.0f);
	const int kStageClearWidth = 800;
	const int kStageClearHeight = 100;
};

#endif 


