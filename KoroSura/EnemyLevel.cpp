#include"EnemyLevel.h"
#include"Fonts.h"
#include"DirectGraphics.h"
#include"Lib.h"
#include"Renderer.h"
#include"Billboard.h"

EnemyLevel::EnemyLevel(D3DXVECTOR3 pos, int level) :
	m_Pos(pos),
	m_Level(level)
{
}

EnemyLevel::~EnemyLevel()
{
}
void EnemyLevel::Update()
{
}

void EnemyLevel::Draw()
{
	VERTEX_3D vertex[] = {
		{- Fonts::g_Width / 2 , + Fonts::g_Height / 2, 0.0f ,0xffffffff,0.0f,0.0f },
		{+ Fonts::g_Width / 2 , + Fonts::g_Height / 2, 0.0f ,0xffffffff,1.0f,0.0f },
		{+ Fonts::g_Width / 2 , - Fonts::g_Height / 2, 0.0f ,0xffffffff,1.0f,1.0f },
		{- Fonts::g_Width / 2 , - Fonts::g_Height / 2, 0.0f ,0xffffffff,0.0f,1.0f }
	};
	Lib::GetInstance().SetRenderState3D();
	(*DirectGraphics::GetInstance().GetDevice())->SetFVF(FVF_3D);

	//todo 書き直す
	//文字を中央ぞろえにする
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			vertex[j].x -= Fonts::g_Width;
		}
	}

	Billboard::GetInstans().BillboardingTransform(m_Pos, 0.5f);
	EnemyLevel::GetUV3D('L', vertex);
	EnemyLevel::Draw3D(vertex, "Picture\\UI.png");
	NextCharPos(vertex);

	EnemyLevel::GetUV3D('v', vertex);
	EnemyLevel::Draw3D(vertex, "Picture\\UI.png");
	NextCharPos(vertex);

	EnemyLevel::GetUV3D('/', vertex);
	EnemyLevel::Draw3D(vertex, "Picture\\UI.png");
	NextCharPos(vertex);

	EnemyLevel::GetUV3D(Utility::TransformChar(m_Level / 10), vertex);
	EnemyLevel::Draw3D(vertex, "Picture\\UI.png");
	NextCharPos(vertex);

	EnemyLevel::GetUV3D(Utility::TransformChar(m_Level % 10), vertex);
	EnemyLevel::Draw3D(vertex, "Picture\\UI.png");
}

void EnemyLevel::TrimingVertex(VERTEX_3D vertex[], float leftTopTu, float leftTopTv, float width, float height, float pngWidth, float pngHeight) {
	vertex[0].tu = leftTopTu / pngWidth;
	vertex[0].tv = leftTopTv / pngHeight;

	vertex[1].tu = (leftTopTu + width) / pngWidth;
	vertex[1].tv = leftTopTv / pngHeight;

	vertex[2].tu = (leftTopTu + width) / pngWidth;
	vertex[2].tv = (leftTopTv + height) / pngHeight;

	vertex[3].tu = leftTopTu / pngWidth;
	vertex[3].tv = (leftTopTv + height) / pngHeight;

}

VERTEX_3D* EnemyLevel::GetUV3D(const char ch, VERTEX_3D* vertex)
{
	switch (ch) {
	case 'A':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 0, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'B':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 1, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'C':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 2, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'D':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 3, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'E':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 4, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'F':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 5, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'G':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 6, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'H':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 7, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'I':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 8, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'J':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 9, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'K':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 10, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'L':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 11, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'M':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 12, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'N':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 13, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'O':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 14, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'P':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 15, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'Q':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 16, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'R':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 17, Fonts::g_Height * 0, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'S':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 0, Fonts::g_Height * 1, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'T':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 1, Fonts::g_Height * 1, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'U':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 2, Fonts::g_Height * 1, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'V':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 3, Fonts::g_Height * 1, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'W':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 4, Fonts::g_Height * 1, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'X':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 5, Fonts::g_Height * 1, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'Y':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 6, Fonts::g_Height * 1, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'Z':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 7, Fonts::g_Height * 1, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'a':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 0, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'b':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 1, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'c':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 2, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'd':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 3, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'e':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 4, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'f':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 5, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'g':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 6, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'h':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 7, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'i':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 8, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'j':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 9, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'k':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 10, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'l':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 11, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'm':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 12, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'n':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 13, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'o':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 14, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'p':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 15, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'q':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 16, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'r':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 17, Fonts::g_Height * 2, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 's':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 0, Fonts::g_Height * 3, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 't':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 1, Fonts::g_Height * 3, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'u':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 2, Fonts::g_Height * 3, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'v':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 3, Fonts::g_Height * 3, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'w':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 4, Fonts::g_Height * 3, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'x':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 5, Fonts::g_Height * 3, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'y':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 6, Fonts::g_Height * 3, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case 'z':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 7, Fonts::g_Height * 3, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '0':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 0, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '1':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 1, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '2':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 2, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '3':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 3, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '4':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 4, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '5':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 5, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '6':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 6, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '7':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 7, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '8':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 8, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '9':
		EnemyLevel::TrimingVertex(vertex,Fonts::g_Width * 9, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '!':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 10, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '?':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 11, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '+':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 12, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '*':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 13, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '-':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 14, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;

	case '/':
		EnemyLevel::TrimingVertex(vertex, Fonts::g_Width * 15, Fonts::g_Height * 4, Fonts::g_Width, Fonts::g_Height, Fonts::g_PngSize, Fonts::g_PngSize);
		break;
	}
	return vertex;
}

bool EnemyLevel::Draw3D(const VERTEX_3D vertex[], const char* fileName) {
	Utility::PICTURE_INFO pic = TextureManager::GetInstance().GetPictureInfo(fileName);

	// テクスチャをステージに割り当てる
	if (FAILED((*Renderer::GetInstance().GetDXDevice())->SetTexture(0, pic.texture)))
	{
		return false;
	}
	// 描画
	if (FAILED((*Renderer::GetInstance().GetDXDevice())->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX_3D))))
	{
		return false;
	}

	return true;
}

void EnemyLevel::NextCharPos(VERTEX_3D vertex[])
{
	for (int i = 0; i < 4; ++i) {
		vertex[i].x += Fonts::g_Width;
	}
}