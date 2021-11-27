#include "Model.h"
#include "DoctorsOffice.h"
#include "Student.h"
#include "ClassRoom.h"
#include "Virus.h"
#include <stdlib.h> 
using namespace std;

Model::Model() : time(0)
{
    Student *S1 = new Student(string("Homer"), 1, 'S', 2, Point2D(5, 1));
    Student *S2 = new Student(string("Marge"), 2, 'S', 1, Point2D(10, 1));
    Virus *V1 = new Virus(string("COVID-19"), 8, 3, 20, false, 1, Point2D(15, 5));
    Virus *V2 = new Virus(string("Influenza"), 2, Point2D(10, 12));
    DoctorsOffice *D1 = new DoctorsOffice(1, 1, 100, Point2D(1, 20));
    DoctorsOffice *D2 = new DoctorsOffice(2, 2, 200, Point2D(10, 20));
    ClassRoom *C1 = new ClassRoom(10, 1, 2.0, 3, 1, Point2D(0, 0));
    ClassRoom *C2 = new ClassRoom(20, 5, 7.5, 4, 2, Point2D(5, 5));

    object_ptrs = {S1, S2, D1, D2, C1, C2, V1, V2};
    active_ptrs = {S1, S2, V1, V2};
    office_ptrs = {D1, D2};
    class_ptrs = {C1, C2};
    student_ptrs = {S1, S2};
    virus_ptrs = {V1, V2};

    cout << "Model default constructed" << endl;
}

Model::~Model() 
{
    for (GameObject* &object : object_ptrs)
        delete object;

    cout << "Model destructed" << endl;
}

Student* Model::GetStudentPtr(int id)
{
    for (Student* &student : student_ptrs)
    {
        if ((*student).GetId() == id)
        {
            return student;
        }
    }

    return NULL;
}

DoctorsOffice* Model::GetDoctorsOfficePtr(int id)
{
    for (DoctorsOffice* &office : office_ptrs)
    {
        if ((*office).GetId() == id)
        {
            return office;
        }
    }

    return NULL;
}

ClassRoom* Model::GetClassRoomPtr(int id)
{
    for (ClassRoom* &classroom : class_ptrs)
    {
        if ((*classroom).GetId() == id)
        {
            return classroom;
        }
    }

    return NULL;
}

bool Model::Update()
{
    time++; // Increment game time

    bool changed, result = false, all_infected = true, all_passed = true;

    for (GameObject* &object : object_ptrs)
    {
        changed = (*object).Update();
        
        if (changed)
        {
            result = true;
        }
    }


    // Check if all the students are infected 
    for (Student* &student : student_ptrs)
    {   
        changed = (*student).IsInfected();

        if (!changed)
        {
            all_infected = false;
            break;
        }

        else    
            continue;
    }


    if (all_infected)
    {
        cout << endl << "GAME OVER: You lose! All of your students are infected" << endl;
        exit(0);
    }

    for (ClassRoom* &classroom : class_ptrs)
    {
        changed = (*classroom).Passed();

        if (!changed)
        {
            all_passed = false;
            break;
        }

        else
            continue;
    }

    if (all_passed)
    {
        cout << endl << "GAME OVER: You win! All assignments done!" << endl;
        exit(0);
    }

    for (Student* &student : student_ptrs)
    {
        for (Virus* &virus : virus_ptrs)
        {
            (*virus).infect(student);
        }
    }

    return result;
}

void Model::ShowStatus()
{
    cout << endl << "Time: " << time << endl;

    for (GameObject* &object : object_ptrs)
        (*object).ShowStatus();

    return;
}

void Model::Display(View &view)
{
    view.Clear();
    cout << endl;

    for (GameObject* &object : object_ptrs)
    {
        view.Plot(object);
    }

    view.Draw();
}