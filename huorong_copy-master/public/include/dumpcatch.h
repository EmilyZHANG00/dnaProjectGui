#ifndef DUMPCATCH_H
#define DUMPCATCH_H

#pragma once

#ifdef Q_OS_WIN32
#include <QDir>
#include <QTextCodec>
#include <stdio.h>
#include <stdarg.h>
#include <QStandardPaths>
#include <QString>

#include <windows.h>
#include <TCHAR.H>
#include <strsafe.h>
#include <time.h>
#include <DbgHelp.h>
#include <Psapi.h>
#include <shlobj.h>
#include <string>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "Dbghelp.lib")

using namespace std;
// 记录日志
const int MAXLEN_PATH   = 256;
const unsigned int MSG_PRINT_BUF = 16 * 512;
char  g_szLogFile[MAXLEN_PATH] = {0};

BOOL IsDataSectionNeeded(const WCHAR* pModuleName)
{
    if(pModuleName == 0)
    {
        return FALSE;
    }

    WCHAR szFileName[_MAX_FNAME] = L"";
    _wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);
    if(wcsicmp(szFileName, L"ntdll") == 0)
        return TRUE;

    return FALSE;
}

BOOL CALLBACK MiniDumpCallback(PVOID pParam,
                               const PMINIDUMP_CALLBACK_INPUT   pInput,
                               PMINIDUMP_CALLBACK_OUTPUT        pOutput)
{
    if (pInput == 0 || pOutput == 0)
        return FALSE;

    switch(pInput->CallbackType)
    {
    case ModuleCallback:
        if(pOutput->ModuleWriteFlags & ModuleWriteDataSeg)
            if(!IsDataSectionNeeded(pInput->Module.FullPath))
                pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);

    case IncludeModuleCallback:
    case IncludeThreadCallback:
    case ThreadCallback:
    case ThreadExCallback:
        return TRUE;

    default:;
    }

    return FALSE;
}

void CreateDumpFile(LPCSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pep)
{
    // 创建Dump文件
	HANDLE hFile = CreateFileA(lpstrDumpFilePathName, GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE,
                               NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
    {
        // Create the minidump

        MINIDUMP_EXCEPTION_INFORMATION mdei;
        mdei.ThreadId           = GetCurrentThreadId();
        mdei.ExceptionPointers  = pep;
        mdei.ClientPointers     = FALSE;

        MINIDUMP_CALLBACK_INFORMATION mci;
        mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
        mci.CallbackParam       = 0;

        MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)(MiniDumpNormal |
                                                  /*MiniDumpWithPrivateReadWriteMemory |*/
                                                  MiniDumpWithDataSegs |
                                                  MiniDumpWithHandleData |
                                                  /*MiniDumpWithFullMemoryInfo |*/
                                                  MiniDumpWithThreadInfo/* |
                                                  MiniDumpWithUnloadedModules*/);

        BOOL rv = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
                                     hFile, mdt, (pep != 0) ? &mdei : 0, 0, &mci);
        if (!rv)
        {
            // Retrieve the system error message for the last-error code
            LPVOID lpMsgBuf;
            LPVOID lpDisplayBuf;
            DWORD dw = GetLastError();
            FormatMessage(
                        FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        dw,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR) &lpMsgBuf,
                        0, NULL );

            // Display the error message and exit the process
            lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
                                              (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)"vic.exe")+40)*sizeof(TCHAR));
            StringCchPrintf((LPTSTR)lpDisplayBuf,
                            LocalSize(lpDisplayBuf),
                            TEXT("%s failed with error %d: %s"),
                            "vic.exe", dw, lpMsgBuf);
            //MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
            //g_Log("MiniDumpWriteDump failed. vic Error %u : %s\n", dw, lpMsgBuf);

            LocalFree(lpMsgBuf);
            LocalFree(lpDisplayBuf);
            //ExitProcess(dw);
        }
 
        CloseHandle(hFile);
    }
}

LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
    return NULL;
}


