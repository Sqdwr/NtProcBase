#pragma once

#include "NtBase.h"

typedef NTSTATUS(NTAPI *pfn_NtQuerySecurityObject)(
	HANDLE					Handle,
	SECURITY_INFORMATION	SecurityInformation,
	PSECURITY_DESCRIPTOR	SecurityDescriptor,
	ULONG					Length,
	PULONG					LengthNeeded
	);

extern pfn_NtQuerySecurityObject NtQuerySecurityObject;