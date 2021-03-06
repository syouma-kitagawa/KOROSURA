#ifndef SELECTION_H
#define SELECTION_H

#include<functional>

class Selecter{
public:
	Selecter(int MaxChoices, std::function<void(int selectPoint)> function);
	~Selecter();

	//0〜の番号
	int GetCurrentSelection() {
		return m_SelectPoint;
	}

	void Update();

private:
	//決定キーが押されたら呼ばれる
	std::function<void(int selectPoint)> m_Function;
	int m_SelectPoint = 0;

	const int m_MaxChoices = 0;
};
#endif