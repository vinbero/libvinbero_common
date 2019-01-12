#ifndef _VINBERO_COMMON_MODULE_H
#define _VINBERO_COMMON_MODULE_H

#include <dlfcn.h>
#include <fastdl.h>
#include <pthread.h>
#include <libgenc/genc_Generic.h>
#include <libgenc/genc_Tree.h>
#include <libgenc/genc_ArrayList.h>
#include "vinbero_common_Config.h"
#include "vinbero_common_Dlsym.h"
#include "vinbero_common_Error.h"
#include "vinbero_common_Status.h"

struct vinbero_common_Module {
    const char* name;
    const char* version;
    bool childrenRequired;
    struct vinbero_common_Config* config;
    const char* id;
    struct fastdl_Handle dlHandle;
    union genc_Generic localModule;
    void* arg; // arg from parentModule
    GENC_TREE_NODE(struct vinbero_common_Module, struct vinbero_common_Module*);
};

struct vinbero_common_Module_Id {
    const char* value;
};

struct vinbero_common_Module_Ids {
    GENC_ARRAY_LIST(struct vinbero_common_Module_Id);
};

int vinbero_common_Module_init(struct vinbero_common_Module* module, const char* name, const char* version, bool childrenRequired);

int vinbero_common_Module_Ids_init(struct vinbero_common_Module_Ids* ids);

int vinbero_common_Module_Ids_destroy(struct vinbero_common_Module_Ids* ids);

#define VINBERO_COMMON_MODULE_DLOPEN(module, ret) do { \
    const char* modulePath; \
    VINBERO_COMMON_CONFIG_MGET_REQ((module)->config, module, "path", string, &modulePath, ret); \
    if(*(ret) < VINBERO_COMMON_STATUS_SUCCESS) \
        *(ret) = VINBERO_COMMON_ERROR_NOT_FOUND; \
    else if(fastdl_open(&(module)->dlHandle, modulePath, RTLD_LAZY | RTLD_GLOBAL) == -1) \
        *(ret) = VINBERO_COMMON_ERROR_DLOPEN; \
    else \
        *(ret) = VINBERO_COMMON_STATUS_SUCCESS; \
} while(0)

#define VINBERO_COMMON_MODULE_DLSYM(interface, dlHandle, functionName, ret) do { \
    (interface)->functionName = NULL; \
    VINBERO_COMMON_DLSYM(dlHandle, #functionName, (void**)&(interface)->functionName, ret); \
} while(0)

#endif
