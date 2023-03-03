#include "pch.h"
#include "BaiduTranslateApi.hpp"

using namespace boost::network;
using namespace boost::network::http;

int GetTranslatedText(IN BaiduApiAccount Account, IN CString OriginalText, OUT BaiduTranslateApiResponse& TranslatedOut, IN CString To)
{
	CString Sign;
	CString Salt;
	GetSign(Account, OriginalText, Sign, Salt);

	//解析网址
	if (To == L"")
		To = L"zh";
	std::string FinalUrl = "q=" + UnicodeToUtf8(OriginalText) + "&from=auto&to=" + UnicodeToUtf8(To) + "&appid=" + UnicodeToUtf8(Account.AppID) + "&salt=" + UnicodeToUtf8(Salt) + "&sign=" + UnicodeToUtf8(Sign);
	UrlEncodeSpace(OriginalText, OriginalText);

	uri::uri TranslateApiUrl("http://fanyi-api.baidu.com/api/trans/vip/translate");
	TranslateApiUrl << uri::query(FinalUrl);
	/*AfxMessageBox(CString(TranslateApiUrl.query().c_str()));*/

	//http客户端
	client Client;
	client::request Request(TranslateApiUrl);
	Request << header("Connection", "close");
	client::response Response = Client.get(Request);
	std::string ResponseStr = body(Response);

	//Json解析
	Json::Reader Parser;
	Json::Value Root;

	if (Parser.parse(ResponseStr, Root))
	{
		try
		{
			TranslatedOut.error_code = Root["error_code"].asCString();
			TranslatedOut.error_msg = Root["error_msg"].asCString();
		}
		catch (Json::LogicError logicError) {
			TranslatedOut.from = Root["from"].asCString();
			TranslatedOut.to = Root["to"].asCString();

			const Json::Value ArrayValue = Root["trans_result"];
			TranslatedOut.trans_result.src = ArrayValue[0]["src"].asCString();
			TranslatedOut.trans_result.dst = ConvertUTF8ToCString(ArrayValue[0]["dst"].asCString());
		}
	}
	else
	{
		return 1;
	}

	return 0;
}

int GetSign(IN BaiduApiAccount Account, IN CString OriginalText, OUT CString& Sign, OUT CString& Salt)
{
	srand(rand());
	for (size_t i = 0; i < 10; i++)
	{
		srand(rand());//设置种子,但真的有用吗?
	}
	int iSalt = rand();//数字盐
	char aSalt[16] = "\0\0\0\0\0\0\0\0\0\0\0\0\0";//字符盐
	_itoa_s(iSalt, aSalt, 10); //转换int -> char[]
	Salt = CString(aSalt); //盐字符串

	CString UnMD5String = (((Account.AppID + OriginalText) + Salt) + Account.SecretKey); //未进行MD5获取哈希的字符串
	std::string UnMD5UTF8String = UnicodeToUtf8(UnMD5String);//未进行MD5获取哈希的UTF8字符串

	//What?
	DWORD err;
	if (GetMd5Hash((BYTE*)UnMD5UTF8String.c_str(), UnMD5UTF8String.size(), Sign, err) == FALSE)
		return 1;

	return 0;
}

int UrlEncodeSpace(IN CString SpaceString, OUT CString& EncodedString)
{
	SpaceString.Replace(L" ", L"%20");
	EncodedString = SpaceString;

	return 0;
}
