// GassSimulation1.1View.cpp : implementation of the CGassSimulation11View class
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "GassSimulation1.1Doc.h"
#include "GassSimulation1.1View.h"
#include "Chart.h"
#include "graph2.h"
#include "Welldataflx.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGassSimulation11View

//Extern variables and functions

extern double xD[100][100][100], yD[100][100][100], zD[100][100][100],
	dx[100][100][100], dy[100][100][100], dz[100][100][100], poro[100][100][100],
	xThick[100][100][100], yThick[100][100][100], zThick[100][100][100];
extern int wellSet, startSimulation, simulationSet, firstTime, reservoirMaked, reservoirMakedfirst, gridMakedfirst, i, j, k, gridType, nteta, nr, nx, ny, nz, startZ, endZ, ok, gridMaked;
extern void StartSimulation();
extern int nwell, XCoor[100], YCoor[100], ZCoor[100];
extern char well[100][100][100];
extern double rw[100][100][100];
extern double skin[100][100][100],qw[100][100][100],qg[100][100][100],pwf[100][100][100],minbhp[100][100][100];
extern char wellconstraint[100][100][100],typewell[100][100][100],TypeWell_read[100][100];
extern char outputTextFile[100], outputTextFilef[100], outputTextFilem[100];

IMPLEMENT_DYNCREATE(CGassSimulation11View, CView)

BEGIN_MESSAGE_MAP(CGassSimulation11View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_NEW, &CGassSimulation11View::OnFileNew)
	ON_COMMAND(ID_FILE_SETRESERVOIR, &CGassSimulation11View::OnFileSetreservoir)
	ON_COMMAND(ID_SIMULATION_SETDATA, &CGassSimulation11View::OnSimulationSetdata)
	ON_COMMAND(ID_SIMULATION_STARTSIMULATION, &CGassSimulation11View::OnSimulationStartsimulation)
	ON_COMMAND(ID_FILE_SETWELLS, &CGassSimulation11View::OnFileSetwells)
	ON_COMMAND(ID_CHARTS_PRESSURE, &CGassSimulation11View::OnChartsPressure)
	ON_COMMAND(ID_CHARTS_PERMABILITY, &CGassSimulation11View::OnChartsPermability)
	ON_COMMAND(ID_CHARTS_POROSITY, &CGassSimulation11View::OnChartsPorosity)
	ON_COMMAND(ID_CHARTS_GASSSATURATION, &CGassSimulation11View::OnChartsGasssaturation)
	ON_COMMAND(ID_CHARTS_WATERSATU, &CGassSimulation11View::OnChartsWatersatu)
	ON_COMMAND(ID_GRAPH_PRESSURE, &CGassSimulation11View::OnGraphPressure)
	ON_COMMAND(ID_GRAPH_GASSSATURATIO, &CGassSimulation11View::OnGraphGasssaturatio)
	ON_COMMAND(ID_GRAPH_WATERSATURATIO, &CGassSimulation11View::OnGraphWatersaturatio)
END_MESSAGE_MAP()

// CGassSimulation11View construction/destruction

CGassSimulation11View::CGassSimulation11View()
{
	// TODO: add construction code here

}

CGassSimulation11View::~CGassSimulation11View()
{
}

BOOL CGassSimulation11View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGassSimulation11View drawing

void CGassSimulation11View::OnDraw(CDC* pDC)
{
	CGassSimulation11Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(firstTime == 1)
	{
		pDoc->DeleteContents();
		UpdateWindow();
		if(gridMaked == 1)
		{
			//CGassSimulation11View::OnReservoirDraw(pDC);
			this->OnPressuerDraw(pDC);
		}
		/*if(gridMaked == 1)
		{
			CGassSimulation11View::OnGridDraw(pDC);
		}
		if(wellSet == 1)
		{
			CGassSimulation11View::OnWellDraw(pDC);
		}*/
	}
	else
	{
		int setRectx ,setRecty;
		this->setChartBox(&setRectx ,&setRecty);
		CDC memCDC;
		CBitmap bmpPicture;
		bmpPicture.LoadBitmapW(IDB_BITMAPARM);
		memCDC.CreateCompatibleDC(pDC);
		memCDC.SelectObject(&bmpPicture);
		pDC->StretchBlt(setRectx * 5 / 2 - 125, setRecty * 5 / 4 - 175, 250, 350, &memCDC, 0, 0, 600, 800, SRCCOPY);
	}
	UpdateWindow();
	// TODO: add draw code for native data here
	
}

void CGassSimulation11View::OnLine(CDC *pdc,CPoint newStart,CPoint newEnd,int M_F)
{
	if(M_F == 1)//set color to black
	{
		CPen newPen(PS_SOLID,1,RGB(0,0,0));//black
		pdc->SelectObject(&newPen);
		pdc->MoveTo(newStart);
		pdc->LineTo(newEnd);
	}
	else//set color to red
	{
		CPen newPen(PS_SOLID,1,RGB(255,0,0));//red
		pdc->SelectObject(&newPen);
		pdc->MoveTo(newStart);
		pdc->LineTo(newEnd);
	}
}
// CGassSimulation11View printing

BOOL CGassSimulation11View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGassSimulation11View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGassSimulation11View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGassSimulation11View diagnostics

#ifdef _DEBUG
void CGassSimulation11View::AssertValid() const
{
	CView::AssertValid();
}

void CGassSimulation11View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGassSimulation11Doc* CGassSimulation11View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGassSimulation11Doc)));
	return (CGassSimulation11Doc*)m_pDocument;
}
#endif //_DEBUG


