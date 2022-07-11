#include "NtQuerySecurityObject.h"

pfn_NtQuerySecurityObject NtQuerySecurityObject = (pfn_NtQuerySecurityObject)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQuerySecurityObject");

VOID Example_NtQuerySecurityObject_0(HANDLE QueryObject)
{
	PSECURITY_DESCRIPTOR SecurityDescriptor = NULL;
	ULONG RetLength = 0;

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		Status = NtQuerySecurityObject(QueryObject, DACL_SECURITY_INFORMATION, NULL, 0, &RetLength);
		if (Status != STATUS_BUFFER_TOO_SMALL)
		{
			break;
		}

		SecurityDescriptor = (PSECURITY_DESCRIPTOR)VirtualAlloc(NULL, RetLength, MEM_COMMIT, PAGE_READWRITE);
		if (SecurityDescriptor == NULL)
		{
			break;
		}
		RtlZeroMemory(SecurityDescriptor, RetLength);

		Status = NtQuerySecurityObject(QueryObject, DACL_SECURITY_INFORMATION, SecurityDescriptor, RetLength, &RetLength);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

	} while (FALSE);

	if (SecurityDescriptor != NULL)
	{
		VirtualFree(SecurityDescriptor, 0, MEM_RELEASE);
		SecurityDescriptor = NULL;
	}
}