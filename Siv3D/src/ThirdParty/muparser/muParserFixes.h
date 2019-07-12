/*
                 __________                                      
    _____   __ __\______   \_____  _______  ______  ____ _______ 
   /     \ |  |  \|     ___/\__  \ \_  __ \/  ___/_/ __ \\_  __ \
  |  Y Y  \|  |  /|    |     / __ \_|  | \/\___ \ \  ___/ |  | \/
  |__|_|  /|____/ |____|    (____  /|__|  /____  > \___  >|__|   
        \/                       \/            \/      \/        
  Copyright (C) 2013 Ingo Berg

  Permission is hereby granted, free of charge, to any person obtaining a copy of this 
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify, 
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
  permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or 
  substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
  NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
*/

#ifndef MU_PARSER_FIXES_H
#define MU_PARSER_FIXES_H

/** \file
    \brief This file contains compatibility fixes for some platforms.
*/

//
// Compatibility fixes
//

//---------------------------------------------------------------------------
//
// Intel Compiler
//
//---------------------------------------------------------------------------

#ifdef __INTEL_COMPILER

// remark #981: operands are evaluated in unspecified order
// disabled -> completely pointless if the functions do not have side effects
//
#pragma warning(disable:981)

// remark #383: value copied to temporary, reference to temporary used
#pragma warning(disable:383)

// remark #1572: floating-point equality and inequality comparisons are unreliable
// disabled -> everyone knows it, the parser passes this problem
//             deliberately to the user
#pragma warning(disable:1572)

#endif


/* From http://gcc.gnu.org/wiki/Visibility */
/* Generic helper definitions for shared library support */
#if defined _WIN32 || defined __CYGWIN__
#define MUPARSER_HELPER_DLL_IMPORT __declspec(dllimport)
#define MUPARSER_HELPER_DLL_EXPORT __declspec(dllexport)
#define MUPARSER_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define MUPARSER_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define MUPARSER_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define MUPARSER_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define MUPARSER_HELPER_DLL_IMPORT
#define MUPARSER_HELPER_DLL_EXPORT
#define MUPARSER_HELPER_DLL_LOCAL
#endif
#endif

/* Now we use the generic helper definitions above to define API_EXPORT_CXX and MUPARSER_LOCAL.
 * API_EXPORT_CXX is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
 * MUPARSER_LOCAL is used for non-api symbols. */

#ifndef MUPARSER_STATIC /* defined if muParser is compiled as a DLL */
#ifdef MUPARSERLIB_EXPORTS /* defined if we are building the muParser DLL (instead of using it) */
#define API_EXPORT_CXX MUPARSER_HELPER_DLL_EXPORT
#else
#define API_EXPORT_CXX MUPARSER_HELPER_DLL_IMPORT
#endif /* MUPARSER_DLL_EXPORTS */
#define MUPARSER_LOCAL MUPARSER_HELPER_DLL_LOCAL
#else /* MUPARSER_STATIC is defined: this means muParser is a static lib. */
#define API_EXPORT_CXX
#define MUPARSER_LOCAL
#endif /* !MUPARSER_STATIC */


#ifdef _WIN32
#define API_EXPORT(TYPE) API_EXPORT_CXX TYPE __cdecl
#else
#define API_EXPORT(TYPE) TYPE
#endif


#endif // include guard


