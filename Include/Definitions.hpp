#pragma once
#include <stdlib.h>
#include <stdio.h>

//set default definitions

#if !( defined(FLUSH_OS_LINUX) || defined(FLUSH_OS_WINDOWS) )
    #define FLUSH_OS_LINUX
#endif 

#if !( defined(FLUSH_PROC_X86) || defined(FLUSH_PROC_X64) || defined(FLUSH_PROC_ARM64) || defined(FLUSH_PROC_ARM32))
    #define FLUSH_PROC_X64
#endif

#if !( defined(FLUSH_DEBUG) || defined(FLUSH_RELEASE) || defined(FLUSH_DIST))
    #define FLUSH_DEBUG
#endif 



//Basic types definitions for Windows(x86 , x64 ) , linux(x86 , x64 , arm64 , arm32)
#if     defined(FLUSH_OS_LINUX)
    #include <stdint.h>
    #include <stddef.h>

    #define __flush_u8  uint8_t
    #define __flush_u16 uint16_t 
    #define __flush_u32 uint32_t 
    #define __flush_u64 uint64_t

    #define __flush_i8   int8_t
    #define __flush_i16  int16_t 
    #define __flush_i32  int32_t 
    #define __flush_i64  int64_t

#elif   defined(FLUSH_OS_WINDOWS)
    #include <stdint.h>

    #define __flush_u8  uint8_t
    #define __flush_u16 uint16_t 
    #define __flush_u32 uint32_t 
    #define __flush_u64 uint64_t

    #define __flush_i8   int8_t
    #define __flush_i16  int16_t 
    #define __flush_i32  int32_t 
    #define __flush_i64  int64_t

#else 
    
    #error No Operating System is defined (For Windows the support will come soon !!!)

#endif 


// per processor definition for pointer types and breakpoint
#if     defined(FLUSH_PROC_X86)
            
    #define __flush_uptr    __flush_u32 
    #define __flush_iptr    __flush_i32

    #define __flush_breakpoint asm volatile("int3")

#elif   defined(FLUSH_PROC_X64)
            
    #define __flush_uptr    __flush_u64 
    #define __flush_iptr    __flush_i64
            
    #define __flush_breakpoint  asm volatile("int3")

#elif   defined(FLUSH_PROC_ARM64)

    #define __flush_uptr    __flush_u64
    #define __flush_iptr    __flush_i64 

    #define __flush_breakpoint  asm volatile("brk #0")
    
#elif   defined(FLUSH_PROC_ARM32)
 
    #define __flush_uptr    __flush_u32
    #define __flush_iptr    __flush_i32 

    #define __flush_breakpoint  asm volatile("bkpt #0")

#else 
    
    #error  No processor architecture defined 
    
#endif


// per mode definitions for the debug breakpoint usage
#if     defined(FLUSH_DEBUG)

    #define flush_breakpoint __flush_breakpoint

#elif   defined(FLUSH_RELEASE)

    #define flush_breakpoint 

#elif   defined(FLUSH_DIST)

    #define flush_breakpoint

#endif 

#define KB  1024
#define MB  1024 * KB
#define GB  1024 * MB

#define LOG_ENGINE_ERROR( message , ...) { fprintf(stderr , message , __VA_ARGS__ ); __flush_breakpoint; }
#define LOG_ENGINE_WARN ( message , ...) { fprintf(stderr , message , __VA_ARGS__ ); }
#define LOG_ENGINE_INFO ( message , ...) { fprintf(stdout , message , __VA_ARGS__ ); }

#define FLUSH_ASSERT(cond , message , ...) if (!(cond)) {  LOG_ENGINE_ERROR("Flush System Error : %s" , (message) , __VA_ARGS__  ); }

namespace Flush{
    typedef __flush_u8      u8  ;
    typedef __flush_u16     u16 ;
    typedef __flush_u32     u32 ;
    typedef __flush_u64     u64 ;

    typedef __flush_i8      i8  ;
    typedef __flush_i16     i16 ;
    typedef __flush_i32     i32 ;
    typedef __flush_i64     i64 ;

    typedef __flush_u64     fsize; // used for the size of the file
    typedef __flush_u64     lsize; // used for time variables etc.

    typedef __flush_uptr    uptr;
    typedef __flush_iptr    iptr;
    
}
