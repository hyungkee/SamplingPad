
// SamplingPadDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CSamplingPadDlg ��ȭ ����
class CSamplingPadDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSamplingPadDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAMPLINGPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void updateTrackButtons();
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
};