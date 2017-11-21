
// veinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vein.h"
#include "veinDlg.h"
#include "windows.h"
#include "afxdialogex.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"

using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
Mat input,temp,roi,roi3ch,frame3ch;

int rows,cols,flag=0,ukuran=0;
int datapixel,dataori;
int largest_contour_index=0;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CveinDlg dialog




CveinDlg::CveinDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CveinDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CveinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_pict, m_pict);
	DDX_Control(pDX, IDC_pict1, m_pict1);
}

BEGIN_MESSAGE_MAP(CveinDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CveinDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CveinDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CveinDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CveinDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO1, &CveinDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CveinDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CveinDlg message handlers

BOOL CveinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CveinDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CveinDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CveinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CveinDlg::Proses(){
	VideoCapture cap(0); //capture the video from webcam
    if ( !cap.isOpened() ) { // if not success, exit program
         cout << "Cannot open the web cam" << endl;
         //return -1;
    }
	//cvNamedWindow("Output", CV_WINDOW_NORMAL);
	//cvSetWindowProperty("Output", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	namedWindow("Input", CV_WINDOW_NORMAL);
	namedWindow("Input1", CV_WINDOW_NORMAL);
	//setWindowProperty("Input", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	//setWindowProperty("Input", CV_WND_PROP_ASPECTRATIO, CV_WINDOW_KEEPRATIO);
		HWND hWnd = (HWND) cvGetWindowHandle("Input"); 
			HWND hParent = ::GetParent(hWnd); 
			::SetParent(hWnd, GetDlgItem(IDC_pict)->m_hWnd); 
			::ShowWindow(hParent, SW_HIDE);
	
		HWND hWnd1 = (HWND) cvGetWindowHandle("Input1"); 
			HWND hParent1 = ::GetParent(hWnd1); 
			::SetParent(hWnd1, GetDlgItem(IDC_pict1)->m_hWnd); 
			::ShowWindow(hParent1, SW_HIDE);
	
	 //Capture a temporary image from the camera
	 Mat imgTmp; 
	 cap.read(imgTmp); 
	
	 //Create a black image with the size as the camera output
	 Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
	 while (true){
		bool bSuccess = cap.read(input); // read a new frame from video
			if (!bSuccess) { //if not success, break loop
				cout << "Cannot read a frame from video stream" << endl;
				break;
			}
			if(flag==0){
				if(ukuran==0){
					imshow("Input1", input);
					resizeWindow("Input1",640,480);
				}
				if(ukuran==1){
					roi = input(Range(140, 340), Range(220, 420));
					imshow("Input1", roi);
				}
				if(ukuran==0) roi3ch = input(Range(0, 480), Range(0, 640));
				if(ukuran==1) roi3ch = input(Range(140, 340), Range(220, 420));
				frame3ch = roi3ch.clone();
				cvtColor(input,input,CV_RGB2GRAY);
				if(ukuran==0) roi = input(Range(0, 480), Range(0, 640));
				if(ukuran==1) roi = input(Range(140, 340), Range(220, 420));
				Mat output(roi.rows,roi.cols,CV_8UC1,Scalar::all(0));
				medianBlur (roi, temp, 5);
				adaptiveThreshold( temp, temp, 255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,19, 1 );
				bitwise_not(temp,temp);
				Mat element(5,5,CV_8U,cv::Scalar(1));
				morphologyEx(temp,temp,cv::MORPH_OPEN,element);
				//erode(morp, morp, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
				//dilate( temp, temp, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
				
				vector<vector<Point>> contours; // Vector for storing contour 
				vector<Vec4i> hierarchy;
		
				findContours( temp, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image
				for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
				{
					double a=contourArea( contours[i],false); //  Find the area of contour
					if(a>300){
						largest_contour_index=i; //Store the index of largest contour
						Scalar color( 255,255,255);
						drawContours( output, contours,largest_contour_index, color, CV_FILLED, 8, hierarchy ); // Draw the largest contour using previously stored index.
					}
				}

				imshow("Input", output);
				element.release();
				output.release();
			}
			if(flag==1){
				if(ukuran==0){
					imshow("Input1", input);
					resizeWindow("Input1",640,480);
				}
				if(ukuran==1){
					roi = input(Range(140, 340), Range(220, 420));
					imshow("Input1", roi);
				}
				if(ukuran==0) roi3ch = input(Range(0, 480), Range(0, 640));
				if(ukuran==1) roi3ch = input(Range(140, 340), Range(220, 420));
				frame3ch = roi3ch.clone();
				cvtColor(input,input,CV_RGB2GRAY);
				if(ukuran==0) roi = input(Range(0, 480), Range(0, 640));
				if(ukuran==1) roi = input(Range(140, 340), Range(220, 420));
				Mat output(roi.rows,roi.cols,CV_8UC1,Scalar::all(0));
				medianBlur (roi, temp, 5);
				adaptiveThreshold( temp, temp, 255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,19, 1 );
				bitwise_not(temp,temp);
				Mat element(5,5,CV_8U,cv::Scalar(1));
				morphologyEx(temp,temp,cv::MORPH_OPEN,element);
				//erode(morp, morp, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
				//dilate( temp, temp, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
				
				vector<vector<Point>> contours; // Vector for storing contour 
				vector<Vec4i> hierarchy;
		
				findContours( temp, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image
				for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
				{
					double a=contourArea( contours[i],false); //  Find the area of contour
					if(a>300){
						largest_contour_index=i; //Store the index of largest contour
						Scalar color( 255,255,255);
						drawContours( output, contours,largest_contour_index, color, CV_FILLED, 8, hierarchy ); // Draw the largest contour using previously stored index.
					}
				}
		
				for(int i=0; i<output.rows; i++){//row
					for(int j=0; j<output.cols; j++){//col
						datapixel = output.at<uchar>(i,j);
						if(datapixel==0){
							frame3ch.at<Vec3b>(i,j)[0] = 0;
							frame3ch.at<Vec3b>(i,j)[1] = 0;
							frame3ch.at<Vec3b>(i,j)[2] = 255;
						}
						
					}
				}
				imshow("Input", frame3ch);
				element.release();
				output.release();
			}

		roi3ch.release();
		frame3ch.release();
		input.release();
		imgTmp.release();
		temp.release();

		if (waitKey(30) >= 0) { //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}
	cap.release();
}

void CveinDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	flag=0;
	Proses();
}


void CveinDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	
	//ReleaseCapture();
	CDialogEx::OnCancel();
}

void CveinDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	flag=1;
}

void CveinDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	flag=0;
}

void CveinDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	ukuran=0;
	UpdateData(0);
}


void CveinDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	ukuran=1;
	UpdateData(0);
}
