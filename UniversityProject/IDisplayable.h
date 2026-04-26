#pragma once
#include <iostream>

// №8: Чистий інтерфейс
class IDisplayable {
public:
    virtual void displayInfo() const = 0; // Чисто віртуальна функція
    virtual ~IDisplayable() {} // Віртуальний деструктор (Пункт №4)
};