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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Script.hpp>

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

		asITypeInfo* objType;

		SOptionalBuffer* buffer;

		int32 elementSize;

		int32 subTypeId;

		void CreateBuffer(SOptionalBuffer** buf, asUINT hasValue);

		void Construct(SOptionalBuffer* buf);

		void SetValue(void* value);

		void SetValue(SOptionalBuffer* buf, void* value);

		void* At(SOptionalBuffer* buf);

		void DeleteBuffer(SOptionalBuffer* buf);

		//// internal
		void Destruct(SOptionalBuffer* buf);

		void Resize(asUINT hasValue);

		void CopyBuffer(SOptionalBuffer* dst, SOptionalBuffer* src);

	public:

		asITypeInfo* GetArrayObjectType() const;

		CScriptOptional(asITypeInfo* ti);

		CScriptOptional(void* defVal, asITypeInfo* ti);

		~CScriptOptional();

		CScriptOptional& operator=(const CScriptOptional& other);

		CScriptOptional& AssignValue(void* value);

		CScriptOptional& AssignNone(uint8);

		//bool opEqual(const CScriptOptional& other) const;

		//bool opEqualValue(void* value) const;

		bool opEqualNone(uint8) const;

		void ResetValue(void* value);

		void* At();

		const void* At() const;

		bool HasValue() const;

		void Reset();

		void* ValueOr(void* value);
	};
}
