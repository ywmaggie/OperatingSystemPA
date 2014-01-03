#include <stdio.h>
#include "aux.h"
#include "umix.h"


void InitRoad ();
void driveRoad (int c, int from, int mph);

void Main ()
{
  int i;

  InitRoad ();

  driveRoad (1, WEST, 50);

  for (i=0; i<5; i++) {

    if (Fork () == 0) {
      Delay (0);
      driveRoad ((i*3)+2, WEST, 50);
      Exit ();
    }
  
    if (Fork () == 0) {
      Delay (0);
      driveRoad ((i*3)+3, WEST, 50);
      Exit ();
    }
    
    if (Fork () == 0) {
      Delay (0);
      driveRoad ((i*3)+4, WEST, 50);
      Exit ();
    }

    if (Fork () == 0) {
      Delay (0);
      driveRoad (100+(i*3)+2, EAST, 50);
      Exit ();
    }
  
    if (Fork () == 0) {
      Delay (0);
      driveRoad (100+(i*3)+3, EAST, 50);
      Exit ();
    }
    
    if (Fork () == 0) {
      Delay (0);
      driveRoad (100+(i*3)+4, EAST, 50);
      Exit ();
    }
    
    Delay(4000);
  }

  Exit ();
}

