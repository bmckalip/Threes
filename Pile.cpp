#include "stdafx.h"
#include "Pile.h"


Pile::Pile(int initSize) {
	size = initSize;
}

int Pile::getSize() {
	return size;
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
