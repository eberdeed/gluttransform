#include "../include/threadcreate.h"

ThreadCreate::ThreadCreate(string threadName, vector<ThreadInfo>threadInfo)
{
    cout << "\n\n\tCreating ThreadCreate.\n\n";
    numThreads = threadInfo.size();
    name = threadName;
    tinfo = threadInfo;
}

ThreadCreate::~ThreadCreate()
{
    cout << "\n\n\tDestroying ThreadCreate.\n\n";
}

int ThreadCreate::execute(void* func(void*), int threadNum)
{
    int s, opt, num_threads;
    /* Initialize thread creation attributes */
    threadAttr = new pthread_attr_t;
    s = pthread_attr_init(threadAttr);

    /* Allocate memory for pthread_create() arguments */
    
    if (tinfo[threadNum].stackSize > 0) 
    {
        s = pthread_attr_setstacksize(threadAttr, tinfo[threadNum].stackSize);
        if (s != 0)
        {
            string tmp = "\t";
            cout << "\n\n\tAttribute argument:  \n";
            displayPthread(threadAttr, threadNum);
            cout << "\n\n\tStack size:  " << tinfo[threadNum].stackSize << "\n\n";
            handle_error_en(s, "pthread_attr_setstacksize");
        }
    }
    else
    {
        handle_error("stack size at  0");
    }

    if (tinfo[threadNum].detached)
    {
        s = pthread_attr_setdetachstate(threadAttr, PTHREAD_CREATE_DETACHED);
        if (s != 0)
        {
            cout << "\n\n\tAttribute argument:  \n";
            displayPthread(threadAttr, threadNum);
            handle_error_en(s, "pthread_attr_setdetachstate");
        }
        else
        {
            cout << "\n\n\tSet thread detached state for thread"
            << " number:  "  << threadNum << "\n\n";
        }
    }

    if (debug1)
    {
        displayPthread(threadAttr, threadNum);
    }
    if (s != 0)
    {
        handle_error_en(s, "pthread_attr_init");
    }

    /* Create one thread for each command-line argument */
    stringstream ss;
    ss << threadNum + 1;
    string tmp = name + " " + ss.str();
    tinfo[threadNum].threadNum = threadNum + 1;
    tinfo[threadNum].threadName = tmp;
    /* The pthread_create() call stores the thread ID into
        corresponding element of tinfo[] */

    cout << "\n\n\tCreating thread " << tinfo[threadNum].threadNum 
    << " with threadName = " << tinfo[threadNum].threadName << "\n\n";
    s = pthread_create(&tinfo[threadNum].threadID, threadAttr,
    *func, &tinfo[threadNum]);
    if (s != 0)
    {
        handle_error_en(s, "pthread_create");
    }
    else
    {
        cout << "\n\n\tThread " << tinfo[threadNum].threadName << " created.\n\n";
    }
    /* Destroy the thread attributes object, since it is no
        longer needed */
    try 
    {
        s = pthread_attr_destroy(threadAttr);
        if (s != 0)
        {
            handle_error_en(s, "pthread_attr_destroy");
        }
    }
    catch (exception exc)
    {
        cout << "\n\n\tError destroying pthread:  " << exc.what() << "\n\n";
        exit(-1);
    }
    return 0;
}

void ThreadCreate::joinThread(int threadNum)
{
    void *res;
    if (!tinfo[threadNum].detached)
    {
        /* Now join with each thread, and display its returned value */
        s = pthread_join(tinfo[threadNum].threadID, &res);
        if (s != 0)
        {
            handle_error_en(s, "pthread_join");
        }
        stringstream ss = stringstream();
        ss << (char*) res;
        string tmp = ss.str();
        cout << "\n\n\tJoined with thread " << tinfo[threadNum].threadNum 
        <<  ", returned value was " << tmp << ",\n\n";
    }
}

void ThreadCreate::cancelThread(int threadNum)
{
    s = pthread_cancel(tinfo[threadNum].threadID);
    if (s != 0)
    {
        handle_error_en(s, "pthread_cancel");
    }
    else
    {
        cout << "\n\n\tThread " << threadNum + 1 << " was cancelled.\n\n";
    }
}

ThreadInfo ThreadCreate::getInfo(int threadNum)
{
    return tinfo[threadNum];
}

void ThreadCreate::displayPthread(pthread_attr_t *displayAttr, int threadNum)
{
    string response;
    cout <<  "\n\n\tAttributes for thread number " << threadNum << ".\n";
    s = pthread_attr_getdetachstate(displayAttr, &i);
    if (s != 0)
    {
        handle_error_en(s, "pthread_attr_getdetachstate");
    }
    if (i == PTHREAD_CREATE_DETACHED)
    {
        response = "PTHREAD_CREATE_DETACHED";
    }
    else if (i == PTHREAD_CREATE_JOINABLE)
    {
        response = "PTHREAD_CREATE_JOINABLE";
    }
    cout << "\n\tDetach state:  " << response;

    s = pthread_attr_getscope(displayAttr, &i);
    if (s != 0)
    {
        handle_error_en(s, "pthread_attr_getscope");
    }
    if (i == PTHREAD_SCOPE_SYSTEM)
    {
        response = "PTHREAD_SCOPE_SYSTEM";
    }
    else if (i == PTHREAD_SCOPE_PROCESS)
    {
        response = "PTHREAD_SCOPE_PROCESS";
    }
    cout << "\n\tThread scope:  " << response;

    s = pthread_attr_getinheritsched(displayAttr, &i);
    if (s != 0)
    {
        handle_error_en(s, "pthread_attr_getinheritsched");
    }
    if (i == PTHREAD_INHERIT_SCHED)
    {
        response = "PTHREAD_INHERIT_SCHED";
    }
    else if (i == PTHREAD_EXPLICIT_SCHED)
    {
        response = "PTHREAD_EXPLICIT_SCHED";
    }
    cout << "\n\tInherit thread scheduler:  " << response;

    s = pthread_attr_getschedpolicy(displayAttr, &i);
    if (s != 0)
    {
        handle_error_en(s, "pthread_attr_getschedpolicy");
    }
    if (i == SCHED_OTHER)
    {
        response = "SCHED_OTHER";
    }
    else if (i == SCHED_FIFO)
    {
        response = "SCHED_FIFO";
    }
    else if (i == SCHED_RR)
    {
        response = "SCHED_RR";
    }
    cout << "\n\tScheduling policy:  " << response;

    s = pthread_attr_getschedparam(displayAttr, &sp);
    if (s != 0)
    {
        handle_error_en(s, "pthread_attr_getschedparam");
    }
    cout << "\n\tScheduling priority:  " << sp.sched_priority;

    s = pthread_attr_getguardsize(displayAttr, &v);
    if (s != 0)
    {
        handle_error_en(s, "pthread_attr_getguardsize");
    }
    cout << "\n\tGuard size:  " << v << " bytes.";

    s = pthread_attr_getstack(displayAttr, &stkaddr, &v);
    if (s != 0)
    {
        handle_error_en(s, "pthread_attr_getstack");
    }
    cout << "\n\tStack address:  " << stkaddr;
    cout << "\n\tStack size:  " << v << " bytes.\n\n";
}

void ThreadCreate::handle_error_en(int en, string msg)
{ 
    cout << "\n\n\tProgram ended in ThreadCreate "
    << "with error number:  " << en 
    << " Error occured in:  " << msg << "\n\n";
    exit(-1); 
    
}

void ThreadCreate::handle_error(string msg) 
{ 
    cout << "\n\n\tProgram ended in Sound Thread "
    << "with error occuring in:  " << msg << "\n\n";
    exit(-1);
    
}

