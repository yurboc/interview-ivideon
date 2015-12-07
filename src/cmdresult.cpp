#include "cmdresult.h"

CmdResult::CmdResult(ResultType res, const string& info)
{
  m_res = res;
  switch (res) {
    case ResultOk: m_info = "OK"; break;
    case ResultFailed: m_info = "FAILED"; break;
  }
  if (!info.empty())
    m_info += " " + info;
}

CmdResult::~CmdResult()
{
  //dtor
}

string CmdResult::info() const
{
  return m_info;
}

bool CmdResult::isSuccess() const
{
  return m_res == ResultOk;
}
