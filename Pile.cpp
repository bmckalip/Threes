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

bool operator<(const Pile& first, const Pile& second) {
	if (first.size < second.size) {
		return true;
	} else {
		return false;
	}
}


Pile operator-(const Pile& first, const Pile& second) {
	return first.size - second.size;
}

bool Pile::operator==(const Pile& other) const {
	return ((this->size == other.size) ? true : false);
}

bool Pile::operator!=(const Pile& other) const {
	return *this == other ? false : true;
}
