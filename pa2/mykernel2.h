void InitSched ();
int StartingProc (int pid);
int EndingProc (int pid);
int SchedProc ();
void HandleTimerIntr ();
int MyRequestCPUrate (int pid, int m, int n);
