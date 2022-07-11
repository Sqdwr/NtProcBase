#include "NtBase.h"

pfn_NtClose NtClose = (pfn_NtClose)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtClose");

pfn_RtlIsNameInExpression RtlIsNameInExpression = (pfn_RtlIsNameInExpression)GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlIsNameInExpression");
pfn_RtlUpcaseUnicodeChar RtlUpcaseUnicodeChar = (pfn_RtlUpcaseUnicodeChar)GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlUpcaseUnicodeChar");

VOID RtlInitUnicodeString(PUNICODE_STRING DestinationString, PCWSTR SourceString)
{
	do
	{
		if (DestinationString == NULL)
		{
			break;
		}

		if (SourceString == NULL)
		{
			DestinationString->Buffer = NULL;
			DestinationString->Length = 0;
			DestinationString->MaximumLength = 0;

			break;
		}

		DestinationString->Buffer = (PWSTR)SourceString;
		DestinationString->Length = (USHORT)(wcslen(SourceString) * sizeof(WCHAR));
		DestinationString->MaximumLength = DestinationString->Length + sizeof(WCHAR);

	} while (FALSE);
}
