#ifndef MAINSCENE_H
#define MAINSCENE_H

#include"SceneBase.h"
#include<d3dx9.h>
#include<vector>

#include"GameClear.h"
#include"GameOver.h"

class MaterialBase;
class Camera;
class LimitTime;
class PlayerLevel;
class ObjectBase;
class EnemyManager;
class GimmickManager;

class MainScene :public SceneBase{
public:
	MainScene();
	virtual ~MainScene();

	//保持しているObujectBaseのUpdate関数をよんでいます
	virtual SceneBase::SCENE_ID Update();
	virtual void Draw();

	void Init();

private:
	void SetRetSceneId(SceneBase::SCENE_ID sceneId) { retId = sceneId; }

	std::vector<MaterialBase*> m_PtrMaterials;
	//std::vector<ObjectBase*> m_PtrObject;
	Camera* m_pCamera;
	LimitTime* m_pLimitTime;
	EnemyManager* m_pEnemyManager;
	GimmickManager* m_pGimmickManager;
	SceneBase::SCENE_ID retId = SceneBase::SCENE_ID::MAIN;
};
#endif