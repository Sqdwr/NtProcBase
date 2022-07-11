#pragma once

#include "NtBase.h"

typedef NTSTATUS (NTAPI *pfn_NtCreateSection)(
	PHANDLE            SectionHandle,
	ACCESS_MASK        DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	PLARGE_INTEGER     MaximumSize,
	ULONG              SectionPageProtection,
	ULONG              AllocationAttributes,
	HANDLE             FileHandle
);

extern pfn_NtCreateSection NtCreateSection;

VOID Example_NtSection_0();