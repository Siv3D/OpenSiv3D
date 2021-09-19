#include "as_config.h"

#ifndef AS_MAX_PORTABILITY
#ifdef AS_WASM32

#include "as_scriptengine.h"
#include "as_texts.h"
#include "as_context.h"

typedef asQWORD ( *funcptr_t )( void );

extern "C" int siv3dCallIndirect(funcptr_t func, const asBYTE* sig, void* retPtr, void* argPtr);
extern "C" int siv3dCallIndirectReturnInMemory(funcptr_t func, const asBYTE* sig, void* retPtr, void* argPtr);

BEGIN_AS_NAMESPACE

#define MAX_ARGS             32

enum argTypes { x32INTARG = 'i', x64INTARG = 'j', x32FLOATARG = 'f', x64FLOATARG = 'd', x32VOIDARG = 'v' };

// returns true if the given parameter is a 'variable argument'
static inline bool IsVariableArgument( asCDataType type )
{
	return ( type.GetTokenType() == ttQuestion ) ? true : false;
}

asQWORD CallSystemFunctionNative(asCContext *context, asCScriptFunction *descr, void *obj, asDWORD *args, void *retPointer, asQWORD &retQW2, void *secondObject)
{
	asCScriptEngine            *engine             = context->m_engine;
	asSSystemFunctionInterface *sysFunc            = descr->sysFuncIntf;
	int                         callConv           = sysFunc->callConv;
	asQWORD                     retQW              = 0;
	asDWORD                    *stack_pointer      = args;
	funcptr_t                  *vftable            = NULL;
	int                         totalArgumentCount = 0;
	int                         returnInMemory     = 0;
	int                         param_post         = 0;
	int                         argIndex           = 0;
	funcptr_t                   func               = (funcptr_t)sysFunc->func;


	if( sysFunc->hostReturnInMemory ) 
	{
		// The return is made in memory
		callConv++;
	}

#ifdef AS_NO_THISCALL_FUNCTOR_METHOD
	// Determine the real function pointer in case of virtual method
	if ( obj && ( callConv == ICC_VIRTUAL_THISCALL || callConv == ICC_VIRTUAL_THISCALL_RETURNINMEM ) ) 
#else
	if ( obj && ( callConv == ICC_VIRTUAL_THISCALL ||
		callConv == ICC_VIRTUAL_THISCALL_RETURNINMEM ||
		callConv == ICC_VIRTUAL_THISCALL_OBJFIRST ||
		callConv == ICC_VIRTUAL_THISCALL_OBJFIRST_RETURNINMEM ||
		callConv == ICC_VIRTUAL_THISCALL_OBJLAST ||
		callConv == ICC_VIRTUAL_THISCALL_OBJLAST_RETURNINMEM) )
#endif
	{
		// vftable = *((funcptr_t**)obj);
		// auto fptr = FuncPtrToUInt(asFUNCTION_t(func));
		// func = vftable[FuncPtrToUInt(asFUNCTION_t(func)) >> 2];
		// printf("detect this_call: vftable = %d, func = %d, deref func = %d\n", vftable, fptr, func);
	}

	asDWORD paramBuffer[MAX_ARGS] = { 0 };
	int 	paramIndex = 0;
	asBYTE 	argsType[MAX_ARGS] = { 0 };

	{
		const asCDataType &returnType = descr->returnType;

		if( returnType.IsFloatType() && !returnType.IsReference() ) 
		{
			argsType[0] = x32FLOATARG;
		} 
		else if( returnType.IsDoubleType() && !returnType.IsReference() )
		{
			argsType[0] = x64FLOATARG;
		}
		else if( returnType.IsPrimitive() ||
		         returnType.IsReference() || 
		         returnType.IsObjectHandle() )
		{
			if( returnType.GetSizeOnStackDWords() == 1 )
			{
				argsType[0] = x32INTARG;
			}
			else
			{
				argsType[0] = x64INTARG;
			}
		}
		else
		{
			// An object is being passed by value
			if( (returnType.GetTypeInfo()->flags & COMPLEX_MASK) ||
			    returnType.GetSizeInMemoryDWords() > 4 )
			{
				argsType[0] = x32INTARG;
			}
			else if( (returnType.GetTypeInfo()->flags & asOBJ_APP_CLASS_ALLINTS) ||
			         (returnType.GetTypeInfo()->flags & asOBJ_APP_PRIMITIVE) )
			{
				// Copy the value of the object
				if( returnType.GetSizeInMemoryDWords() > 2 )
				{
					argsType[0] = x32INTARG;
					printf("Warning: Object may not be copied properly. : Object Size=%d\n", returnType.GetSizeInMemoryBytes());
				}
				else
				{
					argsType[0] = x32INTARG;
				}
			}
			else if( (returnType.GetTypeInfo()->flags & asOBJ_APP_CLASS_ALLFLOATS) ||
			         (returnType.GetTypeInfo()->flags & asOBJ_APP_FLOAT) )
			{
				// Copy the value of the object
				if( returnType.GetSizeInMemoryDWords() > 2 )
				{
					argsType[0] = x32FLOATARG;
					printf("Warning: Object may not be copied properly. : Object Size=%d\n", returnType.GetSizeInMemoryBytes());
				}
				else
				{
					argsType[0] = x32FLOATARG;
				}
			}
			else
			{
				argsType[0] = x32VOIDARG;			
			}
		}

		argIndex = 1;
	}

	switch ( callConv ) 
	{
		case ICC_CDECL_RETURNINMEM:
		case ICC_STDCALL_RETURNINMEM: 
		{
			paramBuffer[0] = (asPWORD)retPointer;
			argsType[argIndex] = x32INTARG;

			argIndex++;
			paramIndex++;

			returnInMemory = 1;
			break;
		}
#ifndef AS_NO_THISCALL_FUNCTOR_METHOD
		case ICC_THISCALL_OBJLAST:
		case ICC_VIRTUAL_THISCALL_OBJLAST:
			param_post = 2;
#endif
		case ICC_THISCALL:
		case ICC_VIRTUAL_THISCALL:
		case ICC_CDECL_OBJFIRST: 
		{
			paramBuffer[0] = (asPWORD)obj;
			argsType[argIndex] = x32INTARG;

			argIndex++;
			paramIndex++;

			break;
		}
#ifndef AS_NO_THISCALL_FUNCTOR_METHOD
		case ICC_THISCALL_OBJLAST_RETURNINMEM:
		case ICC_VIRTUAL_THISCALL_OBJLAST_RETURNINMEM:
			param_post = 2;
#endif
		case ICC_THISCALL_RETURNINMEM:
		case ICC_VIRTUAL_THISCALL_RETURNINMEM:
		case ICC_CDECL_OBJFIRST_RETURNINMEM: 
		{
			paramBuffer[0] = (asPWORD)retPointer;
			paramBuffer[1] = (asPWORD)obj;
			argsType[argIndex] = x32INTARG;
			argsType[argIndex + 1] = x32INTARG;

			argIndex += 2;
			paramIndex += 2;

			returnInMemory = 1;
			break;
		}
#ifndef AS_NO_THISCALL_FUNCTOR_METHOD
		case ICC_THISCALL_OBJFIRST:
		case ICC_VIRTUAL_THISCALL_OBJFIRST:
		{
			paramBuffer[0] = (asPWORD)obj;
			paramBuffer[1] = (asPWORD)secondObject;
			argsType[argIndex] = x32INTARG;
			argsType[argIndex + 1] = x32INTARG;

			argIndex += 2;
			paramIndex += 2;

			break;
		}
		case ICC_THISCALL_OBJFIRST_RETURNINMEM:
		case ICC_VIRTUAL_THISCALL_OBJFIRST_RETURNINMEM:
		{
			paramBuffer[0] = (asPWORD)retPointer;
			paramBuffer[1] = (asPWORD)obj;
			paramBuffer[2] = (asPWORD)secondObject;
			argsType[argIndex] = x32INTARG;
			argsType[argIndex + 1] = x32INTARG;
			argsType[argIndex + 2] = x32INTARG;

			argIndex += 3;
			paramIndex += 3;

			returnInMemory = 1;
			break;
		}
#endif
		case ICC_CDECL_OBJLAST:
			param_post = 1;
			break;
		case ICC_CDECL_OBJLAST_RETURNINMEM: 
		{
			paramBuffer[0] = (asPWORD)retPointer;
			argsType[argIndex] = x32INTARG;

			argIndex += 1;
			paramIndex += 1;
			param_post = 1;

			returnInMemory = 1;
			break;
		}
	}

	int argumentCount = ( int )descr->parameterTypes.GetLength();
	for( int a = 0; a < argumentCount; ++a ) 
	{
		const asCDataType &parmType = descr->parameterTypes[a];

		if( parmType.IsFloatType() && !parmType.IsReference() ) 
		{
			argsType[argIndex] = x32FLOATARG;
			memcpy(paramBuffer + paramIndex, stack_pointer, sizeof(float));
			argIndex++;
			paramIndex += 2;
			stack_pointer += 2;
		}
		else if( parmType.IsDoubleType() && !parmType.IsReference() ) 
		{
			argsType[argIndex] = x64FLOATARG;
            paramIndex += paramIndex % 2;
			memcpy(paramBuffer + paramIndex, stack_pointer, sizeof(double));
			argIndex++;
			paramIndex += 2;
			stack_pointer += 2;
		}
		else if( IsVariableArgument( parmType ) ) 
		{
			// The variable args are really two, one pointer and one type id
			argsType[argIndex] = x32INTARG;
			argsType[argIndex + 1] = x32INTARG;
			memcpy(paramBuffer + paramIndex, stack_pointer, sizeof(void*) + sizeof(asDWORD));
			argIndex++;
			paramIndex += 2;
			stack_pointer += 2;
		}
		else if( parmType.IsPrimitive() ||
		         parmType.IsReference() || 
		         parmType.IsObjectHandle() )
		{
			if( parmType.GetSizeOnStackDWords() == 1 )
			{
				argsType[argIndex] = x32INTARG;
				memcpy(paramBuffer + paramIndex, stack_pointer, sizeof(asDWORD));
				argIndex++;
				paramIndex++;
				stack_pointer++;
			}
			else
			{
				argsType[argIndex] = x64INTARG;
				memcpy(paramBuffer + paramIndex, stack_pointer, sizeof(asQWORD));
				argIndex++;
				paramIndex += 2;
				stack_pointer += 2;
			}
		}
		else {
			// An object is being passed by value
			if( (parmType.GetTypeInfo()->flags & COMPLEX_MASK) ||
			    parmType.GetSizeInMemoryDWords() > 4 )
			{
				argsType[argIndex] = x32INTARG;
				memcpy(paramBuffer + paramIndex, stack_pointer, sizeof(asDWORD));
				argIndex++;
				paramIndex++;
				stack_pointer++;
			}
			else if( (parmType.GetTypeInfo()->flags & asOBJ_APP_CLASS_ALLINTS) ||
			         (parmType.GetTypeInfo()->flags & asOBJ_APP_PRIMITIVE) )
			{
				// Copy the value of the object
				if( parmType.GetSizeInMemoryDWords() > 2 )
				{
					argsType[argIndex] = x32INTARG;
					argsType[argIndex + 1] = x32INTARG;
					memcpy(paramBuffer + paramIndex, stack_pointer, parmType.GetSizeInMemoryBytes());
					argIndex += 2;
					paramIndex += 2;
					stack_pointer += 2;
				}
				else
				{
					argsType[argIndex] = x32INTARG;
					memcpy(paramBuffer + paramIndex, stack_pointer, parmType.GetSizeInMemoryBytes());
					argIndex++;
					paramIndex++;
					stack_pointer++;
				}
				// Delete the original memory
				engine->CallFree(*(void**)stack_pointer);
			}
			else if( (parmType.GetTypeInfo()->flags & asOBJ_APP_CLASS_ALLFLOATS) ||
			         (parmType.GetTypeInfo()->flags & asOBJ_APP_FLOAT) )
			{
				// Copy the value of the object
				if( parmType.GetSizeInMemoryDWords() > 2 )
				{
					argsType[argIndex] = x32FLOATARG;
					argsType[argIndex + 1] = x32FLOATARG;
					memcpy(paramBuffer + paramIndex, stack_pointer, parmType.GetSizeInMemoryBytes());
					argIndex += 2;
					paramIndex += 2;
					stack_pointer += 2;
				}
				else
				{
					argsType[argIndex] = x32FLOATARG;
					memcpy(paramBuffer + paramIndex, stack_pointer, parmType.GetSizeInMemoryBytes());
					argIndex++;
					paramIndex++;
					stack_pointer++;
				}
				// Delete the original memory
				engine->CallFree(*(void**)stack_pointer);
			}
		} 
	}

	// For the CDECL_OBJ_LAST calling convention we need to add the object pointer as the last argument
	if( param_post )
	{
#ifdef AS_NO_THISCALL_FUNCTOR_METHOD
		paramBuffer[paramIndex] = (asPWORD)obj;
#else
		paramBuffer[paramIndex] = (asPWORD)(param_post > 1 ? secondObject : obj);
#endif
		argsType[argIndex] = x32INTARG;
		argIndex++;
		paramIndex++;			
	}

	totalArgumentCount = argIndex;
	
	siv3dCallIndirect(func, argsType, &retQW, paramBuffer);

    return retQW;
}

END_AS_NAMESPACE

#endif // AS_WASM32
#endif // AS_MAX_PORTABILITY
