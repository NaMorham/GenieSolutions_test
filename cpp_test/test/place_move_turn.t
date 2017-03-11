  $ genie_robot -c "place 0 0 e;move;move;report;left;move;report"
  ! Generate test field for robot [5, 5]
  ! Run as a script: [place 0 0 e;move;move;report;left;move;report]
  ! Process [7] commands.
  : place 0 0 e
  : move
  : move
  : report
  2,0,EAST
  : left
  : move
  : report
  2,1,NORTH

  $ genie_robot -c "place 0 0 e;move;move;report;left;move;report" 2> /dev/null
  : place 0 0 e
  : move
  : move
  : report
  2,0,EAST
  : left
  : move
  : report
  2,1,NORTH