// CGassSimulation11View message handlers

void CGassSimulation11View::OnFileNew()
{
	// TODO: Add your command handler code here
	GridBuilder dlgGridbuilder;
	dlgGridbuilder.DoModal();
	if(gridMaked == 1)
	{
		CDC *pDC = GetDC();
		OnDraw(pDC);
	}
}

void CGassSimulation11View::OnFileSetreservoir()
{
	int msg;
	if(firstTime == 0)
	{
		msg = MessageBox(L"You should first make a yThick.\n Would you like do it?",L"Warning",MB_YESNO|MB_ICONQUESTION);
		if(msg == IDYES)
		{
			OnFileNew();
			if(reservoirMaked == 0 && gridMaked == 1)
			{
				Reservoir dlgReservoir;
				dlgReservoir.DoModal();
				if(reservoirMaked == 1)
				{
					CDC *pDC = GetDC();
					OnDraw(pDC);
				}
			}
		}
	}
	else
	{
		Reservoir dlgReservoir;
		dlgReservoir.DoModal();
		if(reservoirMaked == 1)
		{
			CDC *pDC = GetDC();
			OnDraw(pDC);
		}
	}
	// TODO: Add your command handler code here
}

void CGassSimulation11View::OnGridDraw(CDC* pDC)
{
	CRect mainRect;
	GetClientRect(mainRect);
	mainRect.NormalizeRect();
	int setRecty = mainRect.Height()/5*2;	//Get Height of window and get 2 of 5 slid
	int setRectx = mainRect.Width()/5;	//Get Width of window and get 2 of 5 slid
	int first=0,end=0,left=0,right=0;
	if(gridType == 0)
	{
		CPoint newStart,newEnd;
		i=0;
		int max=(int)xD[nx-1][ny-1][nz-1];
		if(yD[nx-1][ny-1][nz-1] > max)
		{
			max=(int)yD[nx-1][ny-1][nz-1];
		}
		if(zD[nx-1][ny-1][nz-1] > max)
		{
			max=(int)zD[nx-1][ny-1][nz-1];
		}
		//up down to up (///)
		newStart.x=setRectx;
		first=setRectx;
		newStart.y=setRecty;
		end=newEnd.x=setRectx+((int)yD[0][ny -1][0]*setRectx/max)/2;
		newEnd.y=setRecty-((int)yD[0][ny-1][0]*setRecty/max)/2;
		OnLine(pDC,newStart,newEnd,1);
		for(i=0;i<nx;i++)
		{
			newStart.x=first+((int)xD[i][0][0]*setRectx/max);
			newEnd.x=end+((int)xD[i][0][0]*setRectx/max);
			OnLine(pDC,newStart,newEnd,1);
		}
		//Up Rows East to West (---)
		first=newStart.x=setRectx;
		left=newStart.y=setRecty;
		end=newEnd.x=setRectx+((int)xD[nx-1][0][0]*setRectx/max);
		right=newEnd.y=setRecty;
		OnLine(pDC,newStart,newEnd,1);
		for(i=0;i<ny;i++)
		{
			newStart.x=first+((int)yD[0][i][0]*setRectx/max)/2;
			newEnd.x=end+((int)yD[0][i][0]*setRectx/max)/2;
			newStart.y=left-((int)yD[0][i][0]*setRecty/max)/2;
			newEnd.y=right-((int)yD[0][i][0]*setRecty/max)/2;
			OnLine(pDC,newStart,newEnd,1);
		}
		//Down Rows Top to Bottom (||||)
		//Matrix clack color
		first=newStart.x=setRectx;
		newStart.y=setRecty;
		end=newEnd.x=setRectx;
		newEnd.y=setRecty+((int)zD[0][0][nz/2-1]*setRecty/max);
		OnLine(pDC,newStart,newEnd,1);
		for(i=0;i<nx;i++)
		{
			newStart.x=first+((int)xD[i][0][0]*setRectx/max);
			newEnd.x=end+((int)xD[i][0][0]*setRectx/max);
			OnLine(pDC,newStart,newEnd,1);
		}
		//fracture red color
		first=newStart.x=setRectx;
		newStart.y=setRecty+((int)zD[0][0][nz/2-1]*setRecty/max);
		end=newEnd.x=setRectx;
		newEnd.y=setRecty+((int)zD[0][0][nz-1]*setRecty/max);
		OnLine(pDC,newStart,newEnd,2);
		for(i=0;i<nx;i++)
		{
			newStart.x=first+((int)xD[i][0][0]*setRectx/max);
			newEnd.x=end+((int)xD[i][0][0]*setRectx/max);
			OnLine(pDC,newStart,newEnd,2);
		}
		//Down Rows East to West (----)
		newStart.x=setRectx;
		left=newStart.y=setRecty;
		newEnd.x=setRectx+((int)xD[nx-1][0][0]*setRectx/max);
		right=newEnd.y=setRecty;
		OnLine(pDC,newStart,newEnd,1);
		//matrix
		for(i=0;i<nz/2;i++)
		{
			newStart.y=left+((int)zD[0][0][i]*setRecty/max);
			newEnd.y=right+((int)zD[0][0][i]*setRecty/max);
			OnLine(pDC,newStart,newEnd,1);
		}
		//fracture
		for(i=nz/2;i<nz;i++)
		{
			newStart.y=left+((int)zD[0][0][i]*setRecty/max);
			newEnd.y=right+((int)zD[0][0][i]*setRecty/max);
			OnLine(pDC,newStart,newEnd,2);
		}
		//Side Rows Top to Bottom (||||)
		//Matrix
		first=newStart.x=setRectx+((int)xD[nx-1][0][0]*setRectx/max);
		left=newStart.y=setRecty;
		end=newEnd.x=setRectx+((int)xD[nx-1][0][nz-1]*setRectx/max);
		right=newEnd.y=setRecty+((int)zD[nx-1][0][nz/2-1]*setRecty/max);
		for(i=0;i<ny;i++)
		{
			newStart.x=first+((int)yD[0][i][0]*setRectx/max)/2;
			newEnd.x=end+((int)yD[0][i][0]*setRectx/max)/2;
			newStart.y=left-((int)yD[0][i][0]*setRecty/max)/2;
			newEnd.y=right-((int)yD[0][i][0]*setRecty/max)/2;
			OnLine(pDC,newStart,newEnd,1);
		}
		//Fracture
		first=newStart.x=setRectx+((int)xD[nx-1][0][0]*setRectx/max);
		left=newStart.y=setRecty+((int)zD[nx-1][0][nz/2-1]*setRecty/max);
		end=newEnd.x=setRectx+((int)xD[nx-1][0][nz-1]*setRectx/max);
		right=newEnd.y=setRecty+((int)zD[nx-1][0][nz-1]*setRecty/max);
		for(i=0;i<ny;i++)
		{
			newStart.x=first+((int)yD[0][i][0]*setRectx/max)/2;
			newEnd.x=end+((int)yD[0][i][0]*setRectx/max)/2;
			newStart.y=left-((int)yD[0][i][0]*setRecty/max)/2;
			newEnd.y=right-((int)yD[0][i][0]*setRecty/max)/2;
			OnLine(pDC,newStart,newEnd,2);
		}
		//Side Rows South to North (/////)
		newStart.x=setRectx+((int)xD[nx-1][0][0]*setRectx/max);
		left=newStart.y=setRecty;
		newEnd.x=setRectx+((int)yD[0][ny-1][0]*setRectx/max)/2+((int)xD[nx-1][0][0]*setRectx/max);
		right=newEnd.y=setRecty-((int)yD[0][ny-1][0]*setRecty/max)/2;
		for(i=0;i<nz/2;i++)
		{
			newStart.y=left+((int)zD[0][0][i]*setRecty/max);
			newEnd.y=right+((int)zD[0][0][i]*setRecty/max);
			OnLine(pDC,newStart,newEnd,1);
		}
		for(i=nz/2;i<nz;i++)
		{
			newStart.y=left+((int)zD[0][0][i]*setRecty/max);
			newEnd.y=right+((int)zD[0][0][i]*setRecty/max);
			OnLine(pDC,newStart,newEnd,2);
		}
	}
	else
	{
		/*CPoint m_start,m_end,m_start2,m_end2;
		CPen m_pen(PS_SOLID,1,RGB(0,0,0));
		pDC->SelectObject(m_pen);
		CRect m_rect(m_start,m_end);
		int max=(int)Rgrid[nr-1][nteta-1][nz-1].vcr;
		if((Rgrid[nr-1][nteta-1][nz-1].vcteta)/360>max)
		{
			max=(int)Rgrid[nr-1][nteta-1][nz-1].vcteta;
		}
		if(Rgrid[nr-1][nteta-1][nz-1].vcz>max)
		{
			max=(int)Rgrid[nr-1][nteta-1][nz-1].vcz;
		}
		//Illustrate Circles(Ellipse)(...((.))...)
		m_start.x=setRectx*2-(int)(Rgrid[nr-1][0][0].vcr*setRectx/max);
		m_start.y=setRecty-(int)(Rgrid[nr-1][0][0].vcr*setRecty/max)/2;
		m_end.x=setRectx*2+(int)(Rgrid[nr-1][0][0].vcr*setRectx/max);
		m_end.y=setRecty+(int)(Rgrid[nr-1][0][0].vcr*setRecty/max)/2;
		m_rect.BottomRight()=m_end;
		m_rect.TopLeft()=m_start;
		pDC->Ellipse(m_rect);
		for(i=nr-2;i>-1;i--)
		{
			m_start.x=setRectx*2-(int)(Rgrid[i][0][0].vcr*setRectx/max);
			m_start.y=setRecty-(int)(Rgrid[i][0][0].vcr*setRecty/max)/2;
			m_end.x=setRectx*2+(int)(Rgrid[i][0][0].vcr*setRectx/max);
			m_end.y=setRecty+(int)(Rgrid[i][0][0].vcr*setRecty/max)/2;
			m_rect.BottomRight()=m_end;
			m_rect.TopLeft()=m_start;
			pDC->Ellipse(m_rect);
		}
		m_end.x=setRectx*2-1;
		m_end.y=setRecty-5;
		m_start.x=setRectx*2+1;
		m_start.y=setRecty+5;
		m_rect.BottomRight()=m_end;
		m_rect.TopLeft()=m_start;
		pDC->Ellipse(m_rect);
		//Illustrate radius
		m_start.x=setRectx*2;
		m_start.y=setRecty;
		m_end.x=setRectx*2-(int)(Rgrid[nr-1][0][0].vcr*setRectx/max);
		m_end.y=setRecty;
		for(i=0;i<nteta;i++)
		{
			m_end.x=setRectx*2+(int)((Rgrid[nr-1][0][0].vcr*setRectx/max)*cos((Rgrid[0][i][0].vcteta)*3.14/180));
			m_end.y=setRecty-(int)((Rgrid[nr-1][0][0].vcr*setRecty/max)/2*sin((Rgrid[0][i][0].vcteta)*3.14/180));
			OnLine(pDC,m_start,m_end);
			//If ys point is more than setRect it means you can Illustrate vertical line in Cylinder 
			if(m_end.y>setRecty)
			{
				pDC->MoveTo(m_end);
				pDC->LineTo(m_end.x,(int)(m_end.y+(Rgrid[0][0][nz-1].vcz*setRecty/max)));
			}
		}
		//*****************************************
		m_start.x=setRectx*2-(int)(Rgrid[nr-1][0][0].vcr*setRectx/max);
		first=m_start.y=setRecty;
		m_end.x=setRectx*2+(int)(Rgrid[nr-1][0][0].vcr*setRectx/max);
		end=m_end.y=setRecty;
		m_start2.x=setRectx*2-(int)(Rgrid[nr-1][0][0].vcr*setRectx/max);
		m_start2.y=setRecty+(int)(Rgrid[0][0][nz-1].vcz*setRecty/max);
		m_end2.x=setRectx*2+(int)(Rgrid[nr-1][0][0].vcr*setRectx/max);
		m_end2.y=setRecty+(int)(Rgrid[0][0][nz-1].vcz*setRecty/max);
		pDC->MoveTo(m_start);
		pDC->LineTo(m_start2);
		pDC->MoveTo(m_end);
		pDC->LineTo(m_end2);
		m_start2.x=setRectx*2-(int)(Rgrid[nr-1][0][0].vcr*setRectx/max);
		left=m_start2.y=setRecty-(int)(Rgrid[nr-1][0][0].vcr*setRecty/max)/2;
		m_end2.x=setRectx*2+(int)(Rgrid[nr-1][0][0].vcr*setRectx/max);
		right=m_end2.y=setRecty+(int)(Rgrid[nr-1][0][0].vcr*setRecty/max)/2;
		for(i=0;i<nz;i++)
		{
			m_end.y=end+(int)(Rgrid[0][0][i].vcz*setRecty/max);
			m_start.y=first+(int)(Rgrid[0][0][i].vcz*setRecty/max);
			m_end2.y=right+(int)(Rgrid[0][0][i].vcz*setRecty/max);
			m_start2.y=left+(int)(Rgrid[0][0][i].vcz*setRecty/max);
			m_rect.BottomRight()=m_start2;
			m_rect.TopLeft()=m_end2;
			pDC->Arc(m_rect,m_start,m_end);
		}*/
	}
}

