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
BOOL GetMd5Hash(CONST BYTE* pbData, DWORD dwDataLen, CString& strHash, DWORD& err);

//https://blog.csdn.net/kai69/article/details/81509212

/// <summary>
/// CString���͵Ŀ��ַ���תΪstring���͵�utf-8�ַ���
/// </summary>
/// <param name="Unicodestr">Ҫת���Ŀ��ַ���</param>
/// <returns>utf8�ַ���</returns>
std::string UnicodeToUtf8(CString Unicodestr);

/// <summary>
/// ת��std::string -> CString
/// </summary>
/// <param name="utf8str">Ҫת�����ַ���</param>
/// <returns>ת���Ŀ��ַ���</returns>
CString ConvertUTF8ToCString(std::string utf8str);

//end https://blog.csdn.net/kai69/article/details/81509212