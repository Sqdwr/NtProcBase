#include "NtQueryDirectoryObject.h"
#include "NtCreateDirectoryObject.h"

pfn_NtQueryDirectoryObject NtQueryDirectoryObject = (pfn_NtQueryDirectoryObject)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryDirectoryObject");

VOID Example_NtQueryDirectoryObject_0(HANDLE DirectoryGlobalObject, CONST WCHAR *lpName)
{
	PVOID Buffer = NULL;
	ULONG BufferLength = 0x1000;

	PDIRECTORY_BASIC_INFORMATION DirectoryBasicInfo = NULL;
	ULONG Context = 0;

	BOOL IsExist = FALSE;
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		if (DirectoryGlobalObject == NULL)
		{
			break;
		}

		if (lpName == NULL || wcslen(lpName) == 0)
		{
			break;
		}

		if (NtQueryDirectoryObject == NULL)
		{
			break;
		}

		Buffer = VirtualAlloc(NULL, BufferLength, MEM_COMMIT, PAGE_READWRITE);
		if (Buffer == NULL)
		{
			break;
		}
		RtlZeroMemory(Buffer, BufferLength);

		do
		{
			Status = NtQueryDirectoryObject(DirectoryGlobalObject, Buffer, BufferLength, TRUE, FALSE, &Context, &BufferLength);
			if (Status == STATUS_BUFFER_TOO_SMALL)
			{
				BufferLength *= 2;
				if (Buffer != NULL)
				{
					VirtualFree(Buffer, 0, MEM_RELEASE);
					Buffer = NULL;
				}

				Buffer = VirtualAlloc(NULL, BufferLength, MEM_COMMIT, PAGE_READWRITE);
				if (Buffer == NULL)
				{
					break;
				}
				RtlZeroMemory(Buffer, BufferLength);

				continue;
			}

			if (!NT_SUCCESS(Status))
			{
				break;
			}

			DirectoryBasicInfo = (PDIRECTORY_BASIC_INFORMATION)Buffer;
			if (DirectoryBasicInfo->ObjectName.Buffer != NULL &&
				DirectoryBasicInfo->ObjectName.Length == wcslen(lpName) * sizeof(WCHAR) &&
				_wcsnicmp(DirectoryBasicInfo->ObjectName.Buffer, lpName, wcslen(lpName)) == 0)
			{
				IsExist = TRUE;
				break;
			}

			RtlZeroMemory(Buffer, BufferLength);

		} while (Status != STATUS_MORE_ENTRIES);

	} while (FALSE);

	if (Buffer != NULL)
	{
		VirtualFree(Buffer, 0, MEM_RELEASE);
		Buffer = NULL;
	}

}