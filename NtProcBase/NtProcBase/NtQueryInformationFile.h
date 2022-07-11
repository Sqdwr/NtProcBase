#pragma once

#include "NtBase.h"
#include "NtQueryAttributesFile.h"

typedef enum _FILE_INFORMATION_CLASS 
{
	FileDirectoryInformation = 1,
	FileFullDirectoryInformation,   // 2
	FileBothDirectoryInformation,   // 3
	FileBasicInformation,           // 4
	FileStandardInformation,        // 5
	FileInternalInformation,        // 6
	FileEaInformation,              // 7
	FileAccessInformation,          // 8
	FileNameInformation,            // 9
	FileRenameInformation,          // 10
	FileLinkInformation,            // 11
	FileNamesInformation,           // 12
	FileDispositionInformation,     // 13
	FilePositionInformation,        // 14
	FileFullEaInformation,          // 15
	FileModeInformation,            // 16
	FileAlignmentInformation,       // 17
	FileAllInformation,             // 18
	FileAllocationInformation,      // 19
	FileEndOfFileInformation,       // 20
	FileAlternateNameInformation,   // 21
	FileStreamInformation,          // 22
	FilePipeInformation,            // 23
	FilePipeLocalInformation,       // 24
	FilePipeRemoteInformation,      // 25
	FileMailslotQueryInformation,   // 26
	FileMailslotSetInformation,     // 27
	FileCompressionInformation,     // 28
	FileObjectIdInformation,        // 29
	FileCompletionInformation,      // 30
	FileMoveClusterInformation,     // 31
	FileQuotaInformation,           // 32
	FileReparsePointInformation,    // 33
	FileNetworkOpenInformation,     // 34
	FileAttributeTagInformation,    // 35
	FileTrackingInformation,        // 36
	FileIdBothDirectoryInformation, // 37
	FileIdFullDirectoryInformation, // 38
	FileValidDataLengthInformation, // 39
	FileShortNameInformation,       // 40
	FileIoCompletionNotificationInformation, // 41
	FileIoStatusBlockRangeInformation,       // 42
	FileIoPriorityHintInformation,           // 43
	FileSfioReserveInformation,              // 44
	FileSfioVolumeInformation,               // 45
	FileHardLinkInformation,                 // 46
	FileProcessIdsUsingFileInformation,      // 47
	FileNormalizedNameInformation,           // 48
	FileNetworkPhysicalNameInformation,      // 49
	FileIdGlobalTxDirectoryInformation,      // 50
	FileIsRemoteDeviceInformation,           // 51
	FileUnusedInformation,                   // 52
	FileNumaNodeInformation,                 // 53
	FileStandardLinkInformation,             // 54
	FileRemoteProtocolInformation,           // 55

		//
		//  These are special versions of these operations (defined earlier)
		//  which can be used by kernel mode drivers only to bypass security
		//  access checks for Rename and HardLink operations.  These operations
		//  are only recognized by the IOManager, a file system should never
		//  receive these.
		//

		FileRenameInformationBypassAccessCheck,  // 56
		FileLinkInformationBypassAccessCheck,    // 57

			//
			// End of special information classes reserved for IOManager.
			//

			FileVolumeNameInformation,               // 58
			FileIdInformation,                       // 59
			FileIdExtdDirectoryInformation,          // 60
			FileReplaceCompletionInformation,        // 61
			FileHardLinkFullIdInformation,           // 62
			FileIdExtdBothDirectoryInformation,      // 63
			FileDispositionInformationEx,            // 64
			FileRenameInformationEx,                 // 65
			FileRenameInformationExBypassAccessCheck, // 66
			FileDesiredStorageClassInformation,      // 67
			FileStatInformation,                     // 68
			FileMemoryPartitionInformation,          // 69
			FileMaximumInformation

} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

typedef struct _FILE_LINK_ENTRY_INFORMATION 
{
	ULONG NextEntryOffset;
	LONGLONG ParentFileId;
	ULONG FileNameLength;
	WCHAR FileName[1];

} FILE_LINK_ENTRY_INFORMATION, *PFILE_LINK_ENTRY_INFORMATION;

typedef struct _FILE_LINKS_INFORMATION 
{
	ULONG BytesNeeded;
	ULONG EntriesReturned;
	FILE_LINK_ENTRY_INFORMATION Entry;

} FILE_LINKS_INFORMATION, *PFILE_LINKS_INFORMATION;

typedef struct _FILE_NAME_INFORMATION 
{
	ULONG FileNameLength;
	WCHAR FileName[1];

} FILE_NAME_INFORMATION, *PFILE_NAME_INFORMATION;

typedef struct _FILE_STANDARD_INFORMATION 
{
	LARGE_INTEGER AllocationSize;
	LARGE_INTEGER EndOfFile;
	ULONG         NumberOfLinks;
	BOOLEAN       DeletePending;
	BOOLEAN       Directory;

} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

typedef NTSTATUS(NTAPI *pfn_NtQueryInformationFile)(
	HANDLE                 FileHandle,
	PIO_STATUS_BLOCK       IoStatusBlock,
	PVOID                  FileInformation,
	ULONG                  Length,
	FILE_INFORMATION_CLASS FileInformationClass
	);

extern pfn_NtQueryInformationFile NtQueryInformationFile;