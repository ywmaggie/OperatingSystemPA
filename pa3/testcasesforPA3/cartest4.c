#include <stdio.h>
#include "aux.h"
#include "umix.h"


void InitRoad ();
void driveRoad (int c, int from, int mph);

void Main ()
{
  InitRoad ();

  if (Fork () == 0) {
    Delay (0);
    driveRoad (2, WEST, 50);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (100);
    driveRoad (3, EAST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (100);
    driveRoad (4, EAST, 20);
    Exit ();
  }

  driveRoad (1, WEST, 1);

  Exit ();
}

