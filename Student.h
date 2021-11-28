#ifndef STUDENT_H
#define STUDENT_H
#include "GameObject.h"
#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include "Pharmacy.h"
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
        IN_PHARMACY = 5,
        MOVING_TO_DOCTOR = 6,
        MOVING_TO_CLASS = 7,
        MOVING_TO_PHARMACY = 8,
        STUDYING_IN_CLASS = 9,
        RECOVERING_ANTIBODIES = 10,
        PURCHASING_ITEMS = 11
    };

    private:
        double speed;
        bool is_at_doctor = false;
        bool is_in_class = false;
        bool is_in_pharmacy = false;
        int antibodies = 100;
        unsigned int credits = 0;
        double dollars = 0.0;
        unsigned int hand_sanitizers = 0;
        unsigned int medicine = 0;
        unsigned int masks = 0;
        unsigned int quantity_to_buy;
        char purchase_code = ' ';
        unsigned int assignments_to_buy = 0;
        unsigned int vaccines_to_buy = 0;
        string name;
        DoctorsOffice *current_office = NULL;
        DoctorsOffice *old_office = NULL;
        ClassRoom *current_class = NULL;
        ClassRoom *old_classroom = NULL;
        Pharmacy *current_pharmacy = NULL;
        Pharmacy *old_pharmacy = NULL;
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
        void StartMovingToPharmacy(Pharmacy *pharmacy);
        void StartLearning(unsigned int num_assignments);
        void StartRecoveringAntibodies(unsigned int num_vaccines);
        void PurchaseProduct(char product, unsigned int quantity);
        unsigned int GetNumHandSanitizers();
        unsigned int GetNumMedicine();
        unsigned int GetNumMasks();
        void RemoveHandSanitizer();
        void RemoveMedicine();
        void RemoveMask();
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