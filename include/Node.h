#pragma once

template<typename T>
class Node
{
public:
	Node(T val = 0, Node<T>* lft = nullptr, Node<T>* rght = nullptr, int lftInd = 0, int rghtInd = 0);


	T value;
	Node<T>* left, * right;
	int leftInd, rightInd;
};

template<typename T>
inline Node<T>::Node(T val, Node<T>* lft, Node<T>* rght, int lftInd, int rghtInd) :
	value(val), left(lft), right(rght), leftInd(lftInd), rightInd(rghtInd) {}
