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
		//большие буквы алфавита
		upper_alpabet.insert(u8"A");
		upper_alpabet.insert(u8"Б");
		upper_alpabet.insert(u8"В");
		upper_alpabet.insert(u8"Г");
		upper_alpabet.insert(u8"Д");
		upper_alpabet.insert(u8"Е");
		upper_alpabet.insert(u8"Ё");
		upper_alpabet.insert(u8"Ж");
		upper_alpabet.insert(u8"З");
		upper_alpabet.insert(u8"И");
		upper_alpabet.insert(u8"Й");
		upper_alpabet.insert(u8"К");
		upper_alpabet.insert(u8"Л");
		upper_alpabet.insert(u8"М");
		upper_alpabet.insert(u8"Н");
		upper_alpabet.insert(u8"О");
		upper_alpabet.insert(u8"П");
		upper_alpabet.insert(u8"Р");
		upper_alpabet.insert(u8"С");
		upper_alpabet.insert(u8"Т");
		upper_alpabet.insert(u8"У");
		upper_alpabet.insert(u8"Ф");
		upper_alpabet.insert(u8"Х");
		upper_alpabet.insert(u8"Ц");
		upper_alpabet.insert(u8"Ч");
		upper_alpabet.insert(u8"Ш");
		upper_alpabet.insert(u8"Щ");
		upper_alpabet.insert(u8"Ъ");
		upper_alpabet.insert(u8"Ы");
		upper_alpabet.insert(u8"Ь");
		upper_alpabet.insert(u8"Э");
		upper_alpabet.insert(u8"Ю");
		upper_alpabet.insert(u8"Я");

		//маленькие буквы алфавита
		lower_alpabet.insert(u8"а");
		lower_alpabet.insert(u8"б");
		lower_alpabet.insert(u8"в");
		lower_alpabet.insert(u8"г");
		lower_alpabet.insert(u8"д");
		lower_alpabet.insert(u8"е");
		lower_alpabet.insert(u8"ё");
		lower_alpabet.insert(u8"ж");
		lower_alpabet.insert(u8"з");
		lower_alpabet.insert(u8"и");
		lower_alpabet.insert(u8"й");
		lower_alpabet.insert(u8"к");
		lower_alpabet.insert(u8"л");
		lower_alpabet.insert(u8"м");
		lower_alpabet.insert(u8"н");
		lower_alpabet.insert(u8"о");
		lower_alpabet.insert(u8"п");
		lower_alpabet.insert(u8"р");
		lower_alpabet.insert(u8"с");
		lower_alpabet.insert(u8"т");
		lower_alpabet.insert(u8"у");
		lower_alpabet.insert(u8"ф");
		lower_alpabet.insert(u8"х");
		lower_alpabet.insert(u8"ц");
		lower_alpabet.insert(u8"ч");
		lower_alpabet.insert(u8"ш");
		lower_alpabet.insert(u8"щ");
		lower_alpabet.insert(u8"ъ");
		lower_alpabet.insert(u8"ы");
		lower_alpabet.insert(u8"ь");
		lower_alpabet.insert(u8"э");
		lower_alpabet.insert(u8"ю");
		lower_alpabet.insert(u8"я");
		
		//буквы для преобразования регистра
		lower[u8"A"] = u8"а";
		lower[u8"Б"] = u8"б";
		lower[u8"В"] = u8"в";
		lower[u8"Г"] = u8"г";
		lower[u8"Д"] = u8"д";
		lower[u8"Е"] = u8"е";
		lower[u8"Ё"] = u8"ё";
		lower[u8"Ж"] = u8"ж";
		lower[u8"З"] = u8"з";
		lower[u8"И"] = u8"и";
		lower[u8"Й"] = u8"й";
		lower[u8"К"] = u8"к";
		lower[u8"Л"] = u8"л";
		lower[u8"М"] = u8"м";
		lower[u8"Н"] = u8"н";
		lower[u8"О"] = u8"о";
		lower[u8"П"] = u8"п";
		lower[u8"Р"] = u8"р";
		lower[u8"С"] = u8"с";
		lower[u8"Т"] = u8"т";
		lower[u8"У"] = u8"у";
		lower[u8"Ф"] = u8"ф";
		lower[u8"Х"] = u8"х";
		lower[u8"Ц"] = u8"ц";
		lower[u8"Ч"] = u8"ч";
		lower[u8"Ш"] = u8"ш";
		lower[u8"Щ"] = u8"щ";
		lower[u8"Ъ"] = u8"ъ";
		lower[u8"Ы"] = u8"ы";
		lower[u8"Ь"] = u8"ь";
		lower[u8"Э"] = u8"э";
		lower[u8"Ю"] = u8"ю";
		lower[u8"Я"] = u8"я";

		lower[u8"а"] = u8"а";
		lower[u8"б"] = u8"б";
		lower[u8"в"] = u8"в";
		lower[u8"г"] = u8"г";
		lower[u8"д"] = u8"д";
		lower[u8"е"] = u8"е";
		lower[u8"ё"] = u8"ё";
		lower[u8"ж"] = u8"ж";
		lower[u8"з"] = u8"з";
		lower[u8"и"] = u8"и";
		lower[u8"й"] = u8"й";
		lower[u8"к"] = u8"к";
		lower[u8"л"] = u8"л";
		lower[u8"м"] = u8"м";
		lower[u8"н"] = u8"н";
		lower[u8"о"] = u8"о";
		lower[u8"п"] = u8"п";
		lower[u8"р"] = u8"р";
		lower[u8"с"] = u8"с";
		lower[u8"т"] = u8"т";
		lower[u8"у"] = u8"у";
		lower[u8"ф"] = u8"ф";
		lower[u8"х"] = u8"х";
		lower[u8"ц"] = u8"ц";
		lower[u8"ч"] = u8"ч";
		lower[u8"ш"] = u8"ш";
		lower[u8"щ"] = u8"щ";
		lower[u8"ъ"] = u8"ъ";
		lower[u8"ы"] = u8"ы";
		lower[u8"ь"] = u8"ь";
		lower[u8"э"] = u8"э";
		lower[u8"ю"] = u8"ю";
		lower[u8"я"] = u8"я";
	}
};

#endif