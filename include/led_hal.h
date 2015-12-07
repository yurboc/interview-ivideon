#ifndef LEDHAL_H
#define LEDHAL_H

#include <string>

using namespace std;

class LedHal
{
  public:
    LedHal();
    virtual ~LedHal();

    void storeValue(const string& param, const string& value);
};

#endif // LEDHAL_H
