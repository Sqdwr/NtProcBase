#include "NtCreateFile.h"

pfn_NtCreateFile NtCreateFile = (pfn_NtCreateFile)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtCreateFile");

VOID Example_NtCreateFile_0()
{
	HANDLE FileHandle = NULL;

	UNICODE_STRING FileName = { 0 };
	OBJECT_ATTRIBUTES FileAttributes = { 0 };

	IO_STATUS_BLOCK IoStatusBlock = { 0 };

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		RtlInitUnicodeString(&FileName, L"\\??\\D:\\xxx\\1.txt");
		InitializeObjectAttributes(&FileAttributes, &FileName, OBJ_CASE_INSENSITIVE, NULL, NULL);

		Status = NtCreateFile(
			&FileHandle,
			FILE_GENERIC_READ,
			&FileAttributes,
			&IoStatusBlock,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_VALID_FLAGS,
			FILE_OPEN,
			FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
			NULL,
			0);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

	} while (FALSE);

	if (FileHandle != NULL)
	{
		NtClose(FileHandle);
		FileHandle = NULL;
	}
}

VOID Example_NtCreateFile_1()
{
	HANDLE DirHandle = NULL;
	HANDLE FileHandle = NULL;

	UNICODE_STRING FileName = { 0 };
	OBJECT_ATTRIBUTES FileAttributes = { 0 };

	IO_STATUS_BLOCK IoStatusBlock = { 0 };

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		RtlInitUnicodeString(&FileName, L"\\??\\D:\\xxx");
		InitializeObjectAttributes(&FileAttributes, &FileName, OBJ_CASE_INSENSITIVE, NULL, NULL);

		Status = NtCreateFile(
			&DirHandle,
			FILE_GENERIC_READ,
			&FileAttributes,
			&IoStatusBlock,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_VALID_FLAGS,
			FILE_OPEN,
			FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
			NULL,
			0);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

		RtlInitUnicodeString(&FileName, L"123.txt");
		InitializeObjectAttributes(&FileAttributes, &FileName, OBJ_CASE_INSENSITIVE, DirHandle, NULL);

		Status = NtCreateFile(
			&FileHandle,
			FILE_GENERIC_READ,
			&FileAttributes,
			&IoStatusBlock,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_VALID_FLAGS,
			FILE_OPEN,
			FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
			NULL,
			0);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

	} while (FALSE);

	if (FileHandle != NULL)
	{
		NtClose(FileHandle);
		FileHandle = NULL;
	}

	if (DirHandle != NULL)
	{
		NtClose(DirHandle);
		DirHandle = NULL;
	}
}
