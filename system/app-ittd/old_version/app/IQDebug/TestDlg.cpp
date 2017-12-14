// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IQDebug.h"
#include "TestDlg.h"
#include "afxdialogex.h"


// CTestDlg �Ի���

IMPLEMENT_DYNAMIC(CTestDlg, CDialogEx)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDlg::IDD, pParent)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
	ON_MESSAGE(WM_ITTDDATA, &CTestDlg::OnIttddata)
	ON_MESSAGE(WM_ITTCONNECT, &CTestDlg::OnIttconnect)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������


void CTestDlg::OnBnClickedOk()
{
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	if (!str.IsEmpty())
	{
		int nLen = str.GetLength(); // UNICODE�ַ�ռ2���ֽڣ�ʵ�ʳ��Ȼ�Ҫ����������
		((CIQDebugDlg*)AfxGetApp()->m_pMainWnd)->MsgDataSend((char*)str.GetBuffer(0), 2 * (nLen + 1));
	}
	//CDialogEx::OnOK();
}


afx_msg LRESULT CTestDlg::OnIttddata(WPARAM wParam, LPARAM lParam)
{
	// wParam������ָ��char*��lParam�����ݳ���int
	CString str((LPCTSTR)wParam); // �ַ�����0��β
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	return 0;
}


BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDOK)->EnableWindow(((CIQDebugDlg*)AfxGetApp()->m_pMainWnd)->IsIttdConnect());
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


afx_msg LRESULT CTestDlg::OnIttconnect(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDOK)->EnableWindow((int)wParam);
	return 0;
}
