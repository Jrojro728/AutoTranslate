#pragma once
#include "pch.h"

/// <summary>
/// �����ϸ��Ƶ�: http://blog.chinaunix.net/uid-11712430-id-4052746.html
/// ��MD5���ɹ�ϣ
/// </summary>
/// <param name="pbData">��������</param>
/// <param name="dwDataLen">���������ֽڳ���</param>
/// <param name="strHash">���16����Hash�ַ���������Ϊ32+1</param>
/// <param name="err">GetLastError()��ֵ</param>
/// <returns>�ɹ�����TRUE, ʧ�ܷ���FALSE</returns>
BOOL static GetMd5Hash(CONST BYTE* pbData, DWORD dwDataLen, CString& strHash, DWORD& err)
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

//https://blog.csdn.net/kai69/article/details/81509212

/// <summary>
/// CString���͵Ŀ��ַ���תΪstring���͵�utf-8�ַ���
/// </summary>
/// <param name="Unicodestr">Ҫת���Ŀ��ַ���</param>
/// <returns>utf8�ַ���</returns>
std::string static UnicodeToUtf8(CString Unicodestr)
{
    wchar_t* unicode = Unicodestr.AllocSysString();
    int len;
    len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
    char* szUtf8 = (char*)malloc(len + 1);
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
    std::string result = szUtf8;
    free(szUtf8);
    return result;
}

/// <summary>
/// ת��std::string -> CString
/// </summary>
/// <param name="utf8str">Ҫת�����ַ���</param>
/// <returns>ת���Ŀ��ַ���</returns>
CString static ConvertUTF8ToCString(std::string utf8str)
{
    /* Ԥת�����õ�����ռ�Ĵ�С */
    int nLen = ::MultiByteToWideChar(CP_UTF8, NULL,
        utf8str.data(), utf8str.size(), NULL, 0);
    /* ת��ΪUnicode */
    std::wstring wbuffer;
    wbuffer.resize(nLen);
    ::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
        (LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
    return(CString(wbuffer.data(), wbuffer.length()));
#else
    /*
     * ת��ΪANSI
     * �õ�ת���󳤶�
     */
    nLen = WideCharToMultiByte(CP_ACP, 0,
        wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

    std::string ansistr;
    ansistr.resize(nLen);

    /* ��unicodeת��ansi */
    WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
        (LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
    return(CString(ansistr.data(), ansistr.length()));
#endif
}

//end https://blog.csdn.net/kai69/article/details/81509212