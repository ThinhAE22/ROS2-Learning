#ifndef ACTION_SERVER_CLIENT_CPP__VISIBILITY_CONTROL_H_
#define ACTION_SERVER_CLIENT_CPP__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif


#if defined _WIN32 || defined __CYGWIN__
    #ifdef __GNUC__
        #define ACTION_SERVER_CLIENT_CPP_EXPORT __attribute__ ((dllexport))
        #define ACTION_SERVER_CLIENT_CPP_IMPORT __attribute__ ((dllimport))
    #else
        #define ACTION_SERVER_CLIENT_CPP_EXPORT __declspec(dllexport)
        #define ACTION_SERVER_CLIENT_CPP_IMPORT __declspec(dllimport)
    #endif
    #ifdef ACTION_SERVER_CLIENT_CPP_BUILDING_DLL
        #define ACTION_SERVER_CLIENT_CPP_PUBLIC ACTION_SERVER_CLIENT_CPP_EXPORT
    #else
        #define ACTION_SERVER_CLIENT_CPP_PUBLIC ACTION_SERVER_CLIENT_CPP_IMPORT
    #endif
    #define ACTION_SERVER_CLIENT_CPP_PUBLIC_TYPE ACTION_SERVER_CLIENT_CPP_PUBLIC
    #define ACTION_SERVER_CLIENT_CPP_LOCAL
#else
    #define ACTION_SERVER_CLIENT_CPP_EXPORT __attribute__ ((visibility("default")))
    #define ACTION_SERVER_CLIENT_CPP_IMPORT
    #if __GNUC__ >= 4
        #define ACTION_SERVER_CLIENT_CPP_PUBLIC __attribute__ ((visibility("default")))
        #define ACTION_SERVER_CLIENT_CPP_LOCAL  __attribute__ ((visibility("hidden")))
    #else
        #define ACTION_SERVER_CLIENT_CPP_PUBLIC
        #define ACTION_SERVER_CLIENT_CPP_LOCAL
    #endif
    #define ACTION_SERVER_CLIENT_CPP_PUBLIC_TYPE

    #ifdef __cplusplus
    }
    #endif

#endif  
#endif  // ACTION_SERVER_CLIENT_CPP__VISIBILITY_CONTROL_H_