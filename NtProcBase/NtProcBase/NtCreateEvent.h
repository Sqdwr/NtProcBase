#pragma once

#include "NtBase.h"

typedef enum _EVENT_TYPE {
	NotificationEvent,
	SynchronizationEvent
} EVENT_TYPE;

typedef NTSTATUS(NTAPI *pfn_NtCreateEvent)(
	PHANDLE            EventHandle,
	ACCESS_MASK        DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	EVENT_TYPE         EventType,
	BOOLEAN            InitialState
	);

extern pfn_NtCreateEvent NtCreateEvent;