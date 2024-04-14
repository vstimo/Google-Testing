#pragma once
#include "Wipers.h"
#include "Manager_Wipers.h"

class Manager_Actuators {

public:
    Manager_Actuators(Manager_Wipers wipersSpeed) : managerWipers(wipersSpeed) {}

    void ReadManagerWipers(Manager_Wipers wipersSpeed) {
        managerWipers = wipersSpeed;
    }

    void SetWipers() {
        wipers.SetSpeed(managerWipers.CalculateWipersSpeed());
    }

    Wipers GetWipers() const {
        return wipers;
    }

protected:
    Manager_Wipers managerWipers;
    Wipers wipers;
};
