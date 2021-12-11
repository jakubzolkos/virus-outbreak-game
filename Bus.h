#ifndef BUS_H
#define BUS_H
#include "Building.h"


class Bus : public Building
{
    private:
        double ticket_price = 6.00;
    
    public:
        Bus();
        Bus(int in_id, double ticket_price, Point2D in_loc);
        bool CanAffordTicket(double budget);
        virtual ~Bus();
        virtual bool Update();
        double GetTicketPrice();
        void ShowStatus();
        bool ShouldBeVisible();
};

#endif 