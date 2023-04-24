// welldataflx.cpp : implementation file
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "welldataflx.h"
#include "afxdialogex.h"

//Extern data
extern int wellSet,i,j,k,nx,ny,nz;
extern int nwell;
extern int XCoor[100],YCoor[100],ZCoor[100];
extern double rw_read[100],	Skin_read[100], QT_read[100], QW_read[100],
	QG_read[100], Pwf_read[100], MinBHP_read[100];
extern char TypeWell_read[100][100];

// welldataflx dialog

IMPLEMENT_DYNAMIC(welldataflx, CDialogEx)

welldataflx::welldataflx(CWnd* pParent /*=NULL*/)
	: CDialogEx(welldataflx::IDD, pParent)
	, wellNumber(0)
{

}

welldataflx::~welldataflx()
{
}

void welldataflx::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSFLEXGRID1, wellData);
	DDX_CBIndex(pDX, IDC_COMBONWELL, wellNumber);
	DDX_Control(pDX, IDC_EDIT1, cellVariable);
	DDX_Control(pDX, IDC_COMBO1, cellCombo);
}


BEGIN_MESSAGE_MAP(welldataflx, CDialogEx)
	ON_BN_CLICKED(IDOK, &welldataflx::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBONWELL, &welldataflx::OnCbnSelchangeCombonwell)
	ON_CBN_KILLFOCUS(IDC_COMBO1, &welldataflx::OnCbnKillfocusCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &welldataflx::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// welldataflx message handlers


void welldataflx::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	nwell = wellNumber + 1;
	for(int i = 0;i <= wellNumber;i++)
	{
		wellData.put_Row(i + 1);
		wellData.get_RowSel();
		//***
		wellData.put_Col(1);
		wellData.get_ColSel();
		XCoor[i] = _wtoi(wellData.get_Text());
		//***
		wellData.put_Col(2);
		wellData.get_ColSel();
		YCoor[i] = _wtoi(wellData.get_Text());
		//***
		wellData.put_Col(6);
		wellData.get_ColSel();
		ZCoor[i] = _wtoi(wellData.get_Text());
		//**
		wellData.put_Col(7);
		wellData.get_ColSel();
		//strcpy_s(well[XCoor[i]][YCoor[i]][ZCoor[i]], wellData.get_Text());
		//***
		wellData.put_Col(8);
		wellData.get_ColSel();
		if(wellData.get_Text() == L"P")
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		//***
		wellData.put_Col(9);
		wellData.get_ColSel();
		QW_read[i] = _wtof(wellData.get_Text());
		//***
		wellData.put_Col(10);
		wellData.get_ColSel();
		QG_read[i] = _wtof(wellData.get_Text());
		//***
		wellData.put_Col(11);
		wellData.get_ColSel();
		Pwf_read[i] = _wtof(wellData.get_Text());
		//***
		wellData.put_Col(12);
		wellData.get_ColSel();
		rw_read[i] = _wtof(wellData.get_Text());
		//***
		wellData.put_Col(13);
		wellData.get_ColSel();
		Skin_read[i] = _wtof(wellData.get_Text());
		//***
		wellData.put_Col(14);
		wellData.get_ColSel();
		MinBHP_read[i] = _wtof(wellData.get_Text());
	}
	wellSet = 1;
	OnOK();
}


