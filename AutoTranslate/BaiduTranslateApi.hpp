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

	CString error_code;
	CString error_msg;
};

/// <summary>
/// 翻译文字
/// </summary>
/// <param name="Account">百度翻译api账号</param>
/// <param name="OriginalText">原文字</param>
/// <param name="TranslatedOut">翻译后的输出</param>
/// <param name="To">翻译到的语言</param>
/// <returns>状态</returns>
int GetTranslatedText(IN BaiduApiAccount Account, IN CString OriginalText, OUT BaiduTranslateApiResponse& TranslatedOut, IN CString To);

/// <summary>
/// 获取按照百度api文档要求的MD5标志
/// </summary>
/// <param name="Account">百度翻译api账号</param>
/// <param name="OriginalText">原文字</param>
/// <param name="Sign">Sign</param>
/// <param name="Salt">盐</param>
/// <returns>状态</returns>
int GetSign(IN BaiduApiAccount Account, IN CString OriginalText, OUT CString& Sign, OUT CString& Salt);

/// <summary>
/// 网址编码空格
/// </summary>
/// <param name="SpaceString">带空格的字符串</param>
/// <param name="EncodedString">编码空格后的字符串</param>
/// <returns>状态</returns>
int UrlEncodeSpace(IN CString SpaceString, OUT CString& EncodedString);
