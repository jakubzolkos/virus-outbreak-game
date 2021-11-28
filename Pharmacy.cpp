#include "Pharmacy.h"
#include <iostream>
using namespace std;

Pharmacy::Pharmacy() : Building(), hand_sanitizers(10), medicine(5), masks(3), sanitizer_cost(5), medicine_cost(10), mask_cost(30)
{
    display_code = 'P';
    state = IN_STOCK;
    cout << "Pharmacy default constructed" << endl;
}

Pharmacy::~Pharmacy()
{
    cout << "Pharmacy destructed" << endl;
}

Pharmacy::Pharmacy(int in_id, unsigned int num_sanitizers, unsigned int num_medicine, unsigned int num_masks, Point2D in_loc) : Building('P', in_id, in_loc), 
hand_sanitizers(num_sanitizers), medicine(num_medicine), masks(num_masks), sanitizer_cost(5), medicine_cost(10), mask_cost(20)
{
    state = IN_STOCK;
    cout << "Pharmacy constructed" << endl;
}

unsigned int Pharmacy::GetNumSanitizersRemaining()
{
    return hand_sanitizers;
}

unsigned int Pharmacy::GetNumMedicineRemaining()
{
    return medicine;
}

unsigned int Pharmacy::GetNumMasksRemaining()
{
    return masks;
}

double Pharmacy::GetSanitizerCost(unsigned int quantity)
{
    return quantity*sanitizer_cost;
}

double Pharmacy::GetMedicineCost(unsigned int quantity)
{
    return quantity*medicine_cost;
}

double Pharmacy::GetMaskCost(unsigned int quantity)
{
    return quantity*mask_cost;
}

unsigned int Pharmacy::GetNumProductRemaining(char product)
{
    switch (product)
    {
        case 's':
            return hand_sanitizers;
        
        case 'd':
            return medicine;
        
        case 'm':
            return masks;

        default:
            cout << "No such product in store." << endl;
    }

    return 0;
}

bool Pharmacy::CanAffordProduct(char product, unsigned int quantity, double budget)
{
    switch (product)
    {
        case 's':
            if (quantity * sanitizer_cost <= budget)
                return true;
            else
                return false;
        
        case 'd':
            if (quantity * medicine_cost <= budget)
                return true;
            else
                return false;
        
        case 'm':
            if (quantity * mask_cost <= budget)
                return true;
            
            else
                return false;
        
        default:
            cout << "No such product in store." << endl;
    }

    return false;
}

unsigned int Pharmacy::SellProduct(char product, unsigned int quantity)
{
    switch (product)
    {
        case 's':
            if (hand_sanitizers >= quantity)
            {
                hand_sanitizers -= quantity;
                return quantity;
            }

            else
            {
                unsigned int current = hand_sanitizers;
                hand_sanitizers = 0;
                return current;
            }
        
        case 'd':
            if (medicine >= quantity)
            {
                medicine -= quantity;
                return quantity;
            }

            else
            {
                unsigned int current = medicine;
                medicine = 0;
                return current;
            }
        
        case 'm':
            if (masks >= quantity)
            {
                masks -= quantity;
                return quantity;
            }

            else
            {
                unsigned int current = masks;
                masks = 0;
                return current;
            }
        
        default:
            cout << "No such product in store." << endl;
    }

    return 0;
}

void Pharmacy::ShowStatus()
{
    cout << endl;
    cout << "Pharmacy Status: ";
    Building::ShowStatus();
    cout << "\tHand sanitizers ($" << sanitizer_cost << "): " << hand_sanitizers << endl;
    cout << "\tMedicine ($" << medicine_cost << "): " << medicine << endl;
    cout << "\tMasks ($" << mask_cost << "): " << masks << endl;
    
    return;
}

bool Pharmacy::Update()
{
    if (state == IN_STOCK && hand_sanitizers == 0 && medicine == 0 && masks == 0)
    {
        state = OUT_OF_STOCK;
        display_code = 'p';
        cout << "Pharmacy " << id_num << " has run out of stock." << endl;
        return true;
    }

    else    
        return false;
}