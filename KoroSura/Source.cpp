#include <fbxsdk.h>
#include<iostream>
#include<d3dx9.h>
#include<vector>
#include<string>
#include<list>

const char* filePath = "ball_ex_test.fbx";

struct Color_RGB {
	float red, green, blue;
};

struct ModelDataFBX {
	int PolygonNum;//総ポリゴン数
	int PolygonVertexNum;//ポリゴン頂点インデックス数
	int* IndexAry;//ポリゴン頂点インデックス配列
	D3DXVECTOR4* Positions;//頂点座標配列
	std::vector<D3DXVECTOR3*> NormalVector;//法線ベクトル配列
	std::vector<std::string> uvSetName;
	std::vector<std::string> textures;
	std::vector<D3DXVECTOR2> uvBuffer;
	int MaterialCount;
	Color_RGB Ambient;
	Color_RGB Diffuse;
	Color_RGB Emissive;
};

void GetTextureNames(FbxSurfaceLambert* lambert, const FbxProperty& prop, ModelDataFBX* pMeshData) {

	//FbxLayeredTexture の数を取得
	int layeredTextureCount = prop.GetSrcObjectCount();

	//アタッチされたテクスチャが FbxLayeredTexture の場合
	if (0 < layeredTextureCount) {

		//アタッチされたテクスチャの数だけ繰り返す
		for (int i = 0; i < layeredTextureCount; ++i) {

			//テクスチャを取得
			FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(i);

			//レイヤー数を取得
			int layerNum = prop.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();
			//int textureCount = layeredTexture - &gtGetSrcObjectCount<FbxFileTexture>();

			//レイヤー数だけ繰り返す
			for (int j = 0; j < layerNum; ++j) {

				//テクスチャを取得
				FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);

				if (texture) {

					//テクスチャ名を取得
					std::string textureName = texture->GetRelativeFileName();

					//UVSet名を取得
					std::string UVSetName = texture->UVSet.Get().Buffer();

					//UVSet名を比較し対応しているテクスチャなら保持
					for (int k = 0; k < pMeshData->uvSetName.size(); ++k) {
						if (pMeshData->uvSetName[k] == UVSetName) {
							pMeshData->textures.push_back(textureName);
							break;
						}
					}
				}
			}
		}
	}
	else {
		//テクスチャ数を取得
		int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();

		if (0 < fileTextureCount) {

			//テクスチャの数だけ繰り返す
			for (int j = 0; fileTextureCount > j; j++) {

				//テクスチャを取得
				FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);

				if (texture) {

					//テクスチャ名を取得
					//std::string textureName = texture->GetName();
					std::string textureName = texture->GetRelativeFileName();

					//UVSet名を取得
					std::string UVSetName = texture->UVSet.Get().Buffer();

					//UVSet名を比較し対応しているテクスチャなら保持
					for (int k = 0; k < pMeshData->uvSetName.size(); ++k) {
						if (pMeshData->uvSetName[k] == UVSetName) {
							pMeshData->textures.push_back(textureName);
							break;
						}
					}
				}
			}
		}
	}
}

void GetTexture(FbxMesh* pMesh, ModelDataFBX* pMeshData) {

	//ノードの取得
	FbxNode* node = pMesh->GetNode();
	if (node == 0) {
		return;
	}

	// マテリアルの数
	pMeshData->MaterialCount = node->GetMaterialCount();
	if (pMeshData->MaterialCount == 0) {
		return;
	}

	//マテリアル分繰り返す
	for (int i = 0; i < pMeshData->MaterialCount; ++i) {

		// マテリアル情報を取得
		FbxSurfaceMaterial* material = node->GetMaterial(i);

		if (material != 0) {

			// LambertかPhongか(Lambertのみ対応)
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {

				// Lambertにダウンキャスト
				FbxSurfaceLambert* lambert = (FbxSurfaceLambert*)material;
				
				// アンビエント
				FbxProperty property = lambert->FindProperty(FbxSurfaceMaterial::sAmbient);
				pMeshData->Ambient.red = (float)lambert->Ambient.Get().mData[0];
				pMeshData->Ambient.green = (float)lambert->Ambient.Get().mData[1];
				pMeshData->Ambient.blue = (float)lambert->Ambient.Get().mData[2];
				GetTextureNames(lambert, property, pMeshData);

				// ディフューズ
				pMeshData->Diffuse.red = (float)lambert->Diffuse.Get().mData[0];
				pMeshData->Diffuse.green = (float)lambert->Diffuse.Get().mData[1];
				pMeshData->Diffuse.blue = (float)lambert->Diffuse.Get().mData[2];
				property = lambert->FindProperty(FbxSurfaceMaterial::sDiffuse);
				GetTextureNames(lambert, property, pMeshData);

				// エミッシブ
				pMeshData->Emissive.red = (float)lambert->Emissive.Get().mData[0];
				pMeshData->Emissive.green = (float)lambert->Emissive.Get().mData[1];
				pMeshData->Emissive.blue = (float)lambert->Emissive.Get().mData[2];
				property = lambert->FindProperty(FbxSurfaceMaterial::sEmissive);
				GetTextureNames(lambert, property, pMeshData);

				//// バンプ
				//bump_.x = (float)lambert->GetBump().Get()[0];
				//bump_.y = (float)lambert->GetBump().Get()[1];
				//bump_.z = (float)lambert->GetBump().Get()[2];

				// 透過度
				//pMeshData->Transparency = (float)lambert->TransparentColor.Get().mData[0];

			}
			//else if (material->GetClassId().Is(FbxSurfacePhong::ClassId)) {

			//	// Phongにダウンキャスト
			//	FbxSurfacePhong* phong = (FbxSurfacePhong*)material;
			//}

			
		}
	}
}

