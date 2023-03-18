//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include "ScriptOptional.hpp"

namespace s3d
{
	using namespace AngelScript;

	// This optional callback is called when the template type is first used by the compiler.
	// It allows the application to validate if the template can be instantiated for the requested
	// subtype at compile time, instead of at runtime. The output argument dontGarbageCollect
	// allow the callback to tell the engine if the template instance type shouldn't be garbage collected,
	// i.e. no asOBJ_GC flag.
	static bool ScriptOptionalTemplateCallback(asITypeInfo* ti, bool& dontGarbageCollect)
	{
		// Make sure the subtype can be instantiated with a default factory/constructor,
		// otherwise we won't be able to instantiate the elements.
		int typeId = ti->GetSubTypeId();
		if (typeId == asTYPEID_VOID)
			return false;
		if ((typeId & asTYPEID_MASK_OBJECT) && !(typeId & asTYPEID_OBJHANDLE))
		{
			asITypeInfo* subtype = ti->GetEngine()->GetTypeInfoById(typeId);
			asDWORD flags = subtype->GetFlags();
			if ((flags & asOBJ_VALUE) && !(flags & asOBJ_POD))
			{
				// Verify that there is a default constructor
				bool found = false;
				for (asUINT n = 0; n < subtype->GetBehaviourCount(); n++)
				{
					asEBehaviours beh;
					asIScriptFunction* func = subtype->GetBehaviourByIndex(n, &beh);
					if (beh != asBEHAVE_CONSTRUCT) continue;

					if (func->GetParamCount() == 0)
					{
						// Found the default constructor
						found = true;
						break;
					}
				}

				if (!found)
				{
					// There is no default constructor
					// TODO: Should format the message to give the name of the subtype for better understanding
					ti->GetEngine()->WriteMessage("Optional", 0, 0, asMSGTYPE_ERROR, "The subtype has no default constructor");
					return false;
				}
			}
			else if ((flags & asOBJ_REF))
			{
				bool found = false;

				// If value assignment for ref type has been disabled then the array
				// can be created if the type has a default factory function
				if (!ti->GetEngine()->GetEngineProperty(asEP_DISALLOW_VALUE_ASSIGN_FOR_REF_TYPE))
				{
					// Verify that there is a default factory
					for (asUINT n = 0; n < subtype->GetFactoryCount(); n++)
					{
						asIScriptFunction* func = subtype->GetFactoryByIndex(n);
						if (func->GetParamCount() == 0)
						{
							// Found the default factory
							found = true;
							break;
						}
					}
				}

				if (!found)
				{
					// No default factory
					// TODO: Should format the message to give the name of the subtype for better understanding
					ti->GetEngine()->WriteMessage("Optional", 0, 0, asMSGTYPE_ERROR, "The subtype has no default factory");
					return false;
				}
			}

			// If the object type is not garbage collected then the array also doesn't need to be
			if (!(flags & asOBJ_GC))
				dontGarbageCollect = true;
		}
		else if (!(typeId & asTYPEID_OBJHANDLE))
		{
			// Arrays with primitives cannot form circular references,
			// thus there is no need to garbage collect them
			dontGarbageCollect = true;
		}
		else
		{
			assert(typeId & asTYPEID_OBJHANDLE);

			// It is not necessary to set the array as garbage collected for all handle types.
			// If it is possible to determine that the handle cannot refer to an object type
			// that can potentially form a circular reference with the array then it is not 
			// necessary to make the array garbage collected.
			asITypeInfo* subtype = ti->GetEngine()->GetTypeInfoById(typeId);
			asDWORD flags = subtype->GetFlags();
			if (!(flags & asOBJ_GC))
			{
				if ((flags & asOBJ_SCRIPT_OBJECT))
				{
					// Even if a script class is by itself not garbage collected, it is possible
					// that classes that derive from it may be, so it is not possible to know 
					// that no circular reference can occur.
					if ((flags & asOBJ_NOINHERIT))
					{
						// A script class declared as final cannot be inherited from, thus
						// we can be certain that the object cannot be garbage collected.
						dontGarbageCollect = true;
					}
				}
				else
				{
					// For application registered classes we assume the application knows
					// what it is doing and don't mark the array as garbage collected unless
					// the type is also garbage collected.
					dontGarbageCollect = true;
				}
			}
		}

		// The type is ok
		return true;
	}

