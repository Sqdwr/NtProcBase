#pragma once

#include "NtBase.h"

#define DIRECTORY_QUERY                 (0x0001)
#define DIRECTORY_TRAVERSE              (0x0002)
#define DIRECTORY_CREATE_OBJECT         (0x0004)
#define DIRECTORY_CREATE_SUBDIRECTORY   (0x0008)

#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xF)

typedef NTSTATUS(NTAPI *pfn_NtOpenDirectoryObject)(
	PHANDLE            DirectoryHandle,
	ACCESS_MASK        DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes
	);

extern pfn_NtOpenDirectoryObject NtOpenDirectoryObject;