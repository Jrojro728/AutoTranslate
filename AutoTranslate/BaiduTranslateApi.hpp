#pragma once
#include "pch.h"
#include "Copy.hpp"

/// <summary>
/// �ٶȷ���api�˺�
/// </summary>
struct BaiduApiAccount
{
	CString AppID;
	CString SecretKey;
};

/// <summary>
/// �ٶȷ���api Json���
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
/// ��������
/// </summary>
/// <param name="Account">�ٶȷ���api�˺�</param>
/// <param name="OriginalText">ԭ����</param>
/// <param name="TranslatedOut">���������</param>
/// <param name="To">���뵽������</param>
/// <returns>״̬</returns>
int GetTranslatedText(IN BaiduApiAccount Account, IN CString OriginalText, OUT BaiduTranslateApiResponse& TranslatedOut, IN CString To);

/// <summary>
/// ��ȡ���հٶ�api�ĵ�Ҫ���MD5��־
/// </summary>
/// <param name="Account">�ٶȷ���api�˺�</param>
/// <param name="OriginalText">ԭ����</param>
/// <param name="Sign">Sign</param>
/// <param name="Salt">��</param>
/// <returns>״̬</returns>
int GetSign(IN BaiduApiAccount Account, IN CString OriginalText, OUT CString& Sign, OUT CString& Salt);

/// <summary>
/// ��ַ����ո�
/// </summary>
/// <param name="SpaceString">���ո���ַ���</param>
/// <param name="EncodedString">����ո����ַ���</param>
/// <returns>״̬</returns>
int UrlEncodeSpace(IN CString SpaceString, OUT CString& EncodedString);
