/*
 * A test case which keeps spawning and yielding
 across multiple threads.
 */
#include "aux.h"
#include "umix.h"
#include "mythreads.h"

#define NUMYIELDS      2


static int useDefault = 0;
int  spawnThread(void (*f)(), int p) {if(useDefault) return SpawnThread(f,p); else return MySpawnThread(f,p);}
int  yieldThread(int t) {if(useDefault) return YieldThread(t); else return MyYieldThread(t);}
int  getThread()   {if(useDefault) return GetThread(); else return MyGetThread();}
void exitThread()  {if(useDefault) ExitThread(); else MyExitThread();}
void initThreads() {useDefault? InitThreads(): MyInitThreads();}
void printMyThread(int iter);
void printMyThreadForThread0(int iter);
void Main ()
{
	int i, me;
	void printMyThread();
    
	initThreads ();
    
	me = getThread ();
  	for(i=1; i<MAXTHREADS;i++)
        spawnThread(printMyThread,0);
    
	for (i = 0; i < NUMYIELDS; i++) {
        Printf("0 T%d\n",me);
        yieldThread(1);
	}
    
	exitThread ();
}

void printMyThreadForThread0(int iter)
{
    int tid = getThread();
    
    
    spawnThread(printMyThread,iter);
    // delay
    for(int i=0;i<NUMYIELDS;i++) {
        Delay(100);
        Printf("%d ",iter);
        for(int j=0;(j<tid);j++)
            Printf(".");
        Printf("T%d \n", tid);
        yieldThread((tid+1)%MAXTHREADS);
    }
}

void printMyThread(int iter)
{
    int tid = getThread();
    // delay
    for(int i=0;i<NUMYIELDS;i++) {
        Delay(100);
        Printf("%d ",iter);
        
        for(int j=0;(j<tid);j++)
            Printf(".");
        Printf("T%d \n", tid);
        yieldThread((tid+1)%MAXTHREADS);
    }
    
    if(tid!=1)
        spawnThread(printMyThread,iter+1);
    else
        spawnThread(printMyThreadForThread0,iter+1);
}
