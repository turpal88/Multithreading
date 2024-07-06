
#ifndef API_THREAD_POOL_H
#define API_THREAD_POOL_H

#ifdef THREADPOOL_STATIC_DEFINE
#  define API_THREAD_POOL
#  define THREADPOOL_NO_EXPORT
#else
#  ifndef API_THREAD_POOL
#    ifdef ThreadPool_EXPORTS
        /* We are building this library */
#      define API_THREAD_POOL __declspec(dllexport)
#    else
        /* We are using this library */
#      define API_THREAD_POOL __declspec(dllimport)
#    endif
#  endif

#  ifndef THREADPOOL_NO_EXPORT
#    define THREADPOOL_NO_EXPORT 
#  endif
#endif

#ifndef THREADPOOL_DEPRECATED
#  define THREADPOOL_DEPRECATED __declspec(deprecated)
#endif

#ifndef THREADPOOL_DEPRECATED_EXPORT
#  define THREADPOOL_DEPRECATED_EXPORT API_THREAD_POOL THREADPOOL_DEPRECATED
#endif

#ifndef THREADPOOL_DEPRECATED_NO_EXPORT
#  define THREADPOOL_DEPRECATED_NO_EXPORT THREADPOOL_NO_EXPORT THREADPOOL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef THREADPOOL_NO_DEPRECATED
#    define THREADPOOL_NO_DEPRECATED
#  endif
#endif

#endif /* API_THREAD_POOL_H */
