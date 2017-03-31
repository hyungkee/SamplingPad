
// SamplingPadDlg.cpp : 구현 파일
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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CSamplingPadDlg 대화 상자



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


// CSamplingPadDlg 메시지 처리기

BOOL CSamplingPadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	lengthCombo.AddString(L"8");
	lengthCombo.AddString(L"12");
	lengthCombo.AddString(L"16");
	lengthCombo.SetCurSel(0);

	sliceCombo.AddString(L"1");
	sliceCombo.AddString(L"2");
	sliceCombo.AddString(L"3");
	sliceCombo.SetCurSel(0);

	updateTrackButtons();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSamplingPadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSamplingPadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CSamplingPadDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::OnCommand(wParam, lParam);
}


BOOL CSamplingPadDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) {
			MessageBox(L"메시지박스");
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
			newButton->Create(L"버튼", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect(x, y, x+w, y+h), this, 2000 + i*trackLength + j);
			newButton->SetWindowTextW(L"");
			buttonList.push_back(newButton);
//			newButton->SetFaceColor(RGB(255, 0, 0), true);

		}
	}


	Invalidate(TRUE);
}

void CSamplingPadDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
