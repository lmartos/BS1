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
    cout << "hello welcome to our allocating function" << endl;

	if(wanted <= (getSize()/2)){
	    cout << "dividing" << endl;
		divide();
		if(!buddyFitLeft->used){
			return buddyFitLeft->alloc(wanted);
		}else if(!buddyFitRight->used){
			return buddyFitRight->alloc(wanted);
		}
	} else {
	    cout << "are we full?" << endl;
		if (used){
        cout << "were full boys wrap it up" << endl;
			return nullptr;
		}
	}
    cout << "we are not full!" << endl;
	used = true;
	return this;
}

bool BuddyFit::free(Area *area){
	bool hasMerged = false;
    cout << "welcome to our merging function" << endl;
	if(area->getBase() == this->getBase() && buddyFitLeft == nullptr && buddyFitRight == nullptr){
        if(!this->isUsed()){
        delete area;
        throw "unidentified memory found";
        return false;
        }
		used = false;
		return false;
	}else if (buddyFitLeft == nullptr && buddyFitRight == nullptr) {
	    cout << "unable to find memory!" << endl;
        if(!this->isUsed()){
        delete area;
        throw std::logic_error("Rogue memory detected - deleting rogue memory...");
        return false;
        }
		///kan de area niet vinden, klopt iets niet met de aangegeven memory. throw exception;
	}else if(area->getBase() >= (this->getBase() + this->getSize()/2)){
	    cout << "its somewhere in the left subtree!" << endl;
		buddyFitLeft->free(area);
	}else{
	    cout << "its somewhere in the right subtree!" << endl;
		buddyFitRight->free(area);
	}

	if(!buddyFitLeft->isUsed() && !buddyFitRight->isUsed()){
        cout << "may the merging commence!" << endl;
		this->join(buddyFitLeft);
		buddyFitLeft == nullptr;
		buddyFitRight == nullptr;
		used = false;
		hasMerged = true;
		cout << "merging has happened" << endl;
	}
	return hasMerged;
}

void BuddyFit::divide() {
    cout << "can we make babies?" << endl;
	if((buddyFitLeft == nullptr) && (buddyFitRight == nullptr)){
        cout << "making babies" << endl;
		Area *childMemoryLeft = this->split(this->getSize()/2);
		Area *childMemoryRight = this;
		buddyFitLeft = new BuddyFit(name + "L", childMemoryLeft->getBase(), childMemoryLeft->getSize());
		buddyFitRight = new BuddyFit(name + "R", childMemoryRight->getBase(), childMemoryRight->getSize());
        cout << "babies have been made" << endl;
        return;
	}
	cout << "babies were not made!" << endl;
}