void CGassSimulation11View::OnReservoirDraw(CDC* pDC)
{
	CRect mainRect;
	GetClientRect(mainRect);
	mainRect.NormalizeRect();
	int setRecty = mainRect.Height()/5*2;	//Get Height of window and get 2 of 5 slid
	int setRectx = mainRect.Width()/5;	//Get Width of window and get 2 of 5 slid
	int first=0, end=0, left=0, right=0;
	CPen newPen(PS_SOLID,1,RGB(0,0,0));
	CBrush newBrush(RGB(0,0,255)); //Blue is default brush color
	CPoint point1,point2,point3,point4,point5,point6;
	int max=(int)xD[nx-1][ny-1][nz-1];	//set maximum of x,y and z for drawing
	if(yD[nx-1][ny-1][nz-1]>max)
	{
		max=(int)yD[nx-1][ny-1][nz-1];
	}
	if(zD[nx-1][ny-1][nz-1]>max)
	{
		max=(int)zD[nx-1][ny-1][nz-1];
	}
	//************
	if(poro[0][0][0] < 0.1)	//set brush color that recommended to poro values
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(0,255,0));	//Green
	}
	else if(poro[0][0][0] < 0.2)
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(0,128,0));	//Dark Green
	}
	else if(poro[0][0][0] < 0.3)
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(0,255,255));	//Cyan
	}
	else if(poro[0][0][0] < 0.4)
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(0,128,128));	//Dark Cyan
	}
	else if(poro[0][0][0] < 0.5)
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(255,0,0));	//Red
	}
	else if(poro[0][0][0] < 0.6)
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(128,0,0));	//Dark Red
	}
	else if(poro[0][0][0] < 0.7)
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(0,0,255));	//Blue
	}
	else if(poro[0][0][0] < 0.8)
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(0,0,128));	//Dark Blue
	}
	else if(poro[0][0][0] < 0.9)
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(255,255,0));	//Yellow
	}
	else if(poro[0][0][0] < 1.0)
	{
		newBrush.DeleteObject();
		newBrush.CreateSolidBrush(RGB(128,128,0));	//Dark Yellow
	}
	//************	//set On the shape color
	point1.x = setRectx;
	point1.y = setRecty;
	//************
	point2.x = setRectx + ((int) yD[0][ny-1][0] * setRectx / max) / 2;
	point2.y = setRecty - ((int) yD[0][ny-1][0] * setRecty / max) / 2;
	//************
	point3.x = setRectx + ((int) yD[0][ny-1][0] * setRectx / max) / 2 + ((int) xD[nx-1][0][0] * setRectx / max);
	point3.y = setRecty - ((int) yD[0][ny-1][0] * setRecty / max) / 2;
	//************
	point4.x = setRectx + ((int) xD[nx-1][0][0] * setRectx / max);
	point4.y = setRecty;
	//************
	pDC->SelectObject(&newPen);
	pDC->SelectObject(&newBrush);
	pDC->BeginPath();
	pDC->MoveTo(point1);
	pDC->LineTo(point2);
	pDC->LineTo(point3);
	pDC->LineTo(point4);
	pDC->LineTo(point1);
	pDC->EndPath();
	pDC->FillPath();
	//************
	point1.x = setRectx;
	first=point1.y = setRecty;
	//************
	point2.x = setRectx + ((int) xD[nx-1][0][0] * setRectx / max);
	end=point2.y = setRecty;
	//************
	point3.x = setRectx + ((int) yD[0][ny-1][0] * setRectx / max) / 2 + ((int) xD[nx-1][0][0] * setRectx / max);
	left=point3.y = setRecty - ((int) yD[0][ny-1][0] * setRecty / max) / 2;
	//************
	point4.x = point3.x;
	point4.y = left + ((int) zD[0][0][0] * setRecty / max);
	//************
	point5.x = point2.x;
	point5.y = end + ((int) zD[0][0][0] * setRecty / max);
	//************
	point6.x = point1.x;
	point6.y = first + ((int) zD[0][0][0] * setRecty / max);
	//************
	pDC->SelectObject(&newPen);
	pDC->SelectObject(&newBrush);
	pDC->BeginPath();
	pDC->MoveTo(point1);
	pDC->LineTo(point2);
	pDC->LineTo(point3);
	pDC->LineTo(point4);
	pDC->LineTo(point5);
	pDC->LineTo(point6);
	pDC->LineTo(point1);
	pDC->EndPath();
	pDC->FillPath();
	for(int i = 1;i < nz;i++)
	{
		//************
		if(poro[0][0][i] < 0.1)	//set brush color that recomanded to poro values
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(0,255,0));	//Green
		}
		else if(poro[0][0][i] < 0.2)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(0,128,0));	//Dark Green
		}
		else if(poro[0][0][i] < 0.3)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(0,255,255));	//Cyan
		}
		else if(poro[0][0][i] < 0.4)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(0,128,128));	//Dark Cyan
		}
		else if(poro[0][0][i] < 0.5)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(255,0,0));	//Red
		}
		else if(poro[0][0][i] < 0.6)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(128,0,0));	//Dark Red
		}
		else if(poro[0][0][i] < 0.7)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(0,0,255));	//Blue
		}
		else if(poro[0][0][i] < 0.8)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(0,0,128));	//Dark Blue
		}
		else if(poro[0][0][i] < 0.9)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(255,255,0));	//Yellow
		}
		else if(poro[0][0][i] < 1.0)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(128,128,0));	//Dark Yellow
		}
		//************
		point1 = point6;
		//************
		point2 = point5;
		//************
		point3 = point4;
		//************
		point4.x = point3.x;
		point4.y = left + ((int) zD[0][0][i] * setRecty / max);
		//************
		point5.x = point2.x;
		point5.y = end + ((int) zD[0][0][i] * setRecty / max);
		//************
		point6.x = point1.x;
		point6.y = first + ((int) zD[0][0][i] * setRecty / max);
		//************
		pDC->SelectObject(&newPen);
		pDC->SelectObject(&newBrush);
		pDC->BeginPath();
		pDC->MoveTo(point1);
		pDC->LineTo(point2);
		pDC->LineTo(point3);
		pDC->LineTo(point4);
		pDC->LineTo(point5);
		pDC->LineTo(point6);
		pDC->LineTo(point1);
		pDC->EndPath();
		pDC->FillPath();
	}
}

