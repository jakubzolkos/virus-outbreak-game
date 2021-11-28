#include "GameCommand.h"
using namespace std;

void DoMoveCommand(Model &model, int student_id, Point2D p1)
{
    try
    {
        Student *student = model.GetStudentPtr(student_id);

        if (student == NULL)
            throw (Invalid_Input("Invalid command parameters."));
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
    Student *student = model.GetStudentPtr(student_id);
    DoctorsOffice *office = model.GetDoctorsOfficePtr(office_id);
    cout << "Moving " << (*student).GetName() << " to Doctor's Office " << (*office).GetId() << endl;
    (*student).StartMovingToDoctor(office);
}

void DoMoveToClassCommand(Model &model, int student_id, int class_id)
{
    Student *student = model.GetStudentPtr(student_id);
    ClassRoom *classroom = model.GetClassRoomPtr(class_id);
    cout << "Moving " << (*student).GetName() << " to Doctor's Office " << (*classroom).GetId() << endl;
    (*student).StartMovingToClass(classroom);
}

void DoMoveToPharmacyCommand(Model &model, int student_id, int class_id)
{
    Student *student = model.GetStudentPtr(student_id);
    Pharmacy *pharmacy = model.GetPharmacyPtr(class_id);
    cout << "Moving " << (*student).GetName() << " to Doctor's Office " << (*pharmacy).GetId() << endl;
    (*student).StartMovingToPharmacy(pharmacy);
}

void DoStopCommand(Model &model, int student_id)
{
    Student *student = model.GetStudentPtr(student_id);
    cout << "Stopping " << (*student).GetName() << endl;
    (*student).Stop();
}

void DoLearningCommand(Model &model, int student_id, unsigned int assignments)
{
    Student *student = model.GetStudentPtr(student_id);
    cout << "Teaching " << (*student).GetName() << endl;
    (*student).StartLearning(assignments);
}

void DoRecoverInOfficeCommand(Model &model, int student_id, unsigned int vaccine_needs)
{
    Student *student = model.GetStudentPtr(student_id);
    cout << "Recovering " << (*student).GetName() << "'s antibodies" << endl;
    (*student).StartRecoveringAntibodies(vaccine_needs);
}

void DoPurchaseItemsCommand(Model &model, int student_id, char purchase_code, unsigned int quantity)
{
    Student *student = model.GetStudentPtr(student_id);
    cout << "Purchasing items for " << (*student).GetName() << endl;
    (*student).PurchaseProduct(purchase_code, quantity);
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