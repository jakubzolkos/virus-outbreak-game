#include "GameCommand.h"
using namespace std;

// Function to check if an integer is in a specific range
bool check_range(int number, int lower, int upper)
{
  return (number >= lower && number <= upper);
}

void DoMoveCommand(Model &model, int student_id, Point2D p1)
{
    try
    {
        Student *student = model.GetStudentPtr(student_id);

        if (student == NULL)
            throw Invalid_Input("Student with that ID does not exist");
        else
        {
            cout << "Moving " << (*student).GetName() << " to " << p1 << endl;
            (*student).StartMoving(p1);
        }
    }

    catch (Invalid_Input &except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }
}

void DoMoveToDoctorCommand(Model &model, int student_id, int office_id)
{
    try 
    {
        Student *student = model.GetStudentPtr(student_id);
        DoctorsOffice *office = model.GetDoctorsOfficePtr(office_id);

        if (student == NULL || office == NULL)
        {
            throw Invalid_Input("Student or office with that ID does not exist");
        }

        cout << "Moving " << (*student).GetName() << " to Doctor's Office " << (*office).GetId() << endl;
        (*student).StartMovingToDoctor(office);
    }

    catch (Invalid_Input &except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }
}

void DoMoveToClassCommand(Model &model, int student_id, int class_id)
{
    try 
    {
        Student *student = model.GetStudentPtr(student_id);
        ClassRoom *classroom = model.GetClassRoomPtr(class_id);

        if (student == NULL || classroom == NULL)
        {
            throw Invalid_Input("Student or classroom with that ID does not exist");
        }

        cout << "Moving " << (*student).GetName() << " to Classroom " << (*classroom).GetId() << endl;
        (*student).StartMovingToClass(classroom);
    }

    catch (Invalid_Input &except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }
}

void DoMoveToPharmacyCommand(Model &model, int student_id, int pharmacy_id)
{
    try 
    {
        Student *student = model.GetStudentPtr(student_id);
        Pharmacy *pharmacy = model.GetPharmacyPtr(pharmacy_id);

        if (student == NULL || pharmacy == NULL)
        {
            throw Invalid_Input("Student or pharmacy with that ID does not exist");
        }

        cout << "Moving " << (*student).GetName() << " to Pharmacy " << (*pharmacy).GetId() << endl;
        (*student).StartMovingToPharmacy(pharmacy);
    }

    catch (Invalid_Input &except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }
}

void DoStopCommand(Model &model, int student_id)
{    
    try 
    {
        Student *student = model.GetStudentPtr(student_id); 

        if (student == NULL)
        {
            throw Invalid_Input("Student with that ID does not exist");
        }

        (*student).Stop();
        cout << "Stopping " << (*student).GetName() << endl;
    }
    
    catch (Invalid_Input &except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }
}

void DoLearningCommand(Model &model, int student_id, unsigned int assignments)
{
    try 
    {
        Student *student = model.GetStudentPtr(student_id);

        if (student == NULL)
        {
            throw Invalid_Input("Student with that ID does not exist");
        }

        cout << "Teaching " << (*student).GetName() << endl;
        (*student).StartLearning(assignments);
    }
    
    catch (Invalid_Input &except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }
}

void DoRecoverInOfficeCommand(Model &model, int student_id, unsigned int vaccine_needs)
{
    try 
    {
        Student *student = model.GetStudentPtr(student_id);

        if (student == NULL)
        {
            throw Invalid_Input("Student with that ID does not exist");
        }

        cout << "Recovering " << (*student).GetName() << "'s antibodies" << endl;
        (*student).StartRecoveringAntibodies(vaccine_needs, model);
    }
    
    catch (Invalid_Input &except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }
}

void DoPurchaseItemsCommand(Model &model, int student_id, char purchase_code, unsigned int quantity)
{
    try 
    {
        Student *student = model.GetStudentPtr(student_id);

        if (student == NULL)
        {
            throw Invalid_Input("Student with that ID does not exist");
        }

        cout << "Purchasing items for " << (*student).GetName() << endl;
        (*student).PurchaseProduct(purchase_code, quantity);
    }
    
    catch (Invalid_Input &except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }

    
}

void DoGoCommand(Model &model, View &view)
{
    cout << "Advancing one tick." << endl;
    view.Clear();
    model.Update();
    model.ShowStatus();
    model.Display(view);
}

void DoRunCommand(Model &model, View &view)
{
    cout << "Advancing to next event." << endl;
    
    for (int i = 0; i < 5; i++)
    {
        view.Clear();
        bool updated = model.Update();

        if (updated)
            break;
    }

    model.ShowStatus();
    model.Display(view);
}

void NewCommand(Model &model, char code, int id, Point2D location)
{
    try
    {
        if (!check_range(id, 1, 9))
            throw Invalid_Input("The chosen ID number exceeds acceptable range");
        
        switch (code)
        {
            case 'd':
            {
                if (model.GetDoctorsOfficePtr(id) != NULL)
                    throw (Invalid_Input("DoctorsOffice with ID number " + to_string(id) + " already exists."));

                else
                {
                    DoctorsOffice *office = new DoctorsOffice(id, 1, 100, location);
                    model.AddNewMember(code, office);
                    break;
                }
            }

            case 'c':
            {
                if (model.GetClassRoomPtr(id) != NULL)
                    throw (Invalid_Input("ClassRoom with ID number " + to_string(id) + " already exists."));
                
                else
                {
                    ClassRoom *classroom = new ClassRoom(15, 5, 5, 4, id, location);
                    model.AddNewMember(code, classroom);
                    break;
                }
            }

            case 's':
            {
                if (model.GetStudentPtr(id) != NULL)
                    throw (Invalid_Input("Student with ID number " + to_string(id) + " already exists."));
                
                else
                {
                    Student *student = new Student("Student " + to_string(id), id, 'S', 5, location);
                    model.AddNewMember(code, student);
                    break;
                }
            }

            case 'v':
            {
                if (model.GetVirusPtr(id) != NULL)
                    throw (Invalid_Input("Virus with ID number " + to_string(id) + " already exists."));
                
                else
                {
                    Virus *virus = new Virus("Virus " + to_string(id), 5, 5, 15, false, id, location);
                    model.AddNewMember(code, virus);
                    break;
                }
            }

            // If the type is invalid or any other error occures
            default:
                throw (Invalid_Input("Invalid type or the object with the selected ID already exists."));
        }
    }

    catch (Invalid_Input &except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }

    return;
}