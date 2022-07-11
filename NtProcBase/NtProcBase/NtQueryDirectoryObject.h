#pragma once

#include "NtBase.h"

typedef struct _DIRECTORY_BASIC_INFORMATION {
	UNICODE_STRING ObjectName;
	UNICODE_STRING ObjectTypeName;
} DIRECTORY_BASIC_INFORMATION, *PDIRECTORY_BASIC_INFORMATION;

typedef NTSTATUS(NTAPI *pfn_NtQueryDirectoryObject)(
	HANDLE				DirectoryHandle,
	PVOID				Buffer,
	ULONG				BufferLength,
	BOOLEAN				ReturnSingleEntry,
	BOOLEAN				RestartScan,
	PULONG				Context,
	PULONG				ReturnLength
	);

extern pfn_NtQueryDirectoryObject NtQueryDirectoryObject;