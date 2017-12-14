#pragma once


// CManageDlg �Ի���

class CManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageDlg)

public:
	CManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CManageDlg();

// �Ի�������
	enum { IDD = IDD_MANAGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedDatadir();
	afx_msg void OnBnClickedYuvdir();
	afx_msg void OnBnClickedJpgdir();
private:
	BOOL DirectoryChoose(CWnd* pOwner, CString& strDir);
public:
	virtual BOOL OnInitDialog();
	DWORD m_uIP;
	int m_nPort;
	BOOL GetSaveDir(int nID, CString& strDir);
protected:
	afx_msg LRESULT OnIttconnect(WPARAM wParam, LPARAM lParam);
public:
	BOOL m_bSaveData;
	int m_nProtocol;
};
