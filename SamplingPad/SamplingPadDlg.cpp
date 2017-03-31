
// SamplingPadDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "SamplingPad.h"
#include "SamplingPadDlg.h"
#include "afxdialogex.h"

#include "list"
#include "PadManager.h"
#include "Track.h"
#include "Channel.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSamplingPadDlg ��ȭ ����



CSamplingPadDlg::CSamplingPadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SAMPLINGPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSamplingPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, lengthCombo);
	DDX_Control(pDX, IDC_COMBO2, sliceCombo);
}

BEGIN_MESSAGE_MAP(CSamplingPadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_CBN_SELCHANGE(IDC_COMBO1, &CSamplingPadDlg::OnCbnSelchangeCombo1)
//	ON_CBN_EDITUPDATE(IDC_COMBO1, &CSamplingPadDlg::OnCbnEditupdateCombo1)
//ON_CBN_EDITCHANGE(IDC_COMBO1, &CSamplingPadDlg::OnCbnEditchangeCombo1)
ON_CBN_SELCHANGE(IDC_COMBO1, &CSamplingPadDlg::OnCbnSelchangeCombo1)
ON_CBN_SELCHANGE(IDC_COMBO2, &CSamplingPadDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CSamplingPadDlg �޽��� ó����

BOOL CSamplingPadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ���� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	lengthCombo.AddString(L"8");
	lengthCombo.AddString(L"12");
	lengthCombo.AddString(L"16");
	lengthCombo.SetCurSel(0);

	sliceCombo.AddString(L"1");
	sliceCombo.AddString(L"2");
	sliceCombo.AddString(L"3");
	sliceCombo.SetCurSel(0);

	updateTrackButtons();


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSamplingPadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSamplingPadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSamplingPadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CSamplingPadDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialogEx::OnCommand(wParam, lParam);
}


BOOL CSamplingPadDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) {
			MessageBox(L"�޽����ڽ�");
			return TRUE;

		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


std::list<CMFCButton*> buttonList;

void clearTrackButtons() {
	for (CMFCButton* btn : buttonList) {
		delete btn;
	}
	buttonList.clear();
}

void CSamplingPadDlg::updateTrackButtons() {

	clearTrackButtons();

	UpdateData(TRUE);
	
	int trackLength = PadManager::getInstance()->getTrack()->getChannelSize();
	for (int i = 0; i < trackLength; i++) {
		Track* track = PadManager::getInstance()->getTrack();
		Channel* channel = track->getChannelPtr() + i;

		for (int j = 0; j < channel->getSize(); j++) {
			CMFCButton* newButton = new CMFCButton;
			int buttonSize = 40;
			int margin = 1;
			int slice = track->getSlice();
			int x = 100 + ((buttonSize - (slice - 1) * margin) / slice + margin * 2) * j;
			int y = 100 + (buttonSize + margin * 2) * i;
			int w = (buttonSize - (slice - 1) * margin) / slice;
			int h = buttonSize;
			newButton->Create(L"��ư", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect(x, y, x+w, y+h), this, 2000 + i*trackLength + j);
			newButton->SetWindowTextW(L"");
			buttonList.push_back(newButton);
//			newButton->SetFaceColor(RGB(255, 0, 0), true);

		}
	}


	Invalidate(TRUE);
}

void CSamplingPadDlg::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str = L"init";
	int n;
	int length;

	n = lengthCombo.GetLBTextLen(lengthCombo.GetCurSel());
	lengthCombo.GetLBText(lengthCombo.GetCurSel(), str.GetBuffer(n));
	length = _ttoi(str);
	str.ReleaseBuffer();

	PadManager::getInstance()->getTrack()->setLength(length);

	updateTrackButtons();
}


void CSamplingPadDlg::OnCbnSelchangeCombo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str = L"init";
	int n;
	int slice;

	n = sliceCombo.GetLBTextLen(sliceCombo.GetCurSel());
	sliceCombo.GetLBText(sliceCombo.GetCurSel(), str.GetBuffer(n));
	slice = _ttoi(str);
	str.ReleaseBuffer();

	PadManager::getInstance()->getTrack()->setSlice(slice);

	updateTrackButtons();
}