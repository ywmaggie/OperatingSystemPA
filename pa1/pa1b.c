/* Programming Assignment 1: Exercise B
 *
 * Now we will expand the program of Exercise A to call Fork () multiple times.
 * Run the program below and answer the following questions:
 *
 * 1. Can you explain the order of what gets printed based on the code?
 *
 * 2. Why does the first child execute before the second child?
 *
 * 3. Move the two print statements executed by the parent to just after
 * where it says HERE.  How can you print the pid of the first child?
 *
 */

#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main ()
{
	int pid = 0;
    int a ;

	if ((pid = Fork ()) == 0) {

		/* first child executes here */

		Printf ("I am the first child, my pid is %d\n", Getpid ());
		Exit ();
	}
    a = pid;

	if ((pid = Fork ()) == 0) {

		/* second child executes here */

		Printf ("I am the second child, my pid is %d\n", Getpid ());
		Exit ();
	}
    
	/* HERE */
    Printf ("I am the parent, my pid is %d\n", Getpid ());
	Printf ("I just created a child process whose pid is %d\n", a);
    


	Printf ("I (the parent) just created a second child process whose pid is %d\n", pid);
}
