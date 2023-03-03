#include "pch.h"
#include "Copy.hpp"

BOOL GetMd5Hash(CONST BYTE* pbData, DWORD dwDataLen, CString& strHash, DWORD& err)
{
    HCRYPTPROV hProv;
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        err = GetLastError();
        return FALSE;
    }

    HCRYPTHASH hHash;
    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
    {
        err = GetLastError();
        CryptReleaseContext(hProv, 0);
        return FALSE;
    }

    if (!CryptHashData(hHash, pbData, dwDataLen, 0))
    {
        err = GetLastError();
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return FALSE;
    }

    DWORD dwSize;
    DWORD dwLen = sizeof(dwSize);
    CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)(&dwSize), &dwLen, 0);

    BYTE* pHash = new BYTE[dwSize];
    dwLen = dwSize;
    CryptGetHashParam(hHash, HP_HASHVAL, pHash, &dwLen, 0);

    strHash = _T("");
    for (DWORD i = 0; i < dwLen; i++)
        strHash.AppendFormat(_T("%02x"), pHash[i]);
    delete[] pHash;

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return TRUE;
}

std::string UnicodeToUtf8(CString Unicodestr)
{
    wchar_t* Unicode = Unicodestr.AllocSysString();
    int len;
    len = WideCharToMultiByte(CP_UTF8, 0, Unicode, -1, NULL, 0, NULL, NULL);
    char* szUtf8 = (char*)malloc(len + 1);
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, Unicode, -1, szUtf8, len, NULL, NULL);
    std::string result = szUtf8;
    free(szUtf8);
    return result;
}

CString ConvertUTF8ToCString(std::string utf8str)
{
    /* 预转换，得到所需空间的大小 */
    int nLen = ::MultiByteToWideChar(CP_UTF8, NULL,
        utf8str.data(), utf8str.size(), NULL, 0);
    /* 转换为Unicode */
    std::wstring wbuffer;
    wbuffer.resize(nLen);
    ::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
        (LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
    return(CString(wbuffer.data(), wbuffer.length()));
#else
    /*
     * 转换为ANSI
     * 得到转换后长度
     */
    nLen = WideCharToMultiByte(CP_ACP, 0,
        wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

    std::string ansistr;
    ansistr.resize(nLen);

    /* 把Unicode转成ansi */
    WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
        (LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
    return(CString(ansistr.data(), ansistr.length()));
#endif
}
