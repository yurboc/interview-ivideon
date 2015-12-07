#ifndef LEDSTRPARAM_H
#define LEDSTRPARAM_H

#include <unistd.h>
#include <vector>
#include <string>

using namespace std;

class LedStrParam
{
  public:
    LedStrParam(const vector<string>& validValues);
    virtual ~LedStrParam();

    bool writeValue(const string& value);
    bool readValue(string* value = NULL) const;
    bool isValid() const;

  private:
    const vector<string> m_validValues;
    bool m_valid;
    string m_value;
};


#endif // LEDSTRPARAM_H
