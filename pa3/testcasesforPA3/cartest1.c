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
    driveRoad (2, WEST, 10);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (3, WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (4, WEST, 30);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (5, WEST, 40);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (6, WEST, 50);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (7, WEST, 60);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (8, WEST, 70);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (9, WEST, 80);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (10, WEST, 90);
    Exit ();
  }

  driveRoad (1, WEST, 5);

  Exit ();
}

