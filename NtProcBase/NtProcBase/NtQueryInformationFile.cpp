#include "NtQueryInformationFile.h"
#include "NtCreateFile.h"

pfn_NtQueryInformationFile NtQueryInformationFile = (pfn_NtQueryInformationFile)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationFile");

VOID Example_NtQueryInformationFile_0()
{
	HANDLE FileHandle = NULL;

	UNICODE_STRING FileName = { 0 };
	OBJECT_ATTRIBUTES FileAttributes = { 0 };

	IO_STATUS_BLOCK IoStatusBlock = { 0 };
	PFILE_NAME_INFORMATION FileNameInfo = NULL;

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

		FileNameInfo = (PFILE_NAME_INFORMATION)VirtualAlloc(NULL, sizeof(FILE_NAME_INFORMATION) + sizeof(WCHAR) * MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (FileNameInfo == NULL)
		{
			break;
		}
		RtlZeroMemory(FileNameInfo, sizeof(FILE_NAME_INFORMATION) + sizeof(WCHAR) * MAX_PATH);

		Status = NtQueryInformationFile(FileHandle, &IoStatusBlock, FileNameInfo, sizeof(FILE_NAME_INFORMATION) + sizeof(WCHAR) * MAX_PATH, FileNameInformation);
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

	if (FileNameInfo != NULL)
	{
		VirtualFree(FileNameInfo, 0, MEM_RELEASE);
		FileNameInfo = NULL;
	}

}

VOID Example_NtQueryInformationFile_1()
{
	HANDLE FileHandle = NULL;

	UNICODE_STRING FileName = { 0 };
	OBJECT_ATTRIBUTES FileAttributes = { 0 };

	IO_STATUS_BLOCK IoStatusBlock = { 0 };
	
	CHAR *Buffer = NULL;
	ULONG BufferLength = 0;

	PFILE_LINKS_INFORMATION LinksInfo = NULL;
	PFILE_LINK_ENTRY_INFORMATION LinkEntry = NULL;

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

		BufferLength = sizeof(FILE_LINKS_INFORMATION) + 1024 * 1024;

		Buffer = (CHAR *)VirtualAlloc(NULL, BufferLength, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (Buffer == NULL)
		{
			break;
		}
		RtlZeroMemory(Buffer, BufferLength);

		LinksInfo = (PFILE_LINKS_INFORMATION)Buffer;
		LinksInfo->BytesNeeded = 1024 * 1024;

		Status = NtQueryInformationFile(FileHandle, &IoStatusBlock, LinksInfo, BufferLength, FileHardLinkInformation);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

		LinkEntry = &LinksInfo->Entry;
		for (ULONG i = 0; i < LinksInfo->EntriesReturned; ++i)
		{
			// printf("%ws\n", LinkEntry->FileName);

			LinkEntry = (PFILE_LINK_ENTRY_INFORMATION)((UCHAR*)LinkEntry + LinkEntry->NextEntryOffset);
		}

	} while (FALSE);

	if (FileHandle != NULL)
	{
		NtClose(FileHandle);
		FileHandle = NULL;
	}

	if (Buffer != NULL)
	{
		VirtualFree(Buffer, 0, MEM_RELEASE);
		Buffer = NULL;
	}

}

VOID Example_NtQueryInformationFile_2()
{
	HANDLE FileHandle = NULL;

	UNICODE_STRING FileName = { 0 };
	OBJECT_ATTRIBUTES FileAttributes = { 0 };

	IO_STATUS_BLOCK IoStatusBlock = { 0 };
	FILE_STANDARD_INFORMATION FileStandardInfo = { 0 };

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

		Status = NtQueryInformationFile(FileHandle, &IoStatusBlock, &FileStandardInfo, sizeof(FileStandardInfo), FileStandardInformation);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

		// cout << (ULONG)FileStandardInfo.DeletePending << endl;

	} while (FALSE);

	if (FileHandle != NULL)
	{
		NtClose(FileHandle);
		FileHandle = NULL;
	}
}

VOID Example_NtQueryInformationFile_3()
{
	HANDLE FileHandle = NULL;

	UNICODE_STRING FileName = { 0 };
	OBJECT_ATTRIBUTES FileAttributes = { 0 };

	IO_STATUS_BLOCK IoStatusBlock = { 0 };
	FILE_BASIC_INFORMATION BasicInfo = { 0 };

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

		Status = NtQueryInformationFile(FileHandle, &IoStatusBlock, &BasicInfo, sizeof(BasicInfo), FileBasicInformation);
		if (!NT_SUCCESS(Status))
		{
			break;
		}
		
		// cout << BasicInfo.FileAttributes << endl;

	} while (FALSE);

	if (FileHandle != NULL)
	{
		NtClose(FileHandle);
		FileHandle = NULL;
	}
}