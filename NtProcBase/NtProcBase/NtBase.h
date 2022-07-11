#pragma once

#include <Windows.h>
#include <cstdlib>

// ***************************************** BASE_DEFIND_START *****************************************

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWCH Buffer;

} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES 
{
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
	PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE

} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK 
{
	union {
		NTSTATUS Status;
		PVOID    Pointer;
	} DUMMYUNIONNAME;
	ULONG_PTR Information;

} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

#define OBJ_INHERIT                         0x00000002L
#define OBJ_PERMANENT                       0x00000010L
#define OBJ_EXCLUSIVE                       0x00000020L
#define OBJ_CASE_INSENSITIVE                0x00000040L
#define OBJ_OPENIF                          0x00000080L
#define OBJ_OPENLINK                        0x00000100L
#define OBJ_KERNEL_HANDLE                   0x00000200L
#define OBJ_FORCE_ACCESS_CHECK              0x00000400L
#define OBJ_IGNORE_IMPERSONATED_DEVICEMAP   0x00000800L
#define OBJ_DONT_REPARSE                    0x00001000L
#define OBJ_VALID_ATTRIBUTES                0x00001FF2L

#define InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->RootDirectory = r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = n;                                \
    (p)->SecurityDescriptor = s;                        \
    (p)->SecurityQualityOfService = NULL;               \
    }

#define STATUS_UNSUCCESSFUL					((NTSTATUS)0xC0000001L)
#define STATUS_INFO_LENGTH_MISMATCH			((NTSTATUS)0xC0000004L)
#define STATUS_BUFFER_TOO_SMALL				((NTSTATUS)0xC0000023L)
#define STATUS_OBJECT_NAME_NOT_FOUND		((NTSTATUS)0xC0000034L)
#define STATUS_OBJECT_NAME_COLLISION		((NTSTATUS)0xC0000035L)
#define STATUS_MORE_ENTRIES					((NTSTATUS)0x00000105L)

#define STATUS_OBJECT_NAME_EXISTS			((NTSTATUS)0x40000000L)

#define NT_SUCCESS(Status)					(((NTSTATUS)(Status)) >= 0)

// ***************************************** BASE_DEFIND_END *****************************************







VOID RtlInitUnicodeString(PUNICODE_STRING DestinationString, PCWSTR SourceString);

typedef NTSTATUS(NTAPI *pfn_NtClose)(HANDLE Handle);

typedef BOOLEAN(NTAPI *pfn_RtlIsNameInExpression)(PUNICODE_STRING Expression,PUNICODE_STRING Name,BOOLEAN IgnoreCase,PWCH UpcaseTable);
typedef WCHAR(NTAPI *pfn_RtlUpcaseUnicodeChar)(WCHAR SourceCharacter);

extern pfn_NtClose NtClose;
extern pfn_RtlIsNameInExpression RtlIsNameInExpression;