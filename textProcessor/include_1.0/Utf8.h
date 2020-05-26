#ifndef UTF8_H
#define UTF8_H

#include <unordered_map>
#include <set>

using namespace std;

struct Utf8 {
	unordered_map<string, string> lower;
	set<string> upper_alpabet;
	set<string> lower_alpabet;

	Utf8() {
		//������� ����� ��������
		upper_alpabet.insert(u8"A");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");
		upper_alpabet.insert(u8"�");

		//��������� ����� ��������
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		lower_alpabet.insert(u8"�");
		
		//����� ��� �������������� ��������
		lower[u8"A"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";

		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
		lower[u8"�"] = u8"�";
	}
};

#endif