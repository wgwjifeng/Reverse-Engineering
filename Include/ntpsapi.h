#pragma once
#include "ntbase.h"

using ACCESS_MASK = unsigned long;
//////////////////////////////////////////////////////////////////////////




#define PROCESS_TERMINATE                   0x0001
#define PROCESS_CREATE_THREAD               0x0002
#define PROCESS_SET_SESSIONID               0x0004
#define PROCESS_VM_OPERATION                0x0008
#define PROCESS_VM_READ                     0x0010
#define PROCESS_VM_WRITE                    0x0020
#define PROCESS_CREATE_PROCESS              0x0080
#define PROCESS_SET_QUOTA                   0x0100
#define PROCESS_SET_INFORMATION             0x0200
#define PROCESS_QUERY_INFORMATION           0x0400
#define PROCESS_SET_PORT                    0x0800
#define PROCESS_SUSPEND_RESUME              0x0800
#define PROCESS_QUERY_LIMITED_INFORMATION   0x1000

#define THREAD_QUERY_INFORMATION            0x0040
#define THREAD_SET_THREAD_TOKEN             0x0080
#define THREAD_IMPERSONATE                  0x0100
#define THREAD_DIRECT_IMPERSONATION         0x0200

#define JOB_OBJECT_ASSIGN_PROCESS           0x0001
#define JOB_OBJECT_SET_ATTRIBUTES           0x0002
#define JOB_OBJECT_QUERY                    0x0004
#define JOB_OBJECT_TERMINATE                0x0008
#define JOB_OBJECT_SET_SECURITY_ATTRIBUTES  0x0010
#define JOB_OBJECT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1f)


#define GDI_HANDLE_BUFFER_SIZE32 34
#define GDI_HANDLE_BUFFER_SIZE64 60

#if defined(_WIN64)
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#else
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#endif

typedef UINT32 GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];

typedef UINT32 GDI_HANDLE_BUFFER32[GDI_HANDLE_BUFFER_SIZE32];
typedef UINT32 GDI_HANDLE_BUFFER64[GDI_HANDLE_BUFFER_SIZE64];

#define FLS_MAXIMUM_AVAILABLE   128
#define TLS_MINIMUM_AVAILABLE   64
#define TLS_EXPANSION_SLOTS     1024


