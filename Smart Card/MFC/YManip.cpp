// YManip.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC.h"
#include "YManip.h"
#include "afxdialogex.h"

#include "MFCDlg.h"


// YManip �Ի���

IMPLEMENT_DYNAMIC(YManip, CDialogEx)

YManip::YManip(CWnd* pParent /*=NULL*/)
	: CDialogEx(YManip::IDD, pParent)
{

}

YManip::~YManip()
{
}

void YManip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST5, m_infoList);
	DDX_Control(pDX, IDC_EDIT1, m_passwdArea);
	DDX_Control(pDX, IDC_EDIT2, m_consumeArea);
	DDX_Control(pDX, IDC_EDIT3, m_chargeArea);
}


BEGIN_MESSAGE_MAP(YManip, CDialogEx)
	ON_BN_CLICKED(IDOK, &YManip::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &YManip::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON4, &YManip::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &YManip::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &YManip::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &YManip::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &YManip::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &YManip::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &YManip::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &YManip::OnEnChangeEdit3)
	ON_LBN_DBLCLK(IDC_LIST5, &YManip::OnLbnSelchangeList5)
END_MESSAGE_MAP()


BOOL YManip::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	updateCardInfo();

#ifndef _DEBUG
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
#endif

	return TRUE;
}

void YManip::info(LPCTSTR infoMsg)
{
	int i = m_infoList.GetCount();
	m_infoList.InsertString(i, infoMsg);
	m_infoList.SetCurSel(i);
}

void YManip::warning(LPCTSTR infoMsg)
{
	info(infoMsg);
	MessageBox(infoMsg, L"����", MB_ICONWARNING);
}
void YManip::updateCardInfo()
{
	CardManager *cm = getCardManager();
	std::string tmp;
	if (!cm->getInfo(CardManager::PUBLISHER, tmp)) {
		CString publisher(tmp.c_str());
		SetDlgItemText(IDC_STATIC1, publisher);
	}
	if (!cm->getInfo(CardManager::CARD_ID, tmp)) {
		CString cardId(tmp.c_str());
		SetDlgItemText(IDC_STATIC2, cardId);
	}
	if (!cm->getInfo(CardManager::USER_NAME, tmp)) {
		CString userName(tmp.c_str());
		SetDlgItemText(IDC_STATIC3, userName);

	}
	float balance = cm->getBalance();
	if (balance >= 0) {
		CString bal;
		bal.Format(_T("%.3f Ԫ"), balance);
		SetDlgItemText(IDC_STATIC4, bal);
	}
}

CardManager* YManip::getCardManager()
{
	return dynamic_cast<CMFCDlg*>(GetTopLevelParent())->getCardManager();
}





// YManip ��Ϣ�������


void YManip::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void YManip::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}


void YManip::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_chargeArea.GetWindowTextW(str);
	float amount = static_cast<float>(_wtof(str));

	int st = getCardManager()->charge(amount);
	if (st == 0) {
		updateCardInfo();
		CString s;
		s.Format(L"�ɹ���ֵ %.3f Ԫ", amount);
		info(s);
	} else if (st == -7){
		warning(L"���ȳ�ʼ�����������롣");
	} else if(st == -1) {
		warning(L"��������");
	} else if (st == 1) {
		warning(L"д����Ϣ����");
	}
}

void YManip::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int st = getCardManager()->release(100.0f);
	if (st == 0) {
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		updateCardInfo();
		info(_T("�ѳɹ�����һ�ſ�Ƭ"));
	} else if (st == -1) {
		warning(L"��Ƭδ��ʼ��������ʧ�ܡ�");
	} else {

	}
}

void YManip::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString str;
	m_consumeArea.GetWindowTextW(str);

	float amount;
	amount = static_cast<float>(_wtof(str));

	int st = getCardManager()->consume(amount);

	if (st == 0) {
		updateCardInfo();
		CString s;
		s.Format(L"������ %.3f Ԫ", amount);
		info(s);
	} else if (st == -7){
		warning(L"���ȳ�ʼ�����������롣");
	} else if(st == -1) {
		warning(L"��������");
	} else if (st == 1) {
		warning(L"���㡣");
	} else {
		warning(L"δ֪����");
	}
}


void YManip::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	updateCardInfo();

	float balance = getCardManager()->getBalance();
	if (balance > 0) {
		CString str;
		str.Format(_T("��ʣ��� %.f Ԫ"), balance);
		MessageBox(str, L"��Ϣ", MB_ICONINFORMATION);
		info(str);
	} else {
		warning(L"��ȡ������");
	}
}


void YManip::OnBnClickedButton5()
{
	CString str;
	m_passwdArea.GetWindowTextW(str);

	unsigned char key[7];
	int len = str.GetLength() > 6 ? 6 : str.GetLength();

	int i = 0;
	for ( i = 0; i < len; i++) {
		key[i] = static_cast<unsigned char>(str.GetAt(i));
	}
	for (; i < 7; i++) {
		key[i] = 0;
	}

	bool st =  getCardManager()->checkPassWd(key);
	if (st) {
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		updateCardInfo();
		info(_T("������ȷ��"));
	} else {
		info(_T("���벻��ȷ��"));
		MessageBox(_T("���벻��ȷ��"), L"����", MB_ICONWARNING);
	}
}


void YManip::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void YManip::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void YManip::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void YManip::OnLbnSelchangeList5()
{
	m_infoList.DeleteString(m_infoList.GetCurSel());
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
