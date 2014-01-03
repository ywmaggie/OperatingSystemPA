/**
 * Simple PA4 test to try and make sure threads are spawning and
 * switching as intended.
 *
 * Created by: Jeffrey Schnell
 * Created on: March 14, 2012
 *
 * Modified by: Benjamin Lei
 * Modified on: November 19, 2012
 *
 * Modified by: Vijay Venkataraman
 * Modified on: November 18, 2013
 */

#include "aux.h"
#include "umix.h"
#include "mythreads.h"
#include "string.h"

/** At what fib step should threads stop spawning */
#define SPAWN_STOP 50

/** What thread to call after every step */
#define NEXT_OFFSET 1

/** Variables to keep track of in tests */
static int f, f1, f2, next;

/** pointer to functions so I'll only need one type of func call */
static void (*init)();
static int (*spawn)();
static int (*yield)(int);
static int (*get)();
static void (*exitThread)();

/** Prototyped functions to call */
void CalcFib ();
void StartFib ();

/**
 * Runs a fibonacci sequence in a specific order
 * arg 1: int, the number of arguments
 * arg 2: char**, the arguments passed in
 */
void Main (argc, argv)
int argc;
char** argv;
{
    if (argc != 2) {
        Printf ("Not enough arguments\n");
        return;
    }
    
    if (strncmp(argv[1], "mine", 5) == 0) { // set vars using own funcs
        init = &MyInitThreads;
        spawn = &MySpawnThread;
        yield = &MyYieldThread;
        get = &MyGetThread;
        exitThread = &MyExitThread;
    } else if (strncmp(argv[1], "ref", 4) == 0) { // else use ref funcs
        init = &InitThreads;
        spawn = &SpawnThread;
        yield = &YieldThread;
        get = &GetThread;
        exitThread = &ExitThread;
    } else {
        Printf ("Only arguments accepted are 'mine' or 'ref'\n");
        return;
    }
    
    f1 = 0;
    f2 = 1;
    f = 0;
    next = NEXT_OFFSET;
    
    init ();
    Printf ("Th\tFib : #\n");
    
    for (int i = 0; i < MAXTHREADS; i++)
    {
        spawn (StartFib);
    }
    
    yield (next);
    exitThread ();
}

/**
 * Starts the fibonacci sequence
 */
void StartFib ()
{
    next = (next + NEXT_OFFSET) % MAXTHREADS;
    yield (next+4);
    spawn (CalcFib);
}

/**
 * Calculates the fib for current step, then attempts to start another
 * fib step.
 */
void CalcFib ()
{
    Printf ("%d\t%3d : %d\n", get(), ++f, f1);
    f2 = f1 + f2;
    f1 = f2 - f1;
    
    if (f < SPAWN_STOP) {
        spawn (CalcFib);
    }
}
