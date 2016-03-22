#ifndef BUDDY_H
#define BUDDY_H

#include "BuddyFit.h"

class Buddy : public Allocator
{
	private:
		BuddyFit* memoryControl;

	public:
		Buddy(int size);
		~Buddy();

		/// Stel de omvang van het te beheren gebied in.
		// Afgeleide classes MOGEN setSize zelf herdefinieren
		// zolang ze deze methode maar aanroepen via
		// Allocator::setSize(...);
		void setSize(int size);


		// Afgeleide classes MOETEN de volgende methodes zelf definieren.
		Area *alloc(int wanted);	///< Application vraagt om geheugen
		void  free(Area *);			///< Application geeft een Area weer terug aan geheugenbeheer
		void  report();				///< Report performance statistics

		// ... en hier komen straks misschien nog andere functies ...
		// ... om b.v. de overhead te bepalen ...
		// ... of de fragmentatie graad ...
		//

	protected:

};

#endif // BUDDY_H
