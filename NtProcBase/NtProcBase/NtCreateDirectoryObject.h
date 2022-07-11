#pragma once

#include "NtBase.h"
#include "NtOpenDirectoryObject.h"

typedef NTSTATUS(NTAPI *pfn_NtCreateDirectoryObject)(
	PHANDLE            DirectoryHandle,
	ACCESS_MASK        DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes
	);

extern pfn_NtCreateDirectoryObject NtCreateDirectoryObject;
