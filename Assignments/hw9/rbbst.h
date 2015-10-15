/*
 * rbbst.h
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe
 */

#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes 
 ------------------------------------------------------*/

enum Color {
	red, black
};

template<class KeyType, class ValueType>
class RedBlackNode: public Node<KeyType, ValueType> {
public:
	RedBlackNode(KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p) :
			Node<KeyType, ValueType>(k, v, p) {
		color = red;
	}

	virtual ~RedBlackNode() {
	}

	Color getColor() const {
		return color;
	}

	void setColor(Color c) {
		color = c;
	}

	/* The type casting allows us to treat getParent, getLeft, getRight
	 as returning RedBlackNode instead of Node */
	virtual RedBlackNode<KeyType, ValueType> *getParent() const {
		return (RedBlackNode<KeyType, ValueType>*) this->_parent;
	}

	virtual RedBlackNode<KeyType, ValueType> *getLeft() const {
		return (RedBlackNode<KeyType, ValueType>*) this->_left;
	}

	virtual RedBlackNode<KeyType, ValueType> *getRight() const {
		return (RedBlackNode<KeyType, ValueType>*) this->_right;
	}

	//get grandparent node
	virtual RedBlackNode<KeyType, ValueType> *getGrandparent() const {
		if (this->_parent != NULL)
			return (RedBlackNode<KeyType, ValueType>*) this->_parent->_parent;
		else
			return NULL;
	}

	//get uncle node
	virtual RedBlackNode<KeyType, ValueType> *getUncle() const {
		if (this->getGrandparent() == NULL)
			return NULL;
		if (this->_parent == this->getGrandparent()->_left)
			return (RedBlackNode<KeyType, ValueType>*) this->getGrandparent()->_right;
		else
			return (RedBlackNode<KeyType, ValueType>*) this->getGrandparent()->_left;
	}

protected:
	Color color;
}
;

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template<class KeyType, class ValueType>
class RedBlackTree: public BinarySearchTree<KeyType, ValueType> {
public:
	void add(KeyType key, ValueType value) {
		/* This one is yours to implement.
		 It should add the (key, value) pair to the tree, 
		 making sure that it remains a valid Red-Black Tree.
		 If the key is already in the tree (with a possibly different associated value),
		 then it should overwrite the value with the new one.
		 We strongly recommend defining suitable (private) helper functions. */

		//insert at normal bst location
		bool duplicate = false;
		int rightLeft = 0;
		RedBlackNode<KeyType, ValueType>* locP = (RedBlackNode<KeyType,
				ValueType>*) (this->root);
		while ((RedBlackNode<KeyType, ValueType>*) (this->root) != NULL) {
			if (key > locP->getKey()) {
				if (locP->getRight() == NULL) {
					rightLeft = 2;
					break;
				}
				locP = locP->getRight();
			} else if (key < locP->getKey()) {
				if (locP->getLeft() == NULL) {
					rightLeft = 1;
					break;
				}
				locP = locP->getLeft();
			} else {
				locP->getItem().second = value;
				duplicate = true;
				std::cout << "duplicate" << std::endl;
			}
		}

		if (!duplicate) {
			RedBlackNode<KeyType, ValueType>* loc = new RedBlackNode<KeyType,
					ValueType>(key, value, locP);
			if (locP == NULL) {
				std::cout << "root init done" << std::endl;
				this->root = loc;
			}

			if (rightLeft == 2) {
				locP->setRight(loc);
			} else if (rightLeft == 1) {
				locP->setLeft(loc);
			}

			//start dealing with color conflict
			insert_caseA(loc);
		}
	}

	void insert_caseA(RedBlackNode<KeyType, ValueType>* posA) {
		if (posA->getParent() == NULL) {
			Color bk = black;
			posA->setColor(bk);
		} else {
			insert_caseB(posA);
		}
	}

	void insert_caseB(RedBlackNode<KeyType, ValueType>* posB) {
		if (posB->getParent()->getColor() == black)
			return;
		else
			insert_caseC(posB);
	}

	void insert_caseC(RedBlackNode<KeyType, ValueType>* posC) {
		RedBlackNode<KeyType, ValueType>* uC = posC->getUncle();
		RedBlackNode<KeyType, ValueType>* gD = posC->getGrandparent();

		if ((uC != NULL) && (uC->getColor() == red)) {
			Color bk = black;
			Color rd = red;
			posC->getParent()->setColor(bk);
			uC->setColor(bk);
			gD->setColor(rd);
			insert_caseA(gD);
		} else {
			insert_caseD(posC);
		}
	}

	void insert_caseD(RedBlackNode<KeyType, ValueType>* posD) {
		RedBlackNode<KeyType, ValueType>* gD = posD->getGrandparent();

		if ((posD == posD->getParent()->getRight())
				&& (posD->getParent() == gD->getLeft())) {
			rotate_l(posD->getParent());
			posD = posD->getLeft();
		} else if ((posD == posD->getParent()->getLeft())
				&& (posD->getParent() == gD->getRight())) {
			rotate_r(posD->getParent());
			posD = posD->getRight();
		}
		insert_caseE(posD);
	}

	void insert_caseE(RedBlackNode<KeyType, ValueType>* posE) {
		RedBlackNode<KeyType, ValueType>* gD = posE->getGrandparent();
		Color bk = black;
		Color rd = red;

		posE->getParent()->setColor(bk);
		gD->setColor(rd);
		if (posE == posE->getParent()->getLeft())
			rotate_r(gD);
		else
			rotate_l(gD);
	}

	void rotate_l(RedBlackNode<KeyType, ValueType>* rtL) {
		RedBlackNode<KeyType, ValueType>* rtlP = rtL->getParent();
		rtlP = rtL->getRight();
		rtL->setRight(rtlP->getLeft());
		if (rtlP->getLeft() != NULL)
			rtlP->getLeft()->setParent(rtL);
		rtlP->setParent(rtL->getParent());
		if (rtL->getParent() == NULL)
			this->root = rtlP;
		else if (rtL == (rtL->getParent()->getLeft()))
			rtL->getParent()->setLeft(rtlP);
		else
			rtL->getParent()->setRight(rtlP);

		rtlP->setLeft(rtL);
		rtL->setParent(rtlP);
	}

	void rotate_r(RedBlackNode<KeyType, ValueType>* rtR) {
		RedBlackNode<KeyType, ValueType>* rtrP = rtR->getParent();
		rtrP = rtR->getLeft();
		rtR->setLeft(rtrP->getRight());
		if (rtrP->getRight() != NULL)
			rtrP->getRight()->setParent(rtR);
		rtrP->setParent(rtR->getParent());
		if (rtR->getParent() == NULL)
			this->root = rtrP;
		else if (rtR == (rtR->getParent()->getRight()))
			rtR->getParent()->setRight(rtrP);
		else
			rtR->getParent()->setLeft(rtrP);

		rtrP->setRight(rtR);
		rtR->setParent(rtrP);
	}

};

#endif
