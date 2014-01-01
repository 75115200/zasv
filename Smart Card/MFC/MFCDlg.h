
// MFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "CardManager.h"
#include "YConn.h"
#include "YManip.h"


// CMFCDlg �Ի���
class CMFCDlg : public CDialogEx
{
// ����
public:
	CMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CTabCtrl m_tab;
	YConn m_dlgConn;
	YManip m_dlgManip;

	CardManager *m_pCardManager;

public:
	afx_msg void OnTcnSelchangeTabset(NMHDR *pNMHDR, LRESULT *pResult);
	CardManager* getCardManager();
};
