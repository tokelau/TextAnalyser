#ifndef TEXTPROC_H
#define TEXTPROC_H

#include "Document.h"
#include "Service.h"
#include "Stemmer.h"
#include "HarmonicCenter.h"

//почистить импорты

using namespace std;

//не использовать длинное тире и троеточия

extern "C" class __declspec(dllexport) TextProcessor {
private:
	Text text;
public:
	int textVolume;
	int uniqVolume;
	double lexWealth;
	//int k;
	HarmCenter hc1;
	HarmCenter hc2;

	TextProcessor(wstring fPath) {
		Document doc(fPath);
		text = doc.readDocument();
		ofstream out1("read_words.txt");
		out1.imbue(locale("ru_RU.utf8"));
		for (vector<string>::iterator it = text.clearedText.begin(); it != text.clearedText.end(); it++) {
			out1<< (*it).c_str() << endl;
		}
		out1.close();

		if (text.clearedText.size() > 1) {
			Service service;
			service.clearText(text);

			Stemmer stemmer;
			text.abb = text.clearedText;
			stemmer.stem(text.abb);

			ofstream out("out.txt");
			for (vector<string>::iterator it = text.clearedText.begin(); it != text.clearedText.end(); it++) {
				out << (*it).c_str() << endl;
			}

			//ofstream out_stemmed("out_stemmed.txt");
			//for (vector<string>::iterator it = text.abb.begin(); it != text.abb.end(); it++) {
			//	out_stemmed << (*it).c_str() << endl;
			//}
			//out_stemmed.close();

			//начинаем вычислять параметры
			unordered_map<string, int> repeats; //количество вхождений каждого слова
			for (vector<string>::iterator it = text.abb.begin(); it != text.abb.end(); it++) {
				repeats[*it]++;
			}
			uniqVolume = 0; //количество уникальных слов
			for (unordered_map<string, int>::iterator it = repeats.begin(); it != repeats.end(); it++) {
				if ((*it).second == 1) {
					uniqVolume++;
				}
			}

			textVolume = text.clearedText.size();
			lexWealth = (double)uniqVolume / sqrt(textVolume); //коэфф. лексического богатства

			HarmFinder finder(text);
			hc1 = finder.harmonicCenter((int)round((textVolume / 1.618)) + 1);
			out << (textVolume / 1.618) << " " << round((textVolume / 1.618)) << endl;
			out.close();
			hc2 = finder.harmonicCenter(textVolume - (int)(textVolume / 1.618));
		} 
		else {
			uniqVolume = 0; //количество уникальных слов
			lexWealth = 0; //коэфф. лексического богатства
			hc1.pos = 0;
			hc1.sent = "";
			hc1.word = "";
			//k = (int)(textVolume / 1.618);
			//res << hc1.sent << endl;
			hc2.pos = 0;
			hc2.sent = "";
			hc2.word = "";
		}

	}

	static string getFileContent(wstring fPath) {
		Document doc(fPath);
		return doc.getFileContent();
	}

	static int countByDict(TextProcessor tp, wstring pathToDict, wstring pathToSave) {
		//читаем словарь по которому должны считать вхождения
		CW2A cw2a(pathToDict.c_str());
		string fPath = cw2a;
		
		ifstream inDict(fPath);
		inDict.imbue(locale("ru_RU.utf8"));
		
		ofstream res("cbdResult.txt");
		res.imbue(locale("ru_RU.utf8"));
		if (!inDict.is_open()) {
			return -1;
		}

		list<pair<string, string>> dict;
		unordered_map<string, int> count; //посчитает кол-во вхождений
		string word = "";

		Stemmer stemmer;

		while (!inDict.eof()) {
			char ch = inDict.get();
			if (ch == '\n' || ch == '\0') {
				if (word != "") {
					string abb = Document::toAbb(word);
					Stemmer::stem(abb);
					dict.push_back(pair<string, string>(word, abb));
					count[word] = 0;
					word = "";
					res << word;
				}
			}
			else {
				word += ch;
			}
		}
		inDict.close();
		//это чтобы учесть последнее слово из словаря
		if (!word.empty()) {
			string abb = Document::toAbb(word);
			Stemmer::stem(abb);
			dict.push_back(pair<string, string>(word, abb));
			count[word] = 0;
		}

		//читаем текст для поиска вхождений
		for (vector<string>::iterator it = tp.text.abb.begin(); it != tp.text.abb.end(); it++) {
			for (list<pair<string, string>>::iterator dt = dict.begin(); dt != dict.end(); dt++) {
				if ((*dt).second == (*it)) {
					count[(*dt).first]++;
					//res << (*it) << (*dt).second << " " << endl;
				}
			}
		}

		ofstream out(pathToSave);
		out.imbue(locale("ru_RU.utf8"));
		if (!out.is_open()) {
			return -1;
		}
		double sumCoeff = 0.0;
		for (unordered_map<string, int>::iterator it = count.begin(); it != count.end(); it++) {
			sumCoeff += (*it).second / sqrt(tp.textVolume);
			out << (*it).first << " - " << (*it).second << " (" << (*it).second / sqrt(tp.textVolume) << ")" << endl;
		}
		//string message = "Общий коэффициент объектоцентризма: ";
		out << endl << "Summary: " << sumCoeff << endl;
		out.close();
		//res.close();
		return 0;
	}
};

#endif