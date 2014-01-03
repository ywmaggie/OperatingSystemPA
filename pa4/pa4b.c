/* Programming Assignment 4: Exercise B
 *
 * We will now begin studying a simple user-level thread package.  You are
 * given the file mythreads.c, which contains a rudimentary threads package
 * that will only work for two threads.  It contains the following functions:
 *
 * MyInitThreads (): initializes the thread package.  Must be the first
 * function called by any user program that uses the thread package.
 *
 * MySpawnThread (func, param): spawns a new thread to execute func (param),
 * where func is a function with no return value and param is an integer
 * parameter.  However, the new thread does not begin executing until
 * another thread yields to it.
 *
 * MyYieldThread (t): causes the running thread to yield to thread t. Should
 * return the ID (integer identifier) of the thread that yielded to the
 * thread being given control, i.e., the one returning from its call to
 * MyYieldThread.  More on this below.
 *
 * MyGetThread (): returns the ID of the currently running thread.
 *
 * MySchedThread (): causes the running thread to simply give up the CPU and
 * allow another thread to be scheduled.  Selecting which thread to run is
 * determined in this procedure.  Note that the same thread may be chosen
 * (as will be the case if there are no other threads).
 *
 * MyExitThread () causes the currently running thread to exit.
 *
 * Let us study MySpawnThread and MyYieldThread, both of which contain some
 * preliminary code that you may use.  (Note that for the next part, you will
 * need to change some of this code in a significant way.  If you develop a
 * good understanding of how this preliminary code works, it will help you
 * immensely.)
 *
 * First, there is a very simple thread management table, thread[].  You
 * may add fields as needed.  The only existing field is to save a thread's
 * context (filled by setjmp, and later used by longjmp).
 *
 * Next, MySpawnThread (func, param) is what does the bulk of the work.
 * It first calls setjmp (thread[0].env), which saves the context of
 * thread 0.  Thread 0 already exists by default; it is the "Main" thread.
 * Hence it will be creating a new thread, thread 1 (thread IDs range
 * from 0 to MAXTHREADS-1, where MAXTHREADS is defined in mythreads.h).
 *
 * Each thread requires its own stack.  Here is perhaps the most interesting
 * part of the code, where we simply use the current stack (for this single
 * Umix process, which is currently being used by thread 0), and so there is
 * no need to actually allocate space.  However, to ensure that thread 0's
 * stack may grow and not bump into thread 1's stack, the top of the stack
 * is effectively extended automatically by declaring a local variable s[]
 * (a large "dummy" array, which is never actually used).
 *
 * Two additional automatic local variables are declared, f and p.  These
 * are used to store the passed parameters func and param, but note that
 * f and p are near the top of the stack whereas func and param are somewhere
 * below the "cushion" provided by s[].  The importance of this will become
 * more evident.
 *
 * Next, a check is made to ensure that the stack was indeed extended.
 * It may happen that an optimizing compiler will notice that s[] is not
 * being used, and therefore gets automatically removed.  Here, just by
 * referencing it in the conditional statement would avoid this problem.
 * But if this conditional were removed, the compiler would like remove
 * s[] also.  You should try developing an experiment to see if this
 * would happen, by testing the address of, say, p, with and without
 * the conditional.  Its address should not change, but if it does, it
 * would indicate the absence of s[] (especially if the address changed
 * by the size of s[], i.e., STACKSIZE).
 *
 * Now that the stack is properly set up, the bulk of the work that needs
 * to be done by MySpawnThread (func, param) is complete.  Thread 1 is
 * ready to run and execute func (param), but MySpawnThread stops short
 * of actually doing this at this point in the code.  Since this is the
 * point where we want thread 1 to begin executing whenever thread 0
 * yields to it in the future, the context is saved by calling setjmp,
 * this time supplying thread[1].env as a parameter.  Since a 0 is returned
 * the first time setjmp returns, the call to longjmp (thread[0].env, 1)
 * occurs.  Later, when longjmp (thread[1].env, 1) is called, thread 1
 * again return from this setjmp, but this time since the returned value
 * is 1, the body of the conditional does not execute.  Indeed, what
 * Thread 1 will do is execute func (param), as given by f and p.
 *
 * But what happens during the first return from setjmp, when a call is
 * made to longjmp (thread[0].env, 1)?  The last saved context for Thread
 * 0 was at the very beginning of the body of MySpawnThread, where
 * setjmp (thread[0].env) was called.  This now returns for a second
 * time, with a return value of 1 (the second parameter of longjmp), and
 * so the body of the conditional is skipped, and MySpawnThread returns.
 * Thread 0 has now successfully spawned Thread 1, and can now yield to
 * it.
 *
 * This brings us to MyYieldThread (t).  Here, the context of the calling
 * thread is saved.  Note that the code is currently hard-wired to work
 * with only two threads whose IDs must be 0 and 1.  So when Thread 0
 * calls MyYieldThread (1), then 1-t = 0 and so Thread 0's context is
 * saved in the call to setjmp (thread[1-t].env).  Since the return value
 * is 0, longjmp (thread[t].env, 1) is called.  And where does Thread 1
 * begin executing from?  Answer: wherever its context was last saved.
 * Finally, if MyYieldThread (0) is called by Thread 1, notice that the
 * roles are reversed.
 *
 * The problems with this code are twofold.  First, it assumes there are
 * only two threads.  Second, it assumes the calling thread always yields
 * to the other (when in fact, we must allow for the possibility that a
 * thread might yield to itself).  Hence, these issues need to be addressed.
 *
 * The code below is a simple program that creates two threads, Thread 0
 * which is created by default and Thread 1 which is created by
 * MySpawnThread.  Control is then passed back and forth by calls to
 * MyYieldThread.  Study this program carefully, and make sure you
 * understand how it interacts with the code in mythreads.c  Experiment
 * with it extensively.  (In fact, it is a good idea to make a copy so
 * that you can modify it at will and always retrieve a clean version.)
 *
 * Here are some things to try:
 *
 * 1. Try removing the dummy array s[STACKSIZE].  What happens to the
 * program's behavior?  Try difference sizes for STACKSIZE.
 *
 * 2. Try removing the automatic local variables f and p, and replace
 * the call to (*f) (p) with (*func) (param).  What happens to the
 * program's behavior?
 *
 * 3. How would you generalize the code for MyYieldThread (t)?
 * Implement your solution so that the program below continues to work
 * properly.  Make sure your code allows a thread to yield to itself.
 */

#include "aux.h"
#include "umix.h"
#include "mythreads.h"

#define NUMYIELDS	5

static int square;		/* global variable, shared by threads */

void Main ()
{
	int i, t;
	void printSquares ();

	MyInitThreads ();	/* Initialize, must be called first */

	MySpawnThread (printSquares, 0);

	for (i = 0; i < NUMYIELDS; i++) {
		MyYieldThread (1);
		Printf ("T0: square = %d\n", square);
	}

	MyExitThread ();
}

void printSquares (t)
	int t;				/* thread to yield to */
{
	int i;

	for (i = 0; i < NUMYIELDS; i++) {
		square = i * i;
		Printf ("T1: %d squared = %d\n", i, square);
		MyYieldThread (0);
	}
}
