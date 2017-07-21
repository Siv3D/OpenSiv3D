#include "scriptstdstring.h"
#include <assert.h> // assert()
#include <sstream>  // std::stringstream
#include <string.h> // strstr()
#include <stdio.h>	// sprintf()
#include <stdlib.h> // strtod()
# include <Siv3D/String.hpp>
#ifndef __psp2__
	#include <locale.h> // setlocale()
#endif

using namespace std;
using s3d::String;
using CharType = s3d::String::value_type;

// This macro is used to avoid warnings about unused variables.
// Usually where the variables are only used in debug mode.
#define UNUSED_VAR(x) (void)(x)

#if AS_USE_STRINGPOOL == 1

#ifdef AS_CAN_USE_CPP11
	// The string pool doesn't need to keep a specific order in the
	// pool, so the unordered_map is faster than the ordinary map
	#include <unordered_map>  // std::unordered_map
BEGIN_AS_NAMESPACE
	typedef unordered_map<const CharType *, String> map_t;
END_AS_NAMESPACE
#else
	#include <map>      // std::map
BEGIN_AS_NAMESPACE
	typedef map<const CharType *, String> map_t;
END_AS_NAMESPACE
#endif

BEGIN_AS_NAMESPACE

// By keeping the literal strings in a pool the application
// performance is improved as there are less string copies created.

// The string pool will be kept as user data in the engine. We'll
// need a specific type to identify the string pool user data.
// We just define a number here that we assume nobody else is using for
// object type user data. The add-ons have reserved the numbers 1000
// through 1999 for this purpose, so we should be fine.
const asPWORD STRING_POOL = 1001;

// This global static variable is placed here rather than locally within the
// StringFactory, due to memory leak detectors that don't see the deallocation
// of global variables. By placing the variable globally it will be initialized
// before the memory leak detector starts, thus it won't report the missing
// deallocation. An example of this the Marmalade leak detector initialized with
// IwGxInit() and finished with IwGxTerminate().
static const String emptyString;

static const String &StringFactory(asUINT length, const CharType *s)
{
	length /= 2;

	// Each engine instance has its own string pool
	asIScriptContext *ctx = asGetActiveContext();
	if( ctx == 0 )
	{
		// The string factory can only be called from a script
		assert( ctx );
		return emptyString;
	}
	asIScriptEngine *engine = ctx->GetEngine();

	map_t *pool = reinterpret_cast< map_t* >(engine->GetUserData(STRING_POOL));
	if( !pool )
	{
		// The string pool hasn't been created yet, so we'll create it now
		asAcquireExclusiveLock();

		// Make sure the string pool wasn't created while we were waiting for the lock
		pool = reinterpret_cast< map_t* >(engine->GetUserData(STRING_POOL));
		if( !pool )
		{
			#if defined(__S3E__)
			pool = new map_t;
			#else
			pool = new (nothrow) map_t;
			#endif
			if( pool == 0 )
			{
				ctx->SetException("Out of memory");
				asReleaseExclusiveLock();
				return emptyString;
			}
			engine->SetUserData(pool, STRING_POOL);
		}

		asReleaseExclusiveLock();
	}

	// We can't let other threads modify the pool while we query it
	asAcquireSharedLock();

	// First check if a string object hasn't been created already
	map_t::iterator it;
	it = pool->find(s);
	if( it != pool->end() )
	{
		asReleaseSharedLock();
		return it->second;
	}

	asReleaseSharedLock();

	// Acquire an exclusive lock so we can add the new string to the pool
	asAcquireExclusiveLock();

	// Make sure the string wasn't created while we were waiting for the exclusive lock
	it = pool->find(s);
	if( it == pool->end() )
	{
		// Create a new string object
		it = pool->insert(map_t::value_type(s, String(s, length))).first;
	}

	asReleaseExclusiveLock();
	return it->second;
}

static void CleanupEngineStringPool(asIScriptEngine *engine)
{
	map_t *pool = reinterpret_cast< map_t* >(engine->GetUserData(STRING_POOL));
	if( pool )
		delete pool;
}

#else
static string StringFactory(asUINT length, const CharType *s)
{
	return string(s, length);
}
#endif

static void ConstructString(String *thisPointer)
{
	new(thisPointer) String();
}

static void CopyConstructString(const String &other, String *thisPointer)
{
	new(thisPointer) String(other);
}

static void DestructString(String *thisPointer)
{
	thisPointer->~String();
}

static String &AddAssignStringToString(const String &str, String &dest)
{
	// We don't register the method directly because some compilers
	// and standard libraries inline the definition, resulting in the
	// linker being unable to find the declaration.
	// Example: CLang/LLVM with XCode 4.3 on OSX 10.7
	dest += str;
	return dest;
}

