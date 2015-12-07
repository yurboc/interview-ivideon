#ifndef LEDINTPARAM_H
#define LEDINTPARAM_H

#include <unistd.h>

class LedIntParam
{
  public:
    LedIntParam(int minVal, int maxVal);
    virtual ~LedIntParam();

    bool writeValue(int value);
    bool readValue(int* value = NULL);
    bool isValid();

  private:
    const int m_min = 0;
    const int m_max = 0;
    bool m_valid;
    int m_value;
};

#endif // LEDINTPARAM_H
