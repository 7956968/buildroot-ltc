
// IQDebugDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "testdlg.h"


// CIQDebugDlg �Ի���
class CIQDebugDlg : public CDialogEx
{
// ����
public:
	CIQDebugDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IQDEBUG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int MsgDataSend(char* pData, int nDataLen);
	void IttdConnect(DWORD dwIP, int nPort);
private:
	SOCKET m_hSocket;
	int m_nHeaderLen; /* �������첽���գ�����Ҫ��¼�ѽ��յ�����ͷ���� */
	int m_nDataLen; /* �������첽���գ�����Ҫ��¼�ѽ��յ����ݳ��� */
	iq_test_msg_t m_msgHeader;
protected:
	afx_msg LRESULT OnSocket(WPARAM wParam, LPARAM lParam);
public:
	CTabCtrl m_tabCtrl;
	afx_msg void OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
private:
	int m_nSelect;
	BOOL m_bConnect;
public:
	int MsgDataRecv(char* pData, int nDataLen);
	BOOL IsIttdConnect(void) { return m_bConnect; }
	afx_msg void OnDestroy();
	char* m_pDataBuf;
};