// bool string::isEmpty()
// bool string::empty() // if AS_USE_STLNAMES == 1
static bool StringIsEmpty(const String &str)
{
	// We don't register the method directly because some compilers
	// and standard libraries inline the definition, resulting in the
	// linker being unable to find the declaration
	// Example: CLang/LLVM with XCode 4.3 on OSX 10.7
	return str.empty();
}

static CharType *StringCharAt(unsigned int i, String &str)
{
	if( i >= str.size() )
	{
		// Set a script exception
		asIScriptContext *ctx = asGetActiveContext();
		ctx->SetException("Out of range");

		// Return a null pointer
		return 0;
	}

	return &str[i];
}

// AngelScript signature:
// int string::opCmp(const string &in) const
static int StringCmp(const String &a, const String &b)
{
	int cmp = 0;
	if( a < b ) cmp = -1;
	else if( a > b ) cmp = 1;
	return cmp;
}

// This function returns the index of the first position where the substring
// exists in the input string. If the substring doesn't exist in the input
// string -1 is returned.
//
// AngelScript signature:
// int string::findFirst(const string &in sub, uint start = 0) const
static int StringFindFirst(const String &sub, asUINT start, const String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.indexOf(sub, (size_t)(start < 0 ? String::npos : start));
}

// This function returns the index of the first position where the one of the bytes in substring
// exists in the input string. If the characters in the substring doesn't exist in the input
// string -1 is returned.
//
// AngelScript signature:
// int string::findFirstOf(const string &in sub, uint start = 0) const
static int StringFindFirstOf(const String &sub, asUINT start, const String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.indexOfAny(sub, (size_t)(start < 0 ? string::npos : start));
}

// This function returns the index of the last position where the one of the bytes in substring
// exists in the input string. If the characters in the substring doesn't exist in the input
// string -1 is returned.
//
// AngelScript signature:
// int string::findLastOf(const string &in sub, uint start = -1) const
static int StringFindLastOf(const String &sub, asUINT start, const String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.lastIndexOfAny(sub, (size_t)(start < 0 ? String::npos : start));
}

// This function returns the index of the first position where a byte other than those in substring
// exists in the input string. If none is found -1 is returned.
//
// AngelScript signature:
// int string::findFirstNotOf(const string &in sub, uint start = 0) const
static int StringFindFirstNotOf(const String &sub, asUINT start, const String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.indexNotOfAny(sub, (size_t)(start < 0 ? String::npos : start));
}

// This function returns the index of the last position where a byte other than those in substring
// exists in the input string. If none is found -1 is returned.
//
// AngelScript signature:
// int string::findLastNotOf(const string &in sub, uint start = -1) const
static int StringFindLastNotOf(const String &sub, asUINT start, const String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.lastIndexOfAny(sub, (size_t)(start < 0 ? String::npos : start));
}

// This function returns the index of the last position where the substring
// exists in the input string. If the substring doesn't exist in the input
// string -1 is returned.
//
// AngelScript signature:
// int string::findLast(const string &in sub, int start = -1) const
static int StringFindLast(const String &sub, int start, const String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.lastIndexOf(sub, (size_t)(start < 0 ? String::npos : start));
}

// AngelScript signature:
// void string::insert(uint pos, const string &in other)
static void StringInsert(unsigned int pos, const String &other, String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	str.insert(pos, other);
}

// AngelScript signature:
// void string::erase(uint pos, int count = -1)
static void StringErase(unsigned int pos, int count, String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	str.erase(pos, (size_t)(count < 0 ? String::npos : count));
}


// AngelScript signature:
// uint string::length() const
static asUINT StringLength(const String &str)
{
	// We don't register the method directly because the return type changes between 32bit and 64bit platforms
	return (asUINT)str.length();
}


// AngelScript signature:
// void string::resize(uint l)
static void StringResize(asUINT l, String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	str.resize(l);
}

// This function returns a string containing the substring of the input string
// determined by the starting index and count of characters.
//
// AngelScript signature:
// string string::substr(uint start = 0, int count = -1) const
static String StringSubString(asUINT start, int count, const String &str)
{
	// Check for out-of-bounds
	String ret;
	if( start < str.length() && count != 0 )
		ret = str.substr(start, (size_t)(count < 0 ? String::npos : count));

	return ret;
}

// String equality comparison.
// Returns true iff lhs is equal to rhs.
//
// For some reason gcc 4.7 has difficulties resolving the
// asFUNCTIONPR(operator==, (const string &, const string &)
// makro, so this wrapper was introduced as work around.
static bool StringEquals(const String& lhs, const String& rhs)
{
	return lhs == rhs;
}

