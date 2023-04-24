// graph.cpp : implementation file
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "graph.h"
#include "afxdialogex.h"

//External Variables
extern int nx, ny, nz, reservoirMaked, startSimulation, simulationSet, rc, tmax;
extern double poro[100][100][100], permX[100][100][100], permY[100][100][100], permZ[100][100][100], xD[100][100][100], yD[100][100][100], zD[100][100][100], p[100][100][100], SGI1[100][100][100], SWI1[100][100][100];
extern double Pinit, minPressure, pressurStepsvalue[10000][100], gasStepsvalue[10000][100], waterStepsvalue[10000][100], pminmax[2], wminmax[2], gminmax[2], dt;

// graph dialog

IMPLEMENT_DYNAMIC(graph, CDialogEx)

graph::graph(int i,CWnd* pParent /*=NULL*/)
	: CDialogEx(graph::IDD, pParent)
	, comboLayerValue(0)
{
	ok = true;
	this->PPP = i;	//set pressure ,gass saturation, or water Saturation values
}

graph::~graph()
{
}

void graph::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, comboLayer);
	DDX_CBIndex(pDX, IDC_COMBO1, comboLayerValue);
	DDX_Control(pDX, IDC_MSCHART1, graphVariable);
	DDX_Control(pDX, IDC_NTGRAPHCTRL1, ntgraphVariable);
}


BEGIN_MESSAGE_MAP(graph, CDialogEx)
	ON_BN_CLICKED(IDOK, &graph::OnBnClickedOk)
END_MESSAGE_MAP()


// graph message handlers


void graph::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ntgraphVariable.ClearGraph();
	if(this->PPP == 1)	//Means Pressure Data
	{
		ntgraphVariable.SetCaption(L"Pressure");
		ntgraphVariable.SetYLabel(L"Pressure");
	}
	else if(this->PPP == 2)	//Means Gas Saturation Data
	{
		ntgraphVariable.SetCaption(L"Gas Saturation");
		ntgraphVariable.SetYLabel(L"Gas Saturation");
	}
	else	//Means Water Saturation Data
	{
		ntgraphVariable.SetCaption(L"Water Saturation");
		ntgraphVariable.SetYLabel(L"Water Saturation");
	}

	if(this->PPP == 1)	//Means Pressure Data
	{
		ntgraphVariable.SetRange(0,tmax,pminmax[0],pminmax[1]);
	}
	else if(this->PPP == 2)	//Means Gas Saturation Data
	{
		ntgraphVariable.SetRange(0,tmax,0,1);
	}
	else	//Means Water Saturation Data
	{
		ntgraphVariable.SetRange(0,tmax,0,1);
	}

	ntgraphVariable.SetXLabel(L"Time");
	ntgraphVariable.SetElement(0);
	for(int i=0;i<rc;i++)
	{
		ntgraphVariable.PlotXY(i,i,0);
		ntgraphVariable.put_ElementXValue(i,0,i * dt);
		if(this->PPP == 1)	//Means Pressure Data
		{
			ntgraphVariable.put_ElementYValue(i,0,pressurStepsvalue[i][comboLayerValue]);
		}
		else if(this->PPP == 2)	//Means Gas Saturation Data
		{
			ntgraphVariable.put_ElementYValue(i,0,gasStepsvalue[i][comboLayerValue]);
		}
		else	//Means Water Saturation Data
		{
			ntgraphVariable.put_ElementYValue(i,0,waterStepsvalue[i][comboLayerValue]);
		}
	}
}


BOOL graph::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	for(int i = 1;i < nz + 1;i++)
	{
		CString s;
		s.Format(_T("%d"), i);
		comboLayer.AddString((LPCTSTR)s);
	}
	if(this->PPP == 1)	///PPP = 1	means Pressure
	{
		SetWindowTextW(L"Pressure");
	}
	else if(this->PPP == 2)	///PPP = 2	means Gass Saturation
	{
		SetWindowTextW(L"Gass Saturation");
	}
	else	///PPP = 3	means Water Saturation
	{
		SetWindowTextW(L"Water Saturation");
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
