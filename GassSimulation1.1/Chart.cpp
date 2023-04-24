// Chart.cpp : implementation file
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "Chart.h"
#include "Value.h"
#include "afxdialogex.h"

//External Variables
extern int nx, ny, nz, reservoirMaked, startSimulation, simulationSet;
extern double poro[100][100][100], permX[100][100][100], permY[100][100][100], permZ[100][100][100], xD[100][100][100], yD[100][100][100], zD[100][100][100], pChart[4][100][100][100], SGI1Chart[4][100][100][100], SWI1Chart[4][100][100][100];
extern double Pinit, minPressure;
// Chart dialog

IMPLEMENT_DYNAMIC(Chart, CDialogEx)

Chart::Chart(int i, CWnd* pParent /*=NULL*/)
	: CDialogEx(Chart::IDD, pParent)
	, comboLayerNo(0)
	, comboLayerNo2(0)
	, permType(0)
	, stepValue(0)
{
	ok = true;
	this->PPP = i;	//set porosity, permability or pressure values
	if(this->PPP == 1)	///PPP = 1 means Porosity
	{
		this->selectSet = reservoirMaked;
	}
	else if(this->PPP == 2)	///PPP = 2 meanse Permability
	{
		this->selectSet = reservoirMaked;
	}
	else if(this->PPP == 3)	///PPP = 3 meanse Permability
	{
		this->selectSet = startSimulation;
	}
	else if(this->PPP == 4)	///PPP = 4 meanse Gass Saturation
	{
		this->selectSet = startSimulation;
	}
	else	///PPP = 5	means Water Saturation
	{
		this->selectSet = startSimulation;
	}
}

Chart::~Chart()
{
}

void Chart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOLAYER, comboLayer);
	DDX_CBIndex(pDX, IDC_COMBOLAYER, comboLayerNo);
	DDX_Control(pDX, IDC_COMBOLAYER2, comboLayer2);
	DDX_CBIndex(pDX, IDC_COMBOLAYER2, comboLayerNo2);
	DDX_CBIndex(pDX, IDC_COMBOPERM, permType);
	DDX_CBIndex(pDX, IDC_COMBOSTEP, stepValue);
}


BEGIN_MESSAGE_MAP(Chart, CDialogEx)
	ON_BN_CLICKED(IDOK, &Chart::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTONVALUE, &Chart::OnBnClickedButtonvalue)
	ON_BN_CLICKED(IDCANCEL, &Chart::OnBnClickedCancel)
END_MESSAGE_MAP()


// Chart message handlers


void Chart::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDC *pDC = GetDC();
	onDrawGrid(pDC);
}


void Chart::OnBnClickedButtonvalue()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	Value *dlgPressureValues = new Value(this->comboLayerNo,this->comboLayerNo2,this->PPP,this->permType,this->stepValue);
	dlgPressureValues->DoModal();
	delete(dlgPressureValues);
}


