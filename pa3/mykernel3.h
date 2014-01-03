void InitSem ();			/* initialize semaphores */
int MySeminit (int p, int v);		/* alloc sem, init to v, return semid */
void MyWait (int p, int s);		/* process p waits using sem s */
void MySignal (int p, int s);		/* process p signals using sem s */
