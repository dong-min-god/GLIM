
// Project_GLIMDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project_GLIM.h"
#include "Project_GLIMDlg.h"
#include "afxdialogex.h"
#include <io.h>
#include <direct.h>


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


// CProjectGLIMDlg 대화 상자



CProjectGLIMDlg::CProjectGLIMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_GLIM_DIALOG, pParent)
	, m_iStartPos_X(40)
	, m_iStartPos_Y(40)
	, m_iEndPos_X(50)
	, m_iEndPos_Y(50)
	, m_iStep(0)
	, m_iSize_Min(0)
	, m_iSize_Max(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectGLIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_START_POS_X, m_iStartPos_X);
	DDX_Text(pDX, IDC_EDIT_START_POS_Y, m_iStartPos_Y);
	DDX_Text(pDX, IDC_EDIT_END_POS_X, m_iEndPos_X);
	DDX_Text(pDX, IDC_EDIT_END_POS_Y, m_iEndPos_Y);
	DDX_Control(pDX, IDC_PICTURE, m_pictureCtrl);
	DDX_Text(pDX, IDC_EDIT_STEP, m_iStep);
	DDX_Text(pDX, IDC_EDIT_SIZE_MIN, m_iSize_Min);
	DDX_Text(pDX, IDC_EDIT_SIZE_MAX, m_iSize_Max);
}

BEGIN_MESSAGE_MAP(CProjectGLIMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CProjectGLIMDlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CProjectGLIMDlg::OnBnClickedButtonAction)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CProjectGLIMDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CProjectGLIMDlg 메시지 처리기

BOOL CProjectGLIMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProjectGLIMDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CProjectGLIMDlg::OnPaint()
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
HCURSOR CProjectGLIMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



bool CProjectGLIMDlg::IsCircleInRect(CRect& rect, double dCenX, double dCenY, int iRadius)
{
	// 생성된 원이 사각형 내부에 존재하는지 확인하기 위한 함수
	// 랜덤으로 생성되는 반지름으로 인해 사각형 밖으로 나가는 경우 존재

	if ((rect.left <= dCenX - iRadius) && (rect.right >= dCenX + iRadius) && (rect.top <= dCenY - iRadius) && (rect.bottom >= dCenY + iRadius))
		return true;
	else
		return false;
}

void CProjectGLIMDlg::DrawCircle(int iStep, double dX, double dY)
{
	// 원 그리는 함수

	CClientDC dc(&m_pictureCtrl);

	CRect rectFrame;
	m_pictureCtrl.GetClientRect(&rectFrame);
	dc.FillSolidRect(rectFrame, RGB(0, 0, 0));

	int iRadius = rand() % (m_iSize_Max - m_iSize_Min + 1) + m_iSize_Min; // 랜덤 반지름
	double dCenterX = rectFrame.left + m_iStartPos_X + iStep * dX;
	double dCenterY = rectFrame.top + m_iStartPos_Y + iStep * dY;

	// 원이 사각형 안에 존재하면 그리기
	if (IsCircleInRect(rectFrame, dCenterX, dCenterY, iRadius))
	{
		CRect rect(dCenterX - iRadius, dCenterY - iRadius, dCenterX + iRadius, dCenterY + iRadius);
		CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
		CBrush brush(RGB(255, 255, 255));
		dc.SelectObject(&pen);
		dc.SelectObject(&brush);
		dc.Ellipse(rect);
	}
	else // 밖에 존재하면 알림 띄우기
	{
		MessageBox(L"원이 영역 밖에 존재합니다.");
		return;
	}

	// 저장된 원 이미지를 Open할때 원 중심 좌표를 얻기 위해 vector에 저장
	pair<double, double> pddPos;
	pddPos.first = dCenterX;
	pddPos.second = dCenterY;
	vpddPos.push_back(pddPos);
}

