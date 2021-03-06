#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include<list>
#include"ObjectBase.h"

class EnemyBase;

class EnemyManager :public ObjectBase {
public:
	EnemyManager();
	virtual ~EnemyManager();

	virtual void Update();
	virtual void Draw();

private:
	std::list<EnemyBase*> m_PtrEnemys;
};
#endif