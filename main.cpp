#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <csignal>
#include <sys/stat.h>

#include "led.h"

//#define DEBUG_MODE

using namespace std;


const char *LedCommandPipeName = "/tmp/led_command";
const char *LedStatePipeName = "/tmp/led_state";

ifstream ledCommandPipe;
ofstream ledStatePipe;

Led *led = NULL;

static bool s_interrupted = false;

static void s_signal_handler(int signal_value)
{
    s_interrupted = true;
    cout << "[SYS] STOP" << endl;

    if (led != NULL)
      delete led;

    exit(0);
}

static void s_catch_signals(void)
{
    struct sigaction action;
    action.sa_handler = s_signal_handler;
    action.sa_flags = 0;
    sigemptyset (&action.sa_mask);
    sigaction (SIGINT, &action, NULL);
    sigaction (SIGTERM, &action, NULL);
}

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
  cout << "[SYS] Preparing server..." << endl;

  s_catch_signals();

  if (!create_fifo()) {
    cerr << "[SYS] Can't create FIFO. Check if another example of server already running." << endl;
    return 1;
  }

  led = new Led();

  while (true)
  {
    if (s_interrupted)
      break;

    cout << "[SYS] Ready for commands." << endl;

    ledCommandPipe.open(LedCommandPipeName);
    ledStatePipe.open(LedStatePipeName);

    string line;

    while (true)
    {
      getline(ledCommandPipe, line);

      if (ledCommandPipe.eof()) {
        cout << "[SYS] FIFO closed. Restart." << endl;
        break;
      }
      else {
        stringstream stream(line);
        string cmd, arg;
        stream >> cmd >> arg;
        string commandState = performCommand(led, cmd, arg).info();
  #ifdef DEBUG_MODE
        cout << "[CMD] \"" << cmd << "\": \"" << arg << "\"" << endl;
        cout << commandState << endl;
  #endif
        ledStatePipe << commandState << endl;
      }
    }

    ledCommandPipe.close();
    ledStatePipe.close();
  }

  cout << "[SYS] Server shutdown." << endl;
  ledCommandPipe.close();
  ledStatePipe.close();
  unlink(LedCommandPipeName);
  unlink(LedStatePipeName);

  if (led != NULL)
    delete led;

  return 0;
}