void CGassSimulation11View::OnWellDraw(CDC* pDC)
{
	CRect mainRect;
	GetClientRect(mainRect);
	mainRect.NormalizeRect();
	int setRecty = mainRect.Height()/5*2;	//Get Height of window and get 2 of 5 slid
	int setRectx = mainRect.Width()/5;	//Get Width of window and get 2 of 5 slid
	CPen newPen(PS_SOLID,1,RGB(0,0,0));
	CBrush newBrush(RGB(0,0,0));
	CPoint newStart;
	pDC->SelectObject(&newPen);
	pDC->SelectObject(&newBrush);
	int max=(int)xD[nx-1][ny-1][nz-1];	//set maximum of x,y and z for drawing
	if(yD[nx-1][ny-1][nz-1]>max)
	{
		max=(int)yD[nx-1][ny-1][nz-1];
	}
	if(zD[nx-1][ny-1][nz-1]>max)
	{
		max=(int)zD[nx-1][ny-1][nz-1];
	}
	//************
	for(k=0;k<nwell;k++)
	{
		newStart.x=setRectx + ((int)xD[XCoor[k]][0][0] * setRectx/max);
		newStart.y=setRecty - ((int)yD[0][YCoor[k]][0] * setRectx/max)/2;
		pDC->BeginPath();
		pDC->MoveTo(newStart);
		newStart.x += 10;
		pDC->LineTo(newStart);
		newStart.y -= 30;
		pDC->LineTo(newStart);
		newStart.x -= 20;
		newStart.y += 10;
		pDC->LineTo(newStart);
		newStart.x += 10;
		pDC->LineTo(newStart);
		newStart.y += 20;
		pDC->LineTo(newStart);
		pDC->EndPath();
		pDC->FillPath();
	}
}

