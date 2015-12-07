#include "led_hal.h"

#include <iostream>

LedHal::LedHal()
{
  cout << "[LED] INITIALIZATION" << endl;
}

LedHal::~LedHal()
{
  cout << "[LED] FINALIZATION" << endl;
}

void LedHal::storeValue(const string& param, const string& value)
{
  cout << "[LED] " << param << " = " << value << endl;
}
