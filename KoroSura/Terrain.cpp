#include"Terrain.h"
#include"StageInfo.h"
#include"FBX.h"
#include"DirectGraphics.h"
#include"TextureManager.h"
#include"Lib.h"
#include"DirLightSource.h"
#include"ModelManager.h"
#include"PhysicsManager.h"
#include"EffectManager.h"
#include"BoxCollider.h"
#include"Common.h"
#include"ColliderManager.h"

Terrain::Terrain():
	MaterialBase(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f))
{
//	m_OBB.SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//	m_OBB.SetDirect(0, D3DXVECTOR3(1.0f, 0.0f, 0.0f));
//	m_OBB.SetDirect(1, D3DXVECTOR3(0.0f, 1.0f, 0.0f));
//	m_OBB.SetDirect(2, D3DXVECTOR3(0.0f, 0.0f, 1.0f));
//	m_OBB.SetLength(0, 3000.0f);
//	m_OBB.SetLength(1, 20.0f);
//	m_OBB.SetLength(2, 3000.0f);
//
//	m_pCollider = new BoxCollider("Terrain", this, &m_OBB, std::bind(&Terrain::Collided, this, std::placeholders::_1),
//		CATEGORY_BITS_BOARD, CATEGORY_BITS_SLIME);
//
//	ColliderManager::GetInstance().Register(m_pCollider, 0);
}

Terrain::~Terrain() 
{
	//delete[] m_TerrainData;
}

void Terrain::Update()
{
	//const float* slopeDeg = PhysicsManager::GetInstance().GetSlopeDeg();

	//Matrix matRotation;
	//Matrix tmp;

	//matRotation.m_Row = 3;
	//matRotation.m_Column = 3;
	//matRotation.Initialize();

	//Utility::GetRotationXMatrix(&tmp, slopeDeg[0]);
	//matRotation *= tmp;
	//Utility::GetRotationZMatrix(&tmp, slopeDeg[1]);
	//matRotation *= tmp;

	////回転用行列
	//for (int i = 0; i < 3; ++i) {
	//	D3DXVECTOR3 direct = m_OBB.GetDirect(i);
	//	Matrix mat(3, 1,
	//		direct.x,
	//		direct.y,
	//		direct.z);

	//	mat = matRotation * mat;
	//	direct.x = mat.m_Mat[0][0];
	//	direct.y = mat.m_Mat[1][0];
	//	direct.z = mat.m_Mat[2][0];

	//	m_OBB.SetDirect(i, direct);
	//}
}

void Terrain::Draw()
{
	//最終的なワールドトランスフォーム行列
	D3DXMATRIXA16 matWorld;
	//平行移動用行列
	D3DXMATRIXA16 matPosition;

	//行列の初期化
	D3DXMatrixIdentity(&matWorld);

	//ワールドトランスフォーム（絶対座標変換）
	//回転

	D3DXMatrixMultiply(&matWorld, &matWorld, PhysicsManager::GetInstance().GetRotMatrix());

	//平行移動
	D3DXMatrixTranslation(&matPosition, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPosition);

	//レンダリング仕様の登録
	(*DirectGraphics::GetInstance().GetDevice())->SetTransform(D3DTS_WORLD, &matWorld);

	EffectManager::GetpInstance().GetEffect("Shader\\BasicShader.fx")->SetWorldMatrix(&matWorld);

	// シェーダーパスの開始.%
	EffectManager::GetpInstance().GetEffect("Shader\\BasicShader.fx")->BeginPass(0);
	ModelManager::GetInstance().GetFBXDate("FBX\\FBXModel\\board.fbx").Draw();
	EffectManager::GetpInstance().GetEffect("Shader\\BasicShader.fx")->EndPass();
}

void Terrain::Collided(std::vector<ColliderBase::ObjectData*>* collidedObjects)
{

}