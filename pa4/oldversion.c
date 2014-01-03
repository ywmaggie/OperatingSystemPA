/*	User-level thread system
 *
 */

#include <setjmp.h>

#include "aux.h"
#include "umix.h"
#include "mythreads.h"
#include "string.h"

static int MyInitThreadsCalled = 0;	/* 1 if MyInitThreads called, else 0 */

static int CurrentThread = 0;
static int PrevThread;
int debug =1;

static struct thread {			/* thread table */
	int valid;			/* 1 if entry is valid, else 0 */
	jmp_buf env;			/* current context */
	jmp_buf env_clean;
	void (*func)();
	int param;
} thread[MAXTHREADS];

static struct queue{
	int valid;
	int prev;
	int next;
}queue[MAXTHREADS];

static int front = -1;
static int back = -1;
static int queuesize = 0;

void addFront(int n){
	queue[n].valid = 1;
	queue[n].prev = -1;
	queue[n].next = front;
	if(queuesize != 0) queue[front].prev = n;
	else back = n;
	front = n;
	queuesize ++;
}

void addBack(int n){
	queue[n].valid = 1;
	queue[n].prev = back;
	queue[n].next = -1;
	if(queuesize != 0) queue[back].next = n;
	else front = n;
	back = n;
	queuesize ++;
}

void deleteElement(int n){
	queue[n].valid = 0;
	if(front == n){
		front = queue[n].next;
		//Printf("front:%d\n",front);
		queue[front].prev = -1;
	}
	else if(back == n){
		back = queue[n].prev;
		queue[back].next = -1;
	}
	else{
		queue[queue[n].prev].next = queue[n].next;
		queue[queue[n].next].prev = queue[n].prev;
	}
	queuesize --;
}

#define STACKSIZE	65536		/* maximum size of thread stack */

/*	MyInitThreads () initializes the thread package.  Must be the first
 *	function called by any user program that uses the thread package.
 */

void MyInitThreads ()
{
	int i;
	int t;

	if (MyInitThreadsCalled) {                /* run only once */
		Printf ("InitThreads: should be called only once\n");
		Exit ();
	}

	for (i = 0; i < MAXTHREADS; i++) {	/* initialize thread table */
		thread[i].valid = 0;
		queue[i].valid = 0;
		queue[i].prev = -1;
		queue[i].next = -1;
	}

	thread[0].valid = 1;			/* initialize thread 0 */

	addFront(0);
	if(debug){
		Printf("Front: %d Back: %d prev: %d next: %d size: %d \n",front,back,queue[0].prev,queue[0].next,queuesize );
	}

	if (setjmp(thread[0].env_clean) != 0)
		{Printf ("End!\n");}
		if (setjmp(thread[0].env) == 0){
			for (i = 1; i <= MAXTHREADS; i ++){
				char s[i*STACKSIZE];
				setjmp(thread[i].env_clean);
				if ((t = setjmp(thread[i].env)) != 0){
					if(debug) Printf("longjmp %d\n",t);
					(*thread[t-1].func) (thread[t-1].param);
					MyExitThread();
				}
			}
		}
	MyInitThreadsCalled = 1;
}

/*	MySpawnThread (func, param) spawns a new thread to execute
 *	func (param), where func is a function with no return value and
 *	param is an integer parameter.  The new thread does not begin
 *	executing until another thread yields to it.
 */

