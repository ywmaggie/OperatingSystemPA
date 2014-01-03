/*	User-level thread system
 */

#define MAXTHREADS	10		/* maximum number of threads */

void MyInitThreads ();			/* initialize thread package */
int MySpawnThread (void (*f)(), int p);	/* spawn a thread to execute f(p) */
int MyGetThread ();			/* return id of current thread */
int MyYieldThread (int t);		/* yield to thread t */
void MySchedThread ();			/* yield to scheduler */
void MyExitThread ();			/* exit this thread */

/*	Working version of above functions (reference user-level thread system)
 */

void InitThreads ();			/* initialize thread package */
int SpawnThread (void (*f)(), int p);	/* spawn a thread to execute f(p) */
int GetThread ();			/* return id of current thread */
int YieldThread (int t);		/* yield to thread t */
void SchedThread ();			/* yield to scheduler */
void ExitThread ();			/* exit this thread */
