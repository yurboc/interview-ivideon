#include "led_int_param.h"

LedIntParam::LedIntParam(int minVal, int maxVal):
    m_min(minVal), m_max(maxVal), m_valid(false), m_value(0)
{
  //ctor
}

LedIntParam::~LedIntParam()
{
  //dtor
}

bool LedIntParam::writeValue(int value)
{
  if (value < m_min || value > m_max)
    return false;
  m_value = value;
  m_valid = true;
  return true;
}

bool LedIntParam::readValue(int* value)
{
  if (!m_valid)
    return false;
  if (value != NULL)
    *value = m_value;
  return true;
}

bool LedIntParam::isValid()
{
  return m_valid;
}
