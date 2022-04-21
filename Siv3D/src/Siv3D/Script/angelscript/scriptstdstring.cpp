#include "scriptstdstring.h"
#include <assert.h> // assert()
#include <sstream>  // std::stringstream
#include <string.h> // strstr()
#include <stdio.h>	// sprintf()
#include <stdlib.h> // strtod()
#ifndef __psp2__
	#include <locale.h> // setlocale()
#endif

# include <Siv3D/String.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Unicode.hpp>
using namespace s3d;
using namespace std;
using CharType = String::value_type;

// This macro is used to avoid warnings about unused variables.
// Usually where the variables are only used in debug mode.
#define UNUSED_VAR(x) (void)(x)

#ifdef AS_CAN_USE_CPP11
#include <unordered_map>
BEGIN_AS_NAMESPACE
typedef std::unordered_map<String, int> map_t;
END_AS_NAMESPACE
#else
#include <map>      // std::map
BEGIN_AS_NAMESPACE
typedef map<string, int> map_t;
END_AS_NAMESPACE
#endif

BEGIN_AS_NAMESPACE
class CStdStringFactory : public asIStringFactory
{
public:
	CStdStringFactory() {}
	~CStdStringFactory() 
	{
		// The script engine must release each string 
		// constant that it has requested
		assert(stringCache.size() == 0);
	}

	const void *GetStringConstant(const char *data, asUINT length)
	{
		// The string factory might be modified from multiple 
		// threads, so it is necessary to use a mutex.
		asAcquireExclusiveLock();
		
		String str = s3d::Unicode::FromUTF8(std::string_view(data, length));

		map_t::iterator it = stringCache.find(str);
		if (it != stringCache.end())
			it->second++;
		else
			it = stringCache.insert(map_t::value_type(std::move(str), 1)).first;

		asReleaseExclusiveLock();
		
		return reinterpret_cast<const void*>(&it->first);
	}

	int  ReleaseStringConstant(const void *str)
	{
		if (str == 0)
			return asERROR;

		int ret = asSUCCESS;
		
		// The string factory might be modified from multiple 
		// threads, so it is necessary to use a mutex.
		asAcquireExclusiveLock();
		
		map_t::iterator it = stringCache.find(*reinterpret_cast<const String*>(str));
		if (it == stringCache.end())
			ret = asERROR;
		else
		{
			it->second--;
			if (it->second == 0)
				stringCache.erase(it);
		}
		
		asReleaseExclusiveLock();
		
		return ret;
	}

	int  GetRawStringData(const void *str, char *data, asUINT *length) const
	{
		if (str == 0)
			return asERROR;

		const std::string s = reinterpret_cast<const String*>(str)->toUTF8();

		if (length)
			*length = (asUINT)s.length();

		if (data)
			memcpy(data, s.data(), s.size());

		return asSUCCESS;
	}

	// THe access to the string cache is protected with the common mutex provided by AngelScript
	map_t stringCache;
};

static CStdStringFactory *stringFactory = 0;

// TODO: Make this public so the application can also use the string 
//       factory and share the string constants if so desired, or to
//       monitor the size of the string factory cache.
CStdStringFactory *GetStdStringFactorySingleton()
{
	if( stringFactory == 0 )
	{
		// The following instance will be destroyed by the global 
		// CStdStringFactoryCleaner instance upon application shutdown
		stringFactory = new CStdStringFactory();
	}
	return stringFactory;
}

class CStdStringFactoryCleaner
{
public:
	~CStdStringFactoryCleaner()
	{
		if (stringFactory)
		{
			// Only delete the string factory if the stringCache is empty
			// If it is not empty, it means that someone might still attempt
			// to release string constants, so if we delete the string factory
			// the application might crash. Not deleting the cache would
			// lead to a memory leak, but since this is only happens when the
			// application is shutting down anyway, it is not important.
			if (stringFactory->stringCache.empty())
			{
				delete stringFactory;
				stringFactory = 0;
			}
		}
	}
};

static CStdStringFactoryCleaner cleaner;


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

static CharType* StringCharAt(unsigned int i, String &str)
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
	return (int)str.indexOf(sub, start);
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
	return (int)str.indexOfAny(sub, start);
}

// This function returns the index of the last position where the one of the bytes in substring
// exists in the input string. If the characters in the substring doesn't exist in the input
// string -1 is returned.
//
// AngelScript signature:
// int string::findLastOf(const string &in sub, uint start = -1) const
static int StringFindLastOf(const String &sub, int start, const String &str)
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
	return (int)str.indexNotOfAny(sub, start);
}

