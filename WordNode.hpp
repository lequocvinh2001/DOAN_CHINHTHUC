#pragma once
#ifndef __WNODE_HDR__
#define __WNODE_HDR__
#include <string>

template<class T>
class WordNode
{
	T word;
	T meaning;
	WordNode<T>* left;
	WordNode<T>* right;

public:
	WordNode()
	{
		word = "";
		meaning = "";
		left = NULL;
		right = NULL;
	}
	~WordNode()
	{
		delete left;
		delete right;
	}

	T getWord()
	{
		return this->word;
	}

	void setWord(T word)
	{
		this->word = word;
	}

	T getMeaning()
	{
		return this->meaning;
	}

	void setMeaning(T meaning)
	{
		this->meaning = meaning;
	}

	WordNode<T>* getLeft()
	{
		return this->left;
	}

	void setLeft(WordNode<T>* left)
	{
		this->left = left;
	}

	WordNode<T>* getRight()
	{
		return this->right;
	}

	void setRight(WordNode<T>* right)
	{
		this->right = right;
	}

	WordNode<T> getData()
	{
		WordNode<T> tmp;
		tmp.setWord(this->getWord());
		tmp.setMeaning(this->getMeaning());

		return tmp;
	}

	void setData(WordNode<T> data)
	{
		this->setWord(data.getWord());
		this->setMeaning(data.getMeaning());
	}

	bool hasLeft()
	{
		return left != NULL;
	}

	bool hasRight()
	{
		return right != NULL;
	}

	bool isExternal()
	{
		return left == NULL && right == NULL;
	}
};

#endif /* __WNODE_HDR__ */