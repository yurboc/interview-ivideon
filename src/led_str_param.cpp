#include "led_str_param.h"


LedStrParam::LedStrParam(const vector<string>& validValues):
    m_validValues(validValues), m_valid(false), m_value("")
{
  //ctor
}

LedStrParam::~LedStrParam()
{
  //dtor
}

bool LedStrParam::writeValue(const string& value)
{
  for (unsigned id = 0; id < m_validValues.size(); ++id) {
    if (value == m_validValues[id]) {
      m_value = value;
      m_valid = true;
      return true;
    }
  }
  return false;
}

bool LedStrParam::readValue(string* value) const
{
  if (!m_valid)
    return false;
  if (value != NULL)
    *value = m_value;
  return true;
}

bool LedStrParam::isValid() const
{
  return m_valid;
}
