#pragma once

#include "NtBase.h"

typedef struct _FILE_BASIC_INFORMATION 
{
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	ULONG FileAttributes;

} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

typedef NTSTATUS(NTAPI *pfn_NtQueryAttributesFile)(POBJECT_ATTRIBUTES ObjectAttributes,PFILE_BASIC_INFORMATION FileInformation);

extern pfn_NtQueryAttributesFile NtQueryAttributesFile;