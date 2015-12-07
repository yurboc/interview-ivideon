#ifndef CMDRESULT_H
#define CMDRESULT_H

#include <string>

using namespace std;

class CmdResult
{
  public:

    enum ResultType {
      ResultOk,
      ResultFailed
    };

    CmdResult(ResultType res, const string& info = "");
    virtual ~CmdResult();
    string info() const;
    bool isSuccess() const;

  private:
    ResultType m_res;
    string m_info;
};

#endif // CMDRESULT_H