void CGassSimulation11View::OnSimulationSetdata()
{
	// TODO: Add your command handler code here
	simulationSet = 0;
	startSimulation = 0;
	int msg;
	if(firstTime == 0)
	{
		msg = MessageBox(L"You should first make a yThick.\n Would you lik do it?",L"Error",MB_YESNO|MB_ICONQUESTION);
		if(msg == IDYES)
		{
			OnFileNew();
			if(gridMaked == 1)
			{
				if(reservoirMaked == 0)
				{
					Reservoir dlgReservoir;
					dlgReservoir.DoModal();
				}
				if(reservoirMaked == 1)
				{
					welldataflx dlgWelldata;
					if(dlgWelldata.DoModal() == IDOK)
					{
						InitialCondition dlgInitialcondition;
						if(dlgInitialcondition.DoModal() == IDOK)
						{
							NumericalMethod dlgNumericalmethod;
							if(dlgNumericalmethod.DoModal() == IDOK)
							{
								simulationSet = 1;
							}
						}
					}
				}
				if(simulationSet == 1)
				{
					CDC *pDC = GetDC();
					OnDraw(pDC);
				}
			}
		}
	}
	else
	{
		if(reservoirMaked == 0)
		{
			Reservoir dlgReservoir;
			if(dlgReservoir.DoModal()==IDOK)
			{
				welldataflx dlgWelldata;
				if(dlgWelldata.DoModal() == IDOK)
				{
					InitialCondition dlgInitialcondition;
					if(dlgInitialcondition.DoModal() == IDOK)
					{
						NumericalMethod dlgNumericalmethod;
						if(dlgNumericalmethod.DoModal() == IDOK)
						{
							simulationSet = 1;
						}
					}
				}
				if(simulationSet == 1)
				{
					CDC *pDC = GetDC();
					OnDraw(pDC);
				}
			}
		}
		else
		{
			if(wellSet == 0)
			{
				welldataflx dlgWelldata;
				if(dlgWelldata.DoModal() == IDOK)
				{
					InitialCondition dlgInitialcondition;
					if(dlgInitialcondition.DoModal() == IDOK)
					{
						NumericalMethod dlgNumericalmethod;
						if(dlgNumericalmethod.DoModal() == IDOK)
						{
							simulationSet = 1;
						}
					}
				}
			}
			else
			{
				InitialCondition dlgInitialcondition;
				if(dlgInitialcondition.DoModal() == IDOK)
				{
					NumericalMethod dlgNumericalmethod;
					if(dlgNumericalmethod.DoModal() == IDOK)
					{
						simulationSet = 1;
					}
				}
			}
			if(simulationSet == 1)
			{
				CDC *pDC = GetDC();
				OnDraw(pDC);
			}
		}
	}
	if(simulationSet == 1 && startSimulation == 1)
	{
		/*strcpy(outputTextFile,outputTextFilem);
		startZ = 0;
		endZ = nz / 2;*/
		StartSimulation();
		MessageBox(L"Simulation Don Successfully",L"Report Message",MB_OK|MB_ICONINFORMATION);
		CDC *pDC = GetDC();
		OnDraw(pDC);
	}
}