	CScriptOptional::CScriptOptional(asITypeInfo* ti)
	{
		objType = ti;
		objType->AddRef();
		buffer = 0;
		subTypeId = objType->GetSubTypeId();

		// Determine element size
		if (subTypeId & asTYPEID_MASK_OBJECT)
			elementSize = sizeof(asPWORD);
		else
			elementSize = objType->GetEngine()->GetSizeOfPrimitiveType(subTypeId);

		CreateBuffer(&buffer, 0);

		// Notify the GC of the successful creation
		if (objType->GetFlags() & asOBJ_GC)
			objType->GetEngine()->NotifyGarbageCollectorOfNewObject(this, objType);
	}

	CScriptOptional::CScriptOptional(void* defVal, asITypeInfo* ti)
	{
		objType = ti;
		objType->AddRef();
		buffer = 0;
		subTypeId = objType->GetSubTypeId();

		// Determine element size
		if (subTypeId & asTYPEID_MASK_OBJECT)
			elementSize = sizeof(asPWORD);
		else
			elementSize = objType->GetEngine()->GetSizeOfPrimitiveType(subTypeId);

		CreateBuffer(&buffer, 1);

		// Notify the GC of the successful creation
		if (objType->GetFlags() & asOBJ_GC)
			objType->GetEngine()->NotifyGarbageCollectorOfNewObject(this, objType);

		// Initialize the elements with the default value
		SetValue(defVal);
	}

	CScriptOptional::~CScriptOptional()
	{
		if (buffer)
		{
			DeleteBuffer(buffer);
			buffer = 0;
		}
		if (objType) objType->Release();
	}

	CScriptOptional& CScriptOptional::operator=(const CScriptOptional& other)
	{
		// Only perform the copy if the array types are the same
		if (&other != this &&
			other.GetArrayObjectType() == GetArrayObjectType())
		{
			// Make sure the arrays are of the same size
			Resize(other.buffer->hasValue);

			// Copy the value of each element
			CopyBuffer(buffer, other.buffer);
		}

		return *this;
	}

	void CScriptOptional::CreateBuffer(SOptionalBuffer** buf, asUINT hasValue)
	{
		asUINT numElements = hasValue;

		*buf = reinterpret_cast<SOptionalBuffer*>(::malloc(sizeof(SOptionalBuffer) - 1 + elementSize * numElements));

		if (*buf)
		{
			(*buf)->hasValue = hasValue;
			Construct(*buf);
		}
		else
		{
			// Oops, out of memory
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Optional: Out of memory");
		}
	}

	void CScriptOptional::Construct(SOptionalBuffer* buf)
	{
		assert(buf);

		if (subTypeId & asTYPEID_OBJHANDLE)
		{
			// Set all object handles to null
			void* d = (void*)(buf->data);
			memset(d, 0, (buf->hasValue) * sizeof(void*));
		}
		else if (subTypeId & asTYPEID_MASK_OBJECT)
		{
			void** max = (void**)(buf->data + (buf->hasValue) * sizeof(void*));
			void** d = (void**)(buf->data);

			asIScriptEngine* engine = objType->GetEngine();
			asITypeInfo* subType = objType->GetSubType();

			for (; d < max; d++)
			{
				*d = (void*)engine->CreateScriptObject(subType);
				if (*d == 0)
				{
					// Set the remaining entries to null so the destructor 
					// won't attempt to destroy invalid objects later
					memset(d, 0, sizeof(void*) * (max - d));

					// There is no need to set an exception on the context,
					// as CreateScriptObject has already done that
					return;
				}
			}
		}
	}

	void CScriptOptional::SetValue(void* value)
	{
		SetValue(buffer, value);
	}

