/**
 * A deterministic BFS program to test the threading program for CSE 120
 *
 * Created by: Benjamin Lei
 * Created on: November 26, 2012
 * 
 * Modified by: Vijay Venkataraman
 * Modified on: November 23, 2013
 */

#include "aux.h"
#include "umix.h"
#include "mythreads.h"
#include "string.h"
#include <stdlib.h>
#include <time.h>

void BFS (int vertex);
void ResetDist ();
int Enqueue (int v);
int Dequeue ();
void SearchNeighbors (int curr);
void StartBFS (int curr);

/** pointer to functions so I'll only need one type of func call */
static void (*init)();
static int (*spawn)();
static int (*yield)(int);
static int (*get)();
static void (*exitThread)();
static void (*sched)();

static int matrix[100][100];

static int queue[MAXTHREADS];
static int h = 0;  // head
static int t = 0;  // tail
static int size = 0;  // size of queue
static int threads = 1;

static int dist[MAXTHREADS];

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
    sched = &MySchedThread;
  } else if (strncmp(argv[1], "ref", 4) == 0) { // else use ref funcs
    init = &InitThreads;
    spawn = &SpawnThread;
    yield = &YieldThread;
    get = &GetThread;
    exitThread = &ExitThread;
    sched = &SchedThread;
  } else {
    Printf ("Only arguments accepted are 'mine' or 'ref'\n");
    return;
  }

  init ();


  srand (0xC5E120);

  int i, j;
  Printf ("  ");
  for (i = 0; i < MAXTHREADS; i++) {
    Printf ("%d ", i);
  }
  Printf ("\n");

  for (i = 0; i < MAXTHREADS; i++) {
    Printf ("%d ", i);
    for (j = 0; j < MAXTHREADS; j++) {
      matrix[i][j] = (rand() * rand() * rand()) & 1;
      Printf ("%d ", matrix[i][j]);
    }
    Printf ("\n");
  }

  Printf ("\n");

  spawn (StartBFS, 0);

  exitThread ();
}

void StartBFS(curr)
     int curr;
{
  BFS (curr);
  if (curr < MAXTHREADS) {
    spawn (StartBFS, curr + 1);
  }
}

/** Performs a BFS to find the shortest unit path to every other possible vertex */

void BFS (vertex)
     int vertex;
{
  ResetDist ();
  Enqueue (vertex);
  dist[vertex] = 0;
  Printf ("Source: %d\n", vertex);

  while (0 < size) {
    int curr = Dequeue ();
    while (curr != -1) {
      yield (spawn (SearchNeighbors, curr));
   
 // do not continue until all neighbors searched
      while (MAXTHREADS -1 < size) {
        sched ();
      }
      curr = Dequeue ();
    }
  }
  Printf ("\n");
}

/** Search neighbors of current vertex */
void SearchNeighbors (curr)
     int curr;
{
  int i;
  for (i = 0; i < MAXTHREADS; i++) {
    if (matrix[curr][i] == 1 && dist[i] == -1) {
      dist[i] = dist[curr] + 1;
      Printf ("Test %d: %d\n", i, dist[i]);

      // do not continue until all neighbors searched
      while (MAXTHREADS - 1 < size) {
        sched ();
      }

      Enqueue (i);
    }
  }
}


/** Resets distance array */
void ResetDist ()
{
  int i;
  for (i = 0; i < MAXTHREADS; i++) {
    dist[i] = -1;
  }
}

/** Adds a vertex to the queue */
int Enqueue  (v)
     int v;
{
  if (size == MAXTHREADS) {
    return 0;
  }

  queue[t] = v;
  t = (t + 1) % MAXTHREADS;
  size++;
  return 1;
}

/** Removes a vertex from the queue */
int Dequeue ()
{
  if (size == 0) {
    return -1;
  }

  int v = queue[h];
  h = (h + 1) % MAXTHREADS;
  --size;
  return v;
}