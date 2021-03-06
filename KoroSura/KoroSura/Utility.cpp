#include"Utility.h"
#include<d3dx9.h>
#include<stdio.h>
#include<tchar.h>
#include<time.h>

//min<= random <= max
int Utility::Random(int min, int max)
{
	static bool seedrandom = false;

	if (seedrandom == false) {
		srand((unsigned int)time(NULL));
		seedrandom = true;
	}

	return min + rand() % (max-min + 1);
}

bool Utility::JudgeCollisionCircle(const D3DXVECTOR2& pos1, float r1, const D3DXVECTOR2& pos2, float r2)
{
	float sumR = r1 + r2;

	float L = (float)pow(pos1.x - pos2.x, 2) + (float)pow(pos1.y - pos2.y, 2);
	L = (float)sqrt(L);

	if (sumR >= L) {
		return true;
	}
	return false;
}

bool Utility::JudgeCollisionSquare(const D3DXVECTOR2& pos1, float width1, float height1, const D3DXVECTOR2& pos2, float width2, float height2)
{
	D3DXVECTOR2 LeftTop1;
	D3DXVECTOR2 RightTop1;
	D3DXVECTOR2 LeftBottom1;
	D3DXVECTOR2 LeftTop2;
	D3DXVECTOR2 RightTop2;
	D3DXVECTOR2 LeftBottom2;

	LeftTop1.x = LeftBottom1.x = pos1.x - width1 / 2;
	RightTop1.x = pos1.x + width1 / 2;
	LeftTop1.y = RightTop1.y = pos1.y - height1 / 2;
	LeftBottom1.y = pos1.y + height1 / 2;
	LeftTop2.x = LeftBottom2.x = pos2.x - width2 / 2;
	RightTop2.x = pos2.x + width2 / 2;
	LeftTop2.y = RightTop2.y = pos2.y - height2 / 2;
	LeftBottom2.y = pos2.y + height2 / 2;

	if (LeftTop1.x < RightTop2.x) {
		if (LeftTop2.x < RightTop1.x) {
			if (LeftTop1.y < LeftBottom2.y) {
				if (LeftTop2.y < LeftBottom1.y) {
					return true;
				}
			}
		}
	}
	return false;
}

double Utility::CalculateRad(float x1, float y1, float x2, float y2)
{
	double rad;

	double lengthX = x2 - x1;
	double lengthY = y2 - y1;

	if (lengthX == 0 && lengthY == 0) {
		return 0;
	}

	if (lengthX > 0) {
		if (lengthY < 0) {
			rad = atan(lengthY / lengthX);
		}
		else {
			rad = atan(lengthY / lengthX);
		}
	}
	else if (lengthX < 0) {
		rad = atan(lengthY / lengthX) + D3DX_PI;
	}
	else if (lengthX == 0) {
		if (lengthY < 0) {
			rad = D3DX_PI / 2;
		}
		else {
			rad = 3 / 2 * D3DX_PI;
		}
	}

	return rad;
}

float Utility::CalculateDeg(float x1, float y1, float x2, float y2) 
{
	return (float)D3DXToDegree(CalculateRad(x1, y1, x2, y2));
}

float Utility::CalculateDistance(float x1, float y1, float x2, float y2) 
{
	return (float)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void Utility::OutputDebug_Number(float outputNum, HWND hWnd) 
{
	TCHAR buff[256];
	_stprintf_s(buff, 256, _T("%f\n"), outputNum);
	OutputDebugString(buff);
	SetWindowText(hWnd, buff);
}

void Utility::OutputDebug_Number(float outputNum) 
{
	TCHAR buff[256];
	_stprintf_s(buff, 256, _T("%f\n"), outputNum);
	OutputDebugString(buff);
}

Matrix* Utility::GetRotationXMatrix(Matrix* mat, float deg)
{
	float rad = D3DXToRadian(deg);
	*mat = Matrix(3, 3,
		1.0, 0.0, 0.0,
		0.0, cos(rad), -sin(rad),
		0.0, sin(rad), cos(rad));

	return mat;
}

Matrix* Utility::GetRotationYMatrix(Matrix* mat, float deg)
{
	float rad = D3DXToRadian(deg);
	*mat = Matrix(3, 3,
		cos(rad), 0.0, sin(rad),
		0.0, 1.0, 0.0,
		-sin(rad), 0.0, cos(rad));

	return mat;
}

Matrix* Utility::GetRotationZMatrix(Matrix* mat, float deg)
{
	float rad = D3DXToRadian(deg);
	*mat = Matrix(3, 3,
		cos(rad), -sin(rad), 0.0,
		sin(rad), cos(rad), 0.0,
		0.0, 0.0, 1.0);

	return mat;
}

D3DXVECTOR3* Utility::Tilt(D3DXVECTOR3* vector, float deg)
{
	float rad;
	rad = D3DXToRadian(deg);

	float length = D3DXVec3Length(vector);

	float theta1 = asin(vector->y / length);
	float theta2 = acos(vector->x / length*cos(theta1));

	vector->x += length*(float)cos(theta1 + rad)*(float)cos(theta2);
	vector->y += length*(float)sin(theta1 + rad);
	vector->z += length*(float)cos(theta1 + rad)*(float)sin(theta2);

	return vector;
}