	void CScriptOptional::SetValue(SOptionalBuffer* buf, void* value)
	{
		// At() will take care of the out-of-bounds checking, though
		// if called from the application then nothing will be done
		void* ptr = At(buf);
		if (ptr == 0) return;

		if ((subTypeId & ~asTYPEID_MASK_SEQNBR) && !(subTypeId & asTYPEID_OBJHANDLE))
		{
			objType->GetEngine()->AssignScriptObject(ptr, value, objType->GetSubType());
		}
		else if (subTypeId & asTYPEID_OBJHANDLE)
		{
			void* tmp = *(void**)ptr;
			*(void**)ptr = *(void**)value;
			objType->GetEngine()->AddRefScriptObject(*(void**)value, objType->GetSubType());
			if (tmp)
				objType->GetEngine()->ReleaseScriptObject(tmp, objType->GetSubType());
		}
		else if (subTypeId == asTYPEID_BOOL ||
			subTypeId == asTYPEID_INT8 ||
			subTypeId == asTYPEID_UINT8)
			*(char*)ptr = *(char*)value;
		else if (subTypeId == asTYPEID_INT16 ||
			subTypeId == asTYPEID_UINT16)
			*(short*)ptr = *(short*)value;
		else if (subTypeId == asTYPEID_INT32 ||
			subTypeId == asTYPEID_UINT32 ||
			subTypeId == asTYPEID_FLOAT ||
			subTypeId > asTYPEID_DOUBLE) // enums have a type id larger than doubles
			*(int*)ptr = *(int*)value;
		else if (subTypeId == asTYPEID_INT64 ||
			subTypeId == asTYPEID_UINT64 ||
			subTypeId == asTYPEID_DOUBLE)
			*(double*)ptr = *(double*)value;
	}

	void CScriptOptional::DeleteBuffer(SOptionalBuffer* buf)
	{
		assert(buf);

		Destruct(buf);

		// Free the buffer
		::free(buf);
	}

	void CScriptOptional::Destruct(SOptionalBuffer* buf)
	{
		assert(buf);

		if (subTypeId & asTYPEID_MASK_OBJECT)
		{
			asIScriptEngine* engine = objType->GetEngine();

			void** max = (void**)(buf->data + (buf->hasValue) * sizeof(void*));
			void** d = (void**)(buf->data);

			for (; d < max; d++)
			{
				if (*d)
					engine->ReleaseScriptObject(*d, objType->GetSubType());
			}
		}
	}

	void CScriptOptional::Resize(asUINT hasValue)
	{
		// Create a new buffer
		SOptionalBuffer* tmpBuffer = 0;
		CreateBuffer(&tmpBuffer, hasValue);
		if (tmpBuffer == 0)
			return;

		if (buffer)
		{
			// Copy the existing values to the new buffer
			if (buffer->hasValue && hasValue)
			{
				SetValue(tmpBuffer, At(buffer));
			}

			// Replace the internal buffer
			DeleteBuffer(buffer);
		}

		buffer = tmpBuffer;
	}

	void CScriptOptional::CopyBuffer(SOptionalBuffer* dst, SOptionalBuffer* src)
	{
		asIScriptEngine* engine = objType->GetEngine();
		if (subTypeId & asTYPEID_OBJHANDLE)
		{
			// Copy the references and increase the reference counters
			if (dst->hasValue > 0 && src->hasValue > 0)
			{
				int count = dst->hasValue > src->hasValue ? src->hasValue : dst->hasValue;

				void** max = (void**)(dst->data + count * sizeof(void*));
				void** d = (void**)dst->data;
				void** s = (void**)src->data;

				for (; d < max; d++, s++)
				{
					void* tmp = *d;
					*d = *s;
					if (*d)
						engine->AddRefScriptObject(*d, objType->GetSubType());
					// Release the old ref after incrementing the new to avoid problem incase it is the same ref
					if (tmp)
						engine->ReleaseScriptObject(tmp, objType->GetSubType());
				}
			}
		}
		else
		{
			if (dst->hasValue > 0 && src->hasValue > 0)
			{
				int count = dst->hasValue > src->hasValue ? src->hasValue : dst->hasValue;
				if (subTypeId & asTYPEID_MASK_OBJECT)
				{
					// Call the assignment operator on all of the objects
					void** max = (void**)(dst->data + count * sizeof(void*));
					void** d = (void**)dst->data;
					void** s = (void**)src->data;

					asITypeInfo* subType = objType->GetSubType();
					for (; d < max; d++, s++)
						engine->AssignScriptObject(*d, *s, subType);
				}
				else
				{
					// Primitives are copied byte for byte
					memcpy(dst->data, src->data, count * elementSize);
				}
			}
		}
	}

