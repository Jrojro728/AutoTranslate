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
};

/// <summary>
/// ��������
/// </summary>
/// <param name="Account">�ٶȷ���api�˺�</param>
/// <param name="OriginalText">ԭ����</param>
/// <param name="TranslatedText">����������</param>
/// <returns>״̬</returns>
int GetTranslatedText(IN BaiduApiAccount Account, IN CString OriginalText, OUT BaiduTranslateApiResponse &TranslatedOut);

/// <summary>
/// ��ȡ���հٶ�api�ĵ�Ҫ���MD5��־
/// </summary>
/// <param name="Account">�ٶȷ���api�˺�</param>
/// <param name="OriginalText">ԭ����</param>
/// <param name="Sign">Sign</param>
/// <param name="Salt">��</param>
/// <returns>״̬</returns>
int GetSign(IN BaiduApiAccount Account, IN CString OriginalText, OUT CString &Sign, OUT CString& Salt);
