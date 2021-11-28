#include <iostream>
#include "Virus.h"
#include <list>
#include <random>
using namespace std;


Virus::Virus(string name, int id, Point2D in_loc) : GameObject(in_loc, id, 'V'), name(name)
{
    state = IN_ENVIRONMENT;
    cout << "Virus constructed" << endl;
}

Virus::Virus(string name, double virulence, double resistance, double energy,
bool variant, int id, Point2D in_loc) : GameObject(in_loc, id, 'V'), name(name), virulence(virulence), resistance(resistance), energy(energy), variant(variant) 
{
    state = IN_ENVIRONMENT;
    cout << "Virus constructed" << endl;
}

Virus::~Virus() 
{
    cout << "Virus destructed" << endl;
}

bool Virus::get_variant()
{
    return false;
}

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

string Virus::get_name()
{
    return name;
}

bool Virus::UpdateLocation()
{
    switch (state)
    {
        case IN_ENVIRONMENT:
        {
            cout << display_code << id_num << ": step..." << endl;
            random_device rd;
            default_random_engine eng(rd());
            uniform_real_distribution <double> distr(-3, 3);

            // This ensures that the virus objects always stay in display
            while (true)
            {
                Vector2D delta(distr(eng), distr(eng));
                location = location + delta;
                if (location.x >= 0 && location.x <= view_maxsize && location.y >= 0 && location.y <= view_maxsize)
                {   
                    if (energy >= 0)
                        energy -= 1/(resistance*resistance);
                    else
                    {
                        state = DEAD;
                        energy = 0.0;
                    }

                    break;
                }
            }

            return true;
            break;
        }
        case IN_STUDENT:
            location = (*current_student).GetLocation();
            // If the student runs out of antibodies, release the virus in the environment again
            if ((*current_student).IsInfected())
                state = IN_ENVIRONMENT;
            
            return true;
            break;
        
        case DEAD:
            return false;
            break;
    }

    return false;
}


void Virus::infect(Student *s)
{ 
    if (state == IN_ENVIRONMENT)
    {
        state = IN_STUDENT;
        current_student = s;
        (*s).AddVirus(this);  
        cout << (*s).GetName() << " has been infected with " << name << "!" << endl;
    }

    else
        return;

    return;
}

bool Virus::Update()
{
    if (IsAlive())
    {
        UpdateLocation();
        return false;
    }

    else 
    {
        return true;
    }

    return false;

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

bool Virus::ShouldBeVisible()
{
    if (state == DEAD)
    {
        return false;
    }

    else
        return true;
}

void Virus::destroy_self()
{
    state = DEAD;
    energy = 0.0;
}