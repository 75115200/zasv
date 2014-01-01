#pragma once
#include "afxwin.h"

#include "CardManager.h"

// YConn 对话框

class YConn : public CDialogEx
{
	DECLARE_DYNAMIC(YConn)

public:
	YConn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~YConn();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeCombo1();
private:
	CComboBox m_portList;
	CComboBox m_baudList;
	CardManager* getCardManager();
};
