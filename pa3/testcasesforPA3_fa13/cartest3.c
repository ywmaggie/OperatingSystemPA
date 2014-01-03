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
    driveRoad (WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1000);
    driveRoad (WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1020);
    driveRoad (WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1040);
    driveRoad (WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1000);
    driveRoad (EAST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1020);
    driveRoad (EAST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1040);
    driveRoad (EAST, 20);
    Exit ();
  }

  driveRoad (WEST, 20);

  Exit ();
}

