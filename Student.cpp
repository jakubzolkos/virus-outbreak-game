#include "Student.h"
#include "Virus.h"
#include <random>
#include <iomanip>
#include <math.h>
#include "Virus.h"
using namespace std;

double GetRandomAmountOfDollars()
{
    return double(rand()) / (double(RAND_MAX) + 1.0) * 2.0;
}

Student::Student() : GameObject(), speed(5)
{
    cout << "Student default constructed" << endl;
}

Student::Student(char in_code) : GameObject(in_code), speed(5)
{
    state = STOPPED;
    cout << "Student constructed" << endl;
}

Student::Student(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc)
: GameObject(in_loc, in_id, in_code), speed(in_speed), name(in_name)
{
    cout << "Student constructed" << endl;
}

Student::~Student() 
{
    cout << "Student destructed" << endl;
}

void Student::StartMoving(Point2D dest)
{
    if (IsInfected())
    {
        cout << display_code << id_num << ": I am infected. I may move, but you cannot see me." << endl;
    }

    else if (GetDistanceBetween(location, dest) == 0)
    {
        cout << display_code << id_num << ": I'm already there. See?" << endl;
    }

    else
    {
        SetupDestination(dest);
        state = MOVING;
        cout << display_code << id_num << ": On my way." << endl;
    }
}

string Student::GetName()
{
    return name;
}

void Student::StartMovingToClass(ClassRoom *classr)
{
    if (IsInfected())
    {
        cout << display_code << id_num << ": I am infected so I can't move to class..." << endl;
    }

    else if (GetDistanceBetween((*classr).GetLocation(), location) == 0)
    {
        cout << display_code << id_num << ": I'm already at the Classroom!" << endl;
        state = IN_CLASS;
    }

    else
    {
        SetupDestination((*classr).GetLocation());
        current_class = classr;
        state = MOVING_TO_CLASS;
        cout << display_code << id_num << ": On my way to class " << (*classr).GetId() << "." << endl;
    }
}

void Student::StartMovingToDoctor(DoctorsOffice* office)
{
    if (IsInfected())
    {
        cout << display_code << id_num << ": I am infected so I should have gone to the doctor's..." << endl;
    }

    else if (GetDistanceBetween((*office).GetLocation(), location) == 0)
    {
        cout << display_code << id_num << ": I'm already at the Doctor's!" << endl;
        state = AT_DOCTORS;
    }

    else
    {
        SetupDestination((*office).GetLocation());
        current_office = office;
        state = MOVING_TO_DOCTOR;
        cout << display_code << id_num << ": On my way to Doctor's " << (*office).GetId() << "." << endl;
    }
}

void Student::StartLearning(unsigned int num_assignments)
{
    if (IsInfected())
        cout << display_code << id_num << ": I am infected so no more school for me..." << endl;
    
    else if (state != IN_CLASS)
        cout << display_code << id_num << ": I can only learn in a Classroom!" << endl;
    
    else if ((*current_class).GetNumAssignmentsRemaining() == 0)
        cout << display_code << id_num << ": Cannot learn! This Class has no more assignments!" << endl;
    
    else if ((*current_class).GetDollarCost(num_assignments) > dollars || (*current_class).GetAntibodyCost(num_assignments) > antibodies)
        cout << display_code << id_num << ": Not enough money and/or antibodies for school!" << endl;
    
    else
    {
        state = STUDYING_IN_CLASS;
        
        if ((*current_class).GetNumAssignmentsRemaining() < num_assignments)
        {
            cout << display_code << id_num << ": Started to learn at the Classroom " << (*current_class).GetId() << " with " << (*current_class).GetNumAssignmentsRemaining() << " assignments." << endl;
            assignments_to_buy = (*current_class).GetNumAssignmentsRemaining(); 
        }

        else
        {
            cout << display_code << id_num << ": Started to learn at the Classroom " << (*current_class).GetId() << " with " << num_assignments << " assignments." << endl;
            assignments_to_buy = num_assignments;
        }
    }


}