BOOL welldataflx::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	wellData.put_Row(0);
	//0,1
	wellData.put_Col(1);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"xStart");
	//0,2
	wellData.put_Col(2);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"yStart");
	//0,3
	wellData.put_Col(3);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"zStart");
	//0,4
	wellData.put_Col(4);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"xEnd");
	//0,5
	wellData.put_Col(5);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"yEnd");
	//0,6
	wellData.put_Col(6);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"zEnd");
	//0,7
	wellData.put_Col(7);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"Kind");
	//0,8
	wellData.put_Col(8);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"Type");
	//0,9
	wellData.put_Col(9);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"Qw");
	//0,10
	wellData.put_Col(10);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"Qg");
	//0,11
	wellData.put_Col(11);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"Pwf");
	//0,12
	wellData.put_Col(12);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"Rw");
	//0,13
	wellData.put_Col(13);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"Skin");
	//0,14
	wellData.put_Col(14);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"MinBHP");
	//1,0
	wellData.put_Row(1);
	wellData.put_Col(0);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"1");
	for(int i = 1;i < 3;i++)
	{
		wellData.put_Col(i);
		wellData.put_CellAlignment(4);
		wellData.put_Text(L"1");
	}
	wellData.put_Col(3);
	wellData.put_CellAlignment(4);
	CString zData;
	zData.Format(L"%d",nz / 2);
	wellData.put_Text((LPCTSTR)zData);
	//***
	for(int i = 4;i < 6;i++)
	{
		wellData.put_Col(i);
		wellData.put_CellAlignment(4);
		wellData.put_Text(L"1");
	}
	wellData.put_Col(6);
	wellData.put_CellAlignment(4);
	zData.Format(L"%d",nz / 2);
	wellData.put_Text((LPCTSTR)zData);
	//***
	wellData.put_Col(7);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"H");
	//***
	wellData.put_Col(8);
	wellData.put_CellAlignment(4);
	wellData.put_Text(L"P");
	for(int i = 9;i < 15;i++)
	{
		wellData.put_Col(i);
		wellData.put_CellAlignment(4);
		wellData.put_Text(L"0");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void welldataflx::OnCbnSelchangeCombonwell()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(wellData.get_Rows() < wellNumber + 2)	//Add Rows
	{
		int x = wellNumber + 2 - wellData.get_Rows();	//Adde Rows
		CString s;
		wellData.put_Rows(wellNumber + 2);
		for(int i = wellData.get_Rows() - x;i < wellNumber + 2;i++)
		{
			//i,0
			wellData.put_Row(i);
			wellData.put_Col(0);
			wellData.put_CellAlignment(4);
			s.Format(L"%d",i);
			wellData.put_Text((LPCTSTR)(s));
			for(int j = 1;j < 3;j++)
			{
				wellData.put_Col(j);
				wellData.put_CellAlignment(4);
				wellData.put_Text(L"1");
			}
			wellData.put_Col(3);
			wellData.put_CellAlignment(4);
			CString zData;
			zData.Format(L"%d",nz / 2);
			wellData.put_Text((LPCTSTR)zData);
			//***
			for(int j = 4;j < 6;j++)
			{
				wellData.put_Col(j);
				wellData.put_CellAlignment(4);
				wellData.put_Text(L"1");
			}
			wellData.put_Col(6);
			wellData.put_CellAlignment(4);
			zData.Format(L"%d",nz / 2);
			wellData.put_Text((LPCTSTR)zData);
			//***
			wellData.put_Col(7);
			wellData.put_CellAlignment(4);
			wellData.put_Text(L"H");
			//***
			wellData.put_Col(8);
			wellData.put_CellAlignment(4);
			wellData.put_Text(L"P");
			for(int j = 9;j < 15;j++)
			{
				wellData.put_Col(j);
				wellData.put_CellAlignment(4);
				wellData.put_Text(L"0");
			}
		}
	}
	else if(wellData.get_Rows() > wellNumber + 2)	//Delete Rows
	{
		for(int i = wellData.get_Rows() - 1;i > wellNumber + 1;i--)
		{
			//i,0
			wellData.RemoveItem(i);
		}
	}
}
BEGIN_EVENTSINK_MAP(welldataflx, CDialogEx)
	ON_EVENT(welldataflx, IDC_MSFLEXGRID1, DISPID_DBLCLICK, welldataflx::DblClickMsflexgrid1, VTS_NONE)
END_EVENTSINK_MAP()


void welldataflx::DblClickMsflexgrid1()
{
	// TODO: Add your message handler code here
	CClientDC dc(this);
	int m_pixelsperinchx=dc.GetDeviceCaps(LOGPIXELSX);
	int m_pixelsperinchy=dc.GetDeviceCaps(LOGPIXELSY);

	long left,top,w,h;
	unsigned long fore_color,back_color;
	COLORREF m_back,m_text;
	CRect r_window,r_rectedit;
	
	wellData.GetWindowRect(&r_window);
	ScreenToClient(&r_window);
	
	left=wellData.get_CellLeft();
	top=wellData.get_CellTop();
	w=wellData.get_CellWidth();
	h=wellData.get_CellHeight();
		
	r_rectedit.SetRect((int)(r_window.left+(left)*m_pixelsperinchx/1440),(int)(r_window.top+(top+15)*m_pixelsperinchy/1440),
				(int)(r_window.left+(left+w)*m_pixelsperinchx/1440),(int)(r_window.top+(top+h)*m_pixelsperinchy/1440));
	if(wellData.get_ColSel() < 9)
	{
		cellCombo.SetEditSel(0,-1);
		cellCombo.Clear();
		cellCombo.ResetContent();
		ComboSetData(wellData.get_ColSel());
		cellCombo.ModifyStyleEx(0,WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_NOPARENTNOTIFY,FALSE);
		cellCombo.ShowWindow(SW_SHOW);
		cellCombo.MoveWindow(r_rectedit,true);
		cellCombo.SetFocus();
	}
	else
	{
		cellVariable.ModifyStyleEx(0,WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_NOPARENTNOTIFY,FALSE);
		cellVariable.ShowWindow(SW_SHOW);
		cellVariable.MoveWindow(r_rectedit,true);
		cellVariable.SetSel(0,-1);
		cellVariable.Clear();
		wellData.get_ColSel();
		wellData.get_RowSel();
		cellVariable.SetWindowTextW((LPCTSTR)wellData.get_Text());
		cellVariable.SetFocus();
	}
}


