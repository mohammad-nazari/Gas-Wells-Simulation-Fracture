// Value.cpp : implementation file
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "Value.h"
#include "afxdialogex.h"

//External Variables
extern int nx, ny, nz, reservoirMaked, startSimulation, simulationSet;
extern double poro[100][100][100], permX[100][100][100], permY[100][100][100], permZ[100][100][100], xD[100][100][100], yD[100][100][100], zD[100][100][100], pChart[4][100][100][100], SGI1Chart[4][100][100][100], SWI1Chart[4][100][100][100];
extern double Pinit, minPressure;
// Value dialog

IMPLEMENT_DYNAMIC(Value, CDialogEx)

Value::Value(int from, int to, int i,int k,int s, CWnd* pParent /*=NULL*/)
	: CDialogEx(Value::IDD, pParent)
	, comboLayerNo(0)
	, fromZ(0)
	, toZ(0)
{
	this->fromZ = from;
	this->toZ = to;
	this->PPP = i;	//set porosity, permability or pressure values
	this->permType = k;	//Set perm Type (X, Y, Z)
	this->stepValue = s; //Set Step Value
}

Value::~Value()
{
}

void Value::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSFLEXGRID1, flexGridPressure);
	DDX_Control(pDX, IDC_COMBO1, comboLayer);
	DDX_CBIndex(pDX, IDC_COMBO1, comboLayerNo);
}


BEGIN_MESSAGE_MAP(Value, CDialogEx)
	ON_BN_CLICKED(IDOK, &Value::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Value::OnBnClickedCancel)
END_MESSAGE_MAP()


// Value message handlers


void Value::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString s;
	if(this->PPP == 1)	//Means poro
	{
		for(int j = 0;j < ny;j++)
		{
			for(int i = 0;i < nx;i++)
			{
				flexGridPressure.put_Col(i + 1);
				flexGridPressure.put_Row(j + 1);
				s.Format(L"%8.4f",poro[i][j][this->comboLayerNo]);
				flexGridPressure.put_Text((LPCTSTR)s);
			}
		}
	}
	else if(this->PPP == 2)	//Means perm
	{
		if(this->permType == 0)	//Means PermX
		{
			for(int j = 0;j < ny;j++)
			{
				for(int i = 0;i < nx;i++)
				{
					flexGridPressure.put_Col(i + 1);
					flexGridPressure.put_Row(j + 1);
					s.Format(L"%8.4f",permX[i][j][this->comboLayerNo]);
					flexGridPressure.put_Text((LPCTSTR)s);
				}
			}
		}
		else if(this->permType == 1)	//Means PermY
		{
			for(int j = 0;j < ny;j++)
			{
				for(int i = 0;i < nx;i++)
				{
					flexGridPressure.put_Col(i + 1);
					flexGridPressure.put_Row(j + 1);
					s.Format(L"%8.4f",permY[i][j][this->comboLayerNo]);
					flexGridPressure.put_Text((LPCTSTR)s);
				}
			}
		}
		else	//Means PermZ
		{
			for(int j = 0;j < ny;j++)
			{
				for(int i = 0;i < nx;i++)
				{
					flexGridPressure.put_Col(i + 1);
					flexGridPressure.put_Row(j + 1);
					s.Format(L"%8.4f",permZ[i][j][this->comboLayerNo]);
					flexGridPressure.put_Text((LPCTSTR)s);
				}
			}
		}
	}
	else if(this->PPP == 3)	//Means pressure
	{
		for(int j = 0;j < ny;j++)
		{
			for(int i = 0;i < nx;i++)
			{
				flexGridPressure.put_Col(i + 1);
				flexGridPressure.put_Row(j + 1);
				s.Format(L"%8.4f",pChart[this->stepValue][i][j][this->comboLayerNo]);
				flexGridPressure.put_Text((LPCTSTR)s);
			}
		}
	}
	else if(this->PPP == 4)	//Means Gass Saturation
	{
		for(int j = 0;j < ny;j++)
		{
			for(int i = 0;i < nx;i++)
			{
				flexGridPressure.put_Col(i + 1);
				flexGridPressure.put_Row(j + 1);
				s.Format(L"%8.4f",SGI1Chart[this->stepValue][i][j][this->comboLayerNo]);
				flexGridPressure.put_Text((LPCTSTR)s);
			}
		}
	}
	else	//Means Water Saturation
	{
		for(int j = 0;j < ny;j++)
		{
			for(int i = 0;i < nx;i++)
			{
				flexGridPressure.put_Col(i + 1);
				flexGridPressure.put_Row(j + 1);
				s.Format(L"%8.4f",SWI1Chart[this->stepValue][i][j][this->comboLayerNo]);
				flexGridPressure.put_Text((LPCTSTR)s);
			}
		}
	}
}


void Value::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL Value::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->swap();
	// TODO:  Add extra initialization here
	for(int i = this->fromZ + 1;i < this->toZ + 2;i++)
	{
		CString s;
		s.Format(_T("%d"), i);
		this->comboLayer.AddString((LPCTSTR)s);
	}
	flexGridPressure.put_Cols(nx + 1);
	flexGridPressure.put_Rows(ny + 1);
	for(int i = 0;i < nx + 1;i++)
	{
		flexGridPressure.put_ColAlignment(i,flexGridPressure.flexAlignCenterCenter);
	}
	CString s;
	for(int i = 1;i < nx + 1;i++)
	{
		flexGridPressure.put_Col(i);
		flexGridPressure.put_Row(0);
		s.Format(L"%d",i);
		flexGridPressure.put_Text((LPCTSTR)s);
	}
	for(int j = 1;j < ny + 1;j++)
	{
		flexGridPressure.put_Col(0);
		flexGridPressure.put_Row(j);
		s.Format(L"%d",j);
		flexGridPressure.put_Text((LPCTSTR)s);
	}

	if(this->PPP == 1)	///PPP = 1	means Porosity
	{
		SetWindowTextW(L"Porosity");
	}
	else if(this->PPP == 2)	///PPP = 2	means Permability
	{
		SetWindowTextW(L"Permability");
	}
	else if(this->PPP == 3)	///PPP = 3	means Pressure
	{
		SetWindowTextW(L"Pressure");
	}
	else if(this->PPP == 4)	///PPP = 4	means Gass Saturation
	{
		SetWindowTextW(L"Gass Saturation");
	}
	else	///PPP = 5	means Water Saturation
	{
		SetWindowTextW(L"Water Saturation");
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


int Value::swap()
{
	if(this->fromZ > this->toZ)
	{
		int temp;
		temp = this->fromZ;
		this->fromZ = this->toZ;
		this->toZ = temp;
	}
	return 0;
}
