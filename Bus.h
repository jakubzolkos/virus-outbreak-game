#ifndef BUS_H
#define BUS_H
#include "GameObject.h"


class Bus : public GameObject
{
    public:
        Bus();
        Bus(Point2D in_loc, int in_id, char in_code);
        virtual ~Bus();
        virtual bool Update();
        void ShowStatus();
};

#endif 