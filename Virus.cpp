#include <iostream>
#include "Virus.h"
using namespace std;


Virus::Virus(string name, double virulence, double resistance, double energy,
bool variant, int id, Point2D in_loc) : GameObject(in_loc, id, 'V')
{
    state = IN_ENVIRONMENT;
    cout << "Virus constructed" << endl;
}

Virus::~Virus() 
{
    cout << "Virus destructed" << endl;
}

void Virus::infect(Student *s)
{
    if (GetDistanceBetween(GetLocation(), (*s).GetLocation()) == 0)
    {
        state = IN_STUDENT;
    }

    return;
}

bool Virus::get_variant()
{}

double Virus::get_virulence() 
{
    return virulence;
}

double Virus::get_resistance()
{
    return resistance;
}

double Virus::get_energy()
{
    return energy;
}

bool Virus::get_in_student()
{
    return is_in_student;
}

bool Virus::Update()
{
    if (state == IN_ENVIRONMENT)
    {
        return false;
    }

    else if (!IsAlive())
    {
        state = DEAD;
        return true;
    }

}

void Virus::ShowStatus()
{
    cout << endl << name << " Status: ";
    GameObject::ShowStatus();

    switch (state)
    {
        case IN_ENVIRONMENT:
            cout << " in environment" << endl;
            break;
        
        case IN_STUDENT:
            cout << " in " << (*current_student).GetName() << endl;
            break;
        
        case DEAD:
            cout << " dead" << endl;
            break;
    }

    cout << "\tEnergy: " << energy << endl;
    cout << "\tVirulence: " << virulence << endl;
    cout << "\tResistance: " << resistance << endl;
}

bool Virus::IsAlive()
{
    if (get_energy() > 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

void Virus::SetupDestination(Point2D dest)
{
    destination = dest;
    delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
    return;
}

void Virus::UpdateLocation(Model &model)
{
    
}