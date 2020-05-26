#ifndef DOC_H
#define DOC_H

#include <iostream>
#include <fstream>
#include <string>

#include <AtlBase.h>

#include "Text.h"
#include "Utf8.h"
#include "docx\duckx.hpp"

using namespace std;

class Document {
private:
	wstring filePath;
	Text text;
	Utf8 utf8;

	//является ли символ разделителем между словами
	bool isSplit(char ch) {
		if ((ch == '\n' || ch == '\t' || ch == '\v' || ch == ' ' || ch == '\0')) {
			return true;
		}
		return false;
	}
public:
	Document(wstring _filePath) : utf8() {
		filePath = _filePath;
	}
	Document() : utf8() {}

	Text readDocument() {
		size_t pointIndex = filePath.find(L".");

		if (filePath.substr(pointIndex + 1, filePath.length() - pointIndex) == L"docx") {
			string file = getFileContent();
			string word = "";

			ofstream out("out1.txt");

			for (string::iterator it = file.begin(); it != file.end(); it++) {
				char ch = (*it);
				//out << ch << endl;
				if (isSplit(ch)) {
					if (word != "") {
						text.text.push_back(word);
						out << "pushed word: " << word.c_str() << endl;
						string ws = toAbb(word);
						if (!ws.empty()) {
							text.clearedText.push_back(ws);
							out << "pushed ws: " << ws << endl;
						}
						word = "";
					}
				}
				else {
					word += ch;
				}
			}
			if (!word.empty()) {
				if (word != "") {
					text.text.push_back(word);
				}
				string ws = toAbb(word);
				if (!ws.empty()) {
					text.clearedText.push_back(toAbb(word));
				}
			}
			out.close();

		}

		return text; //здесь возвращается Text c заполненными cleared/text
	}
	
	static string toAbb(string full) {
		if (full == "") return "";
		Utf8 utf8;
		
		string abb = full;
		int i = 0;
		// идем с начала
		for (i; i < abb.size(); i++) {
			if (abb[i] < 0) { // для utf8 символы русского алф. будут меньше нуля
				break;
			}
		}
		//cout << i << ' ';
		abb = abb.erase(0, i);
		if (abb == "") {
			return "";
		}

		i = abb.length() - 1;
		//идем с конца
		while ((i > 0) && (abb[i] > 0)) {
			i--;
		}
		abb = abb.erase(i + 1, string::npos);

		//к нижнему регистру
		string trueAbb = "";
		string compare;
		int shift = 0;
		for (int i = 0; i < abb.length(); i++) {
			compare += abb[i];

			//сравним с в середине слова
			if ((int)compare[0] == 45) {
				trueAbb += compare;
				compare = "";
				shift += 1;
				continue;
			}

			if ((i + shift) % 2 == 1) {
				trueAbb += utf8.lower[compare];
				compare = "";
			}

		}
		abb = trueAbb;
		return abb;
	}

	string getFileContent() {
		CW2A cw2a(filePath.c_str());
		string fPath = cw2a;

		duckx::Document doc(fPath);

		doc.open();
		string res = "";
		for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
			for (auto r = p.runs(); r.has_next(); r.next()) {
				res += r.get_text();
			}
			res += "\n";
		}

		return res;
	}
};

#endif 
