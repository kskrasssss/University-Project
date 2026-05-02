#pragma once
#include <iostream>

//×טסעטי ³םעונפויס
class IDisplayable {
public:
    virtual void displayInfo() const = 0;
    virtual ~IDisplayable() {}
};