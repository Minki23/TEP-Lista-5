#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "NodeTree.h"
template <typename T> class UserInterface
{
public:
	UserInterface<T>();
	~UserInterface<T>();
	std::vector<std::string> getwords();
	std::vector<std::string> splitString(std::string sequence);
private:
	void activate();
	NodeTree<T>* mytree;
	std::vector<std::string> words;
	void takeCommand(std::string command);
	void Comp(std::vector<std::string> data);
	void Checktype();
	std::string type;
};
template <typename T>
UserInterface<T>::UserInterface() {
	mytree = new NodeTree<T>();
	Checktype();
	activate();
}
template<>
void UserInterface<int>::Checktype() {
	type = "INT";
}
void UserInterface<double>::Checktype() {
	type = "DOUBLE";
}
void UserInterface<std::string>::Checktype() {
	type = "STRING";
}
template <typename T>
UserInterface<T>::~UserInterface() {
	delete mytree;
}
template <typename T>
std::vector<std::string> UserInterface<T>::splitString(std::string sequence) {
	std::string word;
	std::vector<std::string>words;
	if (sequence[sequence.size() - 1] != ' ') {
		sequence += " ";
	}
	for (int i = 0;i < sequence.size();i++) {
		if (sequence[i] != ' ') {
			if (std::isalnum(sequence[i]) || sequence[i] == '+' || sequence[i] == '-' || sequence[i] == '*' || sequence[i] == '/') {
				word.push_back(sequence[i]);
			}
			else {
				if(sequence[i]=='.' && type=="DOUBLE")
					word.push_back(sequence[i]);
				else
					std::cout << "pominieto znak: " << sequence[i] << " \n";
			}
		}
		else {
			if (!word.empty()) {
				words.push_back(word);
				word.clear();
			}
		}
	}
	return words;
}
template <>
std::vector<std::string> UserInterface<std::string>::splitString(std::string sequence) {
	std::string word;
	std::vector<std::string>words;
	if (sequence[sequence.size() - 1] != ' ') {
		sequence += " ";
	}
	for (int i = 0;i < sequence.size();i++) {
		if (sequence[i] != ' ') 
			word.push_back(sequence[i]);		
		else {
			if (!word.empty()) {
				words.push_back(word);
				word.clear();
			}
		}
	}
	return words;
}
template<typename T>
void UserInterface<T>::activate() {
	std::string wybor = "1";
	std::cout << "Wpisz `enter [sekwencja]` aby stworzyc drzewo\n";
	std::cout << "Wpisz `join [sekwencja]` aby dodac sekwencje do drzewa\n";
	std::cout << "Wpisz `print` aby pokazac obecne drzewo\n";
	std::cout << "Wpisz `comp [wartosci]` aby obliczyc sekwencje na drzewie z podanymi wartosciami zmiennych\n";
	std::cout << "Wpisz `return` aby zmienic typ drzewa / wyjsc\n\n";
	do {
		std::cout << "Podaj komende> ";
		std::getline(std::cin, wybor);
		takeCommand(wybor);
	} while (wybor != "return");
}
template<typename T>
void UserInterface<T>::takeCommand(std::string command) {
	if (command.size() > 0) {
		std::vector<std::string> data = splitString(command);
		std::string toinvoke = data.at(0);
		data.erase(data.begin());
		if (toinvoke == "enter") {
			mytree->put(data);
		}
		else if (toinvoke == "print") {
			mytree->InOrderWalk();
		}
		else if (toinvoke == "comp") {
			Comp(data);
		}
		else if (toinvoke == "join") {
			if (mytree != nullptr) {
				NodeTree<T>* toadd = new NodeTree<T>();
				(*toadd).put(data);
				mytree->join(*toadd);
			}
			else {
				mytree->put(data);
			}
		}
		else if (toinvoke == "vars") {
			for (std::string variable : mytree->getvariables()) {
				std::cout << variable << " ";
			}
			std::cout << "\n";
		}
		else if (toinvoke != "return") {
			std::cout << "Nierozpoznano komendy\n";
		}
	}
}
template<>
void UserInterface<std::string>::Comp(std::vector<std::string> data) {
	std::cout << mytree->CalcVal(*((*mytree).getRoot()), data) << "\n";
}
template<typename T>
void UserInterface<T>::Comp(std::vector<std::string> data) {
	if (data.size() != mytree->getvariables().size())
		std::cout << "bledna ilosc wartosci, spodziewano sie " << mytree->getvariables().size() << " wartosci a otrzymano: " << data.size() << "\n";
	else {
		bool poprawna = true;
		for (std::string dataitem : data) {
			for (char datachar : dataitem) {
				if (isalpha(datachar))
					poprawna = false;
			}
			if (!poprawna)
				std::cout << "bledna wartosc zmiennej, podano: " << dataitem << "\n";
		}
		if (poprawna)
			std::cout << mytree->CalcVal(*((*mytree).getRoot()), data) << "\n";
	}
}