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
    driveRoad (2, WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1000);
    driveRoad (3, WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1020);
    driveRoad (4, WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1040);
    driveRoad (5, WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1000);
    driveRoad (6, EAST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1020);
    driveRoad (7, EAST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (1040);
    driveRoad (8, EAST, 20);
    Exit ();
  }

  driveRoad (1, WEST, 20);

  Exit ();
}

