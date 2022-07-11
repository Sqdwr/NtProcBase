#include "NtCreateDirectoryObject.h"

pfn_NtCreateDirectoryObject NtCreateDirectoryObject = (pfn_NtCreateDirectoryObject)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtCreateDirectoryObject");

VOID Example_NtCreateDirectoryObject_0()
{
	UNICODE_STRING DirectoryName = { 0 };
	OBJECT_ATTRIBUTES DirectoryAttributs = { 0 };

	HANDLE DirectoryHandle = NULL;

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		RtlInitUnicodeString(&DirectoryName, L"\\xxx");
		InitializeObjectAttributes(&DirectoryAttributs, &DirectoryName, OBJ_CASE_INSENSITIVE, NULL, NULL);

		Status = NtCreateDirectoryObject(&DirectoryHandle, DIRECTORY_ALL_ACCESS, &DirectoryAttributs);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

	} while (FALSE);

	if (DirectoryHandle != NULL)
	{
		NtClose(DirectoryHandle);
		DirectoryHandle = NULL;
	}
}