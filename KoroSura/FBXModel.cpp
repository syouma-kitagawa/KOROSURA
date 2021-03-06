#include"FBXModel.h"
#include"DirectGraphics.h"
#include"FBX.h"
#include"EffectManager.h"

void FBXModel::Init(char* filepath)
{
	FBXLoader::GetInstance().FBXLoad(&m_FBXModelDate,filepath);
	m_VertexNum = m_FBXModelDate.PolygonNum / 3;
	m_Vertex = new FBXLoader::UserVertex[m_FBXModelDate.PolygonVertexNum];
	for (int i = 0; i < m_FBXModelDate.PolygonVertexNum; i++) {
		D3DVECTOR tmpPos;
		tmpPos.x = m_FBXModelDate.Positions[m_FBXModelDate.IndexAry[i]].x;
		tmpPos.y = m_FBXModelDate.Positions[m_FBXModelDate.IndexAry[i]].y;
		tmpPos.z = m_FBXModelDate.Positions[m_FBXModelDate.IndexAry[i]].z;
		D3DVECTOR tmpNormal;
		tmpNormal.x = m_FBXModelDate.NormalVector[i]->x;
		tmpNormal.y = m_FBXModelDate.NormalVector[i]->y;
		tmpNormal.z = m_FBXModelDate.NormalVector[i]->z;
		m_Vertex[i].Vec.x = tmpPos.x;
		m_Vertex[i].Vec.y = tmpPos.y;
		m_Vertex[i].Vec.z = tmpPos.z;
		m_Vertex[i].Normal.x = tmpNormal.x;
		m_Vertex[i].Normal.y = tmpNormal.y;
		m_Vertex[i].Normal.z = tmpNormal.z;
		m_Vertex[i].tu = m_FBXModelDate.uvBuffer[i].x;
		m_Vertex[i].tv = m_FBXModelDate.uvBuffer[i].y;
	}
}

void FBXModel::Destroy()
{
	delete[] m_Vertex;
}

void FBXModel::Draw()
{
	(*DirectGraphics::GetInstance().GetDevice())->SetFVF(USERVERTEX_FVF);
	for (unsigned int n = 0; n < m_FBXModelDate.textures.size(); n++)
	{
		(*DirectGraphics::GetInstance().GetDevice())->
			SetTexture(n, m_FBXModelDate.textures[n].pTexture);
	}
	FBXLoader::Color_RGB color;
	float alpha = m_FBXModelDate.Transparency;
	//マテリアル設定
	color.red = m_FBXModelDate.Diffuse.red;
	color.blue = m_FBXModelDate.Diffuse.blue;
	color.green = m_FBXModelDate.Diffuse.green;
	EffectManager::GetpInstance().GetEffect("Shader\\BasicShader.fx")->SetColor(color,alpha);
	(*DirectGraphics::GetInstance().GetDevice())->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		m_FBXModelDate.PolygonNum,
		m_Vertex,
		sizeof(FBXLoader::UserVertex));
}