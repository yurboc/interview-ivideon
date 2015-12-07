#include "led.h"

#include <stdexcept>

Led::Led()
{
  //ctor
}

Led::~Led()
{
  //dtor
}

bool Led::isConfigured()
{
  return m_ledColor.isValid() && m_ledRate.isValid();
}

CmdResult Led::setState(const string& state)
{
  if (!isConfigured() || !m_ledState.writeValue(state))
    return CmdResult(CmdResult::ResultFailed);
  m_ledHal.storeValue("state", state);
  return CmdResult(CmdResult::ResultOk);
}

CmdResult Led::setColor(const string& color)
{
  if (!m_ledColor.writeValue(color))
    return CmdResult(CmdResult::ResultFailed);
  m_ledHal.storeValue("color", color);
  return CmdResult(CmdResult::ResultOk);
}

CmdResult Led::setRate(const string& rate)
{
  int argInt = 0;
  try {
    argInt = stoi(rate);
  }
  catch (const std::invalid_argument& ia) {
    return CmdResult(CmdResult::ResultFailed);
  }
  if (!m_ledRate.writeValue(argInt))
    return CmdResult(CmdResult::ResultFailed);
  m_ledHal.storeValue("rate", to_string(argInt));
  return CmdResult(CmdResult::ResultOk);
}

CmdResult Led::getState()
{
  string value;
  if (!m_ledState.readValue(&value))
    return CmdResult(CmdResult::ResultFailed);
  return CmdResult(CmdResult::ResultOk, value);
}

CmdResult Led::getColor()
{
  string value;
  if (!m_ledColor.readValue(&value))
    return CmdResult(CmdResult::ResultFailed);
  return CmdResult(CmdResult::ResultOk, value);
}

CmdResult Led::getRate()
{
  int value;
  if (!m_ledRate.readValue(&value))
    return CmdResult(CmdResult::ResultFailed);
  return CmdResult(CmdResult::ResultOk, to_string(value));
}
