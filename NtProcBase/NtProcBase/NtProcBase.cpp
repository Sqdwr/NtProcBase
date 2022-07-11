#include <iostream>

#include "NtBase.h"
#include "NtCreateFile.h"
#include "NtQueryObject.h"
#include "NtCreateSection.h"

#include "NtCreateDirectoryObject.h"

using namespace std;

#include <processthreadsapi.h>

int main()
{
	HANDLE FileHandle = NULL;

	UNICODE_STRING FileName = { 0 };
	OBJECT_ATTRIBUTES FileAttributes = { 0 };

	IO_STATUS_BLOCK IoStatusBlock = { 0 };

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		char Buffer[1024] = { 0 };

		fgets(Buffer, 1024, NULL);

		RtlInitUnicodeString(&FileName, L"\\??\\D:\\xxx\\..\\123.txt");
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

	system("pause");

	return 0;
}