void Chart::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL Chart::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//Initial combobox from 1 to nz layer
	for(int i = 1;i < nz + 1;i++)
	{
		CString s;
		s.Format(_T("%d"), i);
		comboLayer.AddString((LPCTSTR)s);
		comboLayer2.AddString((LPCTSTR)s);
	}
	if(this->PPP == 1)	///PPP = 1 means Porosity
	{
		GetDlgItem(IDC_COMBOPERM)->ShowWindow(false);
		GetDlgItem(IDC_STATICPERM)->ShowWindow(false);
		GetDlgItem(IDC_COMBOSTEP)->ShowWindow(false);
		GetDlgItem(IDC_STATICSTEP)->ShowWindow(false);
		SetWindowTextW(L"Porosity");
		this->permType = -1;
	}
	else if(this->PPP == 2)	///PPP = 2 meanse Permability
	{
		GetDlgItem(IDC_COMBOPERM)->ShowWindow(true);
		GetDlgItem(IDC_STATICPERM)->ShowWindow(true);
		GetDlgItem(IDC_COMBOSTEP)->ShowWindow(false);
		GetDlgItem(IDC_STATICSTEP)->ShowWindow(false);
		SetWindowTextW(L"Permability");
	}
	else if(this->PPP == 3)	///PPP = 3	means Pressure
	{
		GetDlgItem(IDC_COMBOPERM)->ShowWindow(false);
		GetDlgItem(IDC_STATICPERM)->ShowWindow(false);
		GetDlgItem(IDC_COMBOSTEP)->ShowWindow(true);
		GetDlgItem(IDC_STATICSTEP)->ShowWindow(true);
		SetWindowTextW(L"Pressure");
		this->permType = -1;
	}
	else if(this->PPP == 4)	///PPP = 4	means Gass Saturation
	{
		GetDlgItem(IDC_COMBOPERM)->ShowWindow(false);
		GetDlgItem(IDC_STATICPERM)->ShowWindow(false);
		GetDlgItem(IDC_COMBOSTEP)->ShowWindow(true);
		GetDlgItem(IDC_STATICSTEP)->ShowWindow(true);
		SetWindowTextW(L"Gass Saturation");
		this->permType = -1;
	}
	else	///PPP = 5	means Water Saturation
	{
		GetDlgItem(IDC_COMBOPERM)->ShowWindow(false);
		GetDlgItem(IDC_STATICPERM)->ShowWindow(false);
		GetDlgItem(IDC_COMBOSTEP)->ShowWindow(true);
		GetDlgItem(IDC_STATICSTEP)->ShowWindow(true);
		SetWindowTextW(L"Water Saturation");
		this->permType = -1;
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void Chart::onDrawGrid(CDC* pDC)
{
	if(this->selectSet == 1)
	{
		UpdateData(TRUE);
		int r, g, b;	//set RGB Color
		int setRectx ,setRecty;	//set a rectangl fram for draw chart
		int fromZ, toZ;	//from wich layer to which on in Z row
		fromZ = comboLayerNo;
		toZ = comboLayerNo2;
		if(fromZ > toZ)
		{
			swap(&fromZ, &toZ);	//swap from and to
		}
		toZ++;	//for 'for' commands
		int i,j,k;
		this->setChartBox(&setRectx ,&setRecty);
		int max = this->getMax();
		CPoint p1, p2, p3, p4;
		CPen newPen(PS_SOLID,1,RGB(255,255,255));
		CBrush newBrush(RGB(0,0,0));	//Black is default brush color
		pDC->SelectObject(&newBrush);
		p1.x = setRectx / 6;
		p1.y = setRecty / 8;
		p4.x = setRectx * 27 / 6;
		p4.y = setRecty * 17 / 8;
		CRect newRect(p1,p4);
		pDC->FillRect(newRect,&newBrush);
		pDC->SelectObject(&newPen);
		int downZ = 0;	//for move down up layer to correct position
		if(fromZ)	//if it isnt the first layer set downZ else it is zero
		{
			downZ = ((int)zD[0][0][fromZ - 1] * setRecty / max);
		}
		for(j = 0;j < ny;j++)
		{
			for(i = 0;i < nx;i++)
			{
				//************* p1
				if(i == 0 && j == 0)	//Initial to start point
				{
					p1.x = setRectx;
					p1.y = setRecty + downZ;
				}
				else
				{
					if(i != 0 )
					{
						p1 = p2;	//Before is calculated in p2
					}
					else
					{
						p1.x = setRectx + ((int)yD[i][j - 1][fromZ] * setRectx / max ) / 2;
						p1.y = setRecty - ((int)yD[i][j - 1][fromZ] * setRecty / max ) / 2 + downZ;
					}
				}
				//**************** p2
				if(j == 0)
				{
					p2.x = setRectx + ((int)xD[i][0][fromZ] * setRectx / max);
				}
				else
				{
					p2.x = setRectx + ((int)xD[i][0][fromZ] * setRectx / max) + ((int)yD[0][j - 1][fromZ] * setRectx / max ) / 2;
				}
				if(j == 0)
				{
					p2.y = setRecty + downZ;
				}
				else
				{
					p2.y = setRecty - ((int)yD[i][j - 1][fromZ] * setRecty / max ) / 2 + downZ;
				}
				//************* p4
				if(i != 0 )
				{
					p4 = p3;	//Before is calculated in p3
				}
				else
				{
					p4.x = setRectx + ((int)yD[i][j][fromZ] * setRectx / max ) / 2;
					p4.y = setRecty - ((int)yD[i][j][fromZ] * setRecty / max ) / 2 + downZ;
				}
				//************* p3
				p3.x = setRectx + ((int)yD[i][j][fromZ] * setRectx / max ) / 2 + ((int)xD[i][j][fromZ] * setRectx / max);
				p3.y = setRecty - ((int)yD[i][j][fromZ] * setRecty / max ) / 2 + downZ;
				//Paint Grids
				if(this->selectSet == 1)
				{
					if(this->PPP == 1)	///PPP = 1 means Porosity
					{
						setRGB(poro[i][j][fromZ] * 1000 , &r, &g, &b);
					}
					else if(this->PPP == 2)	///PPP = 2 meanse Permability
					{
						if(this->permType == 0)	//means permX
						{
							setRGB(permX[i][j][fromZ] * 10, &r, &g, &b);
						}
						else if(this->permType == 1)	//means permY
						{
							setRGB(permY[i][j][fromZ] * 10, &r, &g, &b);
						}
						else	//means permZ
						{
							setRGB(permZ[i][j][fromZ] * 10, &r, &g, &b);
						}
					}
					else if(this->PPP == 3)	///PPP = 3	means Pressure
					{
						setRGB(1000 - (Pinit - pChart[stepValue][i][j][fromZ]) * 1000 / (Pinit - minPressure), &r, &g, &b);
					}
					else if(this->PPP == 4)	///PPP = 4 means Gass Saturation
					{
						setRGB(SGI1Chart[stepValue][i][j][fromZ] * 1000 , &r, &g, &b);
					}
					else	///PPP = 5 means Water Saturation
					{
						setRGB(SWI1Chart[stepValue][i][j][fromZ] * 1000 , &r, &g, &b);
					}
					newBrush.DeleteObject();
					newBrush.CreateSolidBrush(RGB(r,g,b));
					//************
					pDC->SelectObject(&newBrush);
					pDC->BeginPath();
					pDC->MoveTo(p1);
					pDC->LineTo(p2);
					pDC->LineTo(p3);
					pDC->LineTo(p4);
					pDC->LineTo(p1);
					pDC->EndPath();
					pDC->FillPath();
				}
				//*************Draw Lines
				pDC->MoveTo(p1);
				pDC->LineTo(p2);
				pDC->LineTo(p3);
				pDC->LineTo(p4);
				pDC->LineTo(p1);
			}
		}
		//******************
		for(j = fromZ;j < toZ;j++)
		{
			for(i = 0;i < nx;i++)
			{
				//************* p1
				if(i == 0 && j == 0)	//Initial to start point
				{
					p1.x = setRectx;
					p1.y = setRecty;
				}
				else
				{
					if(i != 0 )
					{
						p1 = p2;	//Before is calculated in p2
					}
					else
					{
						p1.x = setRectx;
						p1.y = setRecty + ((int)zD[i][0][j - 1] * setRecty / max);
					}
				}
				//**************** p2
				p2.x = setRectx + ((int)xD[i][0][fromZ] * setRectx / max);
				if(j == 0)
				{
					p2.y = setRecty;
				}
				else
				{
					p2.y = setRecty + ((int)zD[i][0][j - 1] * setRecty / max);
				}
				//************* p4
				if(i != 0)
				{
					p4 = p3;	//Before is calculated in p3
				}
				else
				{
					p4.x = setRectx;
					p4.y = setRecty + ((int)zD[i][0][j] * setRecty / max);
				}
				//************* p3
				p3.x = setRectx + ((int)xD[i][0][fromZ] * setRectx / max);
				p3.y = setRecty + ((int)zD[i][0][j] * setRecty / max);
				//Paint Grids
				if(this->selectSet == 1)
				{
					if(this->PPP == 1)	///PPP = 1 means Porosity
					{
						setRGB(poro[i][0][j] * 1000 , &r, &g, &b);
					}
					else if(this->PPP == 2)	///PPP = 2 meanse Permability
					{
						if(this->permType == 0)	//means permX
						{
							setRGB(permX[i][0][j] * 10, &r, &g, &b);
						}
						else if(this->permType == 1)	//means permY
						{
							setRGB(permY[i][0][j] * 10, &r, &g, &b);
						}
						else	//means permZ
						{
							setRGB(permZ[i][0][j] * 10, &r, &g, &b);
						}
					}
					else if(this->PPP == 3)	///PPP = 3	means Pressure
					{
						setRGB(1000 - (Pinit - pChart[stepValue][i][0][j]) * 1000 / (Pinit - minPressure),&r, &g, &b);
					}
					else if(this->PPP == 4)	///PPP = 4 means Gass Saturation
					{
						setRGB(SGI1Chart[stepValue][i][0][j] * 1000 , &r, &g, &b);
					}
					else	///PPP = 5 means Water Saturation
					{
						setRGB(SWI1Chart[stepValue][i][0][j] * 1000 , &r, &g, &b);
					}
					newBrush.DeleteObject();
					newBrush.CreateSolidBrush(RGB(r,g,b));
					//************
					pDC->SelectObject(&newBrush);
					pDC->BeginPath();
					pDC->MoveTo(p1);
					pDC->LineTo(p2);
					pDC->LineTo(p3);
					pDC->LineTo(p4);
					pDC->LineTo(p1);
					pDC->EndPath();
					pDC->FillPath();
				}
				//*************Draw Lines
				pDC->MoveTo(p1);
				pDC->LineTo(p2);
				pDC->LineTo(p3);
				pDC->LineTo(p4);
				pDC->LineTo(p1);
			}
		}
		//******************
		int setRectxEnd = setRectx + ((int)xD[nx-1][0][fromZ] * setRectx / max);
		for(j = fromZ;j < toZ;j++)
		{
			for(i = 0;i < ny;i++)
			{
				//************* p1
				if(i == 0 && j == 0)	//Initial to start point
				{
					p1.x = setRectxEnd;
					p1.y = setRecty;
				}
				else
				{
					if(i != 0 )
					{
						p1 = p2;	//Before is calculated in p2
					}
					else
					{
						p1.x = setRectxEnd;
						p1.y = setRecty + ((int)zD[0][i][j - 1] * setRecty / max);
					}
				}
				//**************** p2
				p2.x = setRectxEnd + ((int)yD[0][i][fromZ] * setRectx / max) / 2;
				if(j == 0)
				{
					p2.y = setRecty - ((int)yD[0][i][fromZ] * setRecty / max) / 2;
				}
				else
				{
					p2.y = setRecty - ((int)yD[0][i][fromZ] * setRecty / max) / 2 + ((int)zD[0][i][j - 1] * setRecty / max);
				}
				//************* p4
				if(i != 0 )
				{
					p4 = p3;	//Before is calculated in p3
				}
				else
				{
					p4.x = setRectxEnd;
					p4.y = setRecty + ((int)zD[0][i][j] * setRecty / max);
				}
				//************* p3
				p3.x = setRectxEnd + ((int)yD[0][i][fromZ] * setRectx / max) / 2;
				p3.y = setRecty - ((int)yD[0][i][fromZ] * setRecty / max) / 2 + ((int)zD[0][i][j] * setRecty / max);
				//Paint Grids
				if(this->selectSet == 1)
				{
					if(this->PPP == 1)	///PPP = 1 means Porosity
					{
						setRGB(poro[nx - 1][i][j] * 1000 , &r, &g, &b);
					}
					else if(this->PPP == 2)	///PPP = 2 meanse Permability
					{
						if(this->permType == 0)	//means permX
						{
							setRGB(permX[nx - 1][i][j] * 10, &r, &g, &b);
						}
						else if(this->permType == 1)	//means permY
						{
							setRGB(permY[nx - 1][i][j] * 10, &r, &g, &b);
						}
						else	//means permZ
						{
							setRGB(permZ[nx - 1][i][j] * 10, &r, &g, &b);
						}
					}
					else if(this->PPP == 3)	///PPP = 3	means Pressure
					{
						setRGB(1000 - (Pinit - pChart[stepValue][nx - 1][i][j]) * 1000 / (Pinit - minPressure), &r, &g, &b);
					}
					else if(this->PPP == 4)	///PPP = 4 means Gass Saturation
					{
						setRGB(SGI1Chart[stepValue][nx - 1][i][j] * 1000 , &r, &g, &b);
					}
					else	///PPP = 5 means Water Saturation
					{
						setRGB(SWI1Chart[stepValue][nx - 1][i][j] * 1000 , &r, &g, &b);
					}
					newBrush.DeleteObject();
					newBrush.CreateSolidBrush(RGB(r,g,b));
					//************
					pDC->SelectObject(&newBrush);
					pDC->BeginPath();
					pDC->MoveTo(p1);
					pDC->LineTo(p2);
					pDC->LineTo(p3);
					pDC->LineTo(p4);
					pDC->LineTo(p1);
					pDC->EndPath();
					pDC->FillPath();
				}
				//*************Draw Lines
				pDC->MoveTo(p1);
				pDC->LineTo(p2);
				pDC->LineTo(p3);
				pDC->LineTo(p4);
				pDC->LineTo(p1);
			}
		}
		CString s;
		CFont newFont;
		VERIFY(newFont.CreateFontW(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial"));
		this->setChartBox(&setRectx ,&setRecty);
		setRectx = (setRectx * 4);
		setRecty = (setRecty * 2);
		double devidValue, initialSet;
		if(this->PPP == 1)	///PPP = 1 means Porosity
		{
			initialSet = 0;
			devidValue = 0.2;
		}
		else if(this->PPP == 2)	///PPP = 2 meanse Permability
		{
			initialSet = 0;
			devidValue = 20;
		}
		else if(this->PPP == 3)	///PPP = 3	means Pressure
		{
			initialSet = minPressure;
			devidValue = (Pinit - minPressure) / 5;	//Devide pressure distance to 5 section
		}
		else if(this->PPP == 4)	///PPP = 4 meanse Gass Saturation
		{
			initialSet = 0;
			devidValue = 0.2;
		}
		else	///PPP = 5 meanse Water Saturation
		{
			initialSet = 0;
			devidValue = 0.2;
		}
		for(i = 250;i > -1; i--)
		{
			setRGB(i * 4,&r, &g, &b);
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(r, g, b));
			pDC->SelectObject(&newBrush);
			pDC->BeginPath();
			pDC->MoveTo(setRectx, setRecty - i);
			pDC->LineTo(setRectx + 10, setRecty - i);
			pDC->LineTo(setRectx + 10, setRecty - (i + 2));
			pDC->LineTo(setRectx, setRecty - (i + 2));
			pDC->LineTo(setRectx, setRecty - i);
			pDC->EndPath();
			pDC->FillPath();
			if(i % 50 == 0)
			{
				pDC->SelectObject(&newFont);
				s.Format(L"%2.1f",initialSet + devidValue * i / 50);
				pDC->TextOutW(setRectx + 13,setRecty - 10 - i,s);
			}
		}
	}
}


void Chart::swap(int *from, int *to)
{
	int temp;
	temp = *from;
	*from = *to;
	*to = temp;
}


void Chart::setRGB(int inPut, int *r, int *g, int *b)
{
	if(inPut < 0)
	{
		*r = 250;
		*g = 0;
		*b = 0;
	}
	else if(inPut < 251)
	{
		*r = 250;
		*g = inPut;
		*b = 0;
	}
	else if(inPut < 501)
	{
		*r = 250 - (inPut - 250);
		*g = 250;
		*b = 0;
	}
	else if(inPut < 751)
	{
		*r = 0;
		*g = 250;
		*b = inPut - 500;
	}
	else if(inPut < 1001)
	{
		*r = 0;
		*g = 250 - (inPut - 750);
		*b = 250;
	}
	else
	{
		*r = 0;
		*g = 0;
		*b = 250;
	}
}


void Chart::setChartBox(int *setX, int *setY)
{
	CRect mainRect;
	GetClientRect(mainRect);
	mainRect.NormalizeRect();
	*setY = mainRect.Height() / 9 * 4;	//Get Height of window and get 4 out of 9 slid
	*setX = mainRect.Width() / 18 * 3;	//Get Width of window and get 3 out of 18 slid
}

int Chart::getMax(void)
{
	UpdateData(TRUE);
	int max=(int)xD[nx-1][ny-1][comboLayerNo2];	//set maximum of x,y and z for drawing
	if(yD[nx-1][ny-1][comboLayerNo2]>max)
	{
		max=(int)yD[nx-1][ny-1][comboLayerNo2];
	}
	if(zD[nx-1][ny-1][comboLayerNo2]>max)
	{
		max=(int)zD[nx-1][ny-1][comboLayerNo2];
	}
	return max;
}