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
    driveRoad (WEST, 10);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 20);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 30);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 40);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 50);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 60);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 70);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 80);
    Exit ();
  }

  if (Fork () == 0) {
    Delay (0);
    driveRoad (WEST, 90);
    Exit ();
  }

  driveRoad (WEST, 5);

  Exit ();
}

