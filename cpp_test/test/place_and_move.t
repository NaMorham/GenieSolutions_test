  $ genie_robot -c "place 0 0 n;report;move;report"
  ! Generate test field for robot [5, 5]
  ! Run as a script: [place 0 0 n;report;move;report]
  ! Process [4] commands.
  : place 0 0 n
  : report
  0,0,NORTH
  : move
  : report
  0,1,NORTH

  $ genie_robot -c "place 0 0 n;report;move;report" 2> /dev/null
  : place 0 0 n
  : report
  0,0,NORTH
  : move
  : report
  0,1,NORTH
