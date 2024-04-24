#pragma once
#include <iostream>
#include <vector>

template <typename T> class Node
{
public:
	Node();
	Node(const Node& node);
	~Node();
	Node(std::string value);
	std::string getValue() const;
	void setValue(std::string value);
	void setNumberOfChilds(std::string operation);
	int getNumberOfChilds() const;
	std::vector<Node>* getChilds() const;
private:
	std::string value;
	std::vector<Node>* childs;
	int numberOfChilds;
};
template <typename T>
Node<T>::Node() {
	this->value = "0";
	this->numberOfChilds = 0;
	this->childs = new std::vector<Node>();
}
template <typename T>
Node<T>::Node(std::string value)
{
	this->value = value;
	this->childs = new std::vector<Node>();
}
template <typename T>
Node<T>::Node(const Node& node) {
	this->value = node.value;
	this->numberOfChilds = node.numberOfChilds;
	this->childs = new std::vector<Node>();
	for (const Node& child : *node.childs) {
		childs->push_back(child);
	}
}
template <typename T>
Node<T>::~Node() {
	delete childs;
}
template <typename T>
std::string Node<T>::getValue() const {
	return this->value;
}
template <typename T>
void Node<T>::setValue(std::string value) {
	this->value = value;
}
template <typename T>
std::vector<Node<T>>* Node<T>::getChilds() const {
	return this->childs;
}
template <typename T>
int Node<T>::getNumberOfChilds() const {
	return this->numberOfChilds;
}
template <typename T>
void Node<T>::setNumberOfChilds(std::string operation) {
	int number = 0;
	if (operation == "+" || operation == "-" || operation == "*" || operation == "/") {
		number = 2;
	}
	else if (operation == "sin" || operation == "cos") {
		number = 1;
	}
	this->numberOfChilds = number;
}
template <>
void Node<std::string>::setNumberOfChilds(std::string operation) {
	int number = 0;
	if (operation == "+" || operation == "-" || operation == "*" || operation == "/") {
		number = 2;
	}
	this->numberOfChilds = number;
}