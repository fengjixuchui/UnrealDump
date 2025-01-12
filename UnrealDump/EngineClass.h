#pragma once
#include <set>
#include <string>
#include <windows.h>
#include "SmartPtr.hpp"
struct FPointer
{
	uintptr_t Dummy;
};

struct FQWord
{
	int A;
	int B;
};

struct FName
{
	int32_t ComparisonIndex;
	int32_t Number;
};

template<class T>
struct TArray
{
	friend struct FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T operator[](int i)
	{
		return Data[i];
	};

	inline const T operator[](int i) const
	{
		if (i >= Count)
			return nullptr;

		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}

private:
	 SmartPtr< T> Data;
	int32_t Count;
	int32_t Max;
};

template<typename KeyType, typename ValueType>
class TPair
{
public:
	KeyType   Key;
	ValueType Value;
};

struct FString : public TArray<wchar_t>
{
	std::string ToString() const
	{
		WCHAR String[0x100] = { 0 };
		Process::ReadMemory(Data.GetPtr(), String, sizeof(String));
		int size = WideCharToMultiByte(CP_UTF8, 0, String, Count, nullptr, 0, nullptr, nullptr);
		std::string str(size, 0);
		WideCharToMultiByte(CP_UTF8, 0, String, Count, &str[0], size, nullptr, nullptr);
		return str;
	}
};
class UObject;
class FScriptInterface
{
private:
	UObject* ObjectPointer;
	void* InterfacePointer;

public:
	UObject* GetObject() const
	{
		return ObjectPointer;
	}

	UObject*& GetObjectRef()
	{
		return ObjectPointer;
	}

	void* GetInterface() const
	{
		return ObjectPointer != nullptr ? InterfacePointer : nullptr;
	}
};

template<class InterfaceType>
class TScriptInterface : public FScriptInterface
{
public:
	InterfaceType* operator->() const
	{
		return (InterfaceType*)GetInterface();
	}

	InterfaceType& operator*() const
	{
		return *((InterfaceType*)GetInterface());
	}

	operator bool() const
	{
		return GetInterface() != nullptr;
	}
};

struct FText
{
	char UnknownData[0x18];
};

struct FWeakObjectPtr
{
	int32_t ObjectIndex;
	int32_t ObjectSerialNumber;
};

struct FStringAssetReference
{
	FString AssetLongPathname;
};

template<typename TObjectID>
class TPersistentObjectPtr
{
public:
	FWeakObjectPtr WeakPtr;
	int32_t TagAtLastTest;
	TObjectID ObjectID;
};

class FAssetPtr : public TPersistentObjectPtr<FStringAssetReference>
{

};

struct FGuid
{
	uint32_t A;
	uint32_t B;
	uint32_t C;
	uint32_t D;
};

struct FUniqueObjectGuid
{
	FGuid Guid;
};

class FLazyObjectPtr : public TPersistentObjectPtr<FUniqueObjectGuid>
{

};

struct FScriptDelegate
{
	unsigned char UnknownData[16];
};

struct FScriptMulticastDelegate
{
	unsigned char UnknownData[16];
};

class UClass;

class UObject
{
public:
	VOID* vtf;
	char pad_0008[24]; //0x0008
	int64_t Class; //0x0020
	int32_t Index; //0x0028
	char pad_002C[4]; //0x002C
	int64_t Outer; //0x0030
	int32_t ID; //0x0038
	char pad_003C[4]; //0x003C





};

class UField : public UObject
{
public:
	UField* Next;
};

class UEnum : public UField
{
public:
	FString CppType; //0x0030 
	TArray<TPair<FName, uint64_t>> Names; //0x0040
	FString bzd_string; //0x0030 
	__int64 CppForm; //0x0050 
};

class UStruct : public UField
{
public:
	char pad_0048[12]; //0x0048
	uint32_t MinAlignment; //0x0054
	char pad_0058[8]; //0x0058
	class UField* SueprField; //0x0060
	char pad_0068[8]; //0x0068
	class UField* Children; //0x0070
	char pad_0078[144]; //0x0078
	int32_t PropertySize; //0x0108
	char pad_010C[4]; //0x010C





};

class UScriptStruct : public UStruct
{
public:
	char pad_0x0088[0x10]; //0x0088
};

class UFunction : public UStruct
{
public:
	char pad_0110[24]; //0x0110
	int16_t ParmsSize; //0x0128
	char pad_012A[10]; //0x012A
	int16_t NumParms; //0x0134
	char pad_0136[2]; //0x0136
	void* Fun; //0x0138
	int32_t FunctionFlags; //0x0140
	char pad_0144[36]; //0x0144




};

class UClass : public UStruct
{
public:
	char pad_0118[480]; //0x0118

};

class UProperty : public UField
{
public:
	int32_t ArrayDim; //0x0038
	int32_t ElementSize; //0x003C
	FQWord PropertyFlag; //0x0040
	char pad_0040[16]; //0x0040
	int32_t offset; //0x0050
	char pad_0054[4]; //0x0054
	class UField* NextChildren; //0x0058
	char pad_0060[24]; //0x0060




};

class UNumericProperty : public UProperty
{
public:

};

class UByteProperty : public UNumericProperty
{
public:
	UEnum* Enum;										// 0x0088 (0x04)
};

class UUInt16Property : public UNumericProperty
{
public:

};

class UUInt32Property : public UNumericProperty
{
public:

};

class UUInt64Property : public UNumericProperty
{
public:

};

class UInt8Property : public UNumericProperty
{
public:

};

class UInt16Property : public UNumericProperty
{
public:

};

class UIntProperty : public UNumericProperty
{
public:

};

class UInt64Property : public UNumericProperty
{
public:

};

class UFloatProperty : public UNumericProperty
{
public:

};

class UDoubleProperty : public UNumericProperty
{
public:

};

class UBoolProperty : public UProperty
{
public:
	uint8_t FieldSize;
	uint8_t ByteOffset;
	uint8_t ByteMask;
	uint8_t FieldMask;
};

class UObjectPropertyBase : public UProperty
{
public:
	UClass* PropertyClass;
};

class UObjectProperty : public UObjectPropertyBase
{
public:

};

class UClassProperty : public UObjectProperty
{
public:
	UClass* MetaClass;
};

class UInterfaceProperty : public UProperty
{
public:
	UClass* InterfaceClass;
};

class UWeakObjectProperty : public UObjectPropertyBase
{
public:

};

class ULazyObjectProperty : public UObjectPropertyBase
{
public:

};

class UAssetObjectProperty : public UObjectPropertyBase
{
public:

};

class UAssetClassProperty : public UAssetObjectProperty
{
public:
	UClass* MetaClass;
};

class UNameProperty : public UProperty
{
public:

};

class UStructProperty : public UProperty
{
public:
	UScriptStruct* Struct;
};

class UStrProperty : public UProperty
{
public:

};

class UTextProperty : public UProperty
{
public:

};

class UArrayProperty : public UProperty
{
public:
	UProperty* Inner;
};

class UMapProperty : public UProperty
{
public:
	UProperty* KeyProp;
	UProperty* ValueProp;
};

class UDelegateProperty : public UProperty
{
public:
	UFunction* SignatureFunction;
};

class UMulticastDelegateProperty : public UProperty
{
public:
	UFunction* SignatureFunction;
};

class UEnumProperty : public UProperty
{
public:
	class UNumericProperty* UnderlyingProp; //0x0070
	class UEnum* Enum; //0x0078
}; //Size: 0x0080