/* WTFPL 2.0 / Copyright (C) 2024 haloperidozz (TikTok: @haloperidozz) */

#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <math.h>

#define MOVE_STEP                   5

typedef struct tagLVITEMMOVECONTEXT {
    HANDLE hListViewProcess;
    HWND hListView;
    LPPOINT lpptRemote;
    LPRECT lprcRemote;
} LVITEMMOVECONTEXT, *PLVITEMMOVECONTEXT;

/***********************************************************************
 * LvItemMoveContext
 ***********************************************************************/

static VOID LvItemMoveContext_Delete(PLVITEMMOVECONTEXT pContext)
{
    if (pContext == NULL) {
        return;
    }

    if (pContext->lprcRemote != NULL) {
        VirtualFreeEx(
            pContext->hListViewProcess, pContext->lprcRemote,
            0, MEM_RELEASE
        );
    }

    if (pContext->lpptRemote != NULL) {
        VirtualFreeEx(
            pContext->hListViewProcess, pContext->lpptRemote,
            0, MEM_RELEASE
        );
    }

    if (pContext->hListViewProcess != NULL) {
        CloseHandle(pContext->hListViewProcess);
    }

    HeapFree(GetProcessHeap(), 0, pContext);
}

static PLVITEMMOVECONTEXT LvItemMoveContext_CreateFor(HWND hListView)
{
    PLVITEMMOVECONTEXT pContext = NULL;
    DWORD dwProcessId = 0;
    HANDLE hHeap = GetProcessHeap();

    if (hListView == NULL) {
        return NULL;
    }

    if (GetWindowThreadProcessId(hListView, &dwProcessId) == 0) {
        return NULL;
    }

    pContext = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof *pContext);

    if (pContext == NULL) {
        return NULL;
    }

    pContext->hListViewProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION |
        PROCESS_VM_WRITE | PROCESS_VM_READ,
        FALSE, dwProcessId
    );

    pContext->hListView = hListView;
    
    if (pContext->hListViewProcess == NULL) {
        LvItemMoveContext_Delete(pContext);
        return NULL;
    }

    pContext->lpptRemote = VirtualAllocEx(
        pContext->hListViewProcess,
        NULL, sizeof(POINT), MEM_COMMIT, PAGE_READWRITE
    );

    if (pContext->lpptRemote == NULL) {
        LvItemMoveContext_Delete(pContext);
        return NULL;
    }

    pContext->lprcRemote = VirtualAllocEx(
        pContext->hListViewProcess,
        NULL, sizeof(RECT), MEM_COMMIT, PAGE_READWRITE
    );

    if (pContext->lprcRemote == NULL) {
        LvItemMoveContext_Delete(pContext);
        return NULL;
    }

    return pContext;
}

static WINBOOL LvItemMoveContext_GetItemPosition(
    PLVITEMMOVECONTEXT pContext,
    INT i,
    LPPOINT lppt
) {
    BOOL bResult = FALSE;

    if (pContext == NULL || lppt == NULL) {
        return FALSE;
    }
            
    bResult = (WINBOOL) SendMessage(
        pContext->hListView, LVM_GETITEMPOSITION,
        (WPARAM) i, (LPARAM) pContext->lpptRemote
    );

    if (bResult == FALSE) {
        return FALSE;
    }

    return ReadProcessMemory(
        pContext->hListViewProcess, pContext->lpptRemote,
        lppt, sizeof(POINT), NULL
    );
}

static WINBOOL LvItemMoveContext_SetItemPosition(
    PLVITEMMOVECONTEXT pContext,
    INT i,
    INT x, INT y
) {
    if (pContext == NULL) {
        return FALSE;
    }

    return (WINBOOL) SendMessage(                   /* :D */
        pContext->hListView, LVM_SETITEMPOSITION,
        (WPARAM) i, MAKELPARAM(x, y)
    );
}

static WINBOOL LvItemMoveContext_SetItemPositionPoint(
    PLVITEMMOVECONTEXT pContext,
    INT i,
    LPPOINT lppt
) {
    if (lppt == NULL || pContext == NULL) {
        return FALSE;
    }

    return LvItemMoveContext_SetItemPosition(pContext, i, lppt->x, lppt->y);
}

/* unsafe */
static BOOL LvItemMoveContext_GetItem(
    PLVITEMMOVECONTEXT pContext, LPLVITEM lplvi
) {
    BOOL bResult = FALSE;
    LPLVITEM lplviRemote = NULL;
    LPTSTR pszTextRemote = NULL;
    LPTSTR pszTemp;

    if (pContext == NULL || lplvi == NULL) {
        return FALSE;
    }

    if (lplvi->mask & LVIF_TEXT && lplvi->pszText != NULL) {
        pszTextRemote = VirtualAllocEx(
            pContext->hListViewProcess, NULL,
            lplvi->cchTextMax * sizeof(TCHAR), MEM_COMMIT, PAGE_READWRITE
        );

        if (pszTextRemote == NULL) {
            return FALSE;
        }

        WriteProcessMemory(
            pContext->hListViewProcess, pszTextRemote, lplvi->pszText,
            lplvi->cchTextMax * sizeof(TCHAR), NULL
        );

        pszTemp = lplvi->pszText;
        lplvi->pszText = pszTextRemote;
    }

    lplviRemote = VirtualAllocEx(
        pContext->hListViewProcess, NULL,
        sizeof(LVITEM), MEM_COMMIT, PAGE_READWRITE
    );

    if (lplviRemote == NULL) {
        goto cleanup;
    }

    bResult = WriteProcessMemory(
        pContext->hListViewProcess, lplviRemote,
        lplvi, sizeof(LVITEM), NULL
    );

    if (bResult == FALSE) {
        goto cleanup;
    }

    bResult = SendMessage(
        pContext->hListView, LVM_GETITEM, 0, (LPARAM)lplviRemote
    );

    if (bResult == FALSE) {
        goto cleanup;
    }

    bResult = ReadProcessMemory(
        pContext->hListViewProcess, lplviRemote,
        lplvi, sizeof(LVITEM), NULL
    );

    if (bResult == FALSE) {
        goto cleanup;
    }

    if (lplvi->mask & LVIF_TEXT && lplvi->pszText != NULL) {
        ReadProcessMemory(
            pContext->hListViewProcess, pszTextRemote,
            pszTemp, lplvi->cchTextMax * sizeof(TCHAR), NULL
        );

        lplvi->pszText = pszTemp;
    }

cleanup:
    if (pszTextRemote != NULL) {
        VirtualFreeEx(
            pContext->hListViewProcess, pszTextRemote, 0, MEM_RELEASE
        );
    }

    if (lplviRemote != NULL) {
        VirtualFreeEx(
            pContext->hListViewProcess, lplviRemote, 0, MEM_RELEASE
        );
    }

    return bResult;
}

