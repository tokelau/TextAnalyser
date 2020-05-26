#ifndef STEMMER_H
#define STEMMER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "hunspell\hunspell.h"

using namespace std;

class Stemmer {
private:
	Hunhandle* h;
public:
	Stemmer() {
		h = Hunspell_create("ru_RU.aff", "ru_RU.dic");
	}

	void stem(vector<string> &txt) {
		Hunhandle* h = Hunspell_create("ru_RU.aff", "ru_RU.dic");

		//выделяем память для массива с результатами
		char*** slst = new char**;
		//for (int i = 0; i < 100; i++) {
		slst[0] = new char*[20];
		for (int j = 0; j < 20; j++) {
			slst[0][j] = new char[50];
		}
		//}

		for (vector<string>::iterator it = txt.begin(); it != txt.end(); it++) {
			int flag = Hunspell_stem(h, slst, (*it).c_str());

			/*ofstream out("out_stemmed.txt", ios::app);
			out.imbue(locale("ru_RU.utf8"));
			out << (*it).c_str() << " " << flag << endl;*/

			if (flag >= 1) {
				string res(**slst);
				(*it) = res;
				//out << res << " " << flag << endl;
			}

			//out.close();
		}

		//освобождаем память
		delete[] slst;
	}

	//тоже стеммер, но для одного слова
	static void stem(string &word) {
		Hunhandle* h = Hunspell_create("ru_RU.aff", "ru_RU.dic");

		//выделяем память для массива с результатами
		char*** slst = new char**;
		//for (int i = 0; i < 100; i++) {
		slst[0] = new char*[20];
		for (int j = 0; j < 20; j++) {
			slst[0][j] = new char[50];
		}
		//}

		int flag = Hunspell_stem(h, slst, word.c_str());

		if (flag >= 1) {
			string res(**slst);
			word = res;
			//out << res << " " << flag << endl;
		}


		//освобождаем память
		delete[] slst;
	}
};

#endif