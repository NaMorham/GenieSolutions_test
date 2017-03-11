  $ genie_robot -c "report;place 0 0 n;report"
  ! Generate test field for robot [5, 5]
  ! Run as a script: [report;place 0 0 n;report]
  ! Process [3] commands.
  : report
  ! Robot has not been placed yet.
  : place 0 0 n
  : report
  0,0,NORTH

  $ genie_robot -c "report;place 0 0 n;report" 2> /dev/null
  : report
  : place 0 0 n
  : report
  0,0,NORTH