void GetVertexUV(FbxMesh* pMesh, ModelDataFBX* pMeshData) {

	int UVLayerCount = pMesh->GetElementUVCount();

	for (int i = 0; UVLayerCount > i; i++) {

		//UVバッファを取得
		FbxGeometryElementUV* UV = pMesh->GetElementUV(i);

		//マッピングモードの取得
		FbxGeometryElement::EMappingMode mapping = UV->GetMappingMode();

		//リファレンスモードの取得
		FbxGeometryElement::EReferenceMode reference = UV->GetReferenceMode();

		//UV数を取得
		int uvCount = UV->GetDirectArray().GetCount();

		//マッピングモードの判別
		switch (mapping) {
		case FbxGeometryElement::eByControlPoint:
			break;

		case FbxGeometryElement::eByPolygonVertex:
			//リファレンスモードの判別
			switch (reference) {
			case FbxGeometryElement::eDirect:
				break;

			case FbxGeometryElement::eIndexToDirect:
			{
				FbxLayerElementArrayTemplate<int>* uvIndex = &UV->GetIndexArray();
				int uvIndexCount = uvIndex->GetCount();

				//UVを保持
				D3DXVECTOR2 temp;
				for (int j = 0; j < uvIndexCount; ++j) {

					temp.x = (float)UV->GetDirectArray().GetAt(uvIndex->GetAt(i))[0];

					temp.y = 1.0f - (float)UV->GetDirectArray().GetAt(uvIndex->GetAt(i))[1];

					pMeshData->uvBuffer.push_back(temp);
				}

				//UVSet名を取得
				pMeshData->uvSetName.push_back(UV->GetName());
			}
			break;

			default:
				break;
			}
			break;

		case FbxGeometryElement::eByEdge:
			break;

		case FbxGeometryElement::eByPolygon:
			break;

		default:
			break;
		}
	}
}

void GetVertexNormal(FbxMesh* pMesh, ModelDataFBX* pMeshData) {

	int normalLayerCount = pMesh->GetElementNormalCount();

	for (int i = 0; normalLayerCount > i; i++) {

		//法線セットの取得
		FbxGeometryElementNormal* normal = pMesh->GetElementNormal(i);
		//マッピングモードの取得
		FbxGeometryElement::EMappingMode mapping = normal->GetMappingMode();
		//リファレンスモードの取得
		FbxGeometryElement::EReferenceMode reference = normal->GetReferenceMode();

		//マッピングモードの判別
		switch (mapping) {
		case FbxGeometryElement::eByControlPoint:

			//リファレンスモードの判別
			switch (reference) {
			case FbxGeometryElement::eDirect:

				//法線数を取得
				int normalCount = normal->GetDirectArray().GetCount();
				pMeshData->NormalVector.push_back(new D3DXVECTOR3);

				//-----------------------------------------------------------------------
				// eDirect の場合データは順番に格納されているのでそのまま保持
				//-----------------------------------------------------------------------
				for (int i = 0; normalCount > i; i++) {
					//法線の取得
					pMeshData->NormalVector[i]->x = (float)normal->GetDirectArray().GetAt(i)[0];
					pMeshData->NormalVector[i]->y = (float)normal->GetDirectArray().GetAt(i)[1];
					pMeshData->NormalVector[i]->z = (float)normal->GetDirectArray().GetAt(i)[2];
				}
				break;

			//case FbxGeometryElement::eIndexToDirect:
			//	break;
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			break;
		default:
			break;
		}
	}
}


void GetPosition(FbxMesh* pMesh, ModelDataFBX* pMeshData) {
	//総ポリゴン数の取得
	pMeshData->PolygonNum = pMesh->GetPolygonCount();

	//ポリゴン頂点インデックス数の取得
	pMeshData->PolygonVertexNum = pMesh->GetPolygonVertexCount();

	// 頂点数
	int controlNum = pMesh->GetControlPointsCount();

	// 頂点座標配列
	FbxVector4* src = pMesh->GetControlPoints();

	// コピー
	pMeshData->Positions = new D3DXVECTOR4[controlNum];

	for (int i = 0; i < controlNum; ++i) {
		pMeshData->Positions[i].x = src[i][0];
		pMeshData->Positions[i].y = src[i][1];
		pMeshData->Positions[i].z = src[i][2];
		pMeshData->Positions[i].w = src[i][3];
	}

	//ポリゴン頂点インデックス配列の取得
	pMeshData->IndexAry = pMesh->GetPolygonVertices();

	//総ポリゴン数回す
	for (int p = 0; p < pMeshData->PolygonNum; p++) {

		//p番目のポリゴンの頂点数
		int IndexNumInPolygon = pMesh->GetPolygonSize(p);

		for (int n = 0; n < IndexNumInPolygon; n++) {

			// ポリゴンpを構成するn番目の頂点のインデックス番号
			int IndexNumber = pMesh->GetPolygonVertex(p, n);
		}
	}
}

void GetMesh(FbxNode* node,ModelDataFBX* p) {

	//--- ノードの属性を取得 ---//
	FbxNodeAttribute* attr = node->GetNodeAttribute();

	if (NULL != attr) {

		//--- 属性の判別 ---//
		switch (attr->GetAttributeType()) {

			//--- メッシュノード発見 ---//
		case FbxNodeAttribute::eMesh:
			//メッシュの取得
			FbxMesh* pMesh = node->GetMesh();
			GetPosition(pMesh,p);
			GetVertexNormal(pMesh, p);
			GetVertexUV(pMesh, p);
			GetTexture(pMesh, p);

			break;
		}
	}

	//--- 子ノードの再帰探査 ---//
	int childCount = node->GetChildCount();
	for (int i = 0; i < childCount; i++) {
		GetMesh(node->GetChild(i), p);
	}
}

