#include "Student.h"
#include "Virus.h"
#include "Model.h"
#include <random>
#include <iomanip>
#include <math.h>
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

unsigned int Student::GetNumHandSanitizers()
{
    return hand_sanitizers;
}

unsigned int Student::GetNumMedicine()
{
    return medicine;
}

unsigned int Student::GetNumMasks()
{
    return masks;
}

void Student::RemoveHandSanitizer()
{
    hand_sanitizers--;
}

void Student::RemoveMedicine()
{
    medicine--;
}

void Student::RemoveMask()
{
    masks--;
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

void Student::StartMovingToPharmacy(Pharmacy* pharmacy)
{
    if (IsInfected())
    {
        cout << display_code << id_num << ": I am infected so I can't move to the pharmacy..." << endl;
    }

    else if (GetDistanceBetween((*pharmacy).GetLocation(), location) == 0)
    {
        cout << display_code << id_num << ": I'm already at the Pharmacy" << endl;
        state = IN_PHARMACY;
    }

    else
    {
        SetupDestination((*pharmacy).GetLocation());
        current_pharmacy = pharmacy;
        state = MOVING_TO_PHARMACY;
        cout << display_code << id_num << ": On my way to the Pharmacy " << (*pharmacy).GetId() << "." << endl;
    }
}

void Student::StartLearning(unsigned int num_assignments)
{
    if (IsInfected())
        cout << display_code << id_num << ": I am infected so no more school for me..." << endl << endl;
    
    else if (state != IN_CLASS)
        cout << display_code << id_num << ": I can only learn in a Classroom!" << endl << endl;
    
    else if ((*current_class).GetNumAssignmentsRemaining() == 0)
        cout << display_code << id_num << ": Cannot learn! This Class has no more assignments!" << endl << endl;
    
    else if ((*current_class).GetDollarCost(num_assignments) > dollars || (*current_class).GetAntibodyCost(num_assignments) > antibodies)
        cout << display_code << id_num << ": Not enough money and/or antibodies for school!" << endl << endl;
    
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

void Student::StartRecoveringAntibodies(unsigned int num_vaccines, Model &model)
{
    if (IsInfected())
        cout << display_code << id_num << ": I am infected, I should have gone to the doctor earlier.." << endl << endl;
    
    else if (!(*current_office).IsOpen(model))
        cout << display_code << id_num << ": The Doctor's office is closed. Please come later." << endl << endl;
    
    else if (state != AT_DOCTORS)
        cout << display_code << id_num << ": I can only recover antibodies at Doctor's Office." << endl << endl;
    
    else if ((*current_office).GetNumVaccineRemaining() == 0)
        cout << display_code << id_num << ": Cannot recover! No vaccines remaining in this Doctor's Office." << endl << endl;
    
    else if ((*current_office).GetDollarCost(num_vaccines) > dollars)
        cout << display_code << id_num << ": Not enough money to recover antibodies." << endl << endl;
    
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

void Student::PurchaseProduct(char product, unsigned int quantity)
{
    if (IsInfected())
        cout << display_code << id_num << ": I am infected so I can't purchase anything..." << endl << endl;
    
    else if (state != IN_PHARMACY)
        cout << display_code << id_num << ": I can only do shopping at a pharmacy." << endl << endl;

    else if ((*current_pharmacy).GetNumProductRemaining(product) == 0)
        cout << "The selected product is out of stock." << endl << endl;
    
    else if (!(*current_pharmacy).CanAffordProduct(product, quantity, dollars))
        cout << "Not enough money to purchases the selected quantity of product." << endl << endl;
    
    else
    {
        state = PURCHASING_ITEMS;
        purchase_code = product;
        
        switch (product)
        {
            case 's':
            {
                if ((*current_pharmacy).GetNumSanitizersRemaining() < quantity)
                {
                    cout << display_code << id_num << ": Purchasing " << (*current_pharmacy).GetNumSanitizersRemaining() << " hand sanitizer(s) at Pharmacy " << (*current_pharmacy).GetId() << "." << endl;
                    quantity_to_buy = (*current_pharmacy).SellProduct(product, (*current_pharmacy).GetNumSanitizersRemaining());
                }

                else
                {
                    cout << display_code << id_num << ": Purchasing " << quantity << " hand sanitizer(s) at Pharmacy " << (*current_pharmacy).GetId() << "." << endl;
                    quantity_to_buy = (*current_pharmacy).SellProduct(product, quantity);
                }

                break;
            }

            case 'd':
            {
                if ((*current_pharmacy).GetNumMedicineRemaining() < quantity)
                {
                    cout << display_code << id_num << ": Purchasing " << (*current_pharmacy).GetNumMedicineRemaining() << " pack(s) of medicine at Pharmacy " << (*current_pharmacy).GetId() << "." << endl;
                    quantity_to_buy = (*current_pharmacy).SellProduct(product, (*current_pharmacy).GetNumMedicineRemaining());
                }

                else
                {
                    cout << display_code << id_num << ": Purchasing " << quantity << " pack(s) of medicine at Pharmacy " << (*current_pharmacy).GetId() << "." << endl;
                    quantity_to_buy = (*current_pharmacy).SellProduct(product, quantity);
                }

                break;
            }

            case 'm':
            {
                if ((*current_pharmacy).GetNumMasksRemaining() < quantity)
                {
                    cout << display_code << id_num << ": Purchasing " << (*current_pharmacy).GetNumMasksRemaining() << " mask(s) at Pharmacy " << (*current_pharmacy).GetId() << "." << endl;
                    quantity_to_buy = (*current_pharmacy).SellProduct(product, (*current_pharmacy).GetNumMasksRemaining());
                }

                else
                {
                    cout << display_code << id_num << ": Purchasing " << quantity << " mask(s) at Pharmacy " << (*current_pharmacy).GetId() << "." << endl;
                    quantity_to_buy = (*current_pharmacy).SellProduct(product, quantity);
                }

                break;
            }
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

        for (pair <Virus*, double> &immunity : viruses_contracted)
        {
            double virulence = (*immunity.first).get_virulence(); // Get the virulence of the contracted virus
            double virus_resistance = (*immunity.first).get_resistance(); // Get the virus resistance
            double student_resistance = immunity.second; // Get current student resistance
            cout << student_resistance << " " << virulence << endl;

            if (student_resistance >= virulence) // If the student's resistance to the virus exceeds the virulence, continue
                continue;
            
            else
            {
                antibodies -= ceil(0.5 * virulence);
                immunity.second += 1/virus_resistance;

                if (antibodies <= 0) // If the virus decreases the students antibodies below 0, set the state as INFECTED
                {
                    antibodies = 0;
                    state = INFECTED;
                }

                if (immunity.second >= virulence) // If the student obtains full immunity to the virus, eliminate the virus
                {
                    immunity.second = virulence;
                    (*immunity.first).destroy_self();
                    cout << (*immunity.first).get_name() << " has been eliminated!" << endl;
                }
                
            }
        }

        if (antibodies != 0) // If antibodies are not equal to 0. decrease them by 1
            antibodies -= 1;

        dollars += GetRandomAmountOfDollars(); // Increase the student's money by a random amount

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
        
        case MOVING_TO_PHARMACY:
            cout << " heading to Pharmacy " << (*current_pharmacy).GetId() << " at a speed of " << speed << " at each step of " << delta << "." << endl;
            break;

        case IN_CLASS:
            cout << " inside Classroom " << (*current_class).GetId() << "." << endl;
            break;

        case AT_DOCTORS:
            cout << " at Doctor's Office " << (*current_office).GetId() << "." << endl;
            break;
        
        case IN_PHARMACY:
            cout << " in Pharmacy " << (*current_pharmacy).GetId() << "." << endl;
            break;
        
        case STUDYING_IN_CLASS:
            cout << " studying in Classroom " << (*current_class).GetId() << "." << endl;
            break;
        
        case RECOVERING_ANTIBODIES:
            cout << " recovering antibodies at Doctor's Office " << (*current_office).GetId() << "." << endl;
            break;   
        
        case PURCHASING_ITEMS:
            cout << " purchasing items in Pharmacy " << (*current_pharmacy).GetId() << "." << endl;
            break; 
    }

    cout << "\tAntibodies: " << antibodies << endl;
    cout << "\tDollars: " << fixed << setprecision(2) << dollars << endl;
    cout << "\tCredits: " << credits << endl;
    cout << "\tHand Sanitizers: " << hand_sanitizers << endl;
    cout << "\tMedicine Packs: " << medicine << endl;
    cout << "\tMasks: " << masks << endl;

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

            if (is_in_pharmacy && old_pharmacy != NULL)
            {
                (*old_pharmacy).RemoveOneStudent();
                is_in_pharmacy = false;
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

            if (is_in_pharmacy && old_pharmacy != NULL)
            {
                (*old_pharmacy).RemoveOneStudent();
                is_in_pharmacy = false;
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

            if (is_in_pharmacy && old_pharmacy != NULL)
            {
                (*old_pharmacy).RemoveOneStudent();
                is_in_pharmacy = false;
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

        case MOVING_TO_PHARMACY:
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

            if (is_in_pharmacy && old_pharmacy != NULL)
            {
                (*old_pharmacy).RemoveOneStudent();
                is_in_pharmacy = false;
            }

            bool arrived_in_pharmacy = UpdateLocation();

            if (antibodies == 0)
            {
                state = INFECTED;
                return true;
            }


            else if (arrived_in_pharmacy)
            {
                state = IN_PHARMACY;
                is_in_pharmacy = true;
                old_pharmacy = current_pharmacy;
                (*current_pharmacy).AddOneStudent();
                return true;
            }

            else
                return false;
        }

        case IN_CLASS:
            return false;

        case AT_DOCTORS:
            return false;

        case IN_PHARMACY:
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

        case PURCHASING_ITEMS:
        {
            switch (purchase_code)
            {
                case 's':
                    hand_sanitizers += quantity_to_buy;
                    dollars -= (*current_pharmacy).GetSanitizerCost(quantity_to_buy);
                    cout << "** " << name << " bought " << quantity_to_buy << " hand sanitizers! **" << endl;
                    cout << "** " << name << " has " << hand_sanitizers << " hand sanitizer(s) in inventory! **" << endl;
                    state = IN_PHARMACY;
                    return true;
                
                case 'd':
                    medicine += quantity_to_buy;
                    dollars -= (*current_pharmacy).GetMedicineCost(quantity_to_buy);
                    cout << "** " << name << " bought " << quantity_to_buy << " packs of medicine! **" << endl;
                    cout << "** " << name << " has " << medicine << " pack(s) of medicine in inventory! **" << endl;
                    state = IN_PHARMACY;
                    return true;
                
                case 'm':
                    masks += quantity_to_buy;
                    dollars -= (*current_pharmacy).GetMaskCost(quantity_to_buy);
                    cout << "** " << name << " bought " << quantity_to_buy << " masks! **" << endl;
                    cout << "** " << name << " has " << masks << " mask(s) in inventory! **" << endl;
                    state = IN_PHARMACY;
                    return true;
            }
        }

    }

    return false;
}

void Student::AddVirus(Virus* virus)
{
    double resistance_factor = 0.0;

    if (medicine != 0) // If the student has medicine in inventory, boost initial immunity by 2
    {
        resistance_factor = 2.0;
        medicine--;
        cout << name << " used medicine to help with recovery!" << endl;
    }

    pair <Virus*, double> new_virus(virus, resistance_factor);
    viruses_contracted.push_back(new_virus);
}
