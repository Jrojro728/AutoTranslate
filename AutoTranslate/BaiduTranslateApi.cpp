#include "pch.h"
#include "BaiduTranslateApi.hpp"

using namespace boost::network;
using namespace boost::network::http;

int GetTranslatedText(IN BaiduApiAccount Account, IN CString OriginalText, OUT BaiduTranslateApiResponse &TranslatedOut)
{
	CString Sign;
	CString Salt;
	GetSign(Account, OriginalText, Sign, Salt);
	
	//������ַ
	uri::uri TranslateApiUrl("http://fanyi-api.baidu.com/api/trans/vip/translate");
	TranslateApiUrl << uri::query("q=" + UnicodeToUtf8(OriginalText) + "&from=auto&to=zh&appid=" + UnicodeToUtf8(Account.AppID) + "&salt=" + UnicodeToUtf8(Salt) + "&sign=" + UnicodeToUtf8(Sign));
	/*AfxMessageBox(CString(TranslateApiUrl.query().c_str()));*/

	//http�ͻ���
	client Client;
	client::request Request(TranslateApiUrl);
	Request << header("Connection", "close");
	client::response Response = Client.get(Request);
	std::string ResponseStr = body(Response);

	//Json����
	Json::Reader Parser;
	Json::Value Root;

	if (Parser.parse(ResponseStr, Root))
	{
		TranslatedOut.from = Root["from"].asCString();
		TranslatedOut.to = Root["to"].asCString();
		
		const Json::Value ArrayValue = Root["trans_result"];
		TranslatedOut.trans_result.src = ArrayValue[0]["src"].asCString();
		
		TranslatedOut.trans_result.dst = ConvertUTF8ToCString(ArrayValue[0]["dst"].asCString());
	}
	else
	{
		return 1;
	}

	return 0;
}

int GetSign(IN BaiduApiAccount Account, IN CString OriginalText, OUT CString &Sign, OUT CString &Salt)
{
	srand(rand());
	for (size_t i = 0; i < 10; i++)
	{
		srand(rand());//��������,�����������?
	}
	int iSalt = rand();//������
	char aSalt[16] = "\0\0\0\0\0\0\0\0\0\0\0\0\0";//�ַ���
	_itoa_s(iSalt, aSalt, 10); //ת��int -> char[]
    Salt = CString(aSalt); //���ַ���

	CString UnMD5String = (((Account.AppID + OriginalText) + Salt) + Account.SecretKey); //δ����MD5��ȡ��ϣ���ַ���
	std::string UnMD5UTF8String = UnicodeToUtf8(UnMD5String);//δ����MD5��ȡ��ϣ��UTF8�ַ���

	//What?
	DWORD err;
	if (GetMd5Hash((BYTE*)UnMD5UTF8String.c_str(), UnMD5UTF8String.size(), Sign, err) == FALSE)
		return 1;

	return 0;
} 