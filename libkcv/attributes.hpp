#ifndef KCVERIFY_ATTRIBUTES_HPP_INCLUDED
#define KCVERIFY_ATTRIBUTES_HPP_INCLUDED

// noinline属性を定義する. [[NOINLINE]]のように指定する.
#ifndef NOINLINE
    #if defined(__GNUC__) && !defined(__clang__)
        #define NOINLINE gnu::noinline
    #elif defined(__clang__)
        #define NOINLINE clang::noinline
    #elif defined(_MSC_VER)
        #define NOINLINE msvc::noinline
    #else
        #define NOINLINE
    #endif
#elif
    #warning `NOINLINE` macro has already been defined.
#endif

#endif  // KCVERIFY_ATTRIBUTES_HPP_INCLUDED
