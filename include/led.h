#ifndef LED_H
#define LED_H

#include "led_hal.h"

#include "led_str_param.h"
#include "led_int_param.h"
#include "led_types.h"
#include "cmdresult.h"


class Led
{
  public:
    Led();
    virtual ~Led();

    bool isConfigured();

    CmdResult setState(const string& state);
    CmdResult setColor(const string& color);
    CmdResult setRate(const string& rate);

    CmdResult getState();
    CmdResult getColor();
    CmdResult getRate();

  private:
    LedHal m_ledHal;

    LedState m_ledState;
    LedColor m_ledColor;
    LedRate m_ledRate;
};

#endif // LED_H