BOOL PreventSetUnhandledExceptionFilter()
{
    HMODULE hKernel32 = LoadLibrary(TEXT("kernel32.dll"));
    if (hKernel32 ==   NULL)
        return FALSE;

    void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
    if(pOrgEntry == NULL)
        return FALSE;

    unsigned char newJump[ 100 ];
    DWORD dwOrgEntryAddr = (DWORD) pOrgEntry;
    dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far

    void *pNewFunc = &MyDummySetUnhandledExceptionFilter;
    DWORD dwNewEntryAddr = (DWORD) pNewFunc;
    DWORD dwRelativeAddr = dwNewEntryAddr -  dwOrgEntryAddr;

    newJump[ 0 ] = 0xE9;  // JMP absolute
    memcpy(&newJump[ 1 ], &dwRelativeAddr, sizeof(pNewFunc));
    SIZE_T bytesWritten;
    BOOL bRet = WriteProcessMemory(GetCurrentProcess(), pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
    return bRet;
}

string GetBuildTime()
{
    string strBuildTime;
    string strYear;
    string strMonth;
    string strDay;
    string strTime;
    char sztimebuf[512] = {'\0'};
    sprintf_s(sztimebuf, "%s", __DATE__);
    strTime = sztimebuf;
    std::string::size_type nPos = strTime.find(' ', 0);
    strMonth = strTime.substr(0, nPos);
    strTime = strTime.substr(nPos + 1, strTime.length());

    nPos = strTime.find_last_of(' ');
    strDay = strTime.substr(0, nPos);
    strTime = strTime.substr(nPos + 1, strTime.length());
    strYear = strTime;
    if( strMonth == ("January")|| strMonth == ("Jan"))
        strMonth = "01";
    else if( strMonth == ("February") || strMonth == ("Feb") )
        strMonth = "02";
    else if( strMonth == ("March") || strMonth == ("Mar") )
        strMonth = "03";
    else if( strMonth == ("April") || strMonth == ("Apr") )
        strMonth = "04";
    else if( strMonth == ("May") )
        strMonth = "05";
    else if( strMonth == ("June") || strMonth == ("Jun") )
        strMonth = "06";
    else if( strMonth == ("July") || strMonth == ("Jul") )
        strMonth = "07";
    else if( strMonth == ("August") || strMonth == ("Aug") )
        strMonth = "08";
    else if( strMonth == ("September") || strMonth == ("Sep") )
        strMonth = "09";
    else if( strMonth == ("October") || strMonth == ("Oct") )
        strMonth = "10";
    else if( strMonth == ("November") || strMonth == ("Nov") )
        strMonth = "11";
    else if( strMonth == ("December") || strMonth == ("Dec") )
        strMonth = "12";
    memset(sztimebuf, 0, sizeof(sztimebuf));
    int nDay = atoi(strDay.c_str());
    sprintf_s(sztimebuf, "%s.%s.%d%d", strYear.c_str(), strMonth.c_str(), nDay / 10, nDay % 10);

    strTime = sztimebuf;
    sprintf_s(sztimebuf, "_%s", __TIME__);
    strTime += sztimebuf;

    for (int i = 0 ; i < strTime.length() ; i++)
    {
        if (strTime[i] == ':')
        {
            strTime[i] = '.';
        }
    }

    return strTime.c_str();
}

LONG WINAPI UnhandledExceptionFilterEx(struct _EXCEPTION_POINTERS *pException)
{
    char szExePath[MAXLEN_PATH] = {0};
    GetModuleFileNameA(NULL, szExePath, MAXLEN_PATH);
    char *a, *b;
    a = b = szExePath;
    while(b)
    {
        b = strchr(a + 1, '\\');
        if(b) a=b;
    }
    *a='\0';

    QString strDocuments = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    char szMbsFile[MAX_PATH] = { 0 };
    sprintf_s(szMbsFile, sizeof(szMbsFile), "%s\\", strDocuments.toStdString().c_str());

	char* pFind = strrchr(szMbsFile, '\\');
    if(pFind)
    {
        *(pFind+1) = 0;

        SYSTEMTIME st;
        memset(&st, 0, sizeof(st));
        GetLocalTime(&st);
        char szFileName[MAX_PATH] = {0};
        sprintf_s(szFileName, "%d.%d.%d_%d.%d.%d.dmp", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

        strcat_s(szMbsFile, szFileName);
       
		CreateDumpFile(szMbsFile, pException);
    }
    
    return EXCEPTION_EXECUTE_HANDLER;
}

void RunCrashHandler()
{
    SetUnhandledExceptionFilter(UnhandledExceptionFilterEx);
    PreventSetUnhandledExceptionFilter();
}
#endif // Q_OS_WIN32

#endif // DUMPCATCH_H