void CProjectGLIMDlg::SaveCircle(int iStep)
{
	// 원 이미지 저장함수

	CRect rectFrame;
	m_pictureCtrl.GetClientRect(&rectFrame);

	CClientDC dc(&m_pictureCtrl);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rectFrame.Width(), rectFrame.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.BitBlt(0, 0, rectFrame.Width(), rectFrame.Height(), &dc, 0, 0, SRCCOPY);

	// Image 폴더 생성
	// 폴더가 없으면 새롭게 생성
	CString strFolderPath = _T("Image");
	CT2CA pszFolderPath(strFolderPath);

	if (_access(pszFolderPath, 0) != 0)
		_mkdir(pszFolderPath);

	CString strFilePath;
	strFilePath.Format(_T("%s\\Circle_%d.bmp"), strFolderPath, iStep);
	CImage cImage;
	cImage.Attach((HBITMAP)bitmap.Detach());
	cImage.Save(strFilePath);

	memDC.SelectObject(pOldBitmap);
}

void CProjectGLIMDlg::DrawMark(CString strFileName)
{
	// Open버튼 작용시 중심에 x표시와 좌표값 표시하는 함수

	int iPos1 = strFileName.ReverseFind(_T('_'));
	int iPos2 = strFileName.ReverseFind(_T('.'));

	int iIndex = 0;

	if (iPos1 != -1 && iPos2 != -1 && iPos1 < iPos2)
	{
		CString strNum = strFileName.Mid(iPos1 + 1, iPos2 - iPos1 -1);
		iIndex = _ttoi(strNum);
	}

	CClientDC dc(&m_pictureCtrl);

	CRect rectFrame;
	m_pictureCtrl.GetClientRect(&rectFrame);

	double dCenX = vpddPos[iIndex].first;
	double dCenY = vpddPos[iIndex].second;

	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);
	dc.MoveTo(dCenX - 5, dCenY - 5);
	dc.LineTo(dCenX + 5, dCenY + 5);
	dc.MoveTo(dCenX - 5, dCenY + 5);
	dc.LineTo(dCenX + 5, dCenY - 5);
	dc.SelectObject(pOldPen);

	CString strCoordinates;
	strCoordinates.Format(_T("%.3f, %.3f"), dCenX, dCenY);
	dc.TextOut(dCenX + 20, dCenY + 20, strCoordinates);
}

void CProjectGLIMDlg::OnBnClickedButtonDraw()
{
	UpdateData(TRUE);

	DrawCircle(0,0,0);

	UpdateData(FALSE);
 }


void CProjectGLIMDlg::OnBnClickedButtonAction()
{
	// 시작 끝 x,y좌표 받아서 임의의 원 생성하면서 저장하는 함수

	UpdateData(TRUE);
	vpddPos.clear();

	double dX = double(m_iEndPos_X - m_iStartPos_X) / double(m_iStep);
	double dY = double(m_iEndPos_Y - m_iStartPos_Y) / double(m_iStep);

	for (int i = 0; i <= m_iStep; i++)
	{
		DrawCircle(i, dX, dY);
		SaveCircle(i);

		Sleep(100);
	}

	UpdateData(FALSE);
}


void CProjectGLIMDlg::OnBnClickedButtonOpen()
{
	// 저장된 원 이미지를 선택해서 출력하는 함수

	CFileDialog dlg(TRUE, _T("bmp"), nullptr, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("Image Files (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName(); 

		CImage image;
		if (SUCCEEDED(image.Load(strFilePath))) // 파일 open 성공
		{
			CClientDC dc(&m_pictureCtrl);
			CRect rect;
			m_pictureCtrl.GetClientRect(&rect);
			image.Draw(dc.GetSafeHdc(), rect);
		}
		else // 파일 오픈 실패
		{
			MessageBox(_T("이미지를 불러오지 못했습니다."), _T("오류"), MB_ICONERROR);
		}

		DrawMark(strFilePath);
	}
}
