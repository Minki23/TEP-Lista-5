#pragma once
#include "Node.h"
#include <string>
#include <vector>
template <typename T> class NodeTree
{
public:
	NodeTree();
	NodeTree(NodeTree&& othertree);
	~NodeTree();
	Node<T>* getRoot() const;
	const std::vector<std::string>& getvariables() const;
	void PrintTree();
	void put(std::vector<std::string> sequence);
	void InOrderWalk();
	void join(const NodeTree& node);
	T CalcVal(const Node<T>& next, const std::vector<std::string>& values) const;
	NodeTree* operator+(const NodeTree& tojoin);
	NodeTree* operator=(NodeTree toequal);
	NodeTree* operator=(NodeTree&& othertree);
private:
	Node<T>* root;
	std::vector<std::string> variables;
	int indexof(const std::vector<std::string>& vec,const std::string&szukana) const;
	void InOrderInner(Node<T>& node);
	void recAdding(Node<T>& next, std::vector<std::string> sequence);
	void setRoot(Node<T> root);
};
static int shift = 1;
template <typename T>
NodeTree<T>::NodeTree() {
	this->root = new Node<T>();
}

template <typename T>
NodeTree<T>::NodeTree(NodeTree&& othertree) {
	root = othertree.root;
	variables = std::move(othertree.variables);
	othertree.root = NULL;
}
template <typename T>
NodeTree<T>::~NodeTree() {
	delete this->root;
}
template <typename T>
void NodeTree<T>::InOrderWalk() {
	InOrderInner(*this->root);
	std::cout << std::endl;
}
template <typename T>
const std::vector<std::string>& NodeTree<T>::getvariables() const {
	return this->variables;
}
template <typename T>
Node<T>* NodeTree<T>::getRoot() const {
	return this->root;
}
template <typename T>
void NodeTree<T>::put(std::vector<std::string> sequence) {
	this->root = new Node<T>(sequence[0]);
	this->root->setNumberOfChilds(sequence[0]);
	if (isalpha(sequence[0][0]) && sequence[0] != "sin" && sequence[0] != "cos") {
		variables.push_back(sequence[0]);
	}
	recAdding(*root, sequence);
	shift = 1;
}
template <>
void NodeTree<double>::put(std::vector<std::string> sequence) {
	this->root = new Node<double>(sequence[0]);
	this->root->setNumberOfChilds(sequence[0]);
	if (isalpha(sequence[0][0]) && sequence[0] != "sin" && sequence[0] != "cos" && sequence[0] != ".") {
		variables.push_back(sequence[0]);
	}
	recAdding(*root, sequence);
	shift = 1;
}
template<typename T>
void NodeTree<T>::recAdding(Node<T>& next, std::vector<std::string> sequence) {
	if (next.getNumberOfChilds() > next.getChilds()->size()) {
		if (shift < sequence.size()) {
			next.getChilds()->push_back(*(new Node<T>(sequence[shift])));
			next.getChilds()->at(0).setNumberOfChilds(sequence[shift]);
			if (isalpha(sequence[shift][0]) && indexof(variables, sequence[shift]) == -1) {
				variables.push_back(sequence[shift]);
			}
		}
		for (int i = 0;i < next.getNumberOfChilds();i++) {
			if (i >= next.getChilds()->size()) {
				if (shift < sequence.size()) {
					next.getChilds()->push_back(*(new Node<T>(sequence[shift])));
					next.getChilds()->at(i).setNumberOfChilds(sequence[shift]);
					if (isalpha(sequence[shift][0]) && indexof(variables, sequence[shift]) == -1 && sequence[shift] != "sin" && sequence[shift] != "cos") {
						variables.push_back(sequence[shift]);
					}
				}
				else {
					for (int j = 0;j < next.getNumberOfChilds();j++) {
						next.getChilds()->push_back(*(new Node<T>("1")));
						next.getChilds()->at(j).setNumberOfChilds("1");
					}
					std::cout << "blad, poprawiono\n";
				}
			}
			shift++;
			recAdding(next.getChilds()->at(i), sequence);
		}
	}
}
template<>
int NodeTree<int>::CalcVal(const Node<int>& node, const std::vector<std::string>& values) const {
	switch (node.getValue()[0])
	{
	case '+':
		return CalcVal(node.getChilds()->at(0), values) + CalcVal(node.getChilds()->at(1), values);
	case '-':
		return CalcVal(node.getChilds()->at(0), values) - CalcVal(node.getChilds()->at(1), values);
	case '*':
		return CalcVal(node.getChilds()->at(0), values) * CalcVal(node.getChilds()->at(1), values);
	case '/':
		return CalcVal(node.getChilds()->at(0), values) / CalcVal(node.getChilds()->at(1), values);
	case 's':
		if (node.getValue() == "sin")
			return sin(CalcVal(node.getChilds()->at(0), values));
		else
			std::stoi(values.at(indexof(variables, node.getValue())));
	case 'c':
		if (node.getValue() == "cos")
			return cos(CalcVal(node.getChilds()->at(0), values));
		else
			std::stoi(values.at(indexof(variables, node.getValue())));
	default:
		if (isalpha(node.getValue()[0])) {
			return std::stoi(values.at(indexof(variables, node.getValue())));
		}
		return std::stoi(node.getValue());
	}
}

