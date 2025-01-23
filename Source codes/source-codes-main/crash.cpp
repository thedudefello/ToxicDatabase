EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(DWORD, BYTE, BYTE, PBYTE);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS, DWORD, DWORD, PDWORD_PTR, DWORD, PDWORD);
// this is the ntstatus define (made for crashing the system)
// rewritten by Tubercomiosis (me)

BYTE ntBool;
DWORD rsp;
RtlAdjustPrivilege(19, TRUE, FALSE, &ntBool);
NtRaiseHardError(0x, 0, 0, 0, 6, &rsp); // replace 0x with an applicable NTSTATUS error code, check out https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/596a1078-e883-4972-9bbc-49e60bebca55
