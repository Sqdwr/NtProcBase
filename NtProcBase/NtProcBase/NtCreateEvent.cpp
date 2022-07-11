#include "NtCreateEvent.h"

pfn_NtCreateEvent NtCreateEvent = (pfn_NtCreateEvent)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtCreateEvent");

VOID Example_NtCreateEvent_0()
{
	HANDLE EventHandle = NULL;

	UNICODE_STRING EventName = { 0 };
	OBJECT_ATTRIBUTES EventAttributs = { 0 };

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	do
	{
		RtlInitUnicodeString(&EventName, L"TestEvent");
		InitializeObjectAttributes(
			&EventAttributs,
			&EventName,
			OBJ_CASE_INSENSITIVE,
			NULL,
			NULL);

		Status = NtCreateEvent(&EventHandle, EVENT_ALL_ACCESS, &EventAttributs, SynchronizationEvent, TRUE);
		if (!NT_SUCCESS(Status))
		{
			break;
		}

	} while (FALSE);

	if (EventHandle != NULL)
	{
		NtClose(EventHandle);
		EventHandle = NULL;
	}
}