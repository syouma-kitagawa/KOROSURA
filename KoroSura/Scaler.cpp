#include "Scaler.h"
#include<Windows.h>

Scaler::Scaler(float maxScale, float initScale, int maxInterval):
	m_Scale(initScale),
	kMaxScale(maxScale),
	kInitScale(initScale),
	kMaxInterval(maxInterval)
{
	if (kMaxInterval == 0) {
		//0割りするため
		MessageBox(0, "不当な値が入力されました", 0, MB_OK);
		delete this;
	}
}

Scaler::~Scaler()
{
}

void Scaler::Update() 
{
	if (m_FrCnt <= kMaxInterval) {

		++m_FrCnt;

		m_Scale += (kMaxScale - kInitScale) * (m_FrCnt / kMaxInterval);
	}
}