// This function returns the index of the last position where a byte other than those in substring
// exists in the input string. If none is found -1 is returned.
//
// AngelScript signature:
// int string::findLastNotOf(const string &in sub, uint start = -1) const
static int StringFindLastNotOf(const String &sub, int start, const String &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.lastIndexNotOfAny(sub, (size_t)(start < 0 ? String::npos : start));
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

static String StringAdd(const String& lhs, const String& rhs)
{
	return (lhs + rhs);
}

void RegisterStdString_Native(asIScriptEngine *engine)
{
	int r = 0;
	UNUSED_VAR(r);

	// Register the string type

	r = engine->RegisterStringFactory("String", GetStdStringFactorySingleton());

	// Register the object operator overloads
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f()",                    asFUNCTION(ConstructString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(const String &in)",    asFUNCTION(CopyConstructString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT,   "void f()",                    asFUNCTION(DestructString),  asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// operator =
	r = engine->RegisterObjectMethod("String", "String &opAssign(const String &in)", asMETHODPR(String, operator =, (const String&), String&), asCALL_THISCALL); assert( r >= 0 );
	
	// operator +=
	r = engine->RegisterObjectMethod("String", "String &opAddAssign(const String &in)", asMETHODPR(String, operator+=, (const String&), String&), asCALL_THISCALL); assert( r >= 0 );

	// operator ==
	r = engine->RegisterObjectMethod("String", "bool opEquals(const String &in) const", asFUNCTIONPR(StringEquals, (const String &, const String &), bool), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	// operator cmp
	r = engine->RegisterObjectMethod("String", "int opCmp(const String &in) const", asFUNCTION(StringCmp), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	
	// operator +
	r = engine->RegisterObjectMethod("String", "String opAdd(const String &in) const", asFUNCTIONPR(StringAdd, (const String&, const String&), String), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	// operator []
	r = engine->RegisterObjectMethod("String", "char32 &opIndex(uint)", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "const char32 &opIndex(uint) const", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); assert(r >= 0);

	r = engine->RegisterObjectMethod("String", "uint size() const", asFUNCTION(StringLength), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "uint length() const", asFUNCTION(StringLength), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "void resize(uint)", asFUNCTION(StringResize), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "bool empty() const", asFUNCTION(StringIsEmpty), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "bool isEmpty() const", asFUNCTION(StringIsEmpty), asCALL_CDECL_OBJLAST); assert(r >= 0);

	// operatpr <<
	r = engine->RegisterObjectMethod("String", "String& opShl(uint ch)", asMETHODPR(String, operator <<, (char32), String&), asCALL_THISCALL); assert(r >= 0);
	// push_front
	r = engine->RegisterObjectMethod("String", "void push_front(uint ch)", asMETHODPR(String, push_front, (char32), void), asCALL_THISCALL); assert(r >= 0);
	// push_back
	r = engine->RegisterObjectMethod("String", "void push_back(uint ch)", asMETHODPR(String, push_back, (char32), void), asCALL_THISCALL); assert(r >= 0);
	// pop_front
	r = engine->RegisterObjectMethod("String", "void pop_front()", asMETHODPR(String, pop_front, (), void), asCALL_THISCALL); assert(r >= 0);
	// pop_front_N
	r = engine->RegisterObjectMethod("String", "void pop_front_N(size_t)", asMETHODPR(String, pop_front_N, (size_t), void), asCALL_THISCALL); assert(r >= 0);
	// pop_back
	r = engine->RegisterObjectMethod("String", "void pop_back()", asMETHODPR(String, pop_back, (), void), asCALL_THISCALL); assert(r >= 0);
	// pop_back_N
	r = engine->RegisterObjectMethod("String", "void pop_back_N(size_t)", asMETHODPR(String, pop_back_N, (size_t), void), asCALL_THISCALL); assert(r >= 0);

	// front()
	r = engine->RegisterObjectMethod("String", "char32& front()", asMETHODPR(String, front, (), char32&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "const char32& front() const", asMETHODPR(String, front, () const, const char32&), asCALL_THISCALL); assert(r >= 0);

	// back()
	r = engine->RegisterObjectMethod("String", "char32& back()", asMETHODPR(String, back, (), char32&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "const char32& back() const", asMETHODPR(String, back, () const, const char32&), asCALL_THISCALL); assert(r >= 0);

	// substr()
	r = engine->RegisterObjectMethod("String", "String substr(uint start = 0, int count = -1) const", asFUNCTION(StringSubString), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// insert()
	r = engine->RegisterObjectMethod("String", "void insert(uint pos, const String &in other)", asFUNCTION(StringInsert), asCALL_CDECL_OBJLAST); assert(r >= 0);
	
	// erase()
	r = engine->RegisterObjectMethod("String", "void erase(uint pos, int count = -1)", asFUNCTION(StringErase), asCALL_CDECL_OBJLAST); assert(r >= 0);

	r = engine->RegisterObjectMethod("String", "int indexOf(const String &in, uint start = 0) const", asFUNCTION(StringFindFirst), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "int lastIndexOf(const String &in, int start = -1) const", asFUNCTION(StringFindLast), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "int indexOfAny(const String &in, uint start = 0) const", asFUNCTION(StringFindFirstOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "int indexNotOfAny(const String &in, uint start = 0) const", asFUNCTION(StringFindFirstNotOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "int lastIndexOfAny(const String &in, int start = -1) const", asFUNCTION(StringFindLastOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("String", "int lastIndexNotOfAny(const String &in, int start = -1) const", asFUNCTION(StringFindLastNotOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
}

void RegisterStdString(asIScriptEngine * engine)
{
	RegisterStdString_Native(engine);
}

END_AS_NAMESPACE