template<>
double NodeTree<double>::CalcVal(const Node<double>& node, const std::vector<std::string>& values) const {
	switch (node.getValue()[0])
	{
	case '+':
		return CalcVal(node.getChilds()->at(0), values) + CalcVal(node.getChilds()->at(1), values);
	case '-':
		return CalcVal(node.getChilds()->at(0), values) - CalcVal(node.getChilds()->at(1), values);
	case '*':
		return CalcVal(node.getChilds()->at(0), values) * CalcVal(node.getChilds()->at(1), values);
	case '/':
		return CalcVal(node.getChilds()->at(0), values) / CalcVal(node.getChilds()->at(1), values);
	case 's':
		if (node.getValue() == "sin")
			return sin(CalcVal(node.getChilds()->at(0), values));
		else
			std::stod(values.at(indexof(variables, node.getValue())));
	case 'c':
		if (node.getValue() == "cos")
			return cos(CalcVal(node.getChilds()->at(0), values));
		else
			std::stod(values.at(indexof(variables, node.getValue())));
	default:
		if (isalpha(node.getValue()[0])) {
			return std::stod(values.at(indexof(variables, node.getValue())));
		}
		return std::stod(node.getValue());
	}
}
std::string operator-(std::string str1, std::string str2) {
	if (str1.length() >= str2.length() && str1.substr(str1.length() - str2.length()) == str2) {
		return str1.substr(0, str1.length() - str2.length());
	}
	else {
		return str1;
	}
}
std::string operator*(std::string str1, std::string str2) {
	std::string sub = str2.substr(1, str2.size() - 1);
	std::string result = "";
	for (size_t i = 0; i < str1.length(); ++i) {
		result += str1[i];
		if (str1[i] == str2[0]) {
			result += sub;
		}
	}
	return result;
}
std::string operator/(std::string str1, std::string str2) {
	int found = str1.find(str2);
	std::string result = str1;
	if (str2.size() <= 1)
		return result;
	while (found != -1) {
		result = result.substr(0, found+1) + result.substr(found + str2.size());
		found = result.find(str2);  // Update the found variable
	}

	return result;
}

template<>
std::string NodeTree<std::string>::CalcVal(const Node<std::string>& node, const std::vector<std::string>& values) const {
	switch (node.getValue()[0])
	{
	case '+':
		return CalcVal(node.getChilds()->at(0), values) + CalcVal(node.getChilds()->at(1), values);
	case '-':
		return CalcVal(node.getChilds()->at(0), values) - CalcVal(node.getChilds()->at(1), values);
	case '*':
		return CalcVal(node.getChilds()->at(0), values) * CalcVal(node.getChilds()->at(1), values);
	case '/':
		return CalcVal(node.getChilds()->at(0), values) / CalcVal(node.getChilds()->at(1), values);
	default:
		return node.getValue();
	}
}
template <typename T>
void NodeTree<T>::join(const NodeTree& node) {
	Node<T>* toConnect = this->root;
	while (toConnect->getNumberOfChilds() != 0) {
		toConnect = &(toConnect->getChilds()->at(toConnect->getNumberOfChilds() - 1));
	}
	if (isalpha((*toConnect).getValue()[0])) {
		variables.erase(variables.begin() + indexof(variables, toConnect->getValue()));
	}
	for (int i = 0;i < node.getvariables().size();i++) {
		if (indexof(variables, node.getvariables().at(i)) == -1)
			variables.push_back(node.getvariables().at(i));
	}
	*toConnect = *node.getRoot();
}
template<typename T>
void NodeTree<T>::InOrderInner(Node<T>& node) {
	std::cout << node.getValue() << " ";
	if (node.getNumberOfChilds() > 0) {
		for (int i = 0;i < node.getNumberOfChilds();i++) {
			InOrderInner(node.getChilds()->at(i));
		}
	}
	else {
		return;
	}
}
template<typename T>
int NodeTree<T>::indexof(const std::vector<std::string>& vec, const std::string& szukana) const {
	for (int i = 0;i < vec.size();i++) {
		if (vec.at(i) == szukana) {
			return i;
		}
	}
	return -1;
}
template <typename T>
NodeTree<T>* NodeTree<T>::operator+(const NodeTree& tojoin) {
	NodeTree copy = *this;
	copy.join(tojoin);
	return &copy;
}
template <typename T>
NodeTree<T>* NodeTree<T>::operator=(NodeTree toequal) {
	std::swap(this->root, toequal.root);
	this->variables.clear();
	for (std::string variable : toequal.variables) {
		variables.push_back(variable);
	}
	return this;
}
template <typename T>
NodeTree<T>* NodeTree<T>::operator=(NodeTree&& othertree) {
	if (this != &othertree) {
		delete root;
		root = othertree.root;
		othertree.root = NULL;
		variables.clear();
		variables = std::move(othertree.variables);
	}
	return *this;
}