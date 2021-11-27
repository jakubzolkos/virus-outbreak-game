#ifndef STUDENT_H
#define STUDENT_H
#include "GameObject.h"
#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include <utility>
#include <list>

class Virus;

class Student : public virtual GameObject
{
    enum StudentStates 
    {
        STOPPED = 0,
        MOVING = 1,
        INFECTED = 2,
        AT_DOCTORS = 3,
        IN_CLASS = 4,
        MOVING_TO_DOCTOR = 5,
        MOVING_TO_CLASS = 6,
        STUDYING_IN_CLASS = 7,
        RECOVERING_ANTIBODIES = 8
    };

    private:
        double speed;
        bool is_at_doctor = false;
        bool is_in_class = false;
        int antibodies = 100;
        unsigned int credits = 0;
        double dollars = 0.0;
        unsigned int assignments_to_buy = 0;
        unsigned int vaccines_to_buy = 0;
        string name;
        DoctorsOffice *current_office = NULL;
        DoctorsOffice *old_office = NULL;
        ClassRoom *current_class = NULL;
        ClassRoom *old_classroom = NULL;
        Point2D destination;
        Vector2D delta;
        list <pair <Virus*, double>> viruses_contracted;
    
    protected:
        
        void SetupDestination(Point2D dest);
    
    public:
        Student();
        virtual ~Student();
        Student(char in_code);
        Student(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
        void StartMoving(Point2D dest);
        void StartMovingToClass(ClassRoom *classr);
        void StartMovingToDoctor(DoctorsOffice *office);
        void StartLearning(unsigned int num_assignments);
        void StartRecoveringAntibodies(unsigned int num_vaccines);
        void Stop();
        bool IsInfected();
        bool ShouldBeVisible();
        void ShowStatus();
        virtual bool Update();
        bool UpdateLocation();
        string GetName();  
        void AddVirus(Virus* virus);    
};

#endif