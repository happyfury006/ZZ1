#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <stdbool.h>

// Use our own type for potential ports to other plaforms
typedef struct timespec utils_timestamp;

// Do not use directly, if we ever want to wrap this for other platforms
static inline utils_timestamp internal_normalize_timespec(time_t tv_sec, long tv_nsec)
{
    long const billion = 1000000000;
    struct timespec t;
    t.tv_sec = (tv_nsec >= 0 ? tv_nsec : tv_nsec - (billion-1)) / billion;
    t.tv_nsec = tv_nsec - t.tv_sec * billion;
    t.tv_sec += tv_sec;
    return t;
}

static inline utils_timestamp utils_timestamp_subtract(utils_timestamp time1, utils_timestamp time0) {
    return internal_normalize_timespec(time1.tv_sec - time0.tv_sec, time1.tv_nsec - time0.tv_nsec);
}


static inline utils_timestamp utils_get_timestamp()
{
    utils_timestamp t;
    clock_gettime(CLOCK_MONOTONIC, &t); 
    return t;
}

static inline double utils_timestamp_elapsed_ms(utils_timestamp begin, utils_timestamp end)
{
    utils_timestamp delta = utils_timestamp_subtract(begin, end);
    return delta .tv_sec * 1000.0 + delta .tv_nsec / 1000000.0;
}

static inline void utils_print_timestamp(FILE* f, utils_timestamp t)
{
    fprintf(f, "%llus+%09ldns", t.tv_sec, t.tv_nsec);
}

// outExtension must include .
// Result must be freed
static inline char* utils_out_name(const char* outDir, const char *outExtension, const char* inName)
{
    char* inNameDup = strdup(inName); //needed because basename can modify the input
    const char* baseName = basename(inNameDup);
    const char* lastDot = strrchr(baseName, '.');
    const size_t stemLength = lastDot - baseName;
    const size_t outDirLength = strlen(outDir);
    const size_t outExtensionLength = strlen(outExtension);

    const size_t outPathBufferSize = outDirLength + /*/*/1 + stemLength + outExtensionLength + 1 /*\`0*/;
    char* outPath = (char*)malloc(outPathBufferSize);
    char* pathWritePtr = outPath;
    
    memcpy(pathWritePtr, outDir, outDirLength);
    pathWritePtr+= outDirLength;

    *pathWritePtr = '/';
    pathWritePtr++;
    
    memcpy(pathWritePtr, baseName, stemLength);
    pathWritePtr+= stemLength;

    memcpy(pathWritePtr, outExtension, outExtensionLength);
    pathWritePtr+=outExtensionLength;

    *pathWritePtr = '\0';
    pathWritePtr++;

    assert((pathWritePtr-outPath) <= outPathBufferSize);

    free(inNameDup);
    return outPath;
}

typedef void (*utils_task_routineptr) (void *);

typedef struct utils_task {
  struct utils_task* pNextTask;
  utils_task_routineptr pTaskRoutine;
  void* pUserData;
} utils_task;


typedef struct {
  utils_task* pTaskHead;  
  utils_task* pTaskTail;  
} utils_tasklist;


// How to use:
//
//    utils_tasklist tasklist;
//    utils_init_tasklist(&tasklist);
//
//    // Push new tasks
//    utils_push_task(&tasklist, routine, pUserData);
//
//
//    // Pop new tasks
//    utils_task_routineptr pTaskRoutine;
//    void* pUserData;
//    if(utils_try_pop_task(&tasklist, &pTaskRoutine, &pUserData))
//    {
//        (*pTaskRoutine)(pUserData);
//    }
static inline void utils_init_tasklist(utils_tasklist* pTaskList)
{
    pTaskList->pTaskHead = NULL;
    pTaskList->pTaskTail = NULL;
}

// Ideally, for a performant system, we would use our own allocator and (for example) preallocate a big array of tasks.
static inline utils_task* utils_task_alloc()
{
    return (utils_task*)malloc(sizeof(utils_task));
}
static inline void utils_task_free(utils_task* pTask)
{
    return free(pTask);
}

static inline void utils_push_task(utils_tasklist* pTaskList, utils_task_routineptr pTaskRoutine, void* pUserData)
{
    utils_task* pTask = utils_task_alloc();
    pTask->pTaskRoutine = pTaskRoutine;
    pTask->pUserData = pUserData;
    pTask->pNextTask = NULL;

    if(pTaskList->pTaskHead == NULL)
    {
        pTaskList->pTaskHead = pTask;
        pTaskList->pTaskTail = pTask;
    }
    else 
    {
        pTaskList->pTaskTail->pNextTask = pTask;
        pTaskList->pTaskTail = pTask;
    }
}

static inline bool utils_try_pop_task(utils_tasklist* pTaskList, utils_task_routineptr* pOutTaskRoutine, void** pOutUserData)
{
    assert(pOutTaskRoutine != NULL);
    assert(pOutUserData != NULL);
    if(pTaskList->pTaskHead != NULL)
    {
        *pOutTaskRoutine = pTaskList->pTaskHead->pTaskRoutine;
        *pOutUserData = pTaskList->pTaskHead->pUserData;

        utils_task* pToFree = pTaskList->pTaskHead;
        pTaskList->pTaskHead = pTaskList->pTaskHead->pNextTask;
        if(pTaskList->pTaskHead == NULL) pTaskList->pTaskTail = NULL;
        utils_task_free(pToFree);
        return true;
    }
    return false;
}

