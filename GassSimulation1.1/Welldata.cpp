// Welldata.cpp : implementation file
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "Welldata.h"


// Welldata dialog
//external variables
extern int wellSet,i,j,k,nx,ny,nz;
extern int nwell;
extern int XCoor[100],YCoor[100],ZCoor[100];
extern double rw_read[100],	Skin_read[100], QT_read[100], QW_read[100],
	QG_read[100], Pwf_read[100], MinBHP_read[100];
extern char TypeWell_read[100][100];

IMPLEMENT_DYNAMIC(Welldata, CDialog)

Welldata::Welldata(CWnd* pParent /*=NULL*/)
	: CDialog(Welldata::IDD, pParent)
	, textNwell(0)
	, textWelldata(_T(""))
	, comboNwell(0)
	, Nwell(0)
	, comboXwell1(0)
	, comboXwell2(0)
	, comboXwell3(0)
	, comboXwell4(0)
	, comboXwell5(0)
	, comboXwell6(0)
	, comboXwell7(0)
	, comboXwell8(0)
	, comboXwell9(0)
	, comboXwell10(0)
	, comboYwell1(0)
	, comboYwell2(0)
	, comboYwell3(0)
	, comboYwell4(0)
	, comboYwell5(0)
	, comboYwell6(0)
	, comboYwell7(0)
	, comboYwell8(0)
	, comboYwell9(0)
	, comboYwell10(0)
	, comboZwell10(0)
	, comboZwell9(0)
	, comboZwell8(0)
	, comboZwell7(0)
	, comboZwell6(0)
	, comboZwell5(0)
	, comboZwell4(0)
	, comboZwell3(0)
	, comboZwell2(0)
	, comboZwell1(0)
	, comboKind1(0)
	, comboKind2(0)
	, comboKind3(0)
	, comboKind4(0)
	, comboKind5(0)
	, comboKind6(0)
	, comboKind7(0)
	, comboKind8(0)
	, comboKind9(0)
	, comboKind10(0)
	, comboType1(0)
	, comboType2(0)
	, comboType3(0)
	, comboType4(0)
	, comboType5(0)
	, comboType6(0)
	, comboType7(0)
	, comboType8(0)
	, comboType9(0)
	, comboType10(0)
	, Qw10(0)
	, Qw9(0)
	, Qw8(0)
	, Qw7(0)
	, Qw6(0)
	, Qw5(0)
	, Qw4(0)
	, Qw3(0)
	, Qw2(0)
	, Qw1(0)
	, Qg1(0)
	, Qg2(0)
	, Qg3(0)
	, Qg4(0)
	, Qg5(0)
	, Qg6(0)
	, Qg7(0)
	, Qg8(0)
	, Qg9(0)
	, Qg10(0)
	, Pwf10(0)
	, Pwf9(0)
	, Pwf8(0)
	, Pwf7(0)
	, Pwf6(0)
	, Pwf5(0)
	, Pwf4(0)
	, Pwf3(0)
	, Pwf2(0)
	, Pwf1(0)
	, Rw1(0)
	, Rw2(0)
	, Rw3(0)
	, Rw4(0)
	, Rw5(0)
	, Rw6(0)
	, Rw7(0)
	, Rw8(0)
	, Rw9(0)
	, Rw10(0)
	, Skin1(0)
	, Skin2(0)
	, Skin3(0)
	, Skin4(0)
	, Skin5(0)
	, Skin6(0)
	, Skin7(0)
	, Skin8(0)
	, Skin9(0)
	, Skin10(0)
	, minBhp1(0)
	, minBhp2(0)
	, minBhp3(0)
	, minBhp4(0)
	, minBhp5(0)
	, minBhp6(0)
	, minBhp7(0)
	, minBhp8(0)
	, minBhp9(0)
	, minBhp10(0)
	{

}

Welldata::~Welldata()
{
}

