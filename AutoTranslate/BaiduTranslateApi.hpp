#pragma once
#include "pch.h"
#include "Copy.hpp"

/// <summary>
/// 百度翻译api账号
/// </summary>
struct BaiduApiAccount
{
	CString AppID;
	CString SecretKey;
};

/// <summary>
/// 百度翻译api Json输出
/// </summary>
struct BaiduTranslateApiResponse
{
	CString from;
	CString to;
	struct trans_result
	{
		CString src;
		CString dst;
	}trans_result;
};

/// <summary>
/// 翻译文字
/// </summary>
/// <param name="Account">百度翻译api账号</param>
/// <param name="OriginalText">原文字</param>
/// <param name="TranslatedText">翻译后的文字</param>
/// <returns>状态</returns>
int GetTranslatedText(IN BaiduApiAccount Account, IN CString OriginalText, OUT BaiduTranslateApiResponse &TranslatedOut);

/// <summary>
/// 获取按照百度api文档要求的MD5标志
/// </summary>
/// <param name="Account">百度翻译api账号</param>
/// <param name="OriginalText">原文字</param>
/// <param name="Sign">Sign</param>
/// <param name="Salt">盐</param>
/// <returns>状态</returns>
int GetSign(IN BaiduApiAccount Account, IN CString OriginalText, OUT CString &Sign, OUT CString& Salt);