void CGassSimulation11View::OnSimulationStartsimulation()
{
	// TODO: Add your command handler code here
	if(simulationSet == 1)
	{
		StartSimulation();
		MessageBox(L"Simulation Don Successfully",L"Report Message",MB_OK|MB_ICONINFORMATION);
		startSimulation = 1;
		CDC *pDC = GetDC();
		OnDraw(pDC);
	}
	else
	{
		OnSimulationSetdata();
	}
}

void CGassSimulation11View::OnFileSetwells()
{
	// TODO: Add your command handler code here
	if(firstTime == 0)
	{
		int msg = MessageBox(L"You should first make a yThick.\n Would you lik do it?",L"Error",MB_YESNO|MB_ICONQUESTION);
		if(msg == IDYES)
		{
			OnFileNew();
			if(gridMaked == 1)
			{
				if(reservoirMaked == 0)
				{
					Reservoir dlgReservoir;
					dlgReservoir.DoModal();
				}
				if(reservoirMaked == 1)
				{
					welldataflx dlgWelldata;
					if(dlgWelldata.DoModal() == IDOK)
					{
						CDC *pDC = GetDC();
						OnDraw(pDC);
					}
				}
			}
		}
	}
	else if(reservoirMaked == 0)
	{
		Reservoir dlgReservoir;
		dlgReservoir.DoModal();
		if(reservoirMaked == 1)
		{
			welldataflx dlgWelldata;
			if(dlgWelldata.DoModal() == IDOK)
			{
				CDC *pDC = GetDC();
				OnDraw(pDC);
			}
		}
	}
	else
	{
		welldataflx dlgWelldata;
		if(dlgWelldata.DoModal() == IDOK)
		{
			CDC *pDC = GetDC();
			OnDraw(pDC);
		}
	}
}

