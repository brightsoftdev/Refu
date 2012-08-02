/**
** Copyright (c) 2011-2012, Karapetsas Eleftherios
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
**  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
**  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the distribution.
**  3. Neither the name of the Original Author of Refu nor the names of its contributors may be used to endorse or promote products derived from
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
**  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
**  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**  SERVICES;LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
**  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
**  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#include <rf_localmem.h>
#include <rf_setup.h>
#include <stdlib.h>//for exit()
#include <string.h>//for memset()

//define The main thread's local stack memory
RF_LocalMemoryStack RF_MainLMS;
//define the pointer to the thread specific memory stack
__thread RF_LocalMemoryStack* RF_LMS;

// A small macro to find the smallest of the macro evaluation indices. Just to avoid copying pasting
#define i_rfLMS_MinMacroEval() \
    /*If we had any macro evaluations in the function call*/\
    if(RF_LMS->macroEvalsI > 0)\
    {\
        /*find the smallest pointer of the macro evaluations. This is where the stack pointer was before the function call*/\
        stackPtrBefore = 9999999;\
        for(i=0;i< RF_LMS->macroEvalsI; i ++)\
        {\
            if(RF_LMS->macroEvals[i] < stackPtrBefore)\
                stackPtrBefore = RF_LMS->macroEvals[i];\
        }\
        /*now reset the macro evaluations to be ready for the next function call*/\
        RF_LMS->macroEvalsI = 0;\
        memset(RF_LMS->macroEvals,0,4*RF_MAX_FUNC_ARGS);\
    }\
    else\
        stackPtrBefore= RF_LMS->stackPtr;

// Initializes the local memory stack
void rfLMS_Init(RF_LocalMemoryStack* lms,uint64_t size)
{
    lms->stackPtr = 0;
    lms->macroEvalsI = 0;
    RF_MALLOC(lms->stack,size);
    memset(lms->macroEvals,0,4*RF_MAX_FUNC_ARGS);
    //also make the thread specific pointer point to this local memory stack
    RF_LMS = lms;
}


//Allocates some memory from the local memory stack
void* rfLMS_Push(RF_LocalMemoryStack* lms,size_t size)
{
    if(lms->stackPtr+size > RF_OPTION_LOCALSTACKMEMORY_SIZE)
    {
        LOG_ERROR("Local Stack Memory pushing error. Attempted to allocate more memory than currently available",RE_LOCALMEMSTACK_PUSH)
        return 0;
    }
    uint32_t temp = lms->stackPtr;
    lms->stackPtr+=size;
    return lms->stack+temp;
}


//Frees some memory from the local memory stack
void rfLMS_Pop(RF_LocalMemoryStack* lms,size_t size)
{
    if(size > lms->stackPtr)
    {
        LOG_ERROR("Local Stack Memory popping error. Attempted to pop the memory to a point in the stack that's not allocated yet",RE_LOCALMEMSTACK_POP);
        return;
    }
    lms->stackPtr=size;
}


//Keeps the stack pointer before the specific macro evaluation
void rfLMS_MacroEvalPtr(RF_LocalMemoryStack* lms)
{
    if(lms->macroEvalsI+1 >= RF_MAX_FUNC_ARGS)
    {
        LOG_ERROR("Local Stack Memory macro evaluation error. More macros than the specified maximum number of function arguments \"%d\" have been evaluated",
                  RE_LOCALMEMSTACK_MACROEVALS,RF_MAX_FUNC_ARGS);
        exit(RE_LOCALMEMSTACK_MACROEVALS);
    }
    lms->macroEvals[lms->macroEvalsI] = lms->stackPtr;
    lms->macroEvalsI++;
}
///==========================Conversion from the void* type back to basic types ==================================================///
char i_rfRETURN_char(void* ret)
{
    intptr_t cc = (intptr_t)ret;
    char r = cc;
    return r;
}
int32_t i_rfRETURN_int32_t(void* ret)
{
    intptr_t cc =(intptr_t) ret;
    int32_t r = cc;
    return  r;
}

/**These are automatically generated by the python LMS.py script**/
///===================================Local Memory Stack Function Wrappers Begin===================================///

void* i_rfLMSWrapper1(void*(*fptr)(void*),void* arg1)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
#include <String/rfc_string.h>
void* i_rfLMSWrapper2(void*(*fptr)(void*,void*),void* arg1,void* arg2)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper3(void*(*fptr)(void*,void*,void*),void* arg1,void* arg2,void* arg3)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper4(void*(*fptr)(void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper5(void*(*fptr)(void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper6(void*(*fptr)(void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper7(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper8(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,void* arg8)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper9(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,void* arg8,void* arg9)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper10(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,void* arg8,void* arg9,
void*arg10)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper11(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,
void* arg8,void* arg9,void*arg10,void*arg11)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper12(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,
void* arg8,void* arg9,void*arg10,void*arg11,void*arg12)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper13(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,
void* arg8,void* arg9,void*arg10,void*arg11,void*arg12,void*arg13)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper14(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,
void* arg8,void* arg9,void*arg10,void*arg11,void*arg12,void*arg13,void*arg14)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper15(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,
void* arg8,void* arg9,void*arg10,void*arg11,void*arg12,void*arg13,void*arg14,void*arg15)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper16(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,
void* arg8,void* arg9,void*arg10,void*arg11,void*arg12,void*arg13,void*arg14,void*arg15,void*arg16)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper17(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,
void* arg8,void* arg9,void*arg10,void*arg11,void*arg12,void*arg13,void*arg14,void*arg15,void*arg16,void*arg17)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16,arg17);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}
void* i_rfLMSWrapper18(void*(*fptr)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*),void* arg1,void* arg2,void* arg3,void* arg4,void* arg5,void* arg6,void* arg7,
void* arg8,void* arg9,void*arg10,void*arg11,void*arg12,void*arg13,void*arg14,void*arg15,void*arg16,void*arg17,void*arg18)
{
    void* ret;
    uint32_t stackPtrBefore,i;
    //find the stack position at the beginning of the function call
    i_rfLMS_MinMacroEval()
    //run the function
    ret = fptr(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16,arg17,arg18);
    //pop the stack back to where it was before the function call
    rfLMS_Pop(RF_LMS,stackPtrBefore);
    return ret;
}