using sysbus

mach create "${CAR}"
include @cars/${CAR}/board.resc

# machine StartGdbServer 3333
start
