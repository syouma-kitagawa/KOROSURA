#ifndef MAINSCENE_H
#define MAINSCENE_H

#include"SceneBase.h"
#include<d3dx9.h>
#include<vector>

class ObjectBase;
class Camera;

class MainScene :public SceneBase{
public:
	MainScene();
	virtual ~MainScene();

	//保持しているObujectBaseのUpdate関数をよんでいます
	virtual SceneBase::SCENE_ID Update();
	virtual void Draw();

private:
	std::vector<ObjectBase*> m_PtrObjBases;
	Camera* m_pCamera;
};
#endif