int MySpawnThread (func, param)
	void (*func)();		/* function to be executed */
	int param;		/* integer parameter */
{
	int i;
	int t;

	if (! MyInitThreadsCalled) {
		Printf ("SpawnThread: Must call InitThreads first\n");
		Exit ();
	}

	static int CurrentPlace = 0;

	Printf("Enter Spawn!\n");
	while(thread[CurrentPlace].valid == 1){
		CurrentPlace = (CurrentPlace + 1) % MAXTHREADS; 
	}
	Printf("Exit while!\n CurrentPlace:%d\n",CurrentPlace);

	memcpy(thread[CurrentPlace].env, thread[CurrentPlace].env_clean, sizeof(thread[CurrentPlace].env_clean));
	Printf("END2\n");

	if((t = setjmp(thread[CurrentPlace].env)) != 0){
		if(debug) Printf("longjmp %d\n",t);
		(*thread[t-1].func) (thread[t-1].param);
		MyExitThread();
	}
		
		thread[CurrentPlace].valid = 1;
		thread[CurrentPlace].func = func;
		thread[CurrentPlace].param = param;

	if(debug) Printf("Success in spawn");
	if(debug){
		Printf("Front: %d Back: %d prev: %d next: %d size: %d \n",front,back,queue[0].prev,queue[0].next,queuesize );
	}
	addBack(CurrentPlace);
	if(debug){
		Printf("Sequence: ");
		for(i = front ; i != -1 ; i = queue[i].next){
			Printf ("%d ",i);
		}
		Printf("\n");
	}
	if(debug){
		Printf("Front: %d Back: %d prev: %d next: %d size: %d \n",front,back,queue[0].prev,queue[0].next,queuesize );
	}

	return CurrentPlace;

}

/*	MyYieldThread (t) causes the running thread to yield to thread t.
 *	Returns ID of thread that yielded to t (i.e., the thread that called
 *	MyYieldThread), or -1 if t is an invalid ID.
 */

int MyYieldThread (t)
	int t;				/* thread being yielded to */
{
	if(debug)Printf("Enter Yield %d!\n",t);

	if (! MyInitThreadsCalled) {
		Printf ("YieldThread: Must call InitThreads first\n");
		Exit ();
	}

	if (t < 0 || t >= MAXTHREADS) {
		Printf ("YieldThread: %d is not a valid thread ID\n", t);
		return (-1);
	}
	if (! thread[t].valid) {
		Printf ("YieldThread: Thread %d does not exist\n", t);
		return (-1);
	}
	int c = front;
	if(debug){
		Printf("Front: %d Back: %d prev: %d next: %d size: %d \n",front,back,queue[0].prev,queue[0].next,queuesize );
	}
	deleteElement(c);
	addBack(c);
	deleteElement(t);
	addFront(t);
	if(debug){
		Printf("Front: %d Back: %d prev: %d next: %d size: %d \n",front,back,queue[0].prev,queue[0].next,queuesize );
	}

	if(debug){
		Printf("Sequence: ");
		for(int i = front ; i != -1 ; i = queue[i].next){
			Printf ("%d ",i);
		}
		Printf("\n");
	}
	c = MyGetThread();
    if (setjmp (thread[c].env) == 0) {
        PrevThread = c;
        CurrentThread = t;
        if(debug) Printf("c:%d t:%d\n",c,t);
        longjmp (thread[t].env,t+1);
    }
    return PrevThread;
}

/*	MyGetThread () returns ID of currently running thread.
 */

int MyGetThread ()
{
	if (! MyInitThreadsCalled) {
		Printf ("GetThread: Must call InitThreads first\n");
		Exit ();
	}
    return CurrentThread;

}

/*	MySchedThread () causes the running thread to simply give up the
 *	CPU and allow another thread to be scheduled.  Selecting which
 *	thread to run is determined here.  Note that the same thread may
 * 	be chosen (as will be the case if there are no other threads).
 */

void MySchedThread ()
{
	if (! MyInitThreadsCalled) {
		Printf ("SchedThread: Must call InitThreads first\n");
		Exit ();
	}
	if(debug) Printf("Schedule Front: %d\n",front);
	MyYieldThread (front);
}

/*	MyExitThread () causes the currently running thread to exit.
 */

void MyExitThread ()
{

	if (! MyInitThreadsCalled) {
		Printf ("ExitThread: Must call InitThreads first\n");
		Exit ();
	}
	int t = MyGetThread();
	thread[t].valid = 0;
	deleteElement(t);
	if(queuesize == 1) Exit();
	else {Printf("Continue\n" );
	MySchedThread();}
}