void CGassSimulation11View::OnPressuerDraw(CDC* pDC)
{
	int r, g, b, sum;	//RGB Color
	int setRectx ,setRecty;
	this->setChartBox(&setRectx ,&setRecty);
	int max = this->getMax();
	CPoint p1, p2, p3, p4, newStartWell[10];
	CPen newPen(PS_SOLID,1,RGB(255,255,255));
	CBrush newBrush(RGB(255,255,255));	//White is default brush color
	pDC->SelectObject(&newBrush);
	p1.x = 0;
	p1.y = 0;
	p4.x = setRectx * 5;
	p4.y = setRecty * 5 / 2;
	CRect newRect(p1,p4);
	pDC->FillRect(newRect,&newBrush);
	pDC->SelectObject(&newPen);
	//****************
	newBrush.DeleteObject();
	newBrush.CreateSolidBrush(RGB(0,0,0));
	pDC->SelectObject(&newBrush);
	p1.x = setRectx / 2;
	p1.y = setRecty / 4;
	p4.x = setRectx * 3 + setRectx / 2;
	p4.y = setRecty / 2 * 4 + setRecty / 4;
	newRect.SetRect(p1,p4);
	pDC->FillRect(newRect,&newBrush);
	pDC->SelectObject(&newPen);
	for(j = 0;j < ny;j++)
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
					p1.x = setRectx + ((int)yD[0][j - 1][0] * setRectx / max ) / 2;
					p1.y = setRecty - ((int)yD[0][j - 1][0] * setRecty / max ) / 2;
				}
			}
			//**************** p2
			if(j == 0)
			{
				p2.x = setRectx + ((int)xD[i][0][0] * setRectx / max);
			}
			else
			{
				p2.x = setRectx + ((int)xD[i][0][0] * setRectx / max) + ((int)yD[0][j - 1][0] * setRectx / max ) / 2;
			}
			if(j == 0)
			{
				p2.y = setRecty;
			}
			else
			{
				p2.y = setRecty - ((int)yD[0][j - 1][0] * setRecty / max ) / 2;
			}
			//************* p4
			if(i != 0 )
			{
				p4 = p3;	//Before is calculated in p3
			}
			else
			{
				p4.x = setRectx + ((int)yD[0][j][0] * setRectx / max ) / 2;
				p4.y = setRecty - ((int)yD[0][j][0] * setRecty / max ) / 2;
			}
			//************* p3
			p3.x = setRectx + ((int)yD[0][j][0] * setRectx / max ) / 2 + ((int)xD[i][0][0] * setRectx / max);
			p3.y = setRecty - ((int)yD[0][j][0] * setRecty / max ) / 2 ;
			//Paint Grids
			if(reservoirMaked == 1)
			{
				setRGB(poro[i][j][0] * 1000 ,&r, &g, &b);
				newBrush.DeleteObject();
				newBrush.CreateSolidBrush(RGB(r,g,b));
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
			//************ set well
			if(wellSet == 1)
			{
				for(k = 0;k < nwell;k++)
				{
					if(XCoor[k] == i && YCoor[k] == j)
					{
						newStartWell[k].x = (p1.x + p2.x) / 2 - 2;	//Set x and y position values of wells
						newStartWell[k].y = (p1.y + p3.y) / 2;
					}
				}
			}
		}
	}
	//******************
	for(j = 0;j < nz;j++)
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
					p1.y = setRecty + ((int)zD[0][0][j - 1] * setRecty / max);
				}
			}
			//**************** p2
			p2.x = setRectx + ((int)xD[i][0][0] * setRectx / max);
			if(j == 0)
			{
				p2.y = setRecty;
			}
			else
			{
				p2.y = setRecty + ((int)zD[0][0][j - 1] * setRecty / max);
			}
			//************* p4
			if(i != 0)
			{
				p4 = p3;	//Before is calculated in p3
			}
			else
			{
				p4.x = setRectx;
				p4.y = setRecty + ((int)zD[0][0][j] * setRecty / max);
			}
			//************* p3
			p3.x = setRectx + ((int)xD[i][0][0] * setRectx / max);
			p3.y = setRecty + ((int)zD[0][0][j] * setRecty / max);
			//Paint Grids
			if(reservoirMaked == 1)
			{
				setRGB(poro[i][0][j] * 1000 ,&r, &g, &b);
				newBrush.DeleteObject();
				newBrush.CreateSolidBrush(RGB(r,g,b));
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
	//Draw wells
	for(k = 0;k < nwell;k++)
	{
		if(!strcmp(TypeWell_read[k],"PROD"))	//It is a Productio Well
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(0,0,255));	//Draw and Fill With Blue Coler
			pDC->SelectObject(&newBrush);
			//***********
			pDC->BeginPath();
			pDC->MoveTo(newStartWell[k]);
			//****
			newStartWell[k].x += 4;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].y -= 20;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].x += 2;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].x -= 4;
			newStartWell[k].y -= 10;
			pDC->LineTo(newStartWell[k]);
			//********
			newStartWell[k].x -= 4;
			newStartWell[k].y += 10;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].x += 2;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].y += 20;
			pDC->LineTo(newStartWell[k]);
			pDC->EndPath();
			pDC->FillPath();
		}
		else	//It is a Injection Well (WINJ)
		{
			newBrush.DeleteObject();
			newBrush.CreateSolidBrush(RGB(255,0,0));	//Draw and Fill With Red Coler
			pDC->SelectObject(&newBrush);
			//***********
			newStartWell[k].x += 2;
			pDC->BeginPath();
			pDC->MoveTo(newStartWell[k]);
			//****
			newStartWell[k].x += 4;
			newStartWell[k].y -= 10;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].x -= 2;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].y -= 20;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].x -= 4;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].y += 20;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].x -= 2;
			pDC->LineTo(newStartWell[k]);
			newStartWell[k].x += 4;
			newStartWell[k].y += 10;
			pDC->LineTo(newStartWell[k]);
			pDC->EndPath();
			pDC->FillPath();
		}
	}
	//******************
	int setRectxEnd = setRectx + ((int)xD[nx-1][0][0] * setRectx / max);
	for(j = 0;j < nz;j++)
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
					p1.y = setRecty + ((int)zD[0][0][j - 1] * setRecty / max);
				}
			}
			//**************** p2
			p2.x = setRectxEnd + ((int)yD[0][i][0] * setRectx / max) / 2;
			if(j == 0)
			{
				p2.y = setRecty - ((int)yD[0][i][0] * setRecty / max) / 2;
			}
			else
			{
				p2.y = setRecty - ((int)yD[0][i][0] * setRecty / max) / 2 + ((int)zD[0][0][j - 1] * setRecty / max);
			}
			//************* p4
			if(i != 0 )
			{
				p4 = p3;	//Before is calculated in p3
			}
			else
			{
				p4.x = setRectxEnd;
				p4.y = setRecty + ((int)zD[0][0][j] * setRecty / max);
			}
			//************* p3
			p3.x = setRectxEnd + ((int)yD[0][i][0] * setRectx / max) / 2;
			p3.y = setRecty - ((int)yD[0][i][0] * setRecty / max) / 2 + ((int)zD[0][0][j] * setRecty / max);
			//Paint Grids
			if(reservoirMaked == 1)
			{
				setRGB(poro[nx - 1][i][j] * 1000 ,&r, &g, &b);
				newBrush.DeleteObject();
				newBrush.CreateSolidBrush(RGB(r,g,b));
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
	setRectx = setRectx * 3;
	setRecty = setRecty / 2 * 4;
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
			s.Format(L"%2.1f",(double)i / 250);
			pDC->TextOutW(setRectx + 13,setRecty - 10 - i,s);
		}
	}
}

