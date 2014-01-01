// YConn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC.h"
#include "YConn.h"
#include "afxdialogex.h"

#include "MFCDlg.h"


// YConn �Ի���

IMPLEMENT_DYNAMIC(YConn, CDialogEx)

YConn::YConn(CWnd* pParent /*=NULL*/)
	: CDialogEx(YConn::IDD, pParent)
{

}

YConn::~YConn()
{
}

BOOL YConn::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//MessageBox( _T("Hello"), _T("BOX"), 0x1040);
	m_portList.InsertString(0, _T("com1"));
	m_portList.InsertString(1, _T("com2"));
	m_portList.InsertString(2, _T("com3"));
	m_portList.InsertString(3, _T("com4"));
	m_portList.SetCurSel(0);

	m_baudList.InsertString(0, _T("4800Kbps"));
	m_baudList.InsertString(1, _T("9600Kbps"));
	m_baudList.InsertString(2, _T("19200Kbps"));
	m_baudList.SetCurSel(1);
	return TRUE;
}

void YConn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_portList);
	DDX_Control(pDX, IDC_COMBO2, m_baudList);
}


BEGIN_MESSAGE_MAP(YConn, CDialogEx)
	ON_BN_CLICKED(IDOK, &YConn::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &YConn::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, &YConn::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// YConn ��Ϣ�������


void YConn::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	static long baud_arr[] = { 4800, 9600, 19200 };
	int portSel = dynamic_cast<CComboBox*>(GetDlgItem(IDC_COMBO1))->GetCurSel();
	int baudSel = dynamic_cast<CComboBox*>(GetDlgItem(IDC_COMBO2))->GetCurSel();
	int port = portSel;
	long baud = baud_arr[baudSel];
	int st = getCardManager()->init(port, baud);
	if (st == 1) {
		MessageBox(_T("��ʼ���豸ʧ��"), _T("����"), MB_ICONWARNING);
	} else if (st == 2) {
		MessageBox(_T("�豸��û�п�Ƭ"), _T("����"), MB_ICONWARNING);
	}
}


void YConn::OnBnClickedCancel()
{

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();


	CardManager* cm = getCardManager();
	if (cm->isInited()) {
		cm->disConnect();
	}
	exit(0);
}

CardManager* YConn::getCardManager()
{
	return dynamic_cast<CMFCDlg*>(GetTopLevelParent())->getCardManager();
}

void YConn::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
