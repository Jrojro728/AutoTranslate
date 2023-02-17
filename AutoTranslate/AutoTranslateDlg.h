
// AutoTranslateDlg.h: 头文件
//

#pragma once


// CAutoTranslateDlg 对话框
class CAutoTranslateDlg : public CDialogEx
{
// 构造
public:
	CAutoTranslateDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOTRANSLATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	// 主输入框
	CEdit Edit;
	// 输出栏
	CEdit Edit2;

	// 自动翻译
	CButton Check1;
	// 自动复制
	CButton Check2;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox ComboBox1;
};
