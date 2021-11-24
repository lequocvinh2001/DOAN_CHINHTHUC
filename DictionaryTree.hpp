#pragma once
#pragma once
#ifndef __DICT_HDR__
#define __DICT_HDR__
#include <iostream>
#include "Hash.hpp"
#include "WordNode.hpp"

template<class T>
class DictionaryTree
{
	WordNode<T>* root;

	WordNode<T>* insert(WordNode<T> data, WordNode<T>* root);
	WordNode<T>* remove(T word, WordNode<T>* root);
	WordNode<T>* search(T word, WordNode<T>* root);
	void print(WordNode<T>* root);

public:
	DictionaryTree()
	{
		root = NULL;
	}

	~DictionaryTree()
	{
		delete root;
	}

	WordNode<T>* getRoot()
	{
		return root;
	}

	void setRoot(WordNode<T>* root)
	{
		this->root = root;
	}

	void insert(T word, T meaning);
	void remove(T word);
	WordNode<T>* search(T word);
	void modify(T word, T new_meaning);
	void print();
};

template<class T>
// Phuong thuc chen du lieu tu moi
WordNode<T>* DictionaryTree<T>::insert(WordNode<T> data, WordNode<T>* root)
{
	// Kiem tra root va tao moi
	if (!root) {
		root = new WordNode<T>;
		root->setData(data);
		return root;
	}

	/*
	 * Su dung hash de them tu vao cay, dong thoi kiem tra tinh
	 * ton tai cua tu
	 */
	unsigned int dHash = DJBHash(data.getWord());
	unsigned int rHash = DJBHash(root->getWord());
	if (rHash > dHash)
		root->setLeft(this->insert(data, root->getLeft()));
	else if (rHash < dHash)
		root->setRight(this->insert(data, root->getRight()));

	// Them tu moi thanh cong hoac tu can them da ton tai
	return root;
}

template<class T>
void DictionaryTree<T>::insert(T word, T meaning)
{
	WordNode<T> data;
	data.setWord(word);
	data.setMeaning(meaning);

	this->setRoot(this->insert(data, this->getRoot()));
}

template<class T>
// Phuong thuc tim kiem
WordNode<T>* DictionaryTree<T>::search(T word, WordNode<T>* root)
{
	// Tu do khong con tai hoac cay chua duoc khoi tao
	if (!root)
		return root;

	unsigned int wHash = DJBHash(word);
	unsigned int rHash = DJBHash(root->getWord());
	//Da tim thay nut cua tu can tim
	if (rHash == wHash)
		return root;

	if (rHash > wHash)
		return this->search(word, root->getLeft());

	return this->search(word, root->getRight());
}

template<typename T>
WordNode<T>* DictionaryTree<T>::search(T word)
{
	return this->search(word, this->getRoot());
}

template<typename T>
// Phuong thuc xoa
WordNode<T>* DictionaryTree<T>::remove(T word, WordNode<T>* root)
{
	if (root == NULL)
		return root;

	// Su dung hash de kiem tra tinh ton tai cua tu
	unsigned int wHash = DJBHash(word);
	unsigned int rHash = DJBHash(root->getWord());
	if (rHash > wHash)
		root->setLeft(this->remove(word, root->getLeft()));
	else if (rHash < wHash)
		root->setRight(this->remove(word, root->getRight()));
	else {
		// TH 1: Nut chi co 1 la hoac khong co la / khong co nut con
		if (!root->hasLeft()) {
			WordNode<T>* tmp = root->getRight();

			if (tmp)
				root->setRight(NULL);

			delete root;
			return tmp;
		}
		else if (!root->hasRight()) {
			WordNode<T>* tmp = root->getLeft();

			if (tmp)
				root->setLeft(NULL);

			delete root;
			return tmp;
		}

		// TH 2: Nut co 2 nut con / 2 la
		WordNode<T>* tmp = root->getRight();
		while (tmp && tmp->hasLeft())
			tmp = tmp->getLeft();
		//lay la ben phai thay the cho node bi xoa
		root->setData(tmp->getData());
		root->setRight(remove(tmp->getWord(), root->getRight()));
	}

	return root;
}
template<class T>
void DictionaryTree<T>::remove(T word)
{
	this->setRoot(this->remove(word, this->getRoot()));
}
template<class T>
// Phuong thuc sua
void DictionaryTree<T>::modify(T word, T new_meaning)
{
	WordNode<T>* wn = this->search(word);
	wn->setMeaning(new_meaning);
}

template<class T>
// Phuong thuc in ra man hinh
void DictionaryTree<T>::print(WordNode<T>* root)
{
	if (root->hasLeft())
		this->print(root->getLeft());

	std::cout << "Tu: " << root->getWord() << std::endl;
	std::cout << "Nghia: " << root->getMeaning() << std::endl;

	if (root->hasRight())
		this->print(root->getRight());
}

template<class T>
void DictionaryTree<T>::print()
{
	this->print(this->getRoot());
}


#endif /* __DICT_HDR__ */