#include "BuddyFit.h"


BuddyFit::BuddyFit(string name, int base, int size)
:Area(base, size), buddyFitLeft(nullptr), buddyFitRight(nullptr), used(false), name(name), parent(this)
{

}
BuddyFit::BuddyFit(string name, int base, int size, BuddyFit* parent)
:Area(base, size), buddyFitLeft(nullptr), buddyFitRight(nullptr), used(false), name(name), parent(parent)
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

string BuddyFit::getName(){
    return name;
}

Area* BuddyFit::alloc(int wanted){

    stack<BuddyFit*> s;
    bool isFound = false;
    s.push(this);
    while(s.size() > 0 && !isFound){
        BuddyFit* current = s.top();
        s.pop();
        if(current->getBuddyFitLeft() == nullptr){
          if(wanted < (current->getSize() / 2)){
            current->divide();
            s.push(current->getBuddyFitLeft());
            s.push(current->getBuddyFitRight());
          }else{
            if(!current->isUsed() && wanted > current->getSize()){
                isFound = true;
                return current;
            }
          }
        }else{
            s.push(current->getBuddyFitLeft());
            s.push(current->getBuddyFitRight());
        }

    }
    /**cout << "hello welcome to our allocating function" << endl;
    cout << wanted << " " << getSize() << endl;
	if(wanted <= (getSize()/2)){
        if(buddyFitLeft == nullptr && buddyFitRight == nullptr){
	    cout << "dividing" << endl;
		divide();
        }
		if(!buddyFitLeft->used){
			return buddyFitLeft->alloc(wanted);
		}else if(!buddyFitRight->used){
			return buddyFitRight->alloc(wanted);
		}
	} else {
        if(buddyFitLeft == nullptr && buddyFitRight == nullptr){
        cout << "we are not full!" << endl;
        used = true;
        if(name.size() > 4){
            updateParent();
        }
        cout << this->getName() << endl;
        return this;
	}else{
	    if(this->getName().at(this->getName().size() - 1) == 'L'){
            cout << "attempting sibling" << endl;
            parent->getBuddyFitRight()->alloc(wanted);
	    }else{
            cout << "name: " << this->getName() <<  " child memory size: " << buddyFitLeft->getSize() << " left used: " << buddyFitLeft->isUsed() << " right used: " << buddyFitRight->isUsed() << " used: " << isUsed() << " parent used: " << parent->isUsed() << " siblings used: " << parent->getBuddyFitLeft()->isUsed() << " " << parent->getBuddyFitRight()->isUsed() << endl;
            cout << "memory was not found in this tree" << endl;
            return nullptr;
	    }
	}
	}
    **/
}

bool BuddyFit::updateParent(){
    bool hasmerged = false;

    if(parent->getBuddyFitLeft()->isUsed() && parent->getBuddyFitRight()->isUsed()){
        parent->setUsed(true);
        hasmerged = false;
    }else if(!parent->getBuddyFitLeft()->isUsed() && !parent->getBuddyFitRight()->isUsed() && parent->getBuddyFitLeft()->getBuddyFitLeft() == nullptr){
        cout << "may the merging commence!" << endl;
		parent->join(parent->getBuddyFitLeft());
		delete parent->getBuddyFitLeft();
		delete parent->getBuddyFitRight();
		parent->setUsed(false);
		cout << "merging has happened" << endl;
		hasmerged = true;
    }

    if(name != "main"){
    parent->updateParent();
    }
    return hasmerged;
}


bool BuddyFit::free(Area *area){
    try{
    cout << "attempting to free memory" << endl;
    BuddyFit& buddytest = dynamic_cast<BuddyFit&>( *area);
    cout << buddytest.getName() << endl;
    BuddyFit* locatedMemory = findMemory(buddytest.getName().substr(3));
    if(locatedMemory != nullptr){
        if(locatedMemory->getBuddyFitLeft() == nullptr && locatedMemory->getBuddyFitRight() == nullptr){
            locatedMemory->setUsed(false);
            if(locatedMemory->getName() == "main"){
                return false;
            }else{
                return (locatedMemory->updateParent());
            }
            }else{
                throw std::logic_error("memory is not leaf and thus cannot be reclaimed");
                return false;
            }
    }
    }catch(...){
        cout << "this memory cannot be reclaimed" << endl;
        delete area;
        throw;
        return false;
    }

    /**
	bool hasMerged = false;
    cout << "welcome to our merging function" << endl;
	if(area->getBase() == this->getBase() && buddyFitLeft == nullptr && buddyFitRight == nullptr){
        if(!this->isUsed()){
        delete area;
        throw std::logic_error("unidentified memory found");
        return false;
        }
		used = false;
		return false;
	}else if (buddyFitLeft == nullptr && buddyFitRight == nullptr) {
	    cout << "unable to find memory!" << endl;
        delete area;
  //      throw std::logic_error("Rogue memory detected - deleting rogue memory...");
        return false;
		///kan de area niet vinden, klopt iets niet met de aangegeven memory. throw exception;
	}else if(area->getBase() >= (this->getBase() + this->getSize()/2)){
	    cout << "its somewhere in the left subtree!" << endl;
		buddyFitLeft->free(area);
	}else{
	    cout << "its somewhere in the right subtree!" << endl;
		buddyFitRight->free(area);
	}
    **/

}

BuddyFit* BuddyFit::findMemory(string path){
    if(path.size() > 1){
    if(path.at(1) == 'L'){
        cout << "going left" << endl;
        buddyFitLeft->findMemory(path.substr(1));
    }else if(path.at(1) == 'R'){
        cout << "going right" << endl;
        buddyFitRight->findMemory(path.substr(1));
    }}else if(buddyFitLeft == nullptr && buddyFitRight == nullptr && this->isUsed()){
        cout << "memory found" << endl;
        return this;
    }else{
        cout << "memory not found" << endl;
        return nullptr;
    }

}

void BuddyFit::divide() {
    cout << "can we make babies?" << endl;
	if((buddyFitLeft == nullptr) && (buddyFitRight == nullptr)){
        cout << "making babies" << endl;
		Area *childMemoryLeft = this->split(this->getSize()/2);
		Area *childMemoryRight = this;
		buddyFitLeft = new BuddyFit(name + "L", childMemoryLeft->getBase(), childMemoryLeft->getSize(), this);
		buddyFitRight = new BuddyFit(name + "R", childMemoryRight->getBase(), childMemoryRight->getSize(), this);
        cout << "babies have been made" << endl;
        return;
	}
	cout << "babies were not made!" << endl;
}

BuddyFit* BuddyFit::getBuddyFitLeft(){
    return buddyFitLeft;
}

BuddyFit* BuddyFit::getBuddyFitRight(){
    return buddyFitRight;
}


