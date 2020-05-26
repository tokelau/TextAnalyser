#ifndef SERVICE_H
#define SERVICE_H

#include <fstream>
#include <list>
#include <string>
#include <vector>

using namespace std;

class Service {
private:
	list<list<string>> service;
	
	//загружаем словарь служебных слов
	void loadService() {
		ifstream dict("data\\dict.txt");
		dict.imbue(locale("ru_RU.utf8"));

		list<string> ser;
		string word = "";

		while (!dict.eof()) {
			char ch = dict.get();
			if (ch == '\n') {
				ser.push_back(word);
				service.push_back(ser);
				word = "";
				ser.clear();
			}
			else if (ch == ' ') {
				ser.push_back(word);
				word = "";
			}
			else {
				word += ch;
			}
		}
		dict.close();
	}
public:
	Service() {
		loadService();
	}
	
	//удаляем служебные
	void clearText(Text& text) {
		for (list<list<string>>::iterator it = service.begin(); it != service.end(); it++) {
			vector<string>::iterator cur = find(text.clearedText.begin(), text.clearedText.end(), (*(*it).begin()));
			while (cur != text.clearedText.end()) {
				size_t len = (*it).size();
				int count = 0;
				vector<string>::iterator tmp = cur;
				for (list<string>::iterator wd = (*it).begin(); wd != (*it).end(); wd++) {
					if ((*tmp) == (*wd)) {
						count++;
						tmp++;
						//res << (*wd) << " ";
					}

				}
				//res << endl;
				//res << len << " " << count << endl;
				if (len == count) {
					for (int i = 0; i < count; i++) {
						//res << (*cur) << " ";
						text.clearedText.erase(cur);
						cur++;
					}
					//res << endl;
				}
				else {
					break;
				}
				cur = find(text.clearedText.begin(), text.clearedText.end(), (*(*it).begin()));
				//res << endl;
			}
		}
	}
};

#endif