static INT LvItemMoveContext_GetItemCount(PLVITEMMOVECONTEXT pContext)
{
    if (pContext == NULL) {
        return 0;
    }

    return (INT) SendMessage(pContext->hListView, LVM_GETITEMCOUNT, 0, 0);
}

/***********************************************************************
 * GetDesktopListView ("FolderView" SysListView32)
 ***********************************************************************/

/* https://stackoverflow.com/a/60856252 */
static BOOL CALLBACK FindDefView_EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    HWND *phShellDefViewWnd = (HWND*) lParam;
    HWND hNextWin = FindWindowExA(hWnd, 0, "SHELLDLL_DefView", 0);
    HWND hNextNextWin, hPrevNextWin;

    if (hNextWin == NULL) {
        return TRUE;
    }

    hNextNextWin = GetNextWindow(hNextWin, GW_HWNDNEXT);
    hPrevNextWin = GetNextWindow(hNextWin, GW_HWNDPREV);

    if ((hNextNextWin != NULL) || (hPrevNextWin != NULL)) {
        return TRUE;
    }

    *phShellDefViewWnd = hNextWin;
    return FALSE;
}

static HWND GetDesktopListView(VOID)
{
    HWND hDefViewWnd = NULL;

    EnumWindows(&FindDefView_EnumWindowsProc, (LPARAM) &hDefViewWnd);

    if (hDefViewWnd == NULL) {
        return NULL;
    }

    return FindWindowExA(hDefViewWnd, NULL, "SysListView32", NULL);
}

/***********************************************************************
 * Useful Functions
 ***********************************************************************/

static INT GetRecycleBinIndex(PLVITEMMOVECONTEXT pContext)
{
    LVITEM lvi = {0};
    TCHAR szBuffer[256] = {0};
    INT iCount;
    INT i;

    if (pContext == NULL) {
        return -1;
    }

    iCount = LvItemMoveContext_GetItemCount(pContext);

    lvi.mask = LVIF_TEXT;
    lvi.cchTextMax = 256;
    lvi.pszText = szBuffer;

    for (i = 0; i < iCount; ++i) {
        lvi.iItem = i;

        if (LvItemMoveContext_GetItem(pContext, &lvi) == FALSE) {
            continue;
        }

        if (_tcscmp(TEXT("Корзина"), szBuffer) == 0) {
            return i;
        }

        if (_tcscmp(TEXT("Recycle Bin"), szBuffer) == 0) {
            return i;
        }
    }

    return -1;
}

static VOID MovePointTowards(LPPOINT lpptCurrent, POINT ptTarget)
{
    DOUBLE dbDistance = 0.0;
    INT dx, dy;

    if (lpptCurrent == NULL) {
        return;
    }

    dx = ptTarget.x - lpptCurrent->x;
    dy = ptTarget.y - lpptCurrent->y;

    if (dx == 0 && dy == 0) {
        return;
    }

    dbDistance = sqrt(dx * dx + dy * dy);

    lpptCurrent->x += (INT) (MOVE_STEP * dx / dbDistance);
    lpptCurrent->y += (INT) (MOVE_STEP * dy / dbDistance);
}

/***********************************************************************
 * Main
 ***********************************************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    POINT ptItem, ptRecycleBin;
    PLVITEMMOVECONTEXT pContext;
    INT iCount, i;
    INT iRecycleBin, iForDelete = -1;
    RECT rcRecycleBin;

    pContext = LvItemMoveContext_CreateFor(GetDesktopListView());

    if (pContext == NULL) {
        return -1;
    }

    while (TRUE) {
        iCount = LvItemMoveContext_GetItemCount(pContext);
        iRecycleBin = GetRecycleBinIndex(pContext);

        if (iRecycleBin == -1 || iCount <= 1) {
            break;
        }

        LvItemMoveContext_GetItemPosition(
            pContext, iRecycleBin, &ptRecycleBin
        );

        for (i = 0; i < iCount; ++i) {
            if (i == iRecycleBin) {
                continue;
            }

            LvItemMoveContext_GetItemPosition(pContext, i, &ptItem);
            MovePointTowards(&ptItem, ptRecycleBin);
            LvItemMoveContext_SetItemPositionPoint(pContext, i, &ptItem);
        }

        Sleep(5);
    }

    LvItemMoveContext_Delete(pContext);
    return 0;
}
