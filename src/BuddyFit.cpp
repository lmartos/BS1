#include "BuddyFit.h"


BuddyFit::BuddyFit(string name, int base, int size)
:Area(base, size), buddyFitLeft(nullptr), buddyFitRight(nullptr), used(false), name(name)
{

}

BuddyFit::~BuddyFit()
{
  delete buddyFitLeft;
  delete buddyFitRight;
}

bool BuddyFit::isUsed(){
    return used;
}

void BuddyFit::setUsed(bool used){
    used = used;
}

Area* BuddyFit::alloc(int wanted){
	if (wanted > this->getSize()) {
		return nullptr;
	}

	if(wanted <= this->getSize()/2){
		divide();
		if(!buddyFitLeft->used){
			return buddyFitLeft->alloc(wanted);
		}else if(!buddyFitRight->used){
			return buddyFitRight->alloc(wanted);
		}
	} else {
		if (this->used)
			return nullptr;
	}

	this->used = true;
	return this;
}

bool BuddyFit::free(Area *area){
	bool hasMerged = false;

	if(area->getBase() == this->getBase() && buddyFitLeft == nullptr && buddyFitRight == nullptr){
		used = false;
		return false;
	}else if (buddyFitLeft == nullptr && buddyFitRight == nullptr) {
		return false;
		///kan de area niet vinden, klopt iets niet met de aangegeven memory. throw exception;
	}else if(area->getBase() >= (this->getBase() + this->getSize()/2)){
		buddyFitLeft->free(area);
	}else{
		buddyFitRight->free(area);
	}

	if(!buddyFitLeft->isUsed() && !buddyFitRight->isUsed()){
		this->join(buddyFitLeft);
		delete buddyFitLeft;
		delete buddyFitRight;
		used = false;
		hasMerged = true;
	}
	return hasMerged;
}

void BuddyFit::divide() {
	if((buddyFitLeft != nullptr) && (buddyFitRight != nullptr)){
		Area *childMemoryLeft = this->split(this->getSize()/2);
		Area *childMemoryRight = this;
		buddyFitLeft = new BuddyFit(name + "L", childMemoryLeft->getBase(), childMemoryLeft->getSize());
		buddyFitRight = new BuddyFit(name + "R", childMemoryRight->getBase(), childMemoryRight->getSize());
	}
}


