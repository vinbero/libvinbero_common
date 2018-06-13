#include <dlfcn.h>
#include "vinbero_common_Config.h"
#include "vinbero_common_Error.h"
#include "vinbero_common_Module.h"

int vinbero_common_Module_init(struct vinbero_common_Module* module, const char* name, const char* version, bool childrenRequired) {
    module->name = name;
    module->version = version;
    module->childrenRequired = childrenRequired;
    return 0;
}

int vinbero_common_Module_Ids_init(struct vinbero_common_Module_Ids* ids) {
    GENC_ARRAY_LIST_INIT(ids);
    return 0;
}

int vinbero_common_Module_Ids_destroy(struct vinbero_common_Module_Ids* ids) {
    GENC_ARRAY_LIST_FREE(ids);
    return  0;
}

/*
int vinbero_common_Module_dlopen(struct vinbero_common_Module* module) {
    const char* modulePath;
    memset(&module->dlHandle, 0, sizeof(struct fastdl_Handle));
    if((modulePath = json_string_value(json_object_get(json_object_get(module->config->json, (module)->id), "path"))) == NULL)
        return VINBERO_COMMON_ERROR_INVALID_CONFIG;
    else if(fastdl_open(&(module)->dlHandle, modulePath, RTLD_LAZY | RTLD_GLOBAL) == -1)
        return VINBERO_COMMON_ERROR_DLOPEN;
    else
        return 0;
}
*/