	void* CScriptOptional::At(SOptionalBuffer* buf)
	{
		if (!buf || !buf->hasValue)
		{
			// If this is called from a script we raise a script exception
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Optional: Bad Optional access");
			return 0;
		}

		asUINT index = 0;
		if ((subTypeId & asTYPEID_MASK_OBJECT) && !(subTypeId & asTYPEID_OBJHANDLE))
			return *(void**)(buf->data + elementSize * index);
		else
			return buf->data + elementSize * index;
	}

	asITypeInfo* CScriptOptional::GetArrayObjectType() const
	{
		return objType;
	}

	CScriptOptional& CScriptOptional::AssignValue(void* value)
	{
		Resize(1);

		SetValue(value);

		return *this;
	}

	CScriptOptional& CScriptOptional::AssignNone(uint8)
	{
		Resize(0);

		return *this;
	}

	bool CScriptOptional::opEqualNone(uint8) const
	{
		return !HasValue();
	}

	void CScriptOptional::ResetValue(void* value)
	{
		Resize(1);

		SetValue(value);
	}

	void* CScriptOptional::At()
	{
		return At(buffer);
	}

	const void* CScriptOptional::At() const
	{
		return const_cast<CScriptOptional*>(this)->At(const_cast<SOptionalBuffer*>(buffer));
	}

	bool CScriptOptional::HasValue() const
	{
		if (buffer)
			return (buffer->hasValue != 0);

		return false;
	}

	void CScriptOptional::Reset()
	{
		Resize(0);
	}

	void* CScriptOptional::ValueOr(void* value)
	{
		if (HasValue())
		{
			return At();
		}
		else
		{
			return value;
		}
	}

	static void DefaultConstruct(asITypeInfo* ti, CScriptOptional* self)
	{
		new(self) CScriptOptional(ti);
	}

	static void ConstructV(asITypeInfo* ti, void* value, CScriptOptional* self)
	{
		new(self) CScriptOptional(value, ti);
	}

	static void ConstructN(asITypeInfo* ti, uint8, CScriptOptional* self)
	{
		new(self) CScriptOptional(ti);
	}

	static void Destruct(CScriptOptional* self)
	{
		self->~CScriptOptional();
	}

	void RegisterOptional(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Optional<T>";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_TEMPLATE_CALLBACK, "bool f(int32& in, bool& out)", asFUNCTION(ScriptOptionalTemplateCallback), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32& in)", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32& in, const T& in value)", asFUNCTION(ConstructV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32& in, None_t)", asFUNCTION(ConstructN), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Optional<T>& opAssign(const Optional<T>& in)", asMETHODPR(CScriptOptional, operator =, (const CScriptOptional&), CScriptOptional&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Optional<T>& opAssign(const T& in)", asMETHODPR(CScriptOptional, AssignValue, (void*), CScriptOptional&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Optional<T>& opAssign(None_t)", asMETHODPR(CScriptOptional, AssignNone, (uint8), CScriptOptional&), asCALL_THISCALL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "Optional<T>& opEquals(const Optional<T>& in) const", asMETHOD(CScriptOptional, AssignValue), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<T>& opEquals(const T& in) const", asMETHOD(CScriptOptional, AssignValue), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Optional<T>& opEquals(None_t) const", asMETHODPR(CScriptOptional, opEqualNone, (uint8) const, bool), asCALL_THISCALL); assert(r >= 0);

		// The index operator returns the template subtype
		r = engine->RegisterObjectMethod(TypeName, "T& value()", asMETHODPR(CScriptOptional, At, (), void*), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const T& value() const", asMETHODPR(CScriptOptional, At, () const, const void*), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const T& value_or(const T& in value) const", asMETHODPR(CScriptOptional, ValueOr, (void*), void*), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asMETHODPR(CScriptOptional, HasValue, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool has_value() const", asMETHODPR(CScriptOptional, HasValue, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void reset()", asMETHOD(CScriptOptional, Reset), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void reset(const T& in value)", asMETHODPR(CScriptOptional, ResetValue, (void*), void), asCALL_THISCALL); assert(r >= 0);
	}
}
