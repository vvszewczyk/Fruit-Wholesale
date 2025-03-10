#pragma once
#ifndef PAYMENT_H
#define PAYMENT_H
#include "Order.h"
#include <string>

class Payment
{
  public:
    static bool processPayment(Order &o, const std::string &paymentMethod);
};

#endif
