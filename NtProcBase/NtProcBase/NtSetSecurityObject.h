#pragma once

#include "NtBase.h"

typedef NTSTATUS(NTAPI *pfn_NtSetSecurityObject)(
	HANDLE					Handle,
	SECURITY_INFORMATION	SecurityInformation,
	PSECURITY_DESCRIPTOR	SecurityDescriptor
	);

extern pfn_NtSetSecurityObject NtSetSecurityObject;