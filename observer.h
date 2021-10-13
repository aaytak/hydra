
#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <string>

class Observer {
    public:
        virtual ~Observer();
        virtual void cardPlayed(int headId, std::string cardPlayed) = 0;
};

#endif
