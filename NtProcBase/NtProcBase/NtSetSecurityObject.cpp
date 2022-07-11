#include "NtSetSecurityObject.h"

pfn_NtSetSecurityObject NtSetSecurityObject = (pfn_NtSetSecurityObject)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtSetSecurityObject");

VOID Example_NtSetSecurityObject_0(HANDLE Object, PSECURITY_DESCRIPTOR SecurityDescriptor)
{
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		Status = NtSetSecurityObject(Object, DACL_SECURITY_INFORMATION, SecurityDescriptor);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

	} while (FALSE);
}