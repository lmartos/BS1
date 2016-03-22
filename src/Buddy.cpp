#include "Buddy.h"

Buddy::Buddy(int size)
: Allocator(false, "buddy"),memoryControl(new BuddyFit("main", 0, size))
{

}

Buddy::~Buddy()
{
	//doubledtor
}

void Buddy::setSize(int size) {
}

Area* Buddy::alloc(int wanted) {
	Area* area = memoryControl->alloc(wanted);

	if (area == nullptr) {
		//throw exception;
	} else {
		return area;
	}

}

void  Buddy::free(Area * area) {
	memoryControl->free(area);
}

void  Buddy::report(){

}
