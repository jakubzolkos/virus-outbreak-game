#ifndef PHARMACY_H
#define PHARMACY_H
#include "Building.h"
using namespace std;

class Pharmacy : public Building
{
    enum PharmacyStates
    {
        IN_STOCK = 0,
        OUT_OF_STOCK = 1
    };
    
    private:
        unsigned int hand_sanitizers = 10;
        unsigned int medicine = 5;
        unsigned int masks = 3;
        double sanitizer_cost = 10;
        double medicine_cost = 10;
        double mask_cost = 30;
    
    public:
        Pharmacy();
        virtual ~Pharmacy();
        Pharmacy(int in_id, unsigned int num_sanitizers, unsigned int num_medicine, unsigned int num_masks, Point2D in_loc);
        unsigned int GetNumSanitizersRemaining();
        unsigned int GetNumMedicineRemaining();
        unsigned int GetNumMasksRemaining();
        double GetSanitizerCost(unsigned int quantity);
        double GetMedicineCost(unsigned int quantity);
        double GetMaskCost(unsigned int quantity);
        unsigned int GetNumProductRemaining(char product);
        unsigned int SellProduct(char product, unsigned int quantity);
        bool CanAffordProduct(char product, unsigned int quantity, double budget);
        virtual bool Update();
        void ShowStatus();
};

#endif