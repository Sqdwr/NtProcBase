#include "NtQueryObject.h"

pfn_NtQueryObject NtQueryObject = (pfn_NtQueryObject)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryObject");

VOID Example_NtQueryObject_0(HANDLE QueryHandle)
{
	POBJECT_TYPE_INFORMATION ObjectTypeInfo = NULL;
	ULONG Length = 0;

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		if (QueryHandle == NULL)
		{
			break;
		}

		Status = NtQueryObject(QueryHandle, ObjectTypeInformation, NULL, 0, &Length);
		if (Status != STATUS_INFO_LENGTH_MISMATCH)
		{
			break;
		}

		ObjectTypeInfo = (POBJECT_TYPE_INFORMATION)VirtualAlloc(NULL, Length + sizeof(WCHAR), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (ObjectTypeInfo == NULL)
		{
			break;
		}
		RtlZeroMemory(ObjectTypeInfo, Length + sizeof(WCHAR));

		Status = NtQueryObject(QueryHandle, ObjectTypeInformation, ObjectTypeInfo, Length, &Length);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

		// NtOpenDirectoryObject打开句柄的对象类型是Directory
		// NtCreateFile打开文件夹句柄的对象类型是File
		if (_wcsnicmp(ObjectTypeInfo->TypeName.Buffer, L"Directory", ObjectTypeInfo->TypeName.Length / sizeof(WCHAR)) == 0)
		{
			break;
		}

	} while (FALSE);

	if (ObjectTypeInfo != NULL)
	{
		VirtualFree(ObjectTypeInfo, 0, MEM_RELEASE);
		ObjectTypeInfo = NULL;
	}
}

VOID Example_NtQueryObject_1(HANDLE QueryHandle)
{
	POBJECT_NAME_INFORMATION ObjectNameInfo = NULL;
	ULONG Length = 0;

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		if (QueryHandle == NULL)
		{
			break;
		}

		Status = NtQueryObject(QueryHandle, ObjectNameInformation, NULL, 0, &Length);
		if (Status != STATUS_INFO_LENGTH_MISMATCH)
		{
			break;
		}

		ObjectNameInfo = (POBJECT_NAME_INFORMATION)VirtualAlloc(NULL, Length + sizeof(WCHAR), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (ObjectNameInfo == NULL)
		{
			break;
		}
		RtlZeroMemory(ObjectNameInfo, Length + sizeof(WCHAR));

		Status = NtQueryObject(QueryHandle, ObjectNameInformation, ObjectNameInfo, Length, &Length);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

		// NtOpenDirectoryObject打开句柄的对象类型是Directory
		// NtCreateFile打开文件夹句柄的对象类型是File
		if (_wcsnicmp(ObjectNameInfo->ObjectName.Buffer, L"\\??\\D:\\xxx\\123.txt", ObjectNameInfo->ObjectName.Length / sizeof(WCHAR)) == 0)
		{
			break;
		}

	} while (FALSE);

	if (ObjectNameInfo != NULL)
	{
		VirtualFree(ObjectNameInfo, 0, MEM_RELEASE);
		ObjectNameInfo = NULL;
	}

}