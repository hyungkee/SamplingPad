
// SamplingPadDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CSamplingPadDlg 대화 상자
class CSamplingPadDlg : public CDialogEx
{
// 생성입니다.
public:
	CSamplingPadDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAMPLINGPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;


	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void updateTrackViews();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLbnSelchangeList1();
//	afx_msg void OnCbnSelchangeCombo1();
	CComboBox lengthCombo;
	CComboBox sliceCombo;
//	afx_msg void OnCbnEditupdateCombo1();
//	afx_msg void OnCbnEditchangeCombo1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo(int id);

	afx_msg void clearTrackButtons();
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void updatePlayBar();
};
