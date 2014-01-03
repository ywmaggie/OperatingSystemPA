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
    driveRoad (EAST, 10);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 80);
    Exit ();
  }

  driveRoad (WEST, 5);

  Exit ();
}

