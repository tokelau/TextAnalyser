#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>

using namespace std;

struct Text {
	vector<string> text; //�������� ����� ��� ��������������
	vector<string> clearedText; //������� ���������
	vector<string> abb; //�������� �������� � clearedText
};

#endif 