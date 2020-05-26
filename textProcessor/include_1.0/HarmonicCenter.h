#ifndef HARMCENTER_H
#define HARMCENTER_H

#include <iostream>

using namespace std;

struct HarmCenter {
	int pos;
	string word;
	string sent;
	HarmCenter() {
		pos = 0;
		word = "";
		sent = "";
	}
};

class HarmFinder {
private:
	Text text;
	Utf8 utf8;

	string toAbb(string full) {
		if (full == "") return "";
		string abb = full;
		int i = 0;
		// ���� � ������
		for (i; i < abb.size(); i++) {
			if (abb[i] < 0) { // ��� utf8 ������� �������� ���. ����� ������ ����
				break;
			}
		}
		//cout << i << ' ';
		abb = abb.erase(0, i);
		if (abb == "") {
			return "";
		}

		i = abb.length() - 1;
		//���� � �����
		while ((i > 0) && (abb[i] > 0)) {
			i--;
		}
		abb = abb.erase(i + 1, string::npos);

		//� ������� ��������
		string trueAbb = "";
		string compare;
		int shift = 0;
		for (int i = 0; i < abb.length(); i++) {
			compare += abb[i];

			//������� � � �������� �����
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
	
	bool isWordSymb(string symb) {
		if (symb.size() == 1) {
			return true;
		}
		return false;
	}
	bool checkStart(string cur, char prev) {
		if (utf8.upper_alpabet.find(cur) != utf8.upper_alpabet.end()) {
			if (prev == '.' || prev == '?' || prev == '!' || prev == '�') {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
public:
	HarmFinder(Text _text): utf8() {
		text = _text;
	}

	HarmCenter harmonicCenter(int index)  {
		HarmCenter hc;
		hc.pos = index;
		//index = index + 1;
		if (index == 0) {
			hc.word = text.clearedText[0];
			for (vector<string>::iterator it = text.text.begin(); it != text.text.end(); it++) {
				hc.sent = hc.sent + (*it) + " ";
			}
			return hc;
		}
		int count = 0; //�������� �� ���������� ��������� ������� �����
		int pos = 0; //�������� �� ������� ����� � ������ ������

		hc.word = text.clearedText[index - 1];
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
		string sentence = "";

		//��������� ������
		if (pos != 0) {
			int dist = 0; //���������� �� �������-����� �� ������������ �����
			sentence = text.text[pos];
			for (int i = pos - 1; i >= 0; i--) {
				if (i - dist < 0) {
					break;
				}
				if (isWordSymb(text.text[i])) {
					sentence = text.text[i] + ' ' + sentence;
					dist++;
					continue;
				}
				char cur = text.text[i][text.text[i].length() - 1]; //��������� ������ �������� ����� 
				string next = "";
				next += text.text[i + dist + 1][0]; //������ �����������
				next += text.text[i + dist + 1][1]; //������ �����������
				if (checkStart(next, cur)) {
					break;
				}
				sentence = text.text[i] + ' ' + sentence;
				dist = 0;
			}
		}
		else {
			sentence = text.text[0];
		}
		
		//��������, �� ����� �� ���� ����� � �����
		bool isStart = false;
		string cur = string("") + text.text[pos][0] + text.text[pos][1];
		char prev = text.text[pos - 1][text.text[pos - 1].length() - 1];
		if (checkStart(cur, prev)) {
			isStart = true;
		}

		//��������� �����
		if (!isStart) {
			size_t len = text.text.size(); //��� ���� ������� � �������
			int dist = 0;
			for (int i = pos + 1; i < len; i++) {
				if (isWordSymb(text.text[i])) {
					sentence = sentence + ' ' + text.text[i];
					dist++;
					continue;
				}
				string cur = string("") + text.text[i][0] + text.text[i][1];
				char prev = text.text[i - dist - 1][text.text[i - dist - 1].length() - 1];
				if (checkStart(cur, prev)) {
					//if (isWordSymb(L"" + sentence[sentence.length() - 1])) {
					//	sentence.erase();
					//}
					break;
				}
				sentence = sentence + ' ' + text.text[i];
				dist = 0;
			}
		}
		hc.sent = sentence;
		//out.close();
		return hc;
	}

};

#endif
