#include "DoctorsOffice.h"
#include "Model.h"
using namespace std;

DoctorsOffice::DoctorsOffice()
: Building(), vaccine_capacity(100), dollar_cost_per_vaccine(5), num_vaccine_remaining(vaccine_capacity) 
{
    display_code = 'D';
    cout << "DoctorsOffice default constructed" << endl;
}

DoctorsOffice::~DoctorsOffice() 
{
    cout << "DoctorsOffice destructed" << endl;
}

DoctorsOffice::DoctorsOffice(int in_id, double vaccine_cost, unsigned int vaccine_cap, Point2D in_loc)
: Building('D', in_id, in_loc), vaccine_capacity(vaccine_cap), dollar_cost_per_vaccine(vaccine_cost), num_vaccine_remaining(vaccine_cap) 
{
    cout << "DoctorsOffice constructed" << endl;
    state = VACCINE_AVAILABLE;
} 

bool DoctorsOffice::HasVaccine()
{
    if (num_vaccine_remaining >= 1)
        return true;
    else
        return false;
}

unsigned int DoctorsOffice::GetNumVaccineRemaining()
{
    return num_vaccine_remaining;
}

bool DoctorsOffice::CanAffordVaccine(unsigned int vaccine, double budget)
{
    if (vaccine * dollar_cost_per_vaccine > budget)
        return false;
    else 
        return true;
}

double DoctorsOffice::GetDollarCost(unsigned int vaccine)
{
    return vaccine*dollar_cost_per_vaccine;
}

unsigned int DoctorsOffice::DistributeVaccine(unsigned int vaccine_needed)
{
    if (num_vaccine_remaining >= vaccine_needed)
    {
        num_vaccine_remaining -= vaccine_needed;
        return vaccine_needed;
    }

    else
    {
        unsigned int current = num_vaccine_remaining;
        num_vaccine_remaining = 0;
        return current;
    }
}

bool DoctorsOffice::Update()
{
    if (!HasVaccine() && state == VACCINE_AVAILABLE)
    {
        state = NO_VACCINE_AVAILABLE;
        display_code = 'd';
        cout << "DoctorsOffice " << id_num << " has ran out of vaccine." << endl;
        return true;
    }

    else
        return false;
}

void DoctorsOffice::ShowStatus()
{
    cout << endl;
    cout << "DoctorsOffice Status: ";
    Building::ShowStatus();
    cout << "\tDollars per vaccine: " << dollar_cost_per_vaccine << endl;
    cout << "\tHas " << num_vaccine_remaining << " vaccine(s) remaining." << endl; 

    return;
}

bool DoctorsOffice::IsOpen(Model &model)
{
    if (model.GetTime()%6 == 0 || model.GetTime()%7 == 0)
        return false;
    
    else
        return true;
}