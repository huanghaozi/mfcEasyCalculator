
// CalculatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

wstring StoWs(const string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring r(buf);
	delete[] buf;
	return r;
}
int precedence(char ch)
{
	switch (ch) {
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	case '%': return 2;
	default:
		break;
	}
	return 0;
}
//运算操作
int stack_count(stack<double>* num, stack<char>* op)
{
	char oper = op->top(); op->pop();//取出运算符
	//取出两个数据进行运算
	if (num->size() < 2) { return -1; }//如果数据栈的数据少于两个说明出错
	double num1 = num->top(); num->pop();
	double num2 = num->top(); num->pop();
	int s = 0;
	switch (oper)
	{
	case '+': num->push(num2 + num1); break;
	case '-': num->push(num2 - num1); break;
	case '*': num->push(num2 * num1); break;
	case '/': num->push(num2 / num1); break;
	case '%': num->push((int)num2 % (int)num1); break;
	default:s = -1; break;
	}
	return s;
}
double oper_expre(string str, bool* errorFlag)
{
	char* op = { "+-*/%" };
	char* left = { "({[" };
	char* right = { ")]}" };
	stack<double> OPND;//存放数据
	stack<char>   OPTR;   //存放运算符
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (*it == ' ') { continue; }   //跳过空字符
		else if (strchr(op, *it) != NULL)
		{
			while (!OPTR.empty() && precedence(OPTR.top()) >= precedence(*it))
			{
				if (stack_count(&OPND, &OPTR) == -1)
				{
					*errorFlag = true;
					return 0;
				}
			}
			OPTR.push(*it);
		}
		else if (strchr(left, *it) != NULL)//处理左括号
		{
			OPTR.push(*it);
		}
		else if (strchr(right, *it) != NULL)//处理右括号
		{
			while (strchr(left, OPTR.top()) == NULL)
			{
				if (stack_count(&OPND, &OPTR) == -1)
				{
					*errorFlag = true;
					return 0;
				}
			}
			OPTR.pop();
		}
		else if (*it >= '0' && *it <= '9')//处理数据 
		{

			string num;
			while (*it >= '0' && *it <= '9' || *it == '.')
			{
				num += *it;
				it++;
				if (it == str.end()) { break; }
			}
			it--;
			stringstream sir(num);
			double d;
			sir >> d;
			OPND.push(d);
		}
		else
		{
			*errorFlag = true;
			return 0;
		}
	}
	while (!OPTR.empty())
	{
		if (stack_count(&OPND, &OPTR) == -1)
		{
			*errorFlag = true;
			return 0;
		}
	}
	if (OPND.empty()) { return -1; }//如果为空说明输入有问题
	return OPND.top();
}
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

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT, inputEdit);
	DDX_Control(pDX, IDC_OUTPUT, outputEdit);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTONDOT, &CCalculatorDlg::OnBnClickedButtondot)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTONDIV, &CCalculatorDlg::OnBnClickedButtondiv)
	ON_BN_CLICKED(IDC_BUTTONMUL, &CCalculatorDlg::OnBnClickedButtonmul)
	ON_BN_CLICKED(IDC_BUTTONSUB, &CCalculatorDlg::OnBnClickedButtonsub)
	ON_BN_CLICKED(IDC_BUTTONADD, &CCalculatorDlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTONRESULT, &CCalculatorDlg::OnBnClickedButtonresult)
	ON_BN_CLICKED(IDC_BUTTONLK, &CCalculatorDlg::OnBnClickedButtonlk)
	ON_BN_CLICKED(IDC_BUTTONRK, &CCalculatorDlg::OnBnClickedButtonrk)
	ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorDlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_INPUT, &CCalculatorDlg::OnEnChangeInput)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorDlg::OnPaint()
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
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CCalculatorDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "1";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "5";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
	
}


void CCalculatorDlg::OnBnClickedButton0()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "0";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButtondot()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += ".";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "2";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "3";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "7";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "8";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "9";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButtondiv()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "/";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButtonmul()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "*";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButtonsub()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "-";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButtonadd()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "+";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButtonresult()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText = "";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButtonlk()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "(";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButtonrk()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += ")";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}



void CCalculatorDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "6";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	inputText += "4";
	wstring stemp = StoWs(inputText);
	LPCTSTR temp = stemp.c_str();
	inputEdit.SetWindowTextW(temp);
}


void CCalculatorDlg::OnEnChangeInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString tempStr;
	inputEdit.GetWindowTextW(tempStr);
	inputText = CT2A(tempStr.GetString());
	errorFlag = false;
	result = oper_expre(inputText, &errorFlag);
	CString str;
	if (errorFlag == false)
		str.Format(L"%lf", result);
	else
		str = "错误";
	outputEdit.SetWindowTextW(str);
}
