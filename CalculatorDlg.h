
// CalculatorDlg.h: 头文件
//

#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <iterator>
#include <string.h>
#include <sstream>
using namespace std;

// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
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
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtondot();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtondiv();
	afx_msg void OnBnClickedButtonmul();
	afx_msg void OnBnClickedButtonsub();
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtonresult();
	afx_msg void OnBnClickedButtonlk();
	afx_msg void OnBnClickedButtonrk();
	BOOL PreTranslateMessage(MSG* pMsg);
	CEdit inputEdit;
	CEdit outputEdit;
	string inputText;
	double result;
	bool errorFlag;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeInput();
};
