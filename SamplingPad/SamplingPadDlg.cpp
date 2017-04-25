
// SamplingPadDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SamplingPad.h"
#include "SamplingPadDlg.h"
#include "afxdialogex.h"

#include "list"
#include <map>
#include "PadManager.h"
#include "Track.h"
#include "Channel.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define MY_TIMER 1001
#define TIMESLICE 30

// View Variables
int offsetX = 50;
int offsetY = 50;
int buttonSize = 50;
int margin = 1;


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
	ON_BN_CLICKED(IDC_BUTTON1, &CSamplingPadDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
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
	sliceCombo.AddString(L"4");
	sliceCombo.SetCurSel(0);

	updateTrackViews();

	SetTimer(MY_TIMER, TIMESLICE, 0);


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
	/*

	Track* track = PadManager::getInstance()->getTrack();
	int channelSize = track->getChannelSize();
	int length = track->getLength();

	// Draw Lines
	CClientDC dc(this);
	CPen bPen, sPen;
	bPen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	sPen.CreatePen(PS_SOLID, 3, RGB(127, 127, 127));

	CPen* oldPen = dc.SelectObject(&bPen);

	for (int i = 0; i <= length; i ++) { // 4칸 간격
		int x = offsetX + (buttonSize + margin * 2) * i - margin;
		int y = offsetY - margin;
		int h = buttonSize * channelSize + margin * 2 * (channelSize - 1) + margin;

		if (i % 4 == 0)
			dc.SelectObject(&bPen);
		else
			dc.SelectObject(&sPen);

		dc.MoveTo(x, y);
		dc.LineTo(x, y + h);
	}

	CPen pPen;
	pPen.CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	dc.SelectObject(&pPen);

	double i = PadManager::getInstance()->getPlayedLength();
	int aMargin = 5;

	int x = offsetX + (buttonSize + margin * 2) * i - margin;
	int y = offsetY - margin - aMargin;
	int h = buttonSize * channelSize + margin * 2 * (channelSize - 1) + margin + aMargin * 2;

	dc.MoveTo(x, y);
	dc.LineTo(x, y + h);

	bPen.DeleteObject();
	sPen.DeleteObject();
	pPen.DeleteObject();
	dc.SelectObject(oldPen);
	*/
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSamplingPadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


class CButtonLink {
public:
	int pos;
	Channel* channel;
	void setChannel(Channel* channel) { this->channel = channel;  }
	void setPos(int pos) { this->pos = pos;  }
	void toggle() { channel->toggle(pos); }
	bool isChecked() { return channel->getNote(pos); }
};

std::list<CMFCButton*> buttonList;
std::list<CStatic*> staticList;
std::map<CMFCButton*, CButtonLink*> buttonMap;

void updateButtonState(CMFCButton* button) {
	std::map<CMFCButton*, CButtonLink*>::iterator iter = buttonMap.find(button);
	if (iter != buttonMap.end()) {
		CButtonLink* link = iter->second;

		if (link->isChecked())
			button->SetFaceColor(RGB(255, 100, 100), true);
		else
			button->SetFaceColor(RGB(100, 100, 100), true);

	}
}

void clickButton(CMFCButton* button) {
	std::map<CMFCButton*, CButtonLink*>::iterator iter = buttonMap.find(button);
	if (iter != buttonMap.end()) {
		CButtonLink* link = iter->second;
		link->toggle();
	}
	updateButtonState(button);

}

BOOL CSamplingPadDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	for (CMFCButton* button : buttonList) {
		if (button->GetDlgCtrlID() == LOWORD(wParam) && HIWORD(wParam) == BN_CLICKED) {
			clickButton(button);
		}
	}

	return CDialogEx::OnCommand(wParam, lParam);
}


BOOL CSamplingPadDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) {
//			MessageBox(L"메시지박스");
			return TRUE;

		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}




void CSamplingPadDlg::clearTrackButtons() {
	for (std::pair<CMFCButton*, CButtonLink*> p : buttonMap) {
		delete p.first;
		delete p.second;
	}
	buttonList.clear();
	buttonMap.clear();
}

