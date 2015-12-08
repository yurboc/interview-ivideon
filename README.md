# Ivideon interview
From 01.12.2015 17:35

Task requirements see in [PDF](doc/requirements.pdf)

Compilation
----------

- Install build tools and git:
```
$ sudo apt-get install build-essential git
```
- Clone this repository:
```
$ git clone https://github.com/yurboc/Ivideon_interview
```
- Run make:
```
$ cd Ivideon_interview
$ make release
```
- Start server:
```
$ cd bin/Release
$ ./LedCtrl
```
- From another Terminal start client:
```
$ cd Ivideon_interview
$ ./control.sh
```

Usage
----------
In client you will see a menu:
```
+=========================+
|   LED controller v1.0   |
+=========================+

Main Menu
1) Set State  3) Set Color  5) Set Rate	  7) Quit
2) Get State  4) Get Color  6) Get Rate
Pick an option: 
```
At first, the LED should be initialized. Select "3" (Set Color) and then "2" (Green):
```
Main Menu
1) Set State  3) Set Color  5) Set Rate	  7) Quit
2) Get State  4) Get Color  6) Get Rate
Pick an option: 3
1) Red
2) Green
3) Blue
Pick an option: 2

------------------------------
Command done
------------------------------
```
At this moment LED server show fake "hardware" command:
```
[LED] color = green
```
Next step is set rate ("5" in Main Menu) and then state ("1" in Main Menu).
When LED initialized (by color, rate and state) you can read its state:
```
1) Set State  3) Set Color  5) Set Rate	  7) Quit
2) Get State  4) Get Color  6) Get Rate
Pick an option: 2

------------------------------
LED state is on
------------------------------

1) Set State  3) Set Color  5) Set Rate	  7) Quit
2) Get State  4) Get Color  6) Get Rate
Pick an option: 4

------------------------------
LED color is green
------------------------------

1) Set State  3) Set Color  5) Set Rate	  7) Quit
2) Get State  4) Get Color  6) Get Rate
Pick an option: 6

------------------------------
LED rate is 4
------------------------------
```
To close client and stop server select "7" in Main Menu:
```
1) Set State  3) Set Color  5) Set Rate	  7) Quit
2) Get State  4) Get Color  6) Get Rate
Pick an option: 7
Goodbye!
```

Limitations
----------
- Ctrl-C not handled by server properly (because 'open()' still blocked on exit(), need to reimplement this using non-blocking open() and select() with writing to stop_fd).
