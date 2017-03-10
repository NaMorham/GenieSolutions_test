--- Readme ---

* Building

1. Unzip the files
2. Create and enter a new directory for the build
  $ mkdir build_gcc
  $ cd build_gcc
3. Run cmake
  $ cmake ..
4. Build the project...
  4.1. Linux
    $ make
    $ sudo make install
  4.2. Windows
    * Open the generated solution file in Visual Studio
    * build the genie_robot project
    
* Usage

 When the application is run on it's own it goes into interactive mode. and
will accept commands from stdin.  The application can also be run in scripted
mode (added to simplify system tests) by providing the flag -c and the
commands, quoted and separated with simicolons.

* Commands
 Commands are not case sensitive.

 PLACE <xpos> <ypos> <direction>    Place the robot on the board
 REPORT                             Display the position and facing
 MOVE                               Move the robot if possible
 LEFT                               Turn left
 RIGHT                              Turn right
 QUIT                               Quit!

* Testing
 I have only run this on Linux for now.  The system tests use the python cram
test suite.  These tests require the generated executable to be available on
the system path.

1. Run the test files one by one using the command;
  $ cram -v <testname>.t
2. Run all the tests
  $ cram -v *.t

Which will produce a result similar to;

$ cram -v *.t
back_to_start.t: passed
no_commands.t: passed
place_and_move.t: passed
place_move_turn.t: passed
place_only.t: passed
# Ran 5 tests, 0 skipped, 0 failed.
