#include <stdio.h>
#include "aux.h"
#include "umix.h"


void InitRoad ();
void driveRoad (int from, int mph);

void Main ()
{
  int i;

  InitRoad ();

  driveRoad (WEST, 50);

  for (i=0; i<5; i++) {

    if (Fork () == 0) {
      Delay (0);
      driveRoad (WEST, 50);
      Exit ();
    }
  
    if (Fork () == 0) {
      Delay (0);
      driveRoad (WEST, 50);
      Exit ();
    }
    
    if (Fork () == 0) {
      Delay (0);
      driveRoad (WEST, 50);
      Exit ();
    }

    if (Fork () == 0) {
      Delay (0);
      driveRoad (EAST, 50);
      Exit ();
    }
  
    if (Fork () == 0) {
      Delay (0);
      driveRoad (EAST, 50);
      Exit ();
    }
    
    if (Fork () == 0) {
      Delay (0);
      driveRoad (EAST, 50);
      Exit ();
    }
    
    Delay(4000);
  }

  Exit ();
}

