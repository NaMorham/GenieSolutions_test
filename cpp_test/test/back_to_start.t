  $ genie_robot -c "place 0 0 e;move;move;report;left;move;report;left;move;left;move;report;right;move;right;report"
  ! Generate test field for robot [5, 5]
  ! Run as a script: [place 0 0 e;move;move;report;left;move;report;left;move;left;move;report;right;move;right;report]
  ! Process [16] commands.
  : place 0 0 e
  : move
  : move
  : report
  2,0,EAST
  : left
  : move
  : report
  2,1,NORTH
  : left
  : move
  : left
  : move
  : report
  1,0,SOUTH
  : right
  : move
  : right
  : report
  0,0,NORTH

  $ genie_robot -c "place 0 0 e;move;move;report;left;move;report;left;move;left;move;report;right;move;right;report" 2> /dev/null
  : place 0 0 e
  : move
  : move
  : report
  2,0,EAST
  : left
  : move
  : report
  2,1,NORTH
  : left
  : move
  : left
  : move
  : report
  1,0,SOUTH
  : right
  : move
  : right
  : report
  0,0,NORTH