void Welldata::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBONWELL, Nwell);
	DDX_CBIndex(pDX, IDC_COMBOXWELL1, comboXwell1);
	DDX_CBIndex(pDX, IDC_COMBOXWELL2, comboXwell2);
	DDX_CBIndex(pDX, IDC_COMBOXWELL3, comboXwell3);
	DDX_CBIndex(pDX, IDC_COMBOXWELL4, comboXwell4);
	DDX_CBIndex(pDX, IDC_COMBOXWELL5, comboXwell5);
	DDX_CBIndex(pDX, IDC_COMBOXWELL6, comboXwell6);
	DDX_CBIndex(pDX, IDC_COMBOXWELL7, comboXwell7);
	DDX_CBIndex(pDX, IDC_COMBOXWELL8, comboXwell8);
	DDX_CBIndex(pDX, IDC_COMBOXWELL9, comboXwell9);
	DDX_CBIndex(pDX, IDC_COMBOXWELL10, comboXwell10);
	DDX_CBIndex(pDX, IDC_COMBOYWELL1, comboYwell1);
	DDX_CBIndex(pDX, IDC_COMBOYWELL2, comboYwell2);
	DDX_CBIndex(pDX, IDC_COMBOYWELL3, comboYwell3);
	DDX_CBIndex(pDX, IDC_COMBOYWELL4, comboYwell4);
	DDX_CBIndex(pDX, IDC_COMBOYWELL5, comboYwell5);
	DDX_CBIndex(pDX, IDC_COMBOYWELL6, comboYwell6);
	DDX_CBIndex(pDX, IDC_COMBOYWELL7, comboYwell7);
	DDX_CBIndex(pDX, IDC_COMBOYWELL8, comboYwell8);
	DDX_CBIndex(pDX, IDC_COMBOYWELL9, comboYwell9);
	DDX_CBIndex(pDX, IDC_COMBOYWELL10, comboYwell10);
	DDX_CBIndex(pDX, IDC_COMBOZWELL10, comboZwell10);
	DDX_CBIndex(pDX, IDC_COMBOZWELL9, comboZwell9);
	DDX_CBIndex(pDX, IDC_COMBOZWELL8, comboZwell8);
	DDX_CBIndex(pDX, IDC_COMBOZWELL7, comboZwell7);
	DDX_CBIndex(pDX, IDC_COMBOZWELL6, comboZwell6);
	DDX_CBIndex(pDX, IDC_COMBOZWELL5, comboZwell5);
	DDX_CBIndex(pDX, IDC_COMBOZWELL4, comboZwell4);
	DDX_CBIndex(pDX, IDC_COMBOZWELL3, comboZwell3);
	DDX_CBIndex(pDX, IDC_COMBOZWELL2, comboZwell2);
	DDX_CBIndex(pDX, IDC_COMBOZWELL1, comboZwell1);
	DDX_CBIndex(pDX, IDC_COMBOKIND1, comboKind1);
	DDX_CBIndex(pDX, IDC_COMBOKIND2, comboKind2);
	DDX_CBIndex(pDX, IDC_COMBOKIND3, comboKind3);
	DDX_CBIndex(pDX, IDC_COMBOKIND4, comboKind4);
	DDX_CBIndex(pDX, IDC_COMBOKIND5, comboKind5);
	DDX_CBIndex(pDX, IDC_COMBOKIND6, comboKind6);
	DDX_CBIndex(pDX, IDC_COMBOKIND7, comboKind7);
	DDX_CBIndex(pDX, IDC_COMBOKIND8, comboKind8);
	DDX_CBIndex(pDX, IDC_COMBOKIND9, comboKind9);
	DDX_CBIndex(pDX, IDC_COMBOKIND10, comboKind10);
	DDX_CBIndex(pDX, IDC_COMBOTYPE1, comboType1);
	DDX_CBIndex(pDX, IDC_COMBOTYPE2, comboType2);
	DDX_CBIndex(pDX, IDC_COMBOTYPE3, comboType3);
	DDX_CBIndex(pDX, IDC_COMBOTYPE4, comboType4);
	DDX_CBIndex(pDX, IDC_COMBOTYPE5, comboType5);
	DDX_CBIndex(pDX, IDC_COMBOTYPE6, comboType6);
	DDX_CBIndex(pDX, IDC_COMBOTYPE7, comboType7);
	DDX_CBIndex(pDX, IDC_COMBOTYPE8, comboType8);
	DDX_CBIndex(pDX, IDC_COMBOTYPE9, comboType9);
	DDX_CBIndex(pDX, IDC_COMBOTYPE10, comboType10);
	DDX_Text(pDX, IDC_EDITQW10, Qw10);
	DDX_Text(pDX, IDC_EDITQW9, Qw9);
	DDX_Text(pDX, IDC_EDITQW8, Qw8);
	DDX_Text(pDX, IDC_EDITQW7, Qw7);
	DDX_Text(pDX, IDC_EDITQW6, Qw6);
	DDX_Text(pDX, IDC_EDITQW5, Qw5);
	DDX_Text(pDX, IDC_EDITQW4, Qw4);
	DDX_Text(pDX, IDC_EDITQW3, Qw3);
	DDX_Text(pDX, IDC_EDITQW2, Qw2);
	DDX_Text(pDX, IDC_EDITQW1, Qw1);
	DDX_Text(pDX, IDC_EDITQG1, Qg1);
	DDX_Text(pDX, IDC_EDITQG2, Qg2);
	DDX_Text(pDX, IDC_EDITQG3, Qg3);
	DDX_Text(pDX, IDC_EDITQG4, Qg4);
	DDX_Text(pDX, IDC_EDITQG5, Qg5);
	DDX_Text(pDX, IDC_EDITQG6, Qg6);
	DDX_Text(pDX, IDC_EDITQG7, Qg7);
	DDX_Text(pDX, IDC_EDITQG8, Qg8);
	DDX_Text(pDX, IDC_EDITQG9, Qg9);
	DDX_Text(pDX, IDC_EDITQG10, Qg10);
	DDX_Text(pDX, IDC_EDITPWF10, Pwf10);
	DDX_Text(pDX, IDC_EDITPWF9, Pwf9);
	DDX_Text(pDX, IDC_EDITPWF8, Pwf8);
	DDX_Text(pDX, IDC_EDITPWF7, Pwf7);
	DDX_Text(pDX, IDC_EDITPWF6, Pwf6);
	DDX_Text(pDX, IDC_EDITPWF5, Pwf5);
	DDX_Text(pDX, IDC_EDITPWF4, Pwf4);
	DDX_Text(pDX, IDC_EDITPWF3, Pwf3);
	DDX_Text(pDX, IDC_EDITPWF2, Pwf2);
	DDX_Text(pDX, IDC_EDITPWF1, Pwf1);
	DDX_Text(pDX, IDC_EDITRW1, Rw1);
	DDX_Text(pDX, IDC_EDITRW2, Rw2);
	DDX_Text(pDX, IDC_EDITRW3, Rw3);
	DDX_Text(pDX, IDC_EDITRW4, Rw4);
	DDX_Text(pDX, IDC_EDITRW5, Rw5);
	DDX_Text(pDX, IDC_EDITRW6, Rw6);
	DDX_Text(pDX, IDC_EDITRW7, Rw7);
	DDX_Text(pDX, IDC_EDITRW8, Rw8);
	DDX_Text(pDX, IDC_EDITRW9, Rw9);
	DDX_Text(pDX, IDC_EDITRW10, Rw10);
	DDX_Text(pDX, IDC_EDITSKIN1, Skin1);
	DDX_Text(pDX, IDC_EDITSKIN2, Skin2);
	DDX_Text(pDX, IDC_EDITSKIN3, Skin3);
	DDX_Text(pDX, IDC_EDITSKIN4, Skin4);
	DDX_Text(pDX, IDC_EDITSKIN5, Skin5);
	DDX_Text(pDX, IDC_EDITSKIN6, Skin6);
	DDX_Text(pDX, IDC_EDITSKIN7, Skin7);
	DDX_Text(pDX, IDC_EDITSKIN8, Skin8);
	DDX_Text(pDX, IDC_EDITSKIN9, Skin9);
	DDX_Text(pDX, IDC_EDITSKIN10, Skin10);
	DDX_Text(pDX, IDC_EDITMINBHP1, minBhp1);
	DDX_Text(pDX, IDC_EDITMINBHP2, minBhp2);
	DDX_Text(pDX, IDC_EDITMINBHP3, minBhp3);
	DDX_Text(pDX, IDC_EDITMINBHP4, minBhp4);
	DDX_Text(pDX, IDC_EDITMINBHP5, minBhp5);
	DDX_Text(pDX, IDC_EDITMINBHP6, minBhp6);
	DDX_Text(pDX, IDC_EDITMINBHP7, minBhp7);
	DDX_Text(pDX, IDC_EDITMINBHP8, minBhp8);
	DDX_Text(pDX, IDC_EDITMINBHP9, minBhp9);
	DDX_Text(pDX, IDC_EDITMINBHP10, minBhp10);
	DDX_Control(pDX, IDC_COMBOXWELL1, comboNx1);
	DDX_Control(pDX, IDC_COMBOXWELL2, comboNx2);
	DDX_Control(pDX, IDC_COMBOXWELL3, comboNx3);
	DDX_Control(pDX, IDC_COMBOXWELL4, comboNx4);
	DDX_Control(pDX, IDC_COMBOXWELL5, comboNx5);
	DDX_Control(pDX, IDC_COMBOXWELL6, comboNx6);
	DDX_Control(pDX, IDC_COMBOXWELL7, comboNx7);
	DDX_Control(pDX, IDC_COMBOXWELL8, comboNx8);
	DDX_Control(pDX, IDC_COMBOXWELL9, comboNx9);
	DDX_Control(pDX, IDC_COMBOXWELL10, comboNx10);
	DDX_Control(pDX, IDC_COMBOYWELL1, comboNy1);
	DDX_Control(pDX, IDC_COMBOYWELL2, comboNy2);
	DDX_Control(pDX, IDC_COMBOYWELL3, comboNy3);
	DDX_Control(pDX, IDC_COMBOYWELL4, comboNy4);
	DDX_Control(pDX, IDC_COMBOYWELL5, comboNy5);
	DDX_Control(pDX, IDC_COMBOYWELL6, comboNy6);
	DDX_Control(pDX, IDC_COMBOYWELL7, comboNy7);
	DDX_Control(pDX, IDC_COMBOYWELL8, comboNy8);
	DDX_Control(pDX, IDC_COMBOYWELL9, comboNy9);
	DDX_Control(pDX, IDC_COMBOYWELL10, comboNy10);
	DDX_Control(pDX, IDC_COMBOZWELL1, comboNz1);
	DDX_Control(pDX, IDC_COMBOZWELL2, comboNz2);
	DDX_Control(pDX, IDC_COMBOZWELL3, comboNz3);
	DDX_Control(pDX, IDC_COMBOZWELL4, comboNz4);
	DDX_Control(pDX, IDC_COMBOZWELL5, comboNz5);
	DDX_Control(pDX, IDC_COMBOZWELL6, comboNz6);
	DDX_Control(pDX, IDC_COMBOZWELL7, comboNz7);
	DDX_Control(pDX, IDC_COMBOZWELL8, comboNz8);
	DDX_Control(pDX, IDC_COMBOZWELL9, comboNz9);
	DDX_Control(pDX, IDC_COMBOZWELL10, comboNz10);
}