void CGassSimulation11View::setRGB(int inPut/*it is a value between 0 to 1000*/, int *r, int *g, int *b)
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

int CGassSimulation11View::getMax(void)
{
	int max=(int)xD[nx-1][ny-1][nz-1];	//set maximum of x,y and z for drawing
	if(yD[nx-1][ny-1][nz-1]>max)
	{
		max=(int)yD[nx-1][ny-1][nz-1];
	}
	if(zD[nx-1][ny-1][nz-1]>max)
	{
		max=(int)zD[nx-1][ny-1][nz-1];
	}
	return max;
}

int CGassSimulation11View::setChartBox(int *setX, int *setY)
{
	CRect mainRect;
	GetClientRect(mainRect);
	mainRect.NormalizeRect();
	*setY = mainRect.Height() / 5 * 2;	//Get Height of window and get 2 of 5 slid
	*setX = mainRect.Width() / 5;	//Get Width of window and get 2 of 5 slid
	return 0;
}

void CGassSimulation11View::OnChartsPressure()
{
	// TODO: Add your command handler code here
	if(startSimulation == 1)
	{
		Chart dlgPressurechart(3);	//Set Pressure
		dlgPressurechart.DoModal();
	}
	else
	{
		MessageBox(L"You should first do a simulation.\n Pressure isn't set",L"Warning",MB_OK|MB_ICONWARNING);
	}
}


void CGassSimulation11View::OnChartsPorosity()
{
	// TODO: Add your command handler code here
	if(reservoirMaked)
	{
		Chart dlgPressurechart(1);	//Set Porosity
		dlgPressurechart.DoModal();
	}
	else
	{
		MessageBox(L"You should first set Porosity data.\n Porosity isn't set",L"Warning",MB_OK|MB_ICONWARNING);
	}
}


void CGassSimulation11View::OnChartsPermability()
{
	// TODO: Add your command handler code here
	if(reservoirMaked)
	{
		Chart dlgPressurechart(2);	//Set permability
		dlgPressurechart.DoModal();
	}
	else
	{
		MessageBox(L"You should first set Permability data.\n Permability isn't set",L"Warning",MB_OK|MB_ICONWARNING);
	}
}


void CGassSimulation11View::OnChartsGasssaturation()
{
	// TODO: Add your command handler code here
	if(startSimulation)
	{
		Chart dlgPressurechart(4);	//Set to SG
		dlgPressurechart.DoModal();
	}
	else
	{
		MessageBox(L"You should first set Gass Saturation data.\n Gass Saturation isn't set",L"Warning",MB_OK|MB_ICONWARNING);
	}
}


void CGassSimulation11View::OnChartsWatersatu()
{
	// TODO: Add your command handler code here
	if(startSimulation)
	{
		Chart dlgPressurechart(5);	//Set to SW
		dlgPressurechart.DoModal();
	}
	else
	{
		MessageBox(L"You should first set Water Saturation data.\n Water Saturation isn't set",L"Warning",MB_OK|MB_ICONWARNING);
	}
}


void CGassSimulation11View::OnGraphPressure()
{
	// TODO: Add your command handler code here
	if(startSimulation == 1)
	{
		graph2 dlgPressuregraph(1);	//Set Pressure
		dlgPressuregraph.DoModal();
	}
	else
	{
		MessageBox(L"You should first do a simulation.\n Pressure isn't set",L"Warning",MB_OK|MB_ICONWARNING);
	}
}


void CGassSimulation11View::OnGraphGasssaturatio()
{
	// TODO: Add your command handler code here
	if(startSimulation == 1)
	{
		graph2 dlgWSaturationgraph(2);	//Set Gas Saturation
		dlgWSaturationgraph.DoModal();
	}
	else
	{
		MessageBox(L"You should first do a simulation.\n Gas Saturation isn't set",L"Warning",MB_OK|MB_ICONWARNING);
	}
}


void CGassSimulation11View::OnGraphWatersaturatio()
{
	// TODO: Add your command handler code here
	if(startSimulation == 1)
	{
		graph2 dlgGSaturationgraph(3);	//Set Water Saturation
		dlgGSaturationgraph.DoModal();
	}
	else
	{
		MessageBox(L"You should first do a simulation.\n Water Saturation isn't set",L"Warning",MB_OK|MB_ICONWARNING);
	}
}
