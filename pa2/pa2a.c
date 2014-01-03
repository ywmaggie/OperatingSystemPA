/* Programming Assignment 2: Exercise A (last modified 10/18/09)
 *
 * In this first set of exercises, you will study a simple program that
 * starts three processes, each of which prints characters at certain rates.
 * This program will form the basis for experimenting with scheduling
 * policies, the main subject for this programming assignment.
 *
 * The procedure SlowPrintf (n, format, ...) is similar to Printf, but
 * takes a "delay" parameter that specifies how much delay there should
 * be between the printing of EACH character.  An increase in n by 1 unit
 * represents an increase in delay by roughly a factor of 10.
 *
 * Run the program below.  Notice the speed at which the printing occurs.
 * Also notice the order in which the processes execute.  The current
 * scheduler (which you will modify in other exercises) simply selects
 * processes in the order they appear in the process table.
 *
 *
 * Exercises
 *
 * 1. Modify the delay parameters so that process 1 prints with delay 8
 * (more than process 2), and process 3 prints with delay 6 (less than
 * process 2).  Notice the speed and order of execution.
 *
 * 2. Try other delay values and take note of speeds and orders of execution.
 * What are the smallest and largest values, and what are their effects?
 * 0~9
 * 0:0ms 1:0ms 2:0ms 3:0ms 4:30ms 5:240ms 6:2600ms 7:24030ms 8:0ms 9:77170ms
 * 3.1:10ms 3.5:0ms 3.05:10ms 3.2,3.3:0ms
 *
 * 3. Now repeat steps 1 and 2, but this time MEASURE your program using
 * the Gettime () system call, which returns the current system time
 * in milliseconds.  To compute the elapsed time, record the current time
 * immediately before the activity you want to measure (e.g., SlowPrintf)
 * and immediately after, and then take the difference of the former from
 * the latter:
 *
 *	int t1, t2;
 *
 *	t1 = Gettime ();
 *	SlowPrintf (7, "How long does this take?");
 *	t2 = Gettime ();
 *
 *	Printf ("Elapsed time = %d msecs\n", t2 - t1);
 *
 * Do the times you measure correspond to the observations you made in
 * steps 1 and 2?  What is the resolution of Gettime () (i.e., what
 * is the smallest unit of change)?  Note that this is different from
 * Gettime ()'s return value units, which are milliseconds.
 */

#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main ()
{
    /*int t1,t2,t3,t4,t5,t6;
	if (Fork () == 0) {
        SlowPrintf (3.05, "3.05 How long does this take?");
		Exit ();
	}

	if (Fork () == 0) {
        SlowPrintf (3.2, "3.2 How long does this take?");
		Exit ();
	}
    SlowPrintf (3.3, "3.3 How long does this take?");
    Exit ();*/
    
    /*int i;
    
    if (Fork () == 0) {
        i = RequestCPUrate (5, 10);
        Printf("%d",i);
		Exit ();
	}
    
	if (Fork () == 0) {
		i = RequestCPUrate (5, 10);
        Printf("%d",i);
		Exit ();
	}
	i = RequestCPUrate (5, 10);
	Printf("%d",i);
    SlowPrintf (7, "777777777777777");
	Exit ();*/
    /*if (Fork()==0) {
        Printf("pid:%d\n",Getpid());
        if (Fork()==0) {
            Printf("pid:%d\n",Getpid());
            if (Fork()==0) {
                Printf("pid:%d\n",Getpid());
                if (Fork()==0) {
                    Printf("pid:%d\n",Getpid());
                    if (Fork()==0) {
                        Printf("pid:%d\n",Getpid());
                        if (Fork()==0) {
                            Printf("pid:%d\n",Getpid());
                            if (Fork()==0) {
                                Printf("pid:%d\n",Getpid());
                                if (Fork()==0) {
                                    Printf("pid:%d\n",Getpid());
                                    if (Fork()==0) {
                                        Printf("pid:%d\n",Getpid());
                                        if (Fork()==0) {
                                            Printf("pid:%d\n",Getpid());
                                            if (Fork()==0) {
                                                Printf("pid:%d\n",Getpid());
                                                SlowPrintf(7,"11");
                                            }
                                            SlowPrintf(7,"22");
                                        }
                                        SlowPrintf(7,"33");
                                    }
                                    SlowPrintf(7,"44");
                                }
                                SlowPrintf(7,"55");
                            }
                            SlowPrintf(7,"66");
                        }
                        SlowPrintf(7,"77");
                    }
                    SlowPrintf(7,"88");
                }
                SlowPrintf(7,"99");
            }
            SlowPrintf(7,"00");
            
        }
        
    }
    if (Fork()==0) {
        Printf("pid:%d\n",Getpid());
        SlowPrintf(7,"1111111");
    }
    if (Fork()==0) {
        Printf("pid:%d\n",Getpid());
        SlowPrintf(7,"1111111");
    }
    if (Fork()==0) {
        Printf("pid:%d\n",Getpid());
        SlowPrintf(7,"1111111");
    }
    if (Fork()==0) {
        Printf("pid:%d\n",Getpid());
        SlowPrintf(7,"1111111");
    }
    if (Fork()==0) {
        Printf("pid:%d\n",Getpid());
        SlowPrintf(7,"1111111");
    }*/
    Fork();
    Fork();
    Fork();
    Fork();
    Fork();
    Fork();
    Fork();
    Fork();
    Fork();
    Fork();
    Fork();
    Fork();
    Fork();

    
    
    Exit();
}