BEGIN_MESSAGE_MAP(Welldata, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &Welldata::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &Welldata::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Welldata::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBONWELL, &Welldata::OnCbnSelchangeCombonwell)
END_MESSAGE_MAP()


// Welldata message handlers

void Welldata::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textWelldata = file.GetPathName();
		UpdateData(false);
	}
}

void Welldata::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = 0;
	nwell = Nwell+1;
	XCoor[i]=comboXwell1;
	YCoor[i]=comboYwell1;
	ZCoor[i]=comboZwell1 + nz / 2;	//It is should be in FRACTURE Layer
	if(comboKind1==0)
	{
		//well[comboXwell1][comboYwell1][comboZwell1] = 'h';
	}
	else
	{
		//well[comboXwell1][comboYwell1][comboZwell1] = 'v';
	}
	if(comboType1==0)
	{
		strcpy_s(TypeWell_read[i], "PROD");
		_strupr_s(TypeWell_read[i]);
	}
	else
	{
		strcpy_s(TypeWell_read[i], "WINJ");
		_strupr_s(TypeWell_read[i]);
	}
	QW_read[i] = Qw1;
	QG_read[i] = Qg1;
	Pwf_read[i] = Pwf1;
	rw_read[i] = Rw1;
	Skin_read[i] = Skin1;
	MinBHP_read[i] = minBhp1;
	i++;
	if(Nwell > 0)
	{
		XCoor[i]=comboXwell2;
		YCoor[i]=comboYwell2;
		ZCoor[i]=comboZwell2 + nz / 2;	//It is should be in FRACTURE Layer
		if(comboKind2==0)
		{
			//well[comboXwell2][comboYwell2][comboZwell2] = 'h';
		}
		else
		{
			//well[comboXwell][comboYwell2][comboZwell2] = 'v';
		}
		if(comboType2==0)
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		QW_read[i] = Qw2;
		QG_read[i] = Qg2;
		Pwf_read[i] = Pwf2;
		rw_read[i] = Rw2;
		Skin_read[i] = Skin2;
		MinBHP_read[i] = minBhp2;
		i++;
	}
	if(Nwell > 1)
	{
		XCoor[i]=comboXwell3;
		YCoor[i]=comboYwell3;
		ZCoor[i]=comboZwell3 + nz / 2;	//It is should be in FRACTURE Layer
		if(comboKind3==0)
		{
			//well[comboXwell3][comboYwell1][comboZwell1] = 'h';
		}
		else
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'v';
		}
		if(comboType3==0)
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		QW_read[i] = Qw3;
		QG_read[i] = Qg3;
		Pwf_read[i] = Pwf3;
		rw_read[i] = Rw3;
		Skin_read[i] = Skin3;
		MinBHP_read[i] = minBhp3;
		i++;
	}
	if(Nwell > 2)
	{
		XCoor[i]=comboXwell4;
		YCoor[i]=comboYwell4;
		ZCoor[i]=comboZwell4 + nz / 2;	//It is should be in FRACTURE Layer
		if(comboKind4==0)
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'h';
		}
		else
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'v';
		}
		if(comboType4==0)
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		QW_read[i] = Qw4;
		QG_read[i] = Qg4;
		Pwf_read[i] = Pwf4;
		rw_read[i] = Rw4;
		Skin_read[i] = Skin4;
		MinBHP_read[i] = minBhp4;
		i++;
	}
	if(Nwell > 3)
	{
		XCoor[i]=comboXwell5;
		YCoor[i]=comboYwell5;
		ZCoor[i]=comboZwell5 + nz / 2;	//It is should be in FRACTURE Layer
		if(comboKind5==0)
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'h';
		}
		else
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'v';
		}
		if(comboType5==0)
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		QW_read[i] = Qw5;
		QG_read[i] = Qg5;
		Pwf_read[i] = Pwf5;
		rw_read[i] = Rw5;
		Skin_read[i] = Skin5;
		MinBHP_read[i] = minBhp5;
		i++;
	}
	if(Nwell > 4)
	{
		XCoor[i]=comboXwell6;
		YCoor[i]=comboYwell6;
		ZCoor[i]=comboZwell6 + nz / 2;	//It is should be in FRACTURE Layer
		if(comboKind6==0)
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'h';
		}
		else
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'v';
		}
		if(comboType6==0)
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		QW_read[i] = Qw6;
		QG_read[i] = Qg6;
		Pwf_read[i] = Pwf6;
		rw_read[i] = Rw6;
		Skin_read[i] = Skin6;
		MinBHP_read[i] = minBhp6;
		i++;
	}
	if(Nwell > 5)
	{
		XCoor[i]=comboXwell7;
		YCoor[i]=comboYwell7;
		ZCoor[i]=comboZwell7 + nz / 2;	//It is should be in FRACTURE Layer
		if(comboKind7==0)
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'h';
		}
		else
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'v';
		}
		if(comboType7==0)
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		QW_read[i] = Qw7;
		QG_read[i] = Qg7;
		Pwf_read[i] = Pwf7;
		rw_read[i] = Rw7;
		Skin_read[i] = Skin7;
		MinBHP_read[i] = minBhp7;
		i++;
	}
	if(Nwell > 6)
	{
		XCoor[i]=comboXwell8;
		YCoor[i]=comboYwell8;
		ZCoor[i]=comboZwell8 + nz / 2;	//It is should be in FRACTURE Layer
		if(comboKind8==0)
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'h';
		}
		else
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'v';
		}
		if(comboType8==0)
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		QW_read[i] = Qw8;
		QG_read[i] = Qg8;
		Pwf_read[i] = Pwf8;
		rw_read[i] = Rw8;
		Skin_read[i] = Skin8;
		MinBHP_read[i] = minBhp8;
		i++;
	}
	if(Nwell > 7)
	{
		XCoor[i]=comboXwell9;
		YCoor[i]=comboYwell9;
		ZCoor[i]=comboZwell9 + nz / 2;	//It is should be in FRACTURE Layer
		if(comboKind9==0)
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'h';
		}
		else
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'v';
		}
		if(comboType9==0)
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		QW_read[i] = Qw9;
		QG_read[i] = Qg9;
		Pwf_read[i] = Pwf9;
		rw_read[i] = Rw9;
		Skin_read[i] = Skin9;
		MinBHP_read[i] = minBhp9;
		i++;
	}
	if(Nwell > 8)
	{
		XCoor[i]=comboXwell10;
		YCoor[i]=comboYwell10;
		ZCoor[i]=comboZwell10 + nz / 2;	//It is should be in FRACTURE Layer
		if(comboKind10==0)
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'h';
		}
		else
		{
			//well[comboXwell1][comboYwell1][comboZwell1] = 'v';
		}
		if(comboType10==0)
		{
			strcpy_s(TypeWell_read[i], "PROD");
			_strupr_s(TypeWell_read[i]);
		}
		else
		{
			strcpy_s(TypeWell_read[i], "WINJ");
			_strupr_s(TypeWell_read[i]);
		}
		QW_read[i] = Qw10;
		QG_read[i] = Qg10;
		Pwf_read[i] = Pwf10;
		rw_read[i] = Rw10;
		Skin_read[i] = Skin10;
		MinBHP_read[i] = minBhp10;
		i++;
	}
	wellSet = 1;
	OnOK();
}

