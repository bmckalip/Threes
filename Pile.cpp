#include "stdafx.h"
#include "Pile.h"

Pile::Pile(int size) {
	this->size = size;
}

int Pile::getSize() {
	return size;
}

bool Pile::isEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
}

//check if a pile is less then another
bool operator<(const Pile& first, const Pile& second) {
	if (first.size < second.size) {
		return true;
	} else {
		return false;
	}
}

//determine if a pile is greater then another
bool operator>(const Pile& first, const Pile& second) {
	if (first.size > second.size) {
		return true;
	} else {
		return false;
	}
}

//I should overload the <= and >= operators aswell, but i never end up using them 

//determine is a pile is equal to another
bool Pile::operator==(const Pile& other) const {
	return ((this->size == other.size) ? true : false);
}

//determine if a pile is not equal to another
bool Pile::operator!=(const Pile& other) const {
	return *this == other ? false : true;
}

//subtract two piles
Pile operator-(const Pile& first, const Pile& second) {
	return first.size - second.size;
}
