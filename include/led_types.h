#ifndef LED_TYPES_H
#define LED_TYPES_H

class LedColor: public LedStrParam
{
  public:
    LedColor() : LedStrParam({"red", "green", "blue"}) {}
};

class LedState: public LedStrParam
{
  public:
    LedState() : LedStrParam({"off", "on"}) {}
};

class LedRate: public LedIntParam
{
  public:
    LedRate() : LedIntParam(0, 5) {}
};

#endif // LED_TYPES_H
