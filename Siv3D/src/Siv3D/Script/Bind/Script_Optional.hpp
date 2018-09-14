//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	struct SOptionalBuffer
	{
		asDWORD hasValue;
		asBYTE  data[1];
	};

	class CScriptOptional
	{
	protected:

		mutable int32 refCount;
		mutable bool gcFlag;
		asITypeInfo* objType;
		SOptionalBuffer* buffer;
		int32 elementSize;
		int32 subTypeId;

		CScriptOptional(asITypeInfo* ti);

		CScriptOptional(void* defVal, asITypeInfo *ti);

		virtual ~CScriptOptional();

		void CreateBuffer(SOptionalBuffer** buf, asUINT hasValue);

		void Construct(SOptionalBuffer* buf);

		void SetValue(void* value);

		void SetValue(SOptionalBuffer* buf, void* value);

		void* At(SOptionalBuffer* buf);

		void DeleteBuffer(SOptionalBuffer* buf);

		// internal
		void Destruct(SOptionalBuffer* buf);

		void Resize(asUINT hasValue);

		void CopyBuffer(SOptionalBuffer* dst, SOptionalBuffer* src);

	public:

		asITypeInfo* GetArrayObjectType() const;

		static CScriptOptional* Create(asITypeInfo* ti);

		static CScriptOptional* Create(asITypeInfo* ti, void* defVal);

		void AddRef() const;

		void Release() const;

		// GC behaviour
		int GetRefCount();

		// GC behaviour
		void SetFlag();

		// GC behaviour
		bool GetFlag();

		// GC behaviour
		void EnumReferences(asIScriptEngine* engine);

		// GC behaviour
		void ReleaseAllHandles(asIScriptEngine*);

		CScriptOptional& operator=(const CScriptOptional& other);

		CScriptOptional& AssignValue(void* value);

		void ResetValue(void* value);

		void* At();

		const void* At() const;

		bool HasValue() const;

		void Reset();

		void* ValueOr(void* value);
	};
}