void CSamplingPadDlg::updateTrackViews() {

	clearTrackButtons();

	UpdateData(TRUE);

	Track* track = PadManager::getInstance()->getTrack();
	int channelSize = track->getChannelSize();
	int length = track->getLength();
	// Update Buttons
	for (int i = 0; i < channelSize; i++) {
		Channel* channel = track->getChannelPtr() + i;

		for (int j = 0; j < channel->getSize(); j++) {
			CMFCButton* newButton = new CMFCButton;
			int slice = track->getSlice();
			int x = offsetX + (buttonSize - (slice - 1) * margin * 2) * j / slice + margin * 2 * j;
			int y = offsetY + (buttonSize + margin * 2) * i;
			int w = (buttonSize - (slice - 1) * margin) / slice;
			int h = buttonSize;
			int id = 2000 + i*channel->getSize() + j;
			newButton->Create(L"버튼", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect(x, y, x+w, y+h), this, id);
			newButton->SetWindowTextW(L"");
			buttonList.push_back(newButton);

			CButtonLink* link = new CButtonLink();
			link->setChannel(channel);
			link->setPos(j);

			buttonMap.insert(std::pair<CMFCButton*, CButtonLink*>(newButton, link));

			updateButtonState(newButton);
		}
	}

	for (int i = 0; i < track->getLength(); i++) {

		int marginA = 3;
		int x = offsetX + (buttonSize + margin * 2) * i - margin;
		int y = offsetY - margin - marginA;
		int w = 3;
		int h = buttonSize * channelSize + margin * 2 * (channelSize - 1) + margin + marginA * 2;
		int id = 3000 + i;

		CStatic* newStatic = new CStatic;
		newStatic->Create(L"Static", WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(x, y, x + w, y + h), this, id);
		newStatic->SetWindowTextW(L"");
		staticList.push_back(newStatic);

	}


	int marginA = 6;
	double i = PadManager::getInstance()->getPlayedLength();
	int x = offsetX + (buttonSize + margin * 2) * i - margin;
	int y = offsetY - margin - marginA;
	int w = 3;
	int h = buttonSize * channelSize + margin * 2 * (channelSize - 1) + margin + marginA * 2;
	int id = 3500 + i;

	if (PadManager::getInstance()->getPlayBar() == NULL) {
		CStatic* newStatic = new CStatic();
		newStatic->Create(L"Static", WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(x, y, x + w, y + h), this, id);
		newStatic->SetWindowTextW(L"");
		PadManager::getInstance()->setPlayBar(newStatic);

	}

	/*
	// Update 
	Track* track = PadManager::getInstance()->getTrack();
	int channelSize = track->getChannelSize();
	int length = track->getLength();

	// Draw Lines
	CClientDC dc(this);
	CPen bPen, sPen;
	bPen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	sPen.CreatePen(PS_SOLID, 3, RGB(127, 127, 127));

	CPen* oldPen = dc.SelectObject(&bPen);

	for (int i = 0; i <= length; i++) { // 4칸 간격
		int x = offsetX + (buttonSize + margin * 2) * i - margin;
		int y = offsetY - margin;
		int h = buttonSize * channelSize + margin * 2 * (channelSize - 1) + margin;

		if (i % 4 == 0)
			dc.SelectObject(&bPen);
		else
			dc.SelectObject(&sPen);

		dc.MoveTo(x, y);
		dc.LineTo(x, y + h);
	}

	CPen pPen;
	pPen.CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	dc.SelectObject(&pPen);

	double i = PadManager::getInstance()->getPlayedLength();
	int aMargin = 5;

	int x = offsetX + (buttonSize + margin * 2) * i - margin;
	int y = offsetY - margin - aMargin;
	int h = buttonSize * channelSize + margin * 2 * (channelSize - 1) + margin + aMargin * 2;

	dc.MoveTo(x, y);
	dc.LineTo(x, y + h);

	bPen.DeleteObject();
	sPen.DeleteObject();
	pPen.DeleteObject();
	dc.SelectObject(oldPen);
	*/
	Invalidate(true);
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

	updateTrackViews();
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

	updateTrackViews();
}

void CSamplingPadDlg::OnCbnSelchangeCombo(int id) {

}


void CSamplingPadDlg::OnBnClickedButton1()
{
	PadManager::getInstance()->togglePlaying();

	if (PadManager::getInstance()->isPlaying()) {

	}
}


void CSamplingPadDlg::updatePlayBar() {
	int channelSize = PadManager::getInstance()->getTrack()->getChannelSize();
	int marginA = 6;
	double i = PadManager::getInstance()->getPlayedLength();
	int x = offsetX + (buttonSize + margin * 2) * i - margin;
	int y = offsetY - margin - marginA;
	int w = 3;
	int h = buttonSize * channelSize + margin * 2 * (channelSize - 1) + margin + marginA * 2;
	int id = 3500 + i;

	if (PadManager::getInstance()->getPlayBar() != NULL) {
		CStatic* playBar = PadManager::getInstance()->getPlayBar();
		playBar->SetWindowPos(0, x, y, w, h, SWP_NOZORDER);
		playBar->Invalidate();
	}
}


void CSamplingPadDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == MY_TIMER) {
		if (PadManager::getInstance()->isPlaying()) {
			double bpm = PadManager::getInstance()->getBpm();
			//		60s : bpm = TIMESLICE/1000 : x;
			double bpn = bpm * TIMESLICE / 60000;
			// bpn이 1만큼 쌓일때 length는 4만큼 증가하면 된다.
			double playedLength = PadManager::getInstance()->getPlayedLength();
			if (playedLength  < PadManager::getInstance()->getTrack()->getLength()) {
				double nextLength = playedLength + bpn * 4;
				if (nextLength > PadManager::getInstance()->getTrack()->getLength())
					nextLength = PadManager::getInstance()->getTrack()->getLength();
				PadManager::getInstance()->setPlayedLength(nextLength);

				updatePlayBar();
			}
			else {
				PadManager::getInstance()->setPlayedLength(0);
			}

		}
	}
//	Invalidate(false);
	CDialogEx::OnTimer(nIDEvent);
}


CBrush* staticBrush = new CBrush(RGB(255, 0, 0));
CBrush* playBrush = new CBrush(RGB(0, 255, 0));

HBRUSH CSamplingPadDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	for (CStatic* myStatic : staticList) {
		if (pWnd->GetDlgCtrlID() == myStatic->GetDlgCtrlID()) {
			hbr = *staticBrush;
		}

	}

	CStatic* playBar = PadManager::getInstance()->getPlayBar();
	if (playBar != NULL) {
		if (pWnd->GetDlgCtrlID() == playBar->GetDlgCtrlID()) {
			hbr = *playBrush;
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
