#include "NtCreateSection.h"
#include "NtCreateFile.h"

pfn_NtCreateSection NtCreateSection = (pfn_NtCreateSection)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtCreateSection");

VOID Example_NtSection_0()
{
	HANDLE FileHandle = NULL;
	UNICODE_STRING FileName = { 0 };
	OBJECT_ATTRIBUTES FileAttributes = { 0 };

	HANDLE SectionHandle = NULL;
	IO_STATUS_BLOCK IoStatusBlock = { 0 };

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		RtlInitUnicodeString(&FileName, L"\\??\\C:\\Windows\\System32\\ntdll.dll");
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

		RtlInitUnicodeString(&FileName, L"SectionShare");
		Status = NtCreateSection(
			&SectionHandle,
			SECTION_MAP_READ,
			&FileAttributes,
			NULL,
			PAGE_READONLY,
			SEC_IMAGE,
			FileHandle);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

	} while (FALSE);
}