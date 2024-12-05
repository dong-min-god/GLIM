
// Project_GLIMDlg.h: 헤더 파일
//

#pragma once

#include <vector>

using namespace std;

// CProjectGLIMDlg 대화 상자
class CProjectGLIMDlg : public CDialogEx
{
// 생성입니다.
public:
	CProjectGLIMDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_GLIM_DIALOG };
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

private:
	CStatic m_pictureCtrl;

	int m_iStartPos_X;
	int m_iStartPos_Y;
	int m_iEndPos_X;
	int m_iEndPos_Y;
	int m_iStep;
	int m_iSize_Min;
	int m_iSize_Max;
	vector<pair<double,double>> vpddPos;

private:
	bool IsCircleInRect(CRect &rect, double dCenX, double dCenY, int iRadius);
	void DrawCircle(int iStep, double dX, double dY);
	void SaveCircle(int iStep);
	void DrawMark(CString strFileName);

public:
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonAction();
	afx_msg void OnBnClickedButtonOpen();


};