void Student::StartRecoveringAntibodies(unsigned int num_vaccines)
{
    if (state != AT_DOCTORS)
        cout << display_code << id_num << ": I can only recover antibodies at Doctor's Office." << endl;
    
    else if ((*current_office).GetNumVaccineRemaining() == 0)
        cout << display_code << id_num << ": Cannot recover! No vaccines remaining in this Doctor's Office." << endl;
    
    else if ((*current_office).GetDollarCost(num_vaccines) > dollars)
        cout << display_code << id_num << ": Not enough money to recover antibodies." << endl;
    
    else
    {
        state = RECOVERING_ANTIBODIES;
        if ((*current_office).GetNumVaccineRemaining() < num_vaccines)
        {
            cout << display_code << id_num << ": Started recovering antibodies using " << (*current_office).GetNumVaccineRemaining() << " vaccines at Doctor's Office " << (*current_office).GetId() << "." << endl;    
            vaccines_to_buy = (*current_office).DistributeVaccine((*current_office).GetNumVaccineRemaining());
        }

        else
        {
            cout << display_code << id_num << ": Started recovering antibodies using " << num_vaccines << " vaccines at Doctor's Office " << (*current_office).GetId() << "." << endl;
            vaccines_to_buy = (*current_office).DistributeVaccine(num_vaccines);
        }
    }
}

bool Student::UpdateLocation()
{
    double x_distance = fabs(destination.x - location.x);
    double y_distance = fabs(destination.y - location.y);

    if (x_distance <= fabs(delta.x) && y_distance <= fabs(delta.y))
    {
        cout << display_code << id_num << ": I'm there!" << endl;
        location = destination;
        return true;
    }

    else
    {
        cout << display_code << id_num << ": step..." << endl;
        location = location + delta;

        for (pair <Virus*, double> &virus : viruses_contracted)
        {
            double virulence = (*virus.first).get_virulence(); // Obtain virulence of the contracted virus
            double virus_resistance = (*virus.first).get_resistance();
            double student_resistance = virus.second;
            cout << student_resistance << " " << virulence << endl;

            if (student_resistance >= virulence)
                continue;
            
            else
            {
                antibodies -= ceil(0.5 * (virulence - student_resistance));
                virus.second += 0.5 + student_resistance/virus_resistance;

                if (antibodies <= 0)
                {
                    antibodies = 0;
                    state = INFECTED;
                }

                if (virus.second >= virulence)
                {
                    virus.second = virulence;
                    (*virus.first).destroy_self();
                    cout << (*virus.first).get_name() << " has been eliminated!" << endl;
                }
                
            }
        }

        if (antibodies != 0)
            antibodies -= 1;

        dollars += GetRandomAmountOfDollars();
        return false;
    }
    
}

void Student::SetupDestination(Point2D dest)
{
    destination = dest;
    delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
    return;
}

void Student::Stop()
{
    state = STOPPED;
    cout << display_code << id_num << ": Stopping..." << endl;
}

bool Student::IsInfected()
{
    if (antibodies == 0)
        return true;
    else 
        return false;
}

bool Student::ShouldBeVisible()
{
    if (IsInfected())
        return false;
    else
        return true;
}

void Student::ShowStatus()
{
    cout << endl << name << " Status: ";
    GameObject::ShowStatus();

    switch (state)
    {
        case STOPPED:
            cout << " stopped" << endl;
            break;
        
        case INFECTED:
            cout << " infected" << endl;
            break;

        case MOVING:
            cout << " moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << "." << endl;
            break;
        
        case MOVING_TO_CLASS:
            cout << " heading to Classroom " << (*current_class).GetId() << " at a speed of " << speed << " at each step of " << delta << "." << endl;
            break;
        
        case MOVING_TO_DOCTOR:
            cout << " heading to Doctor's Office " << (*current_office).GetId() << " at a speed of " << speed << " at each step of " << delta << "." << endl;
            break;

        case IN_CLASS:
            cout << " inside Classroom " << (*current_class).GetId() << "." << endl;
            break;

        case AT_DOCTORS:
            cout << " at Doctor's Office " << (*current_office).GetId() << "." << endl;
            break;
        
        case STUDYING_IN_CLASS:
            cout << " studying in Classroom " << (*current_class).GetId() << "." << endl;
            break;
        
        case RECOVERING_ANTIBODIES:
            cout << " recovering antibodiese at Doctor's Office " << (*current_office).GetId() << "." << endl;
            break;   
    }

    cout << "\tAntibodies: " << antibodies << endl;
    cout << "\tDollars: " << fixed << setprecision(2) << dollars << endl;
    cout << "\tCredits: " << credits << endl;

    return;
}

