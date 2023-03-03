#pragma once
#include "pch.h"

/// <summary>
/// 从网上复制的: http://blog.chinaunix.net/uid-11712430-id-4052746.html
/// 用MD5生成哈希
/// </summary>
/// <param name="pbData">输入数据</param>
/// <param name="dwDataLen">输入数据字节长度</param>
/// <param name="strHash">输出16进制Hash字符串，长度为32+1</param>
/// <param name="err">GetLastError()的值</param>
/// <returns>成功返回TRUE, 失败返回FALSE</returns>
BOOL GetMd5Hash(CONST BYTE* pbData, DWORD dwDataLen, CString& strHash, DWORD& err);

//https://blog.csdn.net/kai69/article/details/81509212

/// <summary>
/// CString类型的宽字符串转为string类型的utf-8字符串
/// </summary>
/// <param name="Unicodestr">要转换的宽字符串</param>
/// <returns>utf8字符串</returns>
std::string UnicodeToUtf8(CString Unicodestr);

/// <summary>
/// 转换std::string -> CString
/// </summary>
/// <param name="utf8str">要转换的字符串</param>
/// <returns>转换的宽字符串</returns>
CString ConvertUTF8ToCString(std::string utf8str);

//end https://blog.csdn.net/kai69/article/details/81509212