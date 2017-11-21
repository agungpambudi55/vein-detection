
// veinDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CveinDlg dialog
class CveinDlg : public CDialogEx
{
// Construction
public:
	CveinDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VEIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pict;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void Proses();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CStatic m_pict1;
};
