#include "NtQueryAttributesFile.h"

pfn_NtQueryAttributesFile NtQueryAttributesFile = (pfn_NtQueryAttributesFile)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryAttributesFile");

VOID Example_NtQueryAttributesFile_0()
{
	UNICODE_STRING FileName = { 0 };
	OBJECT_ATTRIBUTES FileAttributes = { 0 };

	FILE_BASIC_INFORMATION FileBasicInformation = { 0 };
	
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		RtlInitUnicodeString(&FileName, L"\\??\\D:\\xxx\\1.txt");
		InitializeObjectAttributes(&FileAttributes, &FileName, OBJ_CASE_INSENSITIVE, NULL, NULL);

		Status = NtQueryAttributesFile(&FileAttributes, &FileBasicInformation);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

	} while (FALSE);
}