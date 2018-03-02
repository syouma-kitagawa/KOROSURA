#ifndef GAMEOVER_H
#define GAMEOVER_H

#include<d3dx9.h>
#include "ObjectBase.h"

class GameOver : public ObjectBase
{
public:
	GameOver();
	virtual ~GameOver();

	virtual void Update();
	virtual void Draw();
private:
	const int kPngWidth = 8192;
	const int kPngHeight = 1024;

	const D3DXVECTOR2 kStageOverPos = D3DXVECTOR2(800.0f, 200.0f);
	const int kStageOverWidth = 800;
	const int kStageOverHeight = 100;
};

#endif