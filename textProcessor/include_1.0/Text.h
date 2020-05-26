#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>

using namespace std;

struct Text {
	vector<string> text; //исходный текст без преобразований
	vector<string> clearedText; //удалены служебные
	vector<string> abb; //применен стемминг к clearedText
};

#endif 