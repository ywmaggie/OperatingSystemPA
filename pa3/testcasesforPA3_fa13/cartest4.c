#include <stdio.h>
#include "aux.h"
#include "umix.h"


void InitRoad ();
void driveRoad (int from, int mph);

void Main ()
{
  InitRoad ();

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 50);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (100);
    driveRoad (EAST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (100);
    driveRoad (EAST, 20);
    Exit ();
  }

  driveRoad (WEST, 1);

  Exit ();
}