void Welldata::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void Welldata::OnCbnSelchangeCombonwell()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(Nwell>0)
	{
		GetDlgItem(IDC_COMBOXWELL2)->EnableWindow(true);
		GetDlgItem(IDC_COMBOYWELL2)->EnableWindow(true);
		GetDlgItem(IDC_COMBOZWELL2)->EnableWindow(true);
		GetDlgItem(IDC_COMBOKIND2)->EnableWindow(true);
		GetDlgItem(IDC_COMBOTYPE2)->EnableWindow(true);
		GetDlgItem(IDC_EDITQW2)->EnableWindow(true);
		GetDlgItem(IDC_EDITQG2)->EnableWindow(true);
		GetDlgItem(IDC_EDITPWF2)->EnableWindow(true);
		GetDlgItem(IDC_EDITRW2)->EnableWindow(true);
		GetDlgItem(IDC_EDITSKIN2)->EnableWindow(true);
		GetDlgItem(IDC_EDITMINBHP2)->EnableWindow(true);
		//Initial combobox of First Well from 1 to nx, ny and nz
		CString s;
		for(int i = 1;i < nx + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNx2.AddString((LPCTSTR)s);
		}
		for(int i = 1;i < ny + 1;i++)
		{
			s.Format(_T("%d"), i);
			comboNy2.AddString((LPCTSTR)s);
		}
		for(int i = nz/2 + 1;i < nz + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNz2.AddString((LPCTSTR)s);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBOXWELL2)->EnableWindow(false);
		GetDlgItem(IDC_COMBOYWELL2)->EnableWindow(false);
		GetDlgItem(IDC_COMBOZWELL2)->EnableWindow(false);
		GetDlgItem(IDC_COMBOKIND2)->EnableWindow(false);
		GetDlgItem(IDC_COMBOTYPE2)->EnableWindow(false);
		GetDlgItem(IDC_EDITQW2)->EnableWindow(false);
		GetDlgItem(IDC_EDITQG2)->EnableWindow(false);
		GetDlgItem(IDC_EDITPWF2)->EnableWindow(false);
		GetDlgItem(IDC_EDITRW2)->EnableWindow(false);
		GetDlgItem(IDC_EDITSKIN2)->EnableWindow(false);
		GetDlgItem(IDC_EDITMINBHP2)->EnableWindow(false);
	}
	if(Nwell>1)
	{
		GetDlgItem(IDC_COMBOXWELL3)->EnableWindow(true);
		GetDlgItem(IDC_COMBOYWELL3)->EnableWindow(true);
		GetDlgItem(IDC_COMBOZWELL3)->EnableWindow(true);
		GetDlgItem(IDC_COMBOKIND3)->EnableWindow(true);
		GetDlgItem(IDC_COMBOTYPE3)->EnableWindow(true);
		GetDlgItem(IDC_EDITQW3)->EnableWindow(true);
		GetDlgItem(IDC_EDITQG3)->EnableWindow(true);
		GetDlgItem(IDC_EDITPWF3)->EnableWindow(true);
		GetDlgItem(IDC_EDITRW3)->EnableWindow(true);
		GetDlgItem(IDC_EDITSKIN3)->EnableWindow(true);
		GetDlgItem(IDC_EDITMINBHP3)->EnableWindow(true);
		//Initial combobox of First Well from 1 to nx, ny and nz
		CString s;
		for(int i = 1;i < nx + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNx3.AddString((LPCTSTR)s);
		}
		for(int i = 1;i < ny + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNy3.AddString((LPCTSTR)s);
		}
		for(int i = nz/2 + 1;i < nz + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNz3.AddString((LPCTSTR)s);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBOXWELL3)->EnableWindow(false);
		GetDlgItem(IDC_COMBOYWELL3)->EnableWindow(false);
		GetDlgItem(IDC_COMBOZWELL3)->EnableWindow(false);
		GetDlgItem(IDC_COMBOKIND3)->EnableWindow(false);
		GetDlgItem(IDC_COMBOTYPE3)->EnableWindow(false);
		GetDlgItem(IDC_EDITQW3)->EnableWindow(false);
		GetDlgItem(IDC_EDITQG3)->EnableWindow(false);
		GetDlgItem(IDC_EDITPWF3)->EnableWindow(false);
		GetDlgItem(IDC_EDITRW3)->EnableWindow(false);
		GetDlgItem(IDC_EDITSKIN3)->EnableWindow(false);
		GetDlgItem(IDC_EDITMINBHP3)->EnableWindow(false);
	}
	if(Nwell>2)
	{
		GetDlgItem(IDC_COMBOXWELL4)->EnableWindow(true);
		GetDlgItem(IDC_COMBOYWELL4)->EnableWindow(true);
		GetDlgItem(IDC_COMBOZWELL4)->EnableWindow(true);
		GetDlgItem(IDC_COMBOKIND4)->EnableWindow(true);
		GetDlgItem(IDC_COMBOTYPE4)->EnableWindow(true);
		GetDlgItem(IDC_EDITQW4)->EnableWindow(true);
		GetDlgItem(IDC_EDITQG4)->EnableWindow(true);
		GetDlgItem(IDC_EDITPWF4)->EnableWindow(true);
		GetDlgItem(IDC_EDITRW4)->EnableWindow(true);
		GetDlgItem(IDC_EDITSKIN4)->EnableWindow(true);
		GetDlgItem(IDC_EDITMINBHP4)->EnableWindow(true);
		//Initial combobox of First Well from 1 to nx, ny and nz
		CString s;
		for(int i = 1;i < nx + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNx4.AddString((LPCTSTR)s);
		}
		for(int i = 1;i < ny + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNy4.AddString((LPCTSTR)s);
		}
		for(int i = nz/2 + 1;i < nz + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNz4.AddString((LPCTSTR)s);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBOXWELL4)->EnableWindow(false);
		GetDlgItem(IDC_COMBOYWELL4)->EnableWindow(false);
		GetDlgItem(IDC_COMBOZWELL4)->EnableWindow(false);
		GetDlgItem(IDC_COMBOKIND4)->EnableWindow(false);
		GetDlgItem(IDC_COMBOTYPE4)->EnableWindow(false);
		GetDlgItem(IDC_EDITQW4)->EnableWindow(false);
		GetDlgItem(IDC_EDITQG4)->EnableWindow(false);
		GetDlgItem(IDC_EDITPWF4)->EnableWindow(false);
		GetDlgItem(IDC_EDITRW4)->EnableWindow(false);
		GetDlgItem(IDC_EDITSKIN4)->EnableWindow(false);
		GetDlgItem(IDC_EDITMINBHP4)->EnableWindow(false);
	}
	if(Nwell>3)
	{
		GetDlgItem(IDC_COMBOXWELL5)->EnableWindow(true);
		GetDlgItem(IDC_COMBOYWELL5)->EnableWindow(true);
		GetDlgItem(IDC_COMBOZWELL5)->EnableWindow(true);
		GetDlgItem(IDC_COMBOKIND5)->EnableWindow(true);
		GetDlgItem(IDC_COMBOTYPE5)->EnableWindow(true);
		GetDlgItem(IDC_EDITQW5)->EnableWindow(true);
		GetDlgItem(IDC_EDITQG5)->EnableWindow(true);
		GetDlgItem(IDC_EDITPWF5)->EnableWindow(true);
		GetDlgItem(IDC_EDITRW5)->EnableWindow(true);
		GetDlgItem(IDC_EDITSKIN5)->EnableWindow(true);
		GetDlgItem(IDC_EDITMINBHP5)->EnableWindow(true);
		//Initial combobox of First Well from 1 to nx, ny and nz
		CString s;
		for(int i = 1;i < nx + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNx5.AddString((LPCTSTR)s);
		}
		for(int i = 1;i < ny + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNy5.AddString((LPCTSTR)s);
		}
		for(int i = nz/2 + 1;i < nz + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNz5.AddString((LPCTSTR)s);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBOXWELL5)->EnableWindow(false);
		GetDlgItem(IDC_COMBOYWELL5)->EnableWindow(false);
		GetDlgItem(IDC_COMBOZWELL5)->EnableWindow(false);
		GetDlgItem(IDC_COMBOKIND5)->EnableWindow(false);
		GetDlgItem(IDC_COMBOTYPE5)->EnableWindow(false);
		GetDlgItem(IDC_EDITQW5)->EnableWindow(false);
		GetDlgItem(IDC_EDITQG5)->EnableWindow(false);
		GetDlgItem(IDC_EDITPWF5)->EnableWindow(false);
		GetDlgItem(IDC_EDITRW5)->EnableWindow(false);
		GetDlgItem(IDC_EDITSKIN5)->EnableWindow(false);
		GetDlgItem(IDC_EDITMINBHP5)->EnableWindow(false);
	}
	if(Nwell>4)
	{
		GetDlgItem(IDC_COMBOXWELL6)->EnableWindow(true);
		GetDlgItem(IDC_COMBOYWELL6)->EnableWindow(true);
		GetDlgItem(IDC_COMBOZWELL6)->EnableWindow(true);
		GetDlgItem(IDC_COMBOKIND6)->EnableWindow(true);
		GetDlgItem(IDC_COMBOTYPE6)->EnableWindow(true);
		GetDlgItem(IDC_EDITQW6)->EnableWindow(true);
		GetDlgItem(IDC_EDITQG6)->EnableWindow(true);
		GetDlgItem(IDC_EDITPWF6)->EnableWindow(true);
		GetDlgItem(IDC_EDITRW6)->EnableWindow(true);
		GetDlgItem(IDC_EDITSKIN6)->EnableWindow(true);
		GetDlgItem(IDC_EDITMINBHP6)->EnableWindow(true);
		//Initial combobox of First Well from 1 to nx, ny and nz
		CString s;
		for(int i = 1;i < nx + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNx6.AddString((LPCTSTR)s);
		}
		for(int i = 1;i < ny + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNy6.AddString((LPCTSTR)s);
		}
		for(int i = nz/2 + 1;i < nz + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNz6.AddString((LPCTSTR)s);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBOXWELL6)->EnableWindow(false);
		GetDlgItem(IDC_COMBOYWELL6)->EnableWindow(false);
		GetDlgItem(IDC_COMBOZWELL6)->EnableWindow(false);
		GetDlgItem(IDC_COMBOKIND6)->EnableWindow(false);
		GetDlgItem(IDC_COMBOTYPE6)->EnableWindow(false);
		GetDlgItem(IDC_EDITQW6)->EnableWindow(false);
		GetDlgItem(IDC_EDITQG6)->EnableWindow(false);
		GetDlgItem(IDC_EDITPWF6)->EnableWindow(false);
		GetDlgItem(IDC_EDITRW6)->EnableWindow(false);
		GetDlgItem(IDC_EDITSKIN6)->EnableWindow(false);
		GetDlgItem(IDC_EDITMINBHP6)->EnableWindow(false);
	}
	if(Nwell>5)
	{
		GetDlgItem(IDC_COMBOXWELL7)->EnableWindow(true);
		GetDlgItem(IDC_COMBOYWELL7)->EnableWindow(true);
		GetDlgItem(IDC_COMBOZWELL7)->EnableWindow(true);
		GetDlgItem(IDC_COMBOKIND7)->EnableWindow(true);
		GetDlgItem(IDC_COMBOTYPE7)->EnableWindow(true);
		GetDlgItem(IDC_EDITQW7)->EnableWindow(true);
		GetDlgItem(IDC_EDITQG7)->EnableWindow(true);
		GetDlgItem(IDC_EDITPWF7)->EnableWindow(true);
		GetDlgItem(IDC_EDITRW7)->EnableWindow(true);
		GetDlgItem(IDC_EDITSKIN7)->EnableWindow(true);
		GetDlgItem(IDC_EDITMINBHP7)->EnableWindow(true);
		//Initial combobox of First Well from 1 to nx, ny and nz
		CString s;
		for(int i = 1;i < nx + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNx7.AddString((LPCTSTR)s);
		}
		for(int i = 1;i < ny + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNy7.AddString((LPCTSTR)s);
		}
		for(int i = nz/2 + 1;i < nz + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNz7.AddString((LPCTSTR)s);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBOXWELL7)->EnableWindow(false);
		GetDlgItem(IDC_COMBOYWELL7)->EnableWindow(false);
		GetDlgItem(IDC_COMBOZWELL7)->EnableWindow(false);
		GetDlgItem(IDC_COMBOKIND7)->EnableWindow(false);
		GetDlgItem(IDC_COMBOTYPE7)->EnableWindow(false);
		GetDlgItem(IDC_EDITQW7)->EnableWindow(false);
		GetDlgItem(IDC_EDITQG7)->EnableWindow(false);
		GetDlgItem(IDC_EDITPWF7)->EnableWindow(false);
		GetDlgItem(IDC_EDITRW7)->EnableWindow(false);
		GetDlgItem(IDC_EDITSKIN7)->EnableWindow(false);
		GetDlgItem(IDC_EDITMINBHP7)->EnableWindow(false);
	}
	if(Nwell>6)
	{
		GetDlgItem(IDC_COMBOXWELL8)->EnableWindow(true);
		GetDlgItem(IDC_COMBOYWELL8)->EnableWindow(true);
		GetDlgItem(IDC_COMBOZWELL8)->EnableWindow(true);
		GetDlgItem(IDC_COMBOKIND8)->EnableWindow(true);
		GetDlgItem(IDC_COMBOTYPE8)->EnableWindow(true);
		GetDlgItem(IDC_EDITQW8)->EnableWindow(true);
		GetDlgItem(IDC_EDITQG8)->EnableWindow(true);
		GetDlgItem(IDC_EDITPWF8)->EnableWindow(true);
		GetDlgItem(IDC_EDITRW8)->EnableWindow(true);
		GetDlgItem(IDC_EDITSKIN8)->EnableWindow(true);
		GetDlgItem(IDC_EDITMINBHP8)->EnableWindow(true);
		//Initial combobox of First Well from 1 to nx, ny and nz
		CString s;
		for(int i = 1;i < nx + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNx8.AddString((LPCTSTR)s);
		}
		for(int i = 1;i < ny + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNy8.AddString((LPCTSTR)s);
		}
		for(int i = nz/2 + 1;i < nz + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNz8.AddString((LPCTSTR)s);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBOXWELL8)->EnableWindow(false);
		GetDlgItem(IDC_COMBOYWELL8)->EnableWindow(false);
		GetDlgItem(IDC_COMBOZWELL8)->EnableWindow(false);
		GetDlgItem(IDC_COMBOKIND8)->EnableWindow(false);
		GetDlgItem(IDC_COMBOTYPE8)->EnableWindow(false);
		GetDlgItem(IDC_EDITQW8)->EnableWindow(false);
		GetDlgItem(IDC_EDITQG8)->EnableWindow(false);
		GetDlgItem(IDC_EDITPWF8)->EnableWindow(false);
		GetDlgItem(IDC_EDITRW8)->EnableWindow(false);
		GetDlgItem(IDC_EDITSKIN8)->EnableWindow(false);
		GetDlgItem(IDC_EDITMINBHP8)->EnableWindow(false);
	}
	if(Nwell>7)
	{
		GetDlgItem(IDC_COMBOXWELL9)->EnableWindow(true);
		GetDlgItem(IDC_COMBOYWELL9)->EnableWindow(true);
		GetDlgItem(IDC_COMBOZWELL9)->EnableWindow(true);
		GetDlgItem(IDC_COMBOKIND9)->EnableWindow(true);
		GetDlgItem(IDC_COMBOTYPE9)->EnableWindow(true);
		GetDlgItem(IDC_EDITQW9)->EnableWindow(true);
		GetDlgItem(IDC_EDITQG9)->EnableWindow(true);
		GetDlgItem(IDC_EDITPWF9)->EnableWindow(true);
		GetDlgItem(IDC_EDITRW9)->EnableWindow(true);
		GetDlgItem(IDC_EDITSKIN9)->EnableWindow(true);
		GetDlgItem(IDC_EDITMINBHP9)->EnableWindow(true);
		//Initial combobox of First Well from 1 to nx, ny and nz
		CString s;
		for(int i = 1;i < nx + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNx9.AddString((LPCTSTR)s);
		}
		for(int i = 1;i < ny + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNy9.AddString((LPCTSTR)s);
		}
		for(int i = nz/2 + 1;i < nz + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNz9.AddString((LPCTSTR)s);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBOXWELL9)->EnableWindow(false);
		GetDlgItem(IDC_COMBOYWELL9)->EnableWindow(false);
		GetDlgItem(IDC_COMBOZWELL9)->EnableWindow(false);
		GetDlgItem(IDC_COMBOKIND9)->EnableWindow(false);
		GetDlgItem(IDC_COMBOTYPE9)->EnableWindow(false);
		GetDlgItem(IDC_EDITQW9)->EnableWindow(false);
		GetDlgItem(IDC_EDITQG9)->EnableWindow(false);
		GetDlgItem(IDC_EDITPWF9)->EnableWindow(false);
		GetDlgItem(IDC_EDITRW9)->EnableWindow(false);
		GetDlgItem(IDC_EDITSKIN9)->EnableWindow(false);
		GetDlgItem(IDC_EDITMINBHP9)->EnableWindow(false);
	}
	if(Nwell>8)
	{
		GetDlgItem(IDC_COMBOXWELL10)->EnableWindow(true);
		GetDlgItem(IDC_COMBOYWELL10)->EnableWindow(true);
		GetDlgItem(IDC_COMBOZWELL10)->EnableWindow(true);
		GetDlgItem(IDC_COMBOKIND10)->EnableWindow(true);
		GetDlgItem(IDC_COMBOTYPE10)->EnableWindow(true);
		GetDlgItem(IDC_EDITQW10)->EnableWindow(true);
		GetDlgItem(IDC_EDITQG10)->EnableWindow(true);
		GetDlgItem(IDC_EDITPWF10)->EnableWindow(true);
		GetDlgItem(IDC_EDITRW10)->EnableWindow(true);
		GetDlgItem(IDC_EDITSKIN10)->EnableWindow(true);
		GetDlgItem(IDC_EDITMINBHP10)->EnableWindow(true);
		//Initial combobox of First Well from 1 to nx, ny and nz
		CString s;
		for(int i = 1;i < nx + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNx10.AddString((LPCTSTR)s);
		}
		for(int i = 1;i < ny + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNy10.AddString((LPCTSTR)s);
		}
		for(int i = nz/2 + 1;i < nz + 1;i++)
		{		
			s.Format(_T("%d"), i);
			comboNz10.AddString((LPCTSTR)s);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBOXWELL10)->EnableWindow(false);
		GetDlgItem(IDC_COMBOYWELL10)->EnableWindow(false);
		GetDlgItem(IDC_COMBOZWELL10)->EnableWindow(false);
		GetDlgItem(IDC_COMBOKIND10)->EnableWindow(false);
		GetDlgItem(IDC_COMBOTYPE10)->EnableWindow(false);
		GetDlgItem(IDC_EDITQW10)->EnableWindow(false);
		GetDlgItem(IDC_EDITQG10)->EnableWindow(false);
		GetDlgItem(IDC_EDITPWF10)->EnableWindow(false);
		GetDlgItem(IDC_EDITRW10)->EnableWindow(false);
		GetDlgItem(IDC_EDITSKIN10)->EnableWindow(false);
		GetDlgItem(IDC_EDITMINBHP10)->EnableWindow(false);
	}
	UpdateData(TRUE);
}

BOOL Welldata::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	//Initial combobox of First Well from 1 to nx, ny and nz
	CString s;
	for(int i = 1;i < nx + 1;i++)
	{		
		s.Format(_T("%d"), i);
		comboNx1.AddString((LPCTSTR)s);
	}
	for(int i = 1;i < ny + 1;i++)
	{		
		s.Format(_T("%d"), i);
		comboNy1.AddString((LPCTSTR)s);
	}
	for(int i = nz/2 + 1 ;i < nz + 1;i++)	//Wells just exist in fracture layers
	{		
		s.Format(_T("%d"), i);
		comboNz1.AddString((LPCTSTR)s);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
