#include "Model.h"
#include "DoctorsOffice.h"
#include "Student.h"
#include "ClassRoom.h"
#include "Virus.h"
#include <stdlib.h>
#include <algorithm> 
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
    Pharmacy *P1 = new Pharmacy(1, 10, 5, 3, Point2D(12, 8));

    object_ptrs = {S1, S2, D1, D2, C1, C2, V1, V2, P1};
    active_ptrs = {S1, S2, D1, D2, C1, C2, V1, V2, P1};
    office_ptrs = {D1, D2};
    class_ptrs = {C1, C2};
    student_ptrs = {S1, S2};
    virus_ptrs = {V1, V2};
    pharmacy_ptrs = {P1};

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

Virus* Model::GetVirusPtr(int id)
{
    for (Virus* &virus : virus_ptrs)
    {
        if ((*virus).GetId() == id)
        {
            return virus;
        }
    }

    return NULL;
}

Pharmacy* Model::GetPharmacyPtr(int id)
{
    for (Pharmacy* &pharmacy : pharmacy_ptrs)
    {
        if ((*pharmacy).GetId() == id)
        {
            return pharmacy;
        }
    }

    return NULL;
}

bool Model::Update()
{
    time++; // Increment game time

    bool changed, result = false;

    // Check if any of the students is at the same location as any of the viruses.
    for (Student* &student : student_ptrs)
    {
        for (Virus* &virus : virus_ptrs)
        {
            if (GetDistanceBetween((*virus).GetLocation(), (*student).GetLocation()) <= 3 && !(*student).IsInfected())
            {
                if ((*student).GetNumMasks() != 0)
                {
                    cout << (*student).GetName() << " protected him/herself from infection with a mask!" << endl;
                    (*student).RemoveMask();
                    continue;
                }
                
                else if ((*student).GetNumHandSanitizers() != 0)
                {
                    double chance = rand() / (RAND_MAX + 1.);
                    (*student).RemoveHandSanitizer();
                    
                    if (chance <= 0.7)
                    {
                        cout << (*student).GetName() << " protected him/herself from infection with a hand sanitizer!" << endl;
                    }
                }

                else
                {
                    (*virus).infect(student);
                }
            }
        }
    }

    // Update all active objects and remove dead ones
    for (list <GameObject*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++)
    {
        changed = (*it) -> Update();
        
        if (changed)
        {
            result = true;
        }

        if (!((*it) -> ShouldBeVisible()))
        {
            it = active_ptrs.erase(it);
            cout << "Dead object removed" << endl;
        }
    }

    // Check if all students are infected
    if (all_of(student_ptrs.begin(), student_ptrs.end(), [](Student* student) {return (*student).IsInfected();}))
    {
        cout << endl << "GAME OVER: You lose! All of your students are infected" << endl;
        exit(0);
    }

    // Check if all classes are passed
    if (all_of(class_ptrs.begin(), class_ptrs.end(), [](ClassRoom* classroom) {return (*classroom).Passed();}))
    {
        cout << endl << "GAME OVER: You win! All assignments done!" << endl;
        exit(0);
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

    for (GameObject* &object : active_ptrs)
    {
        view.Plot(object);
    }

    view.Draw();
}

void Model::AddNewMember(char code, GameObject* object)
{
    object_ptrs.push_back(object);
    active_ptrs.push_back(object);
    
    switch (code)
    {
        case 'd':
        {
            DoctorsOffice* new_office = dynamic_cast <DoctorsOffice*>(object);
            office_ptrs.push_back(new_office);
            break;
        }

        case 'c':
        {
            ClassRoom* new_classroom = dynamic_cast <ClassRoom*>(object);
            class_ptrs.push_back(new_classroom);
            break;
        }

        case 's':
        {
            Student* new_student = dynamic_cast <Student*>(object);
            student_ptrs.push_back(new_student);
            break;
        }

        case 'v':
        {
            Virus* new_virus = dynamic_cast <Virus*>(object);
            virus_ptrs.push_back(new_virus);
            break;
        }
    }
}