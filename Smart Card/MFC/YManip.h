#pragma once
#include "afxwin.h"

#include "CardManager.h"


// YManip �Ի���

class YManip : public CDialogEx
{
	DECLARE_DYNAMIC(YManip)

public:
	YManip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~YManip();

// �Ի�������
	enum { IDD = IDD_DIALOG_MANIP };
	
	void info(LPCTSTR infoMsg);
	void warning(LPCTSTR infoMsg);
	void updateCardInfo();
	CardManager* getCardManager();

	CListBox m_infoList;
	CEdit m_passwdArea;
	CEdit m_consumeArea;
	CEdit m_chargeArea;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnLbnSelchangeList5();
};