typedef struct _PEB_LDR_DATA
{
    UINT32 Length;
    BOOLEAN Initialized;
    HANDLE SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    void* EntryInProgress;
    BOOLEAN ShutdownInProgress;
    HANDLE ShutdownThreadId;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _INITIAL_TEB
{
    struct
    {
        void* OldStackBase;
        void* OldStackLimit;
    } OldInitialTeb;
    void* StackBase;
    void* StackLimit;
    void* StackAllocationBase;
} INITIAL_TEB, *PINITIAL_TEB;

typedef struct _WOW64_PROCESS
{
    void* Wow64;
} WOW64_PROCESS, *PWOW64_PROCESS;

//////////////////////////////////////////////////////////////////////////

//
// CreateProcess dwCreationFlag values
//

enum PROCESS_CREATION_FLAGS : UINT32
{
    DEBUG_PROCESS = 0x00000001,
    DEBUG_ONLY_THIS_PROCESS = 0x00000002,
    CREATE_SUSPENDED = 0x00000004,
    DETACHED_PROCESS = 0x00000008,

    CREATE_NEW_CONSOLE = 0x00000010,
    NORMAL_PRIORITY_CLASS = 0x00000020,
    IDLE_PRIORITY_CLASS = 0x00000040,
    HIGH_PRIORITY_CLASS = 0x00000080,

    REALTIME_PRIORITY_CLASS = 0x00000100,
    CREATE_NEW_PROCESS_GROUP = 0x00000200,
    CREATE_UNICODE_ENVIRONMENT = 0x00000400,
    CREATE_SEPARATE_WOW_VDM = 0x00000800,

    CREATE_SHARED_WOW_VDM = 0x00001000,
    CREATE_FORCEDOS = 0x00002000,
    BELOW_NORMAL_PRIORITY_CLASS = 0x00004000,
    ABOVE_NORMAL_PRIORITY_CLASS = 0x00008000,

    INHERIT_PARENT_AFFINITY = 0x00010000,
    INHERIT_CALLER_PRIORITY = 0x00020000,    // Deprecated
    CREATE_PROTECTED_PROCESS = 0x00040000,
    EXTENDED_STARTUPINFO_PRESENT = 0x00080000,

    PROCESS_MODE_BACKGROUND_BEGIN = 0x00100000,
    PROCESS_MODE_BACKGROUND_END = 0x00200000,

    CREATE_BREAKAWAY_FROM_JOB = 0x01000000,
    CREATE_PRESERVE_CODE_AUTHZ_LEVEL = 0x02000000,
    CREATE_DEFAULT_ERROR_MODE = 0x04000000,
    CREATE_NO_WINDOW = 0x08000000,

    PROFILE_USER = 0x10000000,
    PROFILE_KERNEL = 0x20000000,
    PROFILE_SERVER = 0x40000000,
    CREATE_IGNORE_SYSTEM_DEFAULT = 0x80000000,
};

//
// CreateProcess StartupInfo.dwFlags value
//

enum STARTUP_INFO_FLAGS : UINT32
{
    STARTF_USESHOWWINDOW = 0x00000001,
    STARTF_USESIZE = 0x00000002,
    STARTF_USEPOSITION = 0x00000004,
    STARTF_USECOUNTCHARS = 0x00000008,

    STARTF_USEFILLATTRIBUTE = 0x00000010,
    STARTF_RUNFULLSCREEN = 0x00000020,  // ignored for non-x86 platforms
    STARTF_FORCEONFEEDBACK = 0x00000040,
    STARTF_FORCEOFFFEEDBACK = 0x00000080,

    STARTF_USESTDHANDLES = 0x00000100,
    STARTF_USEHOTKEY = 0x00000200,
    STARTF_SHELLPRIVATE = 0x00000400,
    STARTF_TITLEISLINKNAME = 0x00000800,

    STARTF_TITLEISAPPID = 0x00001000,
    STARTF_PREVENTPINNING = 0x00002000,
};

//////////////////////////////////////////////////////////////////////////

// 
// Struct and flag for CreateProcessInternal
//

enum PROC_THREAD_ATTRIBUTE_NUM : UINT32
{
    ProcThreadAttributeParentProcess = 0,
    ProcThreadAttributeExtendedFlags = 1,
    ProcThreadAttributeHandleList = 2,
    ProcThreadAttributeGroupAffinity = 3,
    ProcThreadAttributePreferredNode = 4,
    ProcThreadAttributeIdealProcessor = 5,
    ProcThreadAttributeUmsThread = 6,
    ProcThreadAttributeMitigationPolicy = 7,
    ProcThreadAttributePackageFullName = 8,
    ProcThreadAttributeSecurityCapabilities = 9,
    ProcThreadAttributeConsoleReference = 10,
    ProcThreadAttributeProtectionLevel = 11,
    ProcThreadAttributeJobList = 13,
    ProcThreadAttributeChildProcessPolicy = 14,
    ProcThreadAttributeAllApplicationPackagesPolicy = 15,
    ProcThreadAttributeWin32kFilter = 16,
    ProcThreadAttributeSafeOpenPromptOriginClaim = 17,
};

#define PROC_THREAD_ATTRIBUTE_NUMBER    0x0000FFFF
#define PROC_THREAD_ATTRIBUTE_THREAD    0x00010000  // Attribute may be used with thread creation
#define PROC_THREAD_ATTRIBUTE_INPUT     0x00020000  // Attribute is input only
#define PROC_THREAD_ATTRIBUTE_ADDITIVE  0x00040000  // Attribute may be "accumulated," e.g. bitmasks, counters, etc.

#define PROTECTION_LEVEL_SAME               0xFFFFFFFF

#define ProcThreadAttributeValue(Number, Thread, Input, Additive) \
    (((Number) & PROC_THREAD_ATTRIBUTE_NUMBER) | \
     ((Thread) ? PROC_THREAD_ATTRIBUTE_THREAD : 0) | \
     ((Input) ? PROC_THREAD_ATTRIBUTE_INPUT : 0) | \
     ((Additive) ? PROC_THREAD_ATTRIBUTE_ADDITIVE : 0))

#define PROC_THREAD_ATTRIBUTE_PARENT_PROCESS \
    ProcThreadAttributeValue (ProcThreadAttributeParentProcess, FALSE, TRUE, FALSE)
#define PROC_THREAD_ATTRIBUTE_HANDLE_LIST \
    ProcThreadAttributeValue (ProcThreadAttributeHandleList, FALSE, TRUE, FALSE)
#define PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY \
    ProcThreadAttributeValue (ProcThreadAttributeGroupAffinity, TRUE, TRUE, FALSE)
#define PROC_THREAD_ATTRIBUTE_PREFERRED_NODE \
    ProcThreadAttributeValue (ProcThreadAttributePreferredNode, FALSE, TRUE, FALSE)
#define PROC_THREAD_ATTRIBUTE_IDEAL_PROCESSOR \
    ProcThreadAttributeValue (ProcThreadAttributeIdealProcessor, TRUE, TRUE, FALSE)
#define PROC_THREAD_ATTRIBUTE_UMS_THREAD \
    ProcThreadAttributeValue (ProcThreadAttributeUmsThread, TRUE, TRUE, FALSE)
#define PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY \
    ProcThreadAttributeValue (ProcThreadAttributeMitigationPolicy, FALSE, TRUE, FALSE)
#define PROC_THREAD_ATTRIBUTE_PACKAGE_FULL_NAME \
    ProcThreadAttributeValue (ProcThreadAttributePackageFullName, FALSE, TRUE, TRUE)
#define PROC_THREAD_ATTRIBUTE_SECURITY_CAPABILITIES \
    ProcThreadAttributeValue (ProcThreadAttributeSecurityCapabilities, FALSE, TRUE, FALSE)
#define PROC_THREAD_ATTRIBUTE_PROTECTION_LEVEL \
    ProcThreadAttributeValue (ProcThreadAttributeProtectionLevel, FALSE, TRUE, FALSE)

typedef struct _PROC_THREAD_ATTRIBUTE
{
    UINT_PTR Attribute;
    SIZE_T Size;
    UINT_PTR Value;

}PROC_THREAD_ATTRIBUTE, *LPPROC_THREAD_ATTRIBUTE;

typedef struct _PROC_THREAD_ATTRIBUTE_LIST
{
    UINT32 PresentFlags;
    UINT32 AttributeCount;
    UINT32 LastAttribute;
    UINT32 SpareUlong0;
    PROC_THREAD_ATTRIBUTE* ExtendedFlagsAttribute;
    PROC_THREAD_ATTRIBUTE Attributes[1];
}PROC_THREAD_ATTRIBUTE_LIST, *LPPROC_THREAD_ATTRIBUTE_LIST;

//////////////////////////////////////////////////////////////////////////

// 
// Struct and flag for NtCreateUserProcess
//

enum PROCESS_PRIORITY_CLASSES : UINT8
{
    PROCESS_PRIORITY_CLASS_INVALID,
    PROCESS_PRIORITY_CLASS_IDLE,
    PROCESS_PRIORITY_CLASS_NORMAL,
    PROCESS_PRIORITY_CLASS_HIGH,
    PROCESS_PRIORITY_CLASS_REALTIME,
    PROCESS_PRIORITY_CLASS_BELOW_NORMAL,
    PROCESS_PRIORITY_CLASS_ABOVE_NORMAL,
};

typedef struct _PROCESS_PRIORITY_CLASS {
    BOOLEAN Foreground;
    UINT8 PriorityClass;
} PROCESS_PRIORITY_CLASS, *PPROCESS_PRIORITY_CLASS;

enum PROCESS_CREATE_FLAGS : UINT32
{
    PROCESS_CREATE_FLAGS_BREAKAWAY                  = 0x00000001,
    PROCESS_CREATE_FLAGS_NO_DEBUG_INHERIT           = 0x00000002,
    PROCESS_CREATE_FLAGS_INHERIT_HANDLES            = 0x00000004,
    PROCESS_CREATE_FLAGS_OVERRIDE_ADDRESS_SPACE     = 0x00000008,
    PROCESS_CREATE_FLAGS_LARGE_PAGES                = 0x00000010,
    PROCESS_CREATE_FLAGS_ALL_LARGE_PAGE_FLAGS       = PROCESS_CREATE_FLAGS_LARGE_PAGES,
    PROCESS_CREATE_FLAGS_LARGE_PAGE_SYSTEM_DLL      = 0x00000020,

    // Extended PROCESS_CREATE_FLAGS_
    PROCESS_CREATE_FLAGS_PROTECTED_PROCESS          = 0x00000040,
    PROCESS_CREATE_FLAGS_CREATE_SESSION             = 0x00000080, // ?
    PROCESS_CREATE_FLAGS_INHERIT_FROM_PARENT        = 0x00000100,
    PROCESS_CREATE_FLAGS_SUSPENDED                  = 0x00000200,
    PROCESS_CREATE_FLAGS_UNKNOWN0                   = 0x00000400,

    PROCESS_CREATE_FLAGS_LEGAL_MASK = (PROCESS_CREATE_FLAGS_BREAKAWAY | \
    PROCESS_CREATE_FLAGS_NO_DEBUG_INHERIT | \
        PROCESS_CREATE_FLAGS_INHERIT_HANDLES | \
        PROCESS_CREATE_FLAGS_OVERRIDE_ADDRESS_SPACE | \
        PROCESS_CREATE_FLAGS_ALL_LARGE_PAGE_FLAGS),
};

enum THREAD_CREATE_FLAGS : UINT32
{
    THREAD_CREATE_FLAGS_CREATE_SUSPENDED        = 0x00000001,
    THREAD_CREATE_FLAGS_SKIP_THREAD_ATTACH      = 0x00000002,
    THREAD_CREATE_FLAGS_HIDE_FROM_DEBUGGER      = 0x00000004,
    THREAD_CREATE_FLAGS_HAS_SECURITY_DESCRIPTOR = 0x00000010,
    THREAD_CREATE_FLAGS_ACCESS_CHECK_IN_TARGET  = 0x00000020,
    THREAD_CREATE_FLAGS_INITIAL_THREAD          = 0x00000080,
};


enum PS_STD_HANDLE_STATE : UINT8
{
    PsNeverDuplicate,
    PsRequestDuplicate, // duplicate standard handles specified by PseudoHandleMask, and only if StdHandleSubsystemType matches the image subsystem
    PsAlwaysDuplicate,  // always duplicate standard handles
    PsMaxStdHandleStates
};

typedef struct _PS_STD_HANDLE_INFO
{
    union
    {
        UINT32 Flags;
        struct
        {
            UINT32 StdHandleState : 2;
            UINT32 PseudoHandleMask : 3;
        };
    };
    UINT32 StdHandleSubsystemType;

}PS_STD_HANDLE_INFO, *PPS_STD_HANDLE_INFO;

enum PS_ATTRIBUTE_NUM : UINT32
{
    PsAttributeParentProcess,       // in HANDLE
    PsAttributeDebugPort,           // in HANDLE
    PsAttributeToken,               // in HANDLE
    PsAttributeClientId,            // out PCLIENT_ID
    PsAttributeTebAddress,          // out PTEB *
    PsAttributeImageName,           // in PWSTR
    PsAttributeImageInfo,           // out PSECTION_IMAGE_INFORMATION
    PsAttributeMemoryReserve,       // in PPS_MEMORY_RESERVE
    PsAttributePriorityClass,       // in UINT8
    PsAttributeErrorMode,           // in UINT32
    PsAttributeStdHandleInfo,       // 10, in PPS_STD_HANDLE_INFO
    PsAttributeHandleList,          // in PHANDLE
    PsAttributeGroupAffinity,       // in PGROUP_AFFINITY
    PsAttributePreferredNode,       // in PUSHORT
    PsAttributeIdealProcessor,      // in PPROCESSOR_NUMBER
    PsAttributeUmsThread,           // ? in PUMS_CREATE_THREAD_ATTRIBUTES
    PsAttributeMitigationOptions,   // in UINT8
    PsAttributeProtectionLevel,     // in UINT32
    PsAttributeSecureProcess,       // since THRESHOLD
    PsAttributeJobList,
    PsAttributeChildProcessPolicy,  // since THRESHOLD2
    PsAttributeAllApplicationPackagesPolicy, // since REDSTONE
    PsAttributeWin32kFilter,
    PsAttributeSafeOpenPromptOriginClaim,
    PsAttributeBnoIsolation,        // PS_BNO_ISOLATION_PARAMETERS
    PsAttributeDesktopAppPolicy,    // in UINT32
    PsAttributeMax
};

#define PS_ATTRIBUTE_NUMBER_MASK    0x0000ffff
#define PS_ATTRIBUTE_THREAD         0x00010000 // may be used with thread creation
#define PS_ATTRIBUTE_INPUT          0x00020000 // input only
#define PS_ATTRIBUTE_ADDITIVE       0x00040000 // "accumulated" e.g. bitmasks, counters, etc.

#define PsAttributeValue(Number, Thread, Input, Additive) \
    (((Number) & PS_ATTRIBUTE_NUMBER_MASK) | \
    ((Thread) ? PS_ATTRIBUTE_THREAD : 0) | \
    ((Input) ? PS_ATTRIBUTE_INPUT : 0) | \
    ((Additive) ? PS_ATTRIBUTE_ADDITIVE : 0))

#define PS_ATTRIBUTE_PARENT_PROCESS \
    PsAttributeValue(PsAttributeParentProcess, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_DEBUG_PORT \
    PsAttributeValue(PsAttributeDebugPort, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_TOKEN \
    PsAttributeValue(PsAttributeToken, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_CLIENT_ID \
    PsAttributeValue(PsAttributeClientId, TRUE, FALSE, FALSE)
#define PS_ATTRIBUTE_TEB_ADDRESS \
    PsAttributeValue(PsAttributeTebAddress, TRUE, FALSE, FALSE)
#define PS_ATTRIBUTE_IMAGE_NAME \
    PsAttributeValue(PsAttributeImageName, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_IMAGE_INFO \
    PsAttributeValue(PsAttributeImageInfo, FALSE, FALSE, FALSE)
#define PS_ATTRIBUTE_MEMORY_RESERVE \
    PsAttributeValue(PsAttributeMemoryReserve, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_PRIORITY_CLASS \
    PsAttributeValue(PsAttributePriorityClass, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_ERROR_MODE \
    PsAttributeValue(PsAttributeErrorMode, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_STD_HANDLE_INFO \
    PsAttributeValue(PsAttributeStdHandleInfo, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_HANDLE_LIST \
    PsAttributeValue(PsAttributeHandleList, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_GROUP_AFFINITY \
    PsAttributeValue(PsAttributeGroupAffinity, TRUE, TRUE, FALSE)
#define PS_ATTRIBUTE_PREFERRED_NODE \
    PsAttributeValue(PsAttributePreferredNode, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_IDEAL_PROCESSOR \
    PsAttributeValue(PsAttributeIdealProcessor, TRUE, TRUE, FALSE)
#define PS_ATTRIBUTE_MITIGATION_OPTIONS \
    PsAttributeValue(PsAttributeMitigationOptions, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_PROTECTION_LEVEL \
    PsAttributeValue(PsAttributeProtectionLevel, FALSE, TRUE, FALSE)

typedef struct _PS_ATTRIBUTE
{
    UINT_PTR Attribute;
    SIZE_T Size;
    union
    {
        UINT_PTR Value;
        void* ValuePtr;
    };
    SIZE_T* ReturnLength;
} PS_ATTRIBUTE, *PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST
{
    SIZE_T TotalLength;
    PS_ATTRIBUTE Attributes[1]; // Attributes[8] or Attributes[PsAttributeMax] ?
} PS_ATTRIBUTE_LIST, *PPS_ATTRIBUTE_LIST;

enum PS_CREATE_STATE : UINT32
{
    PsCreateInitialState,
    PsCreateFailOnFileOpen,
    PsCreateFailOnSectionCreate,
    PsCreateFailExeFormat,
    PsCreateFailMachineMismatch,
    PsCreateFailExeName, // Debugger specified
    PsCreateSuccess,
    PsCreateMaximumStates
};

typedef struct _PS_CREATE_INFO
{
    SIZE_T Size;
    PS_CREATE_STATE State;

    union
    {
        // PsCreateInitialState
        struct
        {
            union
            {
                UINT32 InitFlags;
                struct
                {
                    UINT8 WriteOutputOnExit : 1;
                    UINT8 DetectManifest : 1;
                    UINT8 IFEOSkipDebugger : 1;
                    UINT8 IFEODoNotPropagateKeyState : 1;
                    UINT8 SpareBits1 : 4;
                    UINT8 SpareBits2 : 8;
                    UINT16 ProhibitedImageCharacteristics : 16;
                };
            };
            ACCESS_MASK AdditionalFileAccess;
        } InitState;

        // PsCreateFailOnSectionCreate
        struct
        {
            HANDLE FileHandle;
        } FailSection;

        // PsCreateFailExeFormat
        struct
        {
            UINT16 DllCharacteristics;
        } ExeFormat;

        // PsCreateFailExeName
        struct
        {
            HANDLE IFEOKey;
        } ExeName;

        // PsCreateSuccess
        struct
        {
            union
            {
                UINT32 OutputFlags;
                struct
                {
                    UINT8 ProtectedProcess : 1;
                    UINT8 AddressSpaceOverride : 1;
                    UINT8 DevOverrideEnabled : 1; // from Image File Execution Options
                    UINT8 ManifestDetected : 1;
                    UINT8 ProtectedProcessLight : 1;
                    UINT8 SpareBits1 : 3;
                    UINT8 SpareBits2 : 8;
                    UINT16 SpareBits3 : 16;
                };
            };
            HANDLE FileHandle;
            HANDLE SectionHandle;
            struct _RTL_USER_PROCESS_PARAMETERS* UserProcessParametersNative;
            UINT32 UserProcessParametersWow64;  // RTL_USER_PROCESS_PARAMETERS32*
            UINT32 CurrentParameterFlags;
            struct _PEB* PebAddressNative;
            UINT32 PebAddressWow64;             // PEB32*
            void* ManifestAddress;
            UINT32 ManifestSize;
        } SuccessState;
    };
}PS_CREATE_INFO, *PPS_CREATE_INFO;
static_assert(sizeof(PS_CREATE_INFO) == 0x58, "PS_CREATE_INFO size is wrong!");