void RegisterStdString_Native(asIScriptEngine *engine)
{
	using namespace s3d;

	int r = 0;
	UNUSED_VAR(r);

//	// Register the String type
//#if AS_CAN_USE_CPP11
//	// With C++11 it is possible to use asGetTypeTraits to automatically determine the correct flags to use
//	r = engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asGetTypeTraits<String>()); assert( r >= 0 );
//#else
//	r = engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); assert( r >= 0 );
//#endif

#if AS_USE_STRINGPOOL == 1
	// Register the String factory
	r = engine->RegisterStringFactory("const String &", asFUNCTION(StringFactory), asCALL_CDECL); assert( r >= 0 );

	// Register the cleanup callback for the String pool
	engine->SetEngineUserDataCleanupCallback(CleanupEngineStringPool, STRING_POOL);
#else
	// Register the String factory
	r = engine->RegisterStringFactory("String", asFUNCTION(StringFactory), asCALL_CDECL); assert( r >= 0 );
#endif

	// Register the object operator overloads
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f()",                    asFUNCTION(ConstructString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(const String &in)",    asFUNCTION(CopyConstructString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT,   "void f()",                    asFUNCTION(DestructString),  asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String &opAssign(const String &in)", asMETHODPR(String, operator =, (const String&), String&), asCALL_THISCALL); assert( r >= 0 );
	// Need to use a wrapper on Mac OS X 10.7/XCode 4.3 and CLang/LLVM, otherwise the linker fails
	r = engine->RegisterObjectMethod("String", "String &opAddAssign(const String &in)", asFUNCTION(AddAssignStringToString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
//	r = engine->RegisterObjectMethod("String", "String &opAddAssign(const String &in)", asMETHODPR(String, operator+=, (const String&), String&), asCALL_THISCALL); assert( r >= 0 );

	// Need to use a wrapper for operator== otherwise gcc 4.7 fails to compile
	r = engine->RegisterObjectMethod("String", "bool opEquals(const String &in) const", asFUNCTIONPR(StringEquals, (const String &, const String &), bool), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int opCmp(const String &in) const", asFUNCTION(StringCmp), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String opAdd(const String &in) const", asFUNCTIONPR(operator +, (const String &, const String &), String), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	// The String length can be accessed through methods or through virtual property
	r = engine->RegisterObjectMethod("String", "uint length() const", asFUNCTION(StringLength), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "void resize(uint)", asFUNCTION(StringResize), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "uint get_length() const", asFUNCTION(StringLength), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "void set_length(uint)", asFUNCTION(StringResize), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	// Need to use a wrapper on Mac OS X 10.7/XCode 4.3 and CLang/LLVM, otherwise the linker fails
//	r = engine->RegisterObjectMethod("String", "bool isEmpty() const", asMETHOD(String, empty), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool isEmpty() const", asFUNCTION(StringIsEmpty), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// Register the index operator, both as a mutator and as an inspector
	// Note that we don't register the operator[] directly, as it doesn't do bounds checking
	r = engine->RegisterObjectMethod("String", "uint8 &opIndex(uint)", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "const uint8 &opIndex(uint) const", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// Utilities
	r = engine->RegisterObjectMethod("String", "String substr(uint start = 0, int count = -1) const", asFUNCTION(StringSubString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int findFirst(const String &in, uint start = 0) const", asFUNCTION(StringFindFirst), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int findFirstOf(const String &in, uint start = 0) const", asFUNCTION(StringFindFirstOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "int findFirstNotOf(const String &in, uint start = 0) const", asFUNCTION(StringFindFirstNotOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "int findLast(const String &in, int start = -1) const", asFUNCTION(StringFindLast), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int findLastOf(const String &in, int start = -1) const", asFUNCTION(StringFindLastOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "int findLastNotOf(const String &in, int start = -1) const", asFUNCTION(StringFindLastNotOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "void insert(uint pos, const String &in other)", asFUNCTION(StringInsert), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "void erase(uint pos, int count = -1)", asFUNCTION(StringErase), asCALL_CDECL_OBJLAST); assert(r >= 0);

#if AS_USE_STLNAMES == 1
	// Same as length
	r = engine->RegisterObjectMethod("String", "uint size() const", asFUNCTION(StringLength), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	// Same as isEmpty
	r = engine->RegisterObjectMethod("String", "bool empty() const", asFUNCTION(StringIsEmpty), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	// Same as findFirst
	r = engine->RegisterObjectMethod("String", "int find(const String &in, uint start = 0) const", asFUNCTION(StringFindFirst), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	// Same as findLast
	r = engine->RegisterObjectMethod("String", "int rfind(const String &in, int start = -1) const", asFUNCTION(StringFindLast), asCALL_CDECL_OBJLAST); assert( r >= 0 );
#endif

	// TODO: Implement the following
	// findAndReplace - replaces a text found in the String
	// replaceRange - replaces a range of bytes in the String
	// multiply/times/opMul/opMul_r - takes the String and multiplies it n times, e.g. "-".multiply(5) returns "-----"
}

void RegisterStdString(asIScriptEngine * engine)
{
	RegisterStdString_Native(engine);
}

END_AS_NAMESPACE




