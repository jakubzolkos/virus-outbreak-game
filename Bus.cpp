#include "Bus.h"
using namespace std;

Bus::Bus() : Building()
{
    cout << "Bus Stop default constructed" << endl;
}

Bus::~Bus() 
{
    cout << "Bus Stop destructed" << endl;
}

Bus::Bus(int in_id, double ticket_price, Point2D in_loc) : Building('B', in_id, in_loc), ticket_price(ticket_price)
{
    cout << "Bus Stop constructed" << endl;
}

double Bus::GetTicketPrice()
{
    return ticket_price;
}

bool Bus::CanAffordTicket(double budget)
{
    if (budget >= ticket_price)
        return true;
    
    else
        return false;
}

void Bus::ShowStatus()
{
    cout << endl;
    cout << "Bus Station Status: ";
    Building::ShowStatus();
    cout << "\tBus ticket price: $" << ticket_price << endl;

    return;
}

bool Bus::ShouldBeVisible()
{
    return true;
}

bool Bus::Update()
{
    return false; // Class is non-updatetable
}