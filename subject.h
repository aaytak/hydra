
#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include "observer.h"

class Subject {
    protected:
        std::vector<Observer*> observers;

    public:
        ~Subject();
        void attach(Observer* o);
        void detach(Observer* o);
        void playCard(int headId, std::string card) const;
};

#endif
