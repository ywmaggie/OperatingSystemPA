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
    driveRoad (2, EAST, 10);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (3, WEST, 80);
    Exit ();
  }

  driveRoad (1, WEST, 5);

  Exit ();
}

