#ifndef MODEL_H
#define MODEL_H
#include "GameObject.h"
#include "Student.h"
#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include "View.h"
#include "Virus.h"
#include <list>

class Model
{
    private:
        int time;
        list <GameObject*> object_ptrs;
        list <GameObject*> active_ptrs;
        list <Student*> student_ptrs;
        list <DoctorsOffice*> office_ptrs;
        list <ClassRoom*> class_ptrs;
        list <Virus*> virus_ptrs;


    public:
        Model();
        virtual ~Model();
        Student* GetStudentPtr(int id);
        DoctorsOffice* GetDoctorsOfficePtr(int id); 
        ClassRoom* GetClassRoomPtr(int id);
        Virus* GetVirusPtr(int id);
        bool Update();
        void Display(View &view);
        void ShowStatus();
        void AddNewMember(char chode, GameObject* object);
};

#endif