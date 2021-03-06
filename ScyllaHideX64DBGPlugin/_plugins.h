#ifndef _PLUGINS_H
#define _PLUGINS_H

#ifndef PLUG_IMPEXP
#ifdef BUILD_DBG
#define PLUG_IMPEXP __declspec(dllexport)
#else
#define PLUG_IMPEXP __declspec(dllimport)
#endif //BUILD_DBG
#endif //PLUG_IMPEXP

#include "_plugin_types.h"

//default structure alignments forced
#ifdef _WIN64
#pragma pack(push, 16)
#else //x86
#pragma pack(push, 8)
#endif //_WIN64

//defines
#define PLUG_SDKVERSION 1

//structures
struct PLUG_INITSTRUCT
{
    //provided by the debugger
    int pluginHandle;
    //provided by the pluginit function
    int sdkVersion;
    int pluginVersion;
    char pluginName[256];
};

struct PLUG_SETUPSTRUCT
{
    //provided by the debugger
    HWND hwndDlg; //gui window handle
    int hMenu; //plugin menu handle
};

//callback structures
struct PLUG_CB_INITDEBUG
{
    const char* szFileName;
};

struct PLUG_CB_STOPDEBUG
{
    void* reserved;
};

struct PLUG_CB_CREATEPROCESS
{
    CREATE_PROCESS_DEBUG_INFO* CreateProcessInfo;
    IMAGEHLP_MODULE64* modInfo;
    const char* DebugFileName;
    PROCESS_INFORMATION* fdProcessInfo;
};

struct PLUG_CB_EXITPROCESS
{
    EXIT_PROCESS_DEBUG_INFO* ExitProcess;
};

struct PLUG_CB_CREATETHREAD
{
    CREATE_THREAD_DEBUG_INFO* CreateThread;
    DWORD dwThreadId;
};

struct PLUG_CB_EXITTHREAD
{
    EXIT_THREAD_DEBUG_INFO* ExitThread;
    DWORD dwThreadId;
};

struct PLUG_CB_SYSTEMBREAKPOINT
{
    void* reserved;
};

struct PLUG_CB_LOADDLL
{
    LOAD_DLL_DEBUG_INFO* LoadDll;
    IMAGEHLP_MODULE64* modInfo;
    const char* modname;
};

struct PLUG_CB_UNLOADDLL
{
    UNLOAD_DLL_DEBUG_INFO* UnloadDll;
};

struct PLUG_CB_OUTPUTDEBUGSTRING
{
    OUTPUT_DEBUG_STRING_INFO* DebugString;
};

struct PLUG_CB_EXCEPTION
{
    EXCEPTION_DEBUG_INFO* Exception;
};

struct PLUG_CB_BREAKPOINT
{
    BRIDGEBP* breakpoint;
};

struct PLUG_CB_PAUSEDEBUG
{
    void* reserved;
};

struct PLUG_CB_RESUMEDEBUG
{
    void* reserved;
};

struct PLUG_CB_STEPPED
{
    void* reserved;
};

struct PLUG_CB_ATTACH
{
    DWORD dwProcessId;
};

struct PLUG_CB_DETACH
{
    PROCESS_INFORMATION* fdProcessInfo;
};

struct PLUG_CB_DEBUGEVENT
{
    DEBUG_EVENT* DebugEvent;
};

struct PLUG_CB_MENUENTRY
{
    int hEntry;
};

//enums
enum CBTYPE
{
    CB_INITDEBUG, //PLUG_CB_INITDEBUG
    CB_STOPDEBUG, //PLUG_CB_STOPDEBUG
    CB_CREATEPROCESS, //PLUG_CB_CREATEPROCESS
    CB_EXITPROCESS, //PLUG_CB_EXITPROCESS
    CB_CREATETHREAD, //PLUG_CB_CREATETHREAD
    CB_EXITTHREAD, //PLUG_CB_EXITTHREAD
    CB_SYSTEMBREAKPOINT, //PLUG_CB_SYSTEMBREAKPOINT
    CB_LOADDLL, //PLUG_CB_LOADDLL
    CB_UNLOADDLL, //PLUG_CB_UNLOADDLL
    CB_OUTPUTDEBUGSTRING, //PLUG_CB_OUTPUTDEBUGSTRING
    CB_EXCEPTION, //PLUG_CB_EXCEPTION
    CB_BREAKPOINT, //PLUG_CB_BREAKPOINT
    CB_PAUSEDEBUG, //PLUG_CB_PAUSEDEBUG
    CB_RESUMEDEBUG, //PLUG_CB_RESUMEDEBUG
    CB_STEPPED, //PLUG_CB_STEPPED
    CB_ATTACH, //PLUG_CB_ATTACHED (before attaching, after CB_INITDEBUG)
    CB_DETACH, //PLUG_CB_DETACH (before detaching, before CB_STOPDEBUG)
    CB_DEBUGEVENT, //PLUG_CB_DEBUGEVENT (called on any debug event)
    CB_MENUENTRY //PLUG_CB_MENUENTRY
};

//typedefs
typedef void (*CBPLUGIN)(CBTYPE cbType, void* callbackInfo);
typedef bool (*CBPLUGINCOMMAND)(int, char**);

//exports
#ifdef __cplusplus
extern "C"
{
#endif

PLUG_IMPEXP void _plugin_registercallback(int pluginHandle, CBTYPE cbType, CBPLUGIN cbPlugin);
PLUG_IMPEXP bool _plugin_unregistercallback(int pluginHandle, CBTYPE cbType);
PLUG_IMPEXP bool _plugin_registercommand(int pluginHandle, const char* command, CBPLUGINCOMMAND cbCommand, bool debugonly);
PLUG_IMPEXP bool _plugin_unregistercommand(int pluginHandle, const char* command);
PLUG_IMPEXP void _plugin_logprintf(const char* format, ...);
PLUG_IMPEXP void _plugin_logputs(const char* text);
PLUG_IMPEXP void _plugin_debugpause();
PLUG_IMPEXP void _plugin_debugskipexceptions(bool skip);
PLUG_IMPEXP int _plugin_menuadd(int hMenu, const char* title);
PLUG_IMPEXP bool _plugin_menuaddentry(int hMenu, int hEntry, const char* title);
PLUG_IMPEXP bool _plugin_menuaddseparator(int hMenu);
PLUG_IMPEXP bool _plugin_menuclear(int hMenu);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // _PLUGINS_H
