#include <stdio.h>
#include "aux.h"
#include "umix.h"


void Main ()
{
    int yieldID;
    if ((yieldID=Fork ()) == 0) {
        if (Fork () == 0) {
            Yield (yieldID);
            /* Process 4 */
            SlowPrintf (7, "444444444444444444");
            Exit ();
        }
        /* Process 2 */
        Yield(1);
        SlowPrintf (7, "222222222222222222");
        Exit ();
    }
 
    if ((yieldID = Fork ()) == 0) {
        /* Process 3 */
        Yield(1);
        Yield (2);
        SlowPrintf (7, "333333333333333333");
        Exit ();
    }
 
    /* Process 1 */
    Yield (yieldID);
    SlowPrintf (7, "111111111111111111");
    Exit ();
}