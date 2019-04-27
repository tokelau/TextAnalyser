// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#include "targetver.h"
#include "stemming\russian_stem.h"
#include "stemming\english_stem.h"

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows:
#include <windows.h>

// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <locale>
#include <math.h>

//#include "textProcessor.h"

using namespace std;

struct Text {
	vector<wstring> text;
	vector<wstring> clearedText; //без служебных, просто обрезаны
	vector<wstring> abb; //с операцией стемминга, без служебных
};

struct HarmCenter {
	int pos;
	wstring word;
	wstring sent;
	HarmCenter() {
		pos = 0;
		word = L"";
		sent = L"";
	}
};

extern "C" class __declspec(dllexport) TextProcessor {
private:
	//является ли символ разделителем между словами
	bool isSplit(wchar_t ch) {
		if ((ch == '\n' || ch == '\t' || ch == '\v' || ch == ' ' || ch == '\0')) {
			return true;
		}
		else {
			return false;
		}
	}
	//является ли строка символ-словом
	bool isWordSymb(wstring symb) {
		if (symb.length() == 1) {
			if (wordSymbols.find(symb) != wordSymbols.end()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	//стеммер
	void stem(vector<wstring> &txt) {
		stemming::russian_stem<> StemRussian;
		for (vector<wstring>::iterator it = txt.begin(); it != txt.end(); it++) {
			StemRussian((*it));
		}
	}
	// 1 - символ cur стоит в начале предложения
	bool checkStart(wchar_t cur, wchar_t prev) {
		if ((int)cur == 96 || (int)cur == 97) {
			return 0;
		}
		if ((cur >= L'А' && cur <= L'Я') || cur == L'Ё') {
			if (prev == L'.' || prev == L'?' || prev == L'!' || prev == L'…') {
				return 1;
			}
			else {
				return 0;
			}
		}
		return 0;
	}
	// 1 - символ cur стоит в конце предложения
	bool checkEnd(wchar_t cur, wchar_t next) {
		if ((int)cur == 96 || (int)cur == 97) {
			return 0;
		}
		if (cur == L'.' || cur == L'?' || cur == L'!' || cur == L'…') {
			if ((next >= L'А' && next <= L'Я') || next == L'Ё') {
				return 1;
			}
			else {
				return 0;
			}
		}
		return 0;
	}
	HarmCenter harmonicCenter(int index) {
		//wofstream out("hc_res.txt");
		//out.imbue(locale("rus_rus.1251"));
		HarmCenter hc;
		hc.pos = index;
		//index = index + 1;
		if (index == 0) {
			hc.word = text.clearedText[0];
			for (vector<wstring>::iterator it = text.text.begin(); it != text.text.end(); it++) {
				hc.sent = hc.sent + (*it) + L" ";
			}
			return hc;
		}
		int count = 0; //отвечает за количество вхождений нужного слова
		int pos = 0; //отвечает за позицию слова в полном тексте
		for (vector<wstring>::iterator it = text.clearedText.begin(); it != text.clearedText.end(); it++) {
			//out << (*it) << endl;
		}
		hc.word = text.clearedText[index - 1]; 
		//out << "index: " << index << endl;
		//out << hc.word << endl;
		for (int i = 0; i <= index; i++) {
			if (text.clearedText[i] == hc.word) {
				count++;
			}
		}
		//out << "count: " << count << endl;
		for (int i = 0; count != 0; i++) {
			if (!isWordSymb(text.text[i])) {
				if (toAbb(text.text[pos]) == hc.word) {
					count--;
				}
			}
			pos++;
		}
		pos = pos - 1;
		//out << "pos: " << --pos << endl;
		//pos = count;
		wstring sentence = text.text[pos];
		//hc.word = sentence;
		//склеиваем начало
		if (pos != 0) {
			for (int i = pos; i > 0; i--) {
				wchar_t cur = text.text[i][0]; //первый символ текущего слова 
				wchar_t end = text.text[i - 1][text.text[i - 1].length() - 1]; //последний предыдущего
				if (checkStart(cur, end)) {
					break;
				}
				sentence = text.text[i - 1] + L' ' + sentence;
			}
		}
		//склеиваем конец
		//wchar_t cur = sentence[sentence.length() - 1];
		//wchar_t next = text.text[i + 1][0];
		//if (sentence[sentence.length() - 1])
		int len = text.text.size(); //это счет начиная с единицы
		for (int i = pos; i < len; i++) {
			if (i != pos) {
				sentence = sentence + L' ' + text.text[i];
			}
			if (i != (len - 1)) {
				wchar_t cur = text.text[i][text.text[i].length() - 1];
				wchar_t next = text.text[i + 1][0];
				if (checkEnd(cur, next)) {
					break;
				}
			}
			else {
				break;
			}
		}
		hc.sent = sentence;
		//out.close();
		return hc;
	}
public:
	list<list<wstring>> service;
	unordered_set<wstring> wordSymbols;
	Text text;
	int textVolume;
	int uniqVolume;
	double lexWealth;
	HarmCenter hc1;
	HarmCenter hc2;
	//wstring debug;
	int k;
	TextProcessor(wstring filePath, wstring dictPath) {
		setlocale(LC_ALL, "Russian");
		//загружаем словарь служебных слов
		wifstream dict(dictPath);
		dict.imbue(locale("rus_rus.1251"));
		list<wstring> ser;
		wstring word = L"";

		wofstream res("result.txt");
		res.imbue(locale("rus_rus.1251"));

		while (!dict.eof()) {
			wchar_t ch = dict.get();
			if (ch == '\n') {
				ser.push_back(word);
				service.push_back(ser);
				word = L"";
				ser.clear();
				//res << endl;
			}
			else if (ch == L' ') {
				ser.push_back(word);
				//res << word << " ";
				word = L"";
			}
			else {
				word += ch;
			}
		}
		dict.close();
		//res.close();
		//это слова-символы, которые нам не  нужно учитывать при подсчете слов
		wordSymbols.insert(wstring(L"") + ((wchar_t)150)); //тире
		wordSymbols.insert(wstring(L"") + ((wchar_t)151)); //тире 
		wordSymbols.insert(wstring(L"") + ((wchar_t)45)); //минус

		//загружаем текст
		word = L"";
		wifstream in(filePath);
		in.imbue(locale("rus_rus.1251"));
		
		while (!in.eof()) {
			wchar_t ch = in.get();
			if (isSplit(ch)) {
				if (word != L"") {
					//text.text.push_back(word);
					//if (!isWordSymb(word)) {
					//	//debug = debug + L" " + word;
					//	text.clearedText.push_back(toAbb(word));
					//	//res << word << " " << toAbb(word) << endl;
					//}
					////res << word << endl;
					text.text.push_back(word);
					wstring ws = toAbb(word);
					if (!ws.empty()) {
						text.clearedText.push_back(toAbb(ws));
					}
					word = L"";
				}
			}
			else {
				word += ch;
			}
		}
		//uniqVolume = text.text.size();
		//in.close();
		if (!word.empty()) {
			//следующая строчка нужна потому что символ EOF распознается как буква я
			word = word.erase(word.length() - 1, word.length());
			if (word != L"") {
				text.text.push_back(word);
			}
			wstring ws = toAbb(word);
			if (!ws.empty()) {
				text.clearedText.push_back(toAbb(word));
				//res << toAbb(word) << endl;
			}
		}
		in.close();
		res << "txt cleared size: " << text.clearedText.size() << endl;
		if (text.clearedText.size() > 1) {
			//удаляем служебные
			for (list<list<wstring>>::iterator it = service.begin(); it != service.end(); it++) {
				vector<wstring>::iterator cur = find(text.clearedText.begin(), text.clearedText.end(), (*(*it).begin()));
				while (cur != text.clearedText.end()) {
					int len = (*it).size();
					int count = 0;
					vector<wstring>::iterator tmp = cur;
					for (list<wstring>::iterator wd = (*it).begin(); wd != (*it).end(); wd++) {
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
			res << "without service: " << text.clearedText.size() << endl;

			//убираем окончания
			text.abb = text.clearedText;
			stem(text.abb);

			//начинаем вычислять параметры
			/*for (vector<wstring>::iterator it = text.clearedText.begin(); it != text.clearedText.end(); it++) {
				res << (*it)<<endl;
			}
			res.close();*/
			unordered_map<wstring, int> repeats; //количество вхождений каждого слова
			for (vector<wstring>::iterator it = text.abb.begin(); it != text.abb.end(); it++) {
				repeats[*it]++;
			}
			uniqVolume = 0; //количество уникальных слов
			for (unordered_map<wstring, int>::iterator it = repeats.begin(); it != repeats.end(); it++) {
				if ((*it).second == 1) {
					uniqVolume++;
				}
			}
			//res << repeats.size() << endl;
			//for (unordered_map<wstring, int>::iterator it = unique.begin(); it != unique.end(); it++) {
			//	res << (*it).first << " " << (*it).second << endl;
			//}

			textVolume = text.clearedText.size();
			res << "textVolume: " << textVolume << endl;
			res << "uniqSize: " << uniqVolume << endl;
			//for (unordered_set<wstring>::iterator it = unique.begin(); it != unique.end(); it++) {
			//	res << (*it) << endl;
			//}
			lexWealth = (double)uniqVolume / sqrt(textVolume); //коэфф. лексического богатства
			hc1 = harmonicCenter((int)(textVolume / 1.618));
			k = (int)(textVolume / 1.618);
			//res << hc1.sent << endl;
			hc2 = harmonicCenter(textVolume - (int)(textVolume / 1.618));
			//hc2 = harmonicCenter((int)(textVolume / 1.618));
		}
		else {
			uniqVolume = 0; //количество уникальных слов
			lexWealth = 0; //коэфф. лексического богатства
			hc1.pos = 0;
			hc1.sent = L"";
			hc1.word = L"";
			//k = (int)(textVolume / 1.618);
			//res << hc1.sent << endl;
			hc2.pos = 0;
			hc2.sent = L"";
			hc2.word = L"";
		}
		res.close();
	}
	wstring toAbb(wstring full) {
		setlocale(LC_ALL, "Russian");
		if (full == L"") return L"";
		wstring abb = full;
		int i = 0;
		while (i < abb.size() && (abb[i] < L'А' || abb[i] > L'я') && (abb[i] != L'Ё' || abb[i] != L'ё')) {
			i++;
		}
		//cout << i << ' ';
		abb = abb.erase(0, i);
		if (abb == L"") {
			return L"";
		}
		i = abb.length() - 1;
		//cout << i << ' ';
		while ((abb[i] < L'А' || abb[i] > L'я') && (abb[i] != L'Ё' || abb[i] != L'ё')) {
			i--;
		}
		//cout << i << ' ';
		abb = abb.erase(i + 1, abb.length() - 1);
		//cout << i << ' ';
		wstring trueAbb = L"";
		for (wstring::iterator it = abb.begin(); it != abb.end(); it++) {
			switch (*it)
			{
			case L'А':
				trueAbb += L'а';
				break;
			case L'Б':
				trueAbb += L'б';
				break;
			case L'В':
				trueAbb += L'в';
				break;
			case L'Г':
				trueAbb += L'г';
				break;
			case L'Д':
				trueAbb += L'д';
				break;
			case L'Е':
				trueAbb += L'е';
				break;
			case L'Ё':
				trueAbb += L'е';
				break;
			case L'ё':
				trueAbb += L'е';
				break;
			case L'Ж':
				trueAbb += L'ж';
				break;
			case L'З':
				trueAbb += L'з';
				break;
			case L'И':
				trueAbb += L'и';
				break;
			case L'Й':
				trueAbb += L'й';
				break;
			case L'К':
				trueAbb += L'к';
				break;
			case L'Л':
				trueAbb += L'л';
				break;
			case L'М':
				trueAbb += L'м';
				break;
			case L'Н':
				trueAbb += L'н';
				break;
			case L'О':
				trueAbb += L'о';
				break;
			case L'П':
				trueAbb += L'п';
				break;
			case L'Р':
				trueAbb += L'р';
				break;
			case L'С':
				trueAbb += L'с';
				break;
			case L'Т':
				trueAbb += L'т';
				break;
			case L'У':
				trueAbb += L'у';
				break;
			case L'Ф':
				trueAbb += L'ф';
				break;
			case L'Х':
				trueAbb += L'х';
				break;
			case L'Ц':
				trueAbb += L'ц';
				break;
			case L'Ч':
				trueAbb += L'ч';
				break;
			case L'Ш':
				trueAbb += L'ш';
				break;
			case L'Щ':
				trueAbb += L'щ';
				break;
			case L'Ъ':
				trueAbb += L'ъ';
				break;
			case L'Ы':
				trueAbb += L'ы';
				break;
			case L'Ь':
				trueAbb += L'ь';
				break;
			case L'Э':
				trueAbb += L'э';
				break;
			case L'Ю':
				trueAbb += L'ю';
				break;
			case L'Я':
				trueAbb += L'я';
				break;
			default:
				trueAbb += (*it);
			}
		}
		abb = trueAbb;
		return abb;
	}

	static int countByDict(TextProcessor tp, wstring pathToDict, wstring pathToSave) {
		//читаем словарь по которому должны считать вхождения
		wifstream inDict(pathToDict);
		inDict.imbue(locale("rus_rus.1251"));
		//wofstream res("cbdResult.txt");
		//res.imbue(locale("rus_rus.1251"));
		if (!inDict.is_open()) {
			return -1;
		}
		list<pair<wstring, wstring>> dict;
		unordered_map<wstring, int> count;
		wstring word = L"";
		stemming::russian_stem<> StemRussian;
		while (!inDict.eof()) {
			wchar_t ch = inDict.get();
			if (ch == L'\n' || ch == L'\0') {
				if (word != L"") {
					wstring abb = tp.toAbb(word);
					StemRussian(abb);
					dict.push_back(pair<wstring, wstring>(word, abb));
					count[word] = 0;
					word = L"";
					//cout << word;
				}
			}
			else {
				word += ch;
			}
		}
		inDict.close();
		if (!word.empty()) {
			wstring abb = tp.toAbb(word);
			StemRussian(abb);
			dict.push_back(pair<wstring, wstring>(word, abb));
			count[word] = 0;
		}
		//читаем текст для поиска вхождений
		for (vector<wstring>::iterator it = tp.text.abb.begin(); it != tp.text.abb.end(); it++) {
			for (list<pair<wstring, wstring>>::iterator dt = dict.begin(); dt != dict.end(); dt++) {
				if ((*dt).second == (*it)) {
					count[(*dt).first]++;
					//res << (*it) << (*dt).second << " " << endl;
				}
			}
		}
		wofstream out(pathToSave);
		out.imbue(locale("rus_rus.1251"));
		if (!out.is_open()) {
			return -1;
		}
		for (unordered_map<wstring, int>::iterator it = count.begin(); it != count.end(); it++) {
			out << (*it).first << L" - " << (*it).second << endl;
		}
		out.close();
		//res.close();
		return 0;
	}
};