bool Student::Update()
{
    switch (state)
    {
        case STOPPED:
            return false;

        case MOVING:
        {    
            if (is_in_class && old_classroom != NULL)
            {
                (*old_classroom).RemoveOneStudent();
                is_in_class = false;
            }

            if (is_at_doctor && old_office != NULL)
            {
                (*old_office).RemoveOneStudent();
                is_at_doctor = false;
            }

            bool arrived = UpdateLocation();

            if (antibodies == 0)
            {
                cout << name << " is out of antibodies and can't move" << endl;
                state = INFECTED;
                return true;
            }

            else if (arrived)
            {
                state = STOPPED;
                return true;
            }

            else
                return false;
        }

        case MOVING_TO_CLASS:
        {
            if (is_in_class && old_classroom != NULL)
            {
                (*old_classroom).RemoveOneStudent();
                is_in_class = false;
            }

            if (is_at_doctor && old_office != NULL)
            {
                (*old_office).RemoveOneStudent();
                is_at_doctor = false;
            }

            bool arrived_in_class = UpdateLocation();

            if (antibodies == 0)
            {
                state = INFECTED;
                return true;
            }


            else if (arrived_in_class)
            {
                state = IN_CLASS;
                is_in_class = true;
                old_classroom = current_class;
                (*current_class).AddOneStudent();
                return true;
            }

            else
                return false;
        }

        case MOVING_TO_DOCTOR:
        {
            if (is_in_class && old_classroom != NULL)
            {
                (*old_classroom).RemoveOneStudent();
                is_in_class = false;
            }

            if (is_at_doctor && old_office != NULL)
            {
                (*old_office).RemoveOneStudent();
                is_at_doctor = false;
            }

            bool arrived_at_doctors = UpdateLocation();

            if (antibodies == 0)
            {
                state = INFECTED;
                return true;
            }

            else if (arrived_at_doctors)
            {
                state = AT_DOCTORS;
                is_at_doctor = true;
                old_office = current_office;
                (*current_office).AddOneStudent();
                return true;
            }

            else
                return false;
        }

        case IN_CLASS:
            return false;

        case AT_DOCTORS:
            return false;
        
        case STUDYING_IN_CLASS:
        {
            unsigned int credits_gained = (*current_class).TrainStudents(assignments_to_buy);
            credits += credits_gained;
            antibodies -= (*current_class).GetAntibodyCost(assignments_to_buy);
            dollars -= (*current_class).GetDollarCost(assignments_to_buy);
            cout << "** " << name << " completed " << assignments_to_buy << " assignments! **" << endl;
            cout << "** " << name << " gained " << credits_gained << " credits! **" << endl;
            state = IN_CLASS;
            return true;
        
        }

        case RECOVERING_ANTIBODIES:
        {
            unsigned int antibodies_gained = vaccines_to_buy * 5;
            antibodies += antibodies_gained;
            dollars -= (*current_office).GetDollarCost(vaccines_to_buy);
            cout << "** " << name << " recovered " << antibodies_gained << " antibodies! **" << endl;
            cout << "** " << name << " bought " << vaccines_to_buy << " vaccines! **" << endl;
            state = AT_DOCTORS;
            return true;
        }
    }

    return false;
}

void Student::AddVirus(Virus* virus)
{
    pair <Virus*, double> new_virus(virus, 0.0);
    viruses_contracted.push_back(new_virus);
}
