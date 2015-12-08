#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <sys/stat.h>

#include "led.h"

//#define DEBUG_MODE

using namespace std;


const char *LedCommandPipeName = "/tmp/led_command";
const char *LedStatePipeName = "/tmp/led_state";

static bool create_fifo()
{
  if (mkfifo(LedCommandPipeName, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH) != 0)
    return false;

  if (mkfifo(LedStatePipeName, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH) != 0)
    return false;

  return true;
}

CmdResult performCommand(Led *led, const string& cmd, const string& arg)
{
  CmdResult res = CmdResult(CmdResult::ResultFailed);

  if (led == NULL)
    return res;

  if (cmd == "set-led-state") res = led->setState(arg);
  if (cmd == "set-led-color") res = led->setColor(arg);
  if (cmd == "set-led-rate")  res = led->setRate(arg);
  if (cmd == "get-led-state") res = led->getState();
  if (cmd == "get-led-color") res = led->getColor();
  if (cmd == "get-led-rate")  res = led->getRate();

  return res;
}

int main()
{
  Led led;

  cout << "[SYS] Preparing server..." << endl;

  if (!create_fifo()) {
    cerr << "[SYS] Can't create FIFO. Check if another example of server already running." << endl;
    return 1;
  }

  cout << "[SYS] Ready for commands." << endl;
  ifstream ledCommandPipe(LedCommandPipeName);
  ofstream ledStatePipe(LedStatePipeName);
  string line;
  while (true)
  {
    getline(ledCommandPipe, line);
    if (ledCommandPipe.eof()) {
      cout << "[SYS] FIFO closed. Stop." << endl;
      break;
    }
    else {
      stringstream stream(line);
      string cmd, arg;
      stream >> cmd >> arg;
      string commandState = performCommand(&led, cmd, arg).info();
#ifdef DEBUG_MODE
      cout << "[CMD] \"" << cmd << "\": \"" << arg << "\"" << endl;
      cout << commandState << endl;
#endif
      ledStatePipe << commandState << endl;
    }
  }

  cout << "[SYS] Server shutdown." << endl;
  ledCommandPipe.close();
  ledStatePipe.close();
  unlink(LedCommandPipeName);
  unlink(LedStatePipeName);
  return 0;
}
