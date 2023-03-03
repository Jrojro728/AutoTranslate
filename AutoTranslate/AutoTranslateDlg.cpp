
// AutoTranslateDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AutoTranslate.h"
#include "AutoTranslateDlg.h"
#include "afxdialogex.h"
#include "BaiduTranslateApi.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CAutoTranslateDlg* AutoTranslateDlg;

std::list<CString> CanTranslateLauguageList = {
	L"粤语", L"韩语", L"泰语", L"葡萄牙语", L"希腊语", L"保加利亚语", L"芬兰语",
	L"斯洛文尼亚语", L"繁体中文", L"中文", L"文言文", L"法语", L"阿拉伯语", L"德语",
	L"荷兰语", L"爱沙尼亚语", L"捷克语", L"瑞典语", L"越南语", L"英语", L"日语",
	L"西班牙语", L"俄语", L"意大利语", L"波兰语", L"丹麦语", L"瑞典语", L"匈牙利语"
};
std::list<CString> CanTranslateLauguageCodeList = {
	L"yue", L"kor", L"th", L"pt", L"el", L"bul", L"fin", L"slo", L"cht", L"zh",
	L"wyw", L"fra", L"ara", L"de", L"nl", L"est", L"cs", L"swe", L"vie", L"en",
	L"jp", L"spa", L"ru", L"it", L"pl", L"dan", L"rom", L"hu"
};
std::map<CString, CString> CanTranslateLanguageMap;
CString SelectDstLang;

CString LastOriginalText;
CString LastDstLang;

// CAutoTranslateDlg 对话框
void TranslateUsage(IN CString OriginalText, IN CEdit& TrigetEdit);

void CheckCheckBox()
{
	for (;;)
	{
		Sleep(2 * 1000);
		//打开剪切板
		CString FromClipBoard;
		OpenClipboard(NULL);
		if (AutoTranslateDlg->Check1.GetCheck() == 1)
		{
			//获取剪切板的内容
			HANDLE HandleData = GetClipboardData(CF_TEXT);
			char* Buffer = (char*)GlobalLock(HandleData);
			FromClipBoard = Buffer;
			GlobalUnlock(HandleData);
			CloseClipboard();
			TranslateUsage(FromClipBoard, AutoTranslateDlg->Edit2);
		}
		if (AutoTranslateDlg->Check2.GetCheck() == 1)
		{
			//获取翻译后的内容
			CString TranslateOutStr;
			AutoTranslateDlg->Edit2.GetWindowTextW(TranslateOutStr);
			if (TranslateOutStr == L"将会在此输出")
				continue;

			//设置剪切板的内容
			HGLOBAL ClipBuffer;
			char* Buffer;
			EmptyClipboard();
			ClipBuffer = GlobalAlloc(GMEM_DDESHARE, (TranslateOutStr.GetLength() + 1) * sizeof(wchar_t));
			Buffer = (char*)GlobalLock(ClipBuffer);
			strcpy_s(Buffer, (static_cast<unsigned long long>(TranslateOutStr.GetLength()) + 1) * sizeof(wchar_t), UnicodeToUtf8(TranslateOutStr).c_str());
			GlobalUnlock(ClipBuffer);
			SetClipboardData(CF_TEXT, ClipBuffer);
			CloseClipboard();
		}
	}

	return;
}

/// <summary>
/// 使用翻译api
/// </summary>
/// <param name="OriginalText">原文字</param>
/// <param name="TargetEdit">要输出到的输入框</param>
void TranslateUsage(IN CString OriginalText, IN CEdit& TargetEdit)
{
	if (LastOriginalText == OriginalText && LastDstLang == SelectDstLang)
		return;

	LastOriginalText = OriginalText;
	LastDstLang = SelectDstLang;

	BaiduTranslateApiResponse Out;
	GetTranslatedText({ L"20230210001557204", L"f7uY42CO2r_UxSyByjAm" }, LastOriginalText, Out, LastDstLang);
	if (Out.trans_result.dst != L"")
		TargetEdit.SetWindowTextW(Out.trans_result.dst);
	else
		TargetEdit.SetWindowTextW(L"翻译时发生错误: " + Out.error_msg);
}

CAutoTranslateDlg::CAutoTranslateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUTOTRANSLATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Edit);
	DDX_Control(pDX, IDC_EDIT2, Edit2);
	DDX_Control(pDX, IDC_CHECK1, Check1);
	DDX_Control(pDX, IDC_CHECK2, Check2);
	DDX_Control(pDX, IDC_COMBO1, ComboBox1);
}

BEGIN_MESSAGE_MAP(CAutoTranslateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoTranslateDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAutoTranslateDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CAutoTranslateDlg 消息处理程序

BOOL CAutoTranslateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	AutoTranslateDlg = this;

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Edit.SetWindowText(L"在此输入要翻译的文字");
	Edit2.SetWindowText(L"将会在此输出");

	std::thread t(CheckCheckBox);
	t.detach();

	int i = 0;
	for (CString l : CanTranslateLauguageList)
	{
		ComboBox1.AddString(l);

		std::list<CString>::iterator iter = CanTranslateLauguageCodeList.begin();
		std::advance(iter, i);
		CanTranslateLanguageMap.insert({ l, *iter });

		i++;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAutoTranslateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutoTranslateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAutoTranslateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAutoTranslateDlg::OnBnClickedButton1()
{
	CString Temp;
	Edit.GetWindowText(Temp);
	TranslateUsage(Temp, Edit2);
}


void CAutoTranslateDlg::OnCbnSelchangeCombo1()
{
	CString SelectStr;
	int index = ComboBox1.GetCurSel();
	ComboBox1.GetLBText(index, SelectStr);

	SelectDstLang = CanTranslateLanguageMap[SelectStr];
}
