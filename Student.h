#ifndef STUDENT_H
#define STUDENT_H
#include "GameObject.h"
#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include "Pharmacy.h"
#include "Bus.h"
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
        AT_BUS_STATION = 6,
        MOVING_TO_DOCTOR = 7,
        MOVING_TO_CLASS = 8,
        MOVING_TO_PHARMACY = 9,
        MOVING_TO_BUS_STATION = 10,
        STUDYING_IN_CLASS = 11,
        RECOVERING_ANTIBODIES = 12,
        PURCHASING_ITEMS = 13,
        TRAVELING = 14,
    };

    private:
        double speed;
        bool is_at_doctor = false;
        bool is_in_class = false;
        bool is_in_pharmacy = false;
        bool is_at_bus_station = false;
        int antibodies = 100;
        unsigned int credits = 0;
        double dollars = 30;
        unsigned int hand_sanitizers = 0;
        unsigned int medicine = 1;
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
        Bus *current_bus_station = NULL;
        Bus *old_bus_station = NULL;
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
        void StartMovingToBusStation(Bus *bus_station);
        void StartLearning(unsigned int num_assignments);
        void StartRecoveringAntibodies(unsigned int num_vaccines, Model &model);
        void PurchaseProduct(char product, unsigned int quantity);
        void BusTravel(Bus* bus_station);
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