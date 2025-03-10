#include "Payment.h"
#include <iostream>

bool Payment::processPayment(Order &o, const std::string &paymentMethod)
{
    if (paymentMethod == "bank")
    {
        std::string transferCode;
        std::cout << "Wprowadz kod potwierdzajacy przelew: ";
        std::cin >> transferCode;

        // TO DO: zintegrowa� z baz� danych
        if (transferCode == "1234")
        {
            std::cout << "Przelew potwierdzony.\n";
            return true;
        }
        else
        {
            std::cout << "B��dny kod przelewu.\n";
            return false;
        }
    }
    else if (paymentMethod == "card")
    {
        std::string cardNumber;
        std::cout << "Wprowad� numer karty (16 cyfr): ";
        std::cin >> cardNumber;
        if (cardNumber.length() == 16)
        {
            std::cout << "P�atno�� kart� zaakceptowana.\n";
            return true;
        }
        else
        {
            std::cout << "B��dny numer karty.\n";
            return false;
        }
    }
    return false;
}
