#ifndef THREADMANAGER_H
#define THREADMANAGER_H

class ThreadManager
{
public:
    ThreadManager();
private:
    int threadCount;
    int maxThreads;
    void initializeThreads();
    void cleanupThreads();
    void startThread(int threadId);
    void stopThread(int threadId);
    
};

#endif // THREADMANAGER_H
