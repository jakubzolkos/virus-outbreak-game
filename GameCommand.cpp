#include "GameCommand.h"
using namespace std;

void DoMoveCommand(Model &model, int student_id, Point2D p1)
{
    Student *student = model.GetStudentPtr(student_id);
    cout << "Moving " << (*student).GetName() << " to " << p1 << endl;
    (*student).StartMoving(p1);
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