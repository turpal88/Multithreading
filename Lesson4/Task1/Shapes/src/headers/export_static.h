
#ifndef API_SHAPES_H
#define API_SHAPES_H

#ifdef SHAPES_STATIC_DEFINE
#  define API_SHAPES
#  define SHAPES_NO_EXPORT
#else
#  ifndef API_SHAPES
#    ifdef Shapes_EXPORTS
        /* We are building this library */
#      define API_SHAPES 
#    else
        /* We are using this library */
#      define API_SHAPES 
#    endif
#  endif

#  ifndef SHAPES_NO_EXPORT
#    define SHAPES_NO_EXPORT 
#  endif
#endif

#ifndef SHAPES_DEPRECATED
#  define SHAPES_DEPRECATED __declspec(deprecated)
#endif

#ifndef SHAPES_DEPRECATED_EXPORT
#  define SHAPES_DEPRECATED_EXPORT API_SHAPES SHAPES_DEPRECATED
#endif

#ifndef SHAPES_DEPRECATED_NO_EXPORT
#  define SHAPES_DEPRECATED_NO_EXPORT SHAPES_NO_EXPORT SHAPES_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SHAPES_NO_DEPRECATED
#    define SHAPES_NO_DEPRECATED
#  endif
#endif

#endif /* API_SHAPES_H */
