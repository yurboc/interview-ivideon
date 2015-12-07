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


const char *fifoFileName = "/tmp/led_fifo";
const char *fifoStateFileName = "/tmp/state_fifo";

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
  int ledFifo = mkfifo(fifoFileName, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
  int stateFifo = mkfifo(fifoStateFileName, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
  if (ledFifo != 0) {
    cerr << "[SYS] Can't create FIFO. Check if another example of server already running." << endl;
    cerr << "[SYS] If another server is not running perform 'rm " << fifoFileName << "' from console." << endl;
    return 1;
  }
  if (stateFifo != 0) {
    cerr << "[SYS] Can't create state FIFO. Check if another example of server already running." << endl;
    cerr << "[SYS] If another server is not running perform 'rm " << fifoStateFileName << "' from console." << endl;
    return 1;
  }

  cout << "[SYS] Ready for commands." << endl;
  ifstream fifo(fifoFileName);
  ofstream ledState(fifoStateFileName);
  string line;
  while (true)
  {
    getline(fifo, line);
    if (fifo.eof()) {
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
      ledState << commandState << endl;
    }
  }

  cout << "[SYS] Server shutdown." << endl;
  fifo.close();
  unlink(fifoFileName);
  unlink(fifoStateFileName);
  return 0;
}
