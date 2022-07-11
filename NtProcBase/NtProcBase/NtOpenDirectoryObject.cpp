#include "NtOpenDirectoryObject.h"
#include "NtCreateFile.h"

pfn_NtOpenDirectoryObject NtOpenDirectoryObject = (pfn_NtOpenDirectoryObject)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtOpenDirectoryObject");

VOID Example_NtOpenDirectoryObject_0()
{
	HANDLE DirHandle = NULL;
	HANDLE DeviceHandle = NULL;

	UNICODE_STRING ObjectName = { 0 };
	OBJECT_ATTRIBUTES ObjectAttributes = { 0 };

	IO_STATUS_BLOCK IoStatusBlock = { 0 };

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		RtlInitUnicodeString(&ObjectName, L"\\Device");
		InitializeObjectAttributes(&ObjectAttributes, &ObjectName, OBJ_CASE_INSENSITIVE, NULL, NULL);

		Status = NtOpenDirectoryObject(&DirHandle, DIRECTORY_ALL_ACCESS, &ObjectAttributes);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

		RtlInitUnicodeString(&ObjectName, L"xxx_199x");
		InitializeObjectAttributes(&ObjectAttributes, &ObjectName, OBJ_CASE_INSENSITIVE, NULL, NULL);

		Status = NtCreateFile(
			&DeviceHandle,
			FILE_GENERIC_READ,
			&ObjectAttributes,
			&IoStatusBlock,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_VALID_FLAGS,
			FILE_OPEN,
			FILE_SYNCHRONOUS_IO_NONALERT,
			NULL,
			0);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

	} while (FALSE);
}