void welldataflx::OnCbnKillfocusCombo1()
{
	// TODO: Add your control notification handler code here
	CString strCombo;
    wellData.get_RowSel();
    wellData.get_ColSel();
    cellCombo.GetWindowText( strCombo );
	wellData.put_Text((LPCTSTR)strCombo );
    cellCombo.ShowWindow(SW_HIDE);
}


void welldataflx::OnEnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	CString strCombo;
    wellData.get_RowSel();
    wellData.get_ColSel();
    cellVariable.GetWindowText( strCombo );
	wellData.put_Text((LPCTSTR)strCombo );
    cellVariable.ShowWindow(SW_HIDE);
}

void welldataflx::ComboSetData(int Col)
{
	CString s;
	switch (Col)
	{
	case (0 || 1):	//set nx
		{
			for(int i = 1; i <= nx;i++)
			{
				s.Format(L"%d",i);
				cellCombo.AddString((LPCTSTR)(s));
			}
			wellData.get_ColSel();
			wellData.get_RowSel();
			cellCombo.SetCurSel(_wtoi(wellData.get_Text()) - 1);
			break;
		}
	case 2:	//set ny
		{
			for(int i = 1; i <= ny;i++)
			{
				s.Format(L"%d",i);
				cellCombo.AddString((LPCTSTR)(s));
			}
			wellData.get_ColSel();
			wellData.get_RowSel();
			cellCombo.SetCurSel(_wtoi(wellData.get_Text()) - 1);
			break;
		}
	case 3:	//set nz
		{
			for(int i = nz / 2; i <= nz;i++)
			{
				s.Format(L"%d",i);
				cellCombo.AddString((LPCTSTR)(s));
			}
			wellData.get_ColSel();
			wellData.get_RowSel();
			cellCombo.SetCurSel(_wtoi(wellData.get_Text()) - nz / 2);
			break;
		}
		case 4:	//set nx
		{
			for(int i = 1; i <= nx;i++)
			{
				s.Format(L"%d",i);
				cellCombo.AddString((LPCTSTR)(s));
			}
			wellData.get_ColSel();
			wellData.get_RowSel();
			cellCombo.SetCurSel(_wtoi(wellData.get_Text()) - 1);
			break;
		}
	case 5:	//set ny
		{
			for(int i = 1; i <= ny;i++)
			{
				s.Format(L"%d",i);
				cellCombo.AddString((LPCTSTR)(s));
			}
			wellData.get_ColSel();
			wellData.get_RowSel();
			cellCombo.SetCurSel(_wtoi(wellData.get_Text()) - 1);
			break;
		}
	case 6:	//set nz
		{
			for(int i = nz / 2; i <= nz;i++)
			{
				s.Format(L"%d",i);
				cellCombo.AddString((LPCTSTR)(s));
			}
			wellData.get_ColSel();
			wellData.get_RowSel();
			cellCombo.SetCurSel(_wtoi(wellData.get_Text()) - nz / 2);
			break;
		}
	case 7:	//set well Kind
		{
			s.Format(L"H");
			cellCombo.AddString((LPCTSTR)(s));
			s.Format(L"V");
			cellCombo.AddString((LPCTSTR)(s));
			wellData.get_ColSel();
			wellData.get_RowSel();
			if(wellData.get_Text() == L"H")
			{
				cellCombo.SetCurSel(0);
			}
			else
			{
				cellCombo.SetCurSel(1);
			}
			break;
		}
	case 8:	//set well Type
		{
			s.Format(L"P");
			cellCombo.AddString((LPCTSTR)(s));
			s.Format(L"I");
			cellCombo.AddString((LPCTSTR)(s));
			wellData.get_ColSel();
			wellData.get_RowSel();
			if(wellData.get_Text() == L"P")
			{
				cellCombo.SetCurSel(0);
			}
			else
			{
				cellCombo.SetCurSel(1);
			}
			break;
		}
	}
}
