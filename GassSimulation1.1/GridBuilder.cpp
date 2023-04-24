// GridBuilder.cpp : implementation file
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "GridBuilder.h"
#include "string.h"

// GridBuilder dialog

IMPLEMENT_DYNAMIC(GridBuilder, CDialog)

//**************
extern int wellSet, simulationSet, startSimulation, reservoirMaked, reservoirMakedfirst, gridMakedfirst, firstTime, gridMaked, i, j, k, l, m, o, n, nr, nteta, nx, ny, nz, gridType;
extern double xD[100][100][100], yD[100][100][100], zD[100][100][100], rD[100][100][100], tetaD[100][100][100];
extern double xThick[100][100][100], yThick[100][100][100], zThick[100][100][100];
extern void Initial_data();

GridBuilder::GridBuilder(CWnd* pParent /*=NULL*/)
	: CDialog(GridBuilder::IDD, pParent)
	, cartNx(0)
	, cartNy(0)
	, cartNz(0)
	, cartDx(_T(""))
	, cartDy(_T(""))
	, cartDz(_T(""))
	, radNr(0)
	, radNt(0)
	, radNz(0)
	, radDr(_T(""))
	, radDt(_T(""))
	, radDz(_T(""))
	, gridModel(0)
	, setGridtype(0)
	, radioReservoir(0)
	, radioFlowtype(0)
	, radioModel(0)
{
}

GridBuilder::~GridBuilder()
{
}

void GridBuilder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBOCNX, this->cartNx);
	DDX_CBIndex(pDX, IDC_COMBOCNY, this->cartNy);
	DDX_Text(pDX, IDC_EDITCDX, this->cartDx);
	DDX_Text(pDX, IDC_EDITCDY, this->cartDy);
	DDX_Text(pDX, IDC_EDITCDZ, this->cartDz);
	DDX_CBIndex(pDX, IDC_COMBOCNZ, this->cartNz);
	DDX_CBIndex(pDX, IDC_COMBORNR, radNr);
	DDX_CBIndex(pDX, IDC_COMBORNT, radNt);
	DDX_CBIndex(pDX, IDC_COMBORNZ, radNz);
	DDX_Text(pDX, IDC_EDITRDR, radDr);
	DDX_Text(pDX, IDC_EDITRDT, radDt);
	DDX_Text(pDX, IDC_EDITRDZ, radDz);
	DDX_Radio(pDX, IDC_RADIOCART, setGridtype);
	DDX_Radio(pDX, IDC_RADIO1, radioReservoir);
	DDX_Radio(pDX, IDC_RADIO3, radioFlowtype);
	DDX_Radio(pDX, IDC_RADIOCART2, radioModel);
}


BEGIN_MESSAGE_MAP(GridBuilder, CDialog)
	ON_BN_CLICKED(IDOK, &GridBuilder::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIOCART, &GridBuilder::OnBnClickedRadiocart)
	ON_BN_CLICKED(IDC_RADIORAD, &GridBuilder::OnBnClickedRadiorad)
	ON_BN_CLICKED(IDC_RADIOCARA, &GridBuilder::OnBnClickedRadiocara)
	ON_BN_CLICKED(IDC_BUTTON1, &GridBuilder::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &GridBuilder::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO3, &GridBuilder::OnBnClickedRadio3)
END_MESSAGE_MAP()


// GridBuilder message handlers

void GridBuilder::OnBnClickedOk()
{
	UpdateData(TRUE);
	gridMaked = 0;	//Delete all of data for new grids
	reservoirMaked = 0;	//Delete all reservoir data for new grids
	simulationSet = 0;	//Delete all Simulation data for new grids
	startSimulation = 0;	//Delete last simulation data for new grids
	wellSet = 0;	//Delete all wells data for new grids
	if(this->gridModel == 0)
	{
		if(this->cartDx.GetLength() && this->cartDy.GetLength() && this->cartDz.GetLength())
		{
			nx = this->cartNx + 1;
			ny = this->cartNy + 1;
			nz = (this->cartNz + 1) * 2;//For fracture shoulde double dz
			this->cartDx.Trim();
			this->cartDy.Trim();
			this->cartDz.Trim();
			this->dimensionType = 1;	//Now is x Dimension
			this->i = 0;
			do{
				this->cartValue[this->i] = this->cartDx[this->i];
				this->i++;
			}while(this->cartDx[this->i] != '\0');
			this->cartValue[this->i] =  this->cartDx[this->i];
			this->nCount = 0;	//count number of grids to check it is equal to nx,ny or nz
			this->i = 0;	//Index Of cartValue
			this->k = 0;	//Index Of cartValueNo
			if(!(this->setCartesian()) || this->k != nx)
			{
				MessageBox(L"Dx is inCorrect",L"Error",MB_OK|MB_ICONERROR);
				return;
			}
			else
			{
				this->i = 0;
				do{
					this->cartValue[this->i] = this->cartDy[this->i];
					this->i++;
				}while(this->cartDy[this->i] != '\0');
				this->cartValue[this->i] = this->cartDy[this->i];
				this->i = 0;	//Index Of cartValue
				this->k = 0;	//Index Of cartValueNo
				this->dimensionType = 2;	//Now is y Dimension
				if(!(this->setCartesian()) || this->k != ny)
				{
					MessageBox(L"Dy is inCorrect",L"Error",MB_OK|MB_ICONERROR);
					return;
				}
				else
				{
					this->i = 0;
					do{
						this->cartValue[this->i] = this->cartDz[this->i];
						this->i++;
					}while(this->cartDz[this->i] != '\0');
					this->cartValue[this->i] = this->cartDz[this->i];
					this->i = 0;	//Index Of cartValue
					this->k = 0;	//Index Of cartValueNo
					this->dimensionType = 3;	//Now is z Dimension
					if(!(this->setCartesian()) || this->k != nz/2)
					{
						MessageBox(L"Dz is inCorrect",L"Error",MB_OK|MB_ICONERROR);
						return;
					}
					for (k = nz/2;k < nz;k++)
					{
						for (j = 0;j < ny;j++)
						{
							for (i = 0;i < nx;i++)
							{
								zD[i][j][k] = zD[i][j][k - nz/2] + zD[i][j][nz/2 - 1];
								xThick[i][j][k] = xThick[i][j][k - nz/2];
							}
						}
					}
				}
			}
		}
		else
		{
			MessageBox(L"Please fill all boxes",L"Error",MB_OK|MB_ICONERROR);
			return;
		}
	}
	else if(this->gridModel == 1)
	{
		return;
	}
	else
	{
		return;
	}
	firstTime = 1;
	gridMaked = 1;
	CDialog::OnOK();
}

void GridBuilder::OnBnClickedRadiocart()
{
	// TODO: Add your control notification handler code here
	//Set Cartesian model for input data
	GetDlgItem(IDC_COMBOCNX)->EnableWindow(true);
	GetDlgItem(IDC_COMBOCNY)->EnableWindow(true);
	GetDlgItem(IDC_COMBOCNZ)->EnableWindow(true);
	GetDlgItem(IDC_EDITCDX)->EnableWindow(true);
	GetDlgItem(IDC_EDITCDY)->EnableWindow(true);
	GetDlgItem(IDC_EDITCDZ)->EnableWindow(true);
	GetDlgItem(IDC_COMBORNR)->EnableWindow(false);
	GetDlgItem(IDC_COMBORNT)->EnableWindow(false);
	GetDlgItem(IDC_COMBORNZ)->EnableWindow(false);
	GetDlgItem(IDC_EDITRDR)->EnableWindow(false);
	GetDlgItem(IDC_EDITRDT)->EnableWindow(false);
	GetDlgItem(IDC_EDITRDZ)->EnableWindow(false);
}

void GridBuilder::OnBnClickedRadiorad()
{
	// TODO: Add your control notification handler code here
	//Set radial model for input data
	GetDlgItem(IDC_COMBOCNX)->EnableWindow(false);
	GetDlgItem(IDC_COMBOCNY)->EnableWindow(false);
	GetDlgItem(IDC_COMBOCNZ)->EnableWindow(false);
	GetDlgItem(IDC_EDITCDX)->EnableWindow(false);
	GetDlgItem(IDC_EDITCDY)->EnableWindow(false);
	GetDlgItem(IDC_EDITCDZ)->EnableWindow(false);
	GetDlgItem(IDC_COMBORNR)->EnableWindow(true);
	GetDlgItem(IDC_COMBORNT)->EnableWindow(true);
	GetDlgItem(IDC_COMBORNZ)->EnableWindow(true);
	GetDlgItem(IDC_EDITRDR)->EnableWindow(true);
	GetDlgItem(IDC_EDITRDT)->EnableWindow(true);
	GetDlgItem(IDC_EDITRDZ)->EnableWindow(true);
}

void GridBuilder::OnBnClickedRadiocara()
{
	// TODO: Add your control notification handler code here
	//Set combine Cartesian and radial model for input data
	GetDlgItem(IDC_COMBOCNX)->EnableWindow(true);
	GetDlgItem(IDC_COMBOCNY)->EnableWindow(true);
	GetDlgItem(IDC_COMBOCNZ)->EnableWindow(false);
	GetDlgItem(IDC_EDITCDX)->EnableWindow(true);
	GetDlgItem(IDC_EDITCDY)->EnableWindow(true);
	GetDlgItem(IDC_EDITCDZ)->EnableWindow(false);
	GetDlgItem(IDC_COMBORNR)->EnableWindow(true);
	GetDlgItem(IDC_COMBORNT)->EnableWindow(true);
	GetDlgItem(IDC_COMBORNZ)->EnableWindow(false);
	GetDlgItem(IDC_EDITRDR)->EnableWindow(true);
	GetDlgItem(IDC_EDITRDT)->EnableWindow(true);
	GetDlgItem(IDC_EDITRDZ)->EnableWindow(false);
}

void GridBuilder::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	reservoirMaked = 1;
	OnBnClickedOk();
	if(gridMaked == 1)
	{
		dlgReservoir.DoModal();
		CDialog::OnOK();
	}
}

void GridBuilder::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//gridMaked = 0;
	CDialog::OnCancel();
}


int GridBuilder::setCartesian(void)
{
	if(this->cartValue[this->i] != ' ' && this->cartValue[this->i] != '\t' && this->cartValue[this->i] != '0'
		&& this->cartValue[this->i] != '1' && this->cartValue[this->i] != '2' && this->cartValue[this->i] != '3'
		&& this->cartValue[this->i] != '4' && this->cartValue[this->i] != '5' && this->cartValue[this->i] != '6'
		&& this->cartValue[this->i] != '7' && this->cartValue[this->i] != '8' && this->cartValue[this->i] != '9'
		&& this->cartValue[this->i] != '[' && this->cartValue[this->i] != '\0')
	{
		return 0;
	}
	if(this->cartValue[this->i] == ' ' || this->cartValue[this->i] == '\t' || this->cartValue[this->i] == '0')
	{
		while(this->cartValue[this->i] == ' ' || this->cartValue[this->i] == '\t' || this->cartValue[this->i] == '0')
		{
			this->i++;
		}
	}
	if(this->cartValue[this->i] == '1' || this->cartValue[this->i] == '2' || this->cartValue[this->i] == '3'
		|| this->cartValue[this->i] == '4' || this->cartValue[this->i] == '5' || this->cartValue[this->i] == '6'
		|| this->cartValue[this->i] == '7' || this->cartValue[this->i] == '8' || this->cartValue[this->i] == '9')
	{
		return this->pDigit();
	}
	if(this->cartValue[this->i] == '[')
	{
		return this->pBracket();
	}
	if(this->cartValue[this->i] == '\0')
	{
		return this->k;
	}
	return 0;
}


int GridBuilder::pDigit(void)
{
	switch(this->dimensionType)
	{
	case 1:	//Dimension x
		{
			if(this->k > nx)
			{
				return 0;
			}
			break;
		}
	case 2:	//Dimension y
		{
			if(this->k > ny)
			{
				return 0;
			}
			break;
		}
	case 3:	//Dimension z
		{
			if(this->k > nz/2)
			{
				return 0;
			}
			break;
		}
	}
	this->j = 0;
	while(this->cartValue[this->i] == '1' || this->cartValue[this->i] == '2' || this->cartValue[this->i] == '3'
		|| this->cartValue[this->i] == '4' || this->cartValue[this->i] == '5' || this->cartValue[this->i] == '6'
		|| this->cartValue[this->i] == '7' || this->cartValue[this->i] == '8' || this->cartValue[this->i] == '9'
		|| this->cartValue[this->i] == '0')
	{
		this->strCartValue[this->j] = this->cartValue[this->i];
		(this->i)++;
		(this->j)++;
	}
	this->strCartValue[this->j] = '\0';
	switch(this->dimensionType)
	{
	case 1:	//Dimension x
		{
			for(int m = 0; m < nz ; m++)
			{
				for(int l = 0; l < ny ; l++)
				{
					xThick[k][l][m] = atof(this->strCartValue);
					if(k == 0)
					{
						xD[k][l][m] = atof(this->strCartValue);
					}
					else
					{
						xD[k][l][m] = xD[k-1][l][m] + atof(this->strCartValue);
					}
				}
			}
			break;
		}
	case 2:	//Dimension y
		{
			for(int m = 0; m < nz ; m++)
			{
				for(int l = 0; l < nx ; l++)
				{
					yThick[l][k][m] = atof(this->strCartValue);
					if(k == 0)
					{
						yD[l][k][m] = atof(this->strCartValue);
					}
					else
					{
						yD[l][k][m] = yD[l][k-1][m] + atof(this->strCartValue);
					}
				}
			}
			break;
		}
	case 3:	//Dimension z
		{
			for(int m = 0; m < ny ; m++)
			{
				for(int l = 0; l < nx ; l++)
				{
					zThick[l][m][k] = atof(this->strCartValue);
					if(k == 0)
					{
						zD[l][m][k] = atof(this->strCartValue);
					}
					else
					{
						zD[l][m][k] = zD[l][m][k-1] + atof(this->strCartValue);
					}
				}
			}
			break;
		}
	}
	this->k++;
	return this->setCartesian();
}


int GridBuilder::pBracket(void)
{
	(this->j) = 0;
	(this->i)++;
	if(this->cartValue[this->i] != ' ' && this->cartValue[this->i] != '\t' && this->cartValue[this->i] != '0'
		&& this->cartValue[this->i] != '1' && this->cartValue[this->i] != '2' && this->cartValue[this->i] != '3'
		&& this->cartValue[this->i] != '4' && this->cartValue[this->i] != '5' && this->cartValue[this->i] != '6'
		&& this->cartValue[this->i] != '7' && this->cartValue[this->i] != '8' && this->cartValue[this->i] != '9')
	{
		return 0;
	}
	if(this->cartValue[this->i] == ' ' || this->cartValue[this->i] == '\t' || this->cartValue[this->i] == '0')
	{
		while(this->cartValue[this->i] == ' ' || this->cartValue[this->i] == '\t' || this->cartValue[this->i] == '0')
		{
			this->i++;
		}
	}
	if(this->cartValue[this->i] != '1' && this->cartValue[this->i] != '2' && this->cartValue[this->i] != '3'
		&& this->cartValue[this->i] != '4' && this->cartValue[this->i] != '5' && this->cartValue[this->i] != '6'
		&& this->cartValue[this->i] != '7' && this->cartValue[this->i] != '8' && this->cartValue[this->i] != '9')
	{
		return 0;
	}
	while(this->cartValue[this->i] == '1' || this->cartValue[this->i] == '2' || this->cartValue[this->i] == '3'
		|| this->cartValue[this->i] == '4' || this->cartValue[this->i] == '5' || this->cartValue[this->i] == '6'
		|| this->cartValue[this->i] == '7' || this->cartValue[this->i] == '8' || this->cartValue[this->i] == '9'
		|| this->cartValue[this->i] == '0')
	{
		this->strCartNo[this->j] = this->cartValue[this->i];
		(this->i)++;
		(this->j)++;
	}
	this->strCartNo[this->j] = '\0';
	switch(this->dimensionType)
	{
	case 1:	//Dimension x
		{
			if(this->k + atoi(this->strCartNo) > nx)
			{
				return 0;
			}
			break;
		}
	case 2:	//Dimension y
		{
			if(this->k + atoi(this->strCartNo) > ny )
			{
				return 0;
			}
			break;
		}
	case 3:	//Dimension z
		{
			if(this->k + atoi(this->strCartNo) > nz/2)
			{
				return 0;
			}
			break;
		}
	}
	if(this->cartValue[this->i] != ' ' && this->cartValue[this->i] != '\t' && this->cartValue[this->i] != '0')
	{
		return 0;
	}
	if(this->cartValue[this->i] == ' ' || this->cartValue[this->i] == '\t' || this->cartValue[this->i] == '0')
	{
		while(this->cartValue[this->i] == ' ' || this->cartValue[this->i] == '\t' || this->cartValue[this->i] == '0')
		{
			this->i++;
		}
	}
	if(this->cartValue[this->i] != '1' && this->cartValue[this->i] != '2' && this->cartValue[this->i] != '3'
		&& this->cartValue[this->i] != '4' && this->cartValue[this->i] != '5' && this->cartValue[this->i] != '6'
		&& this->cartValue[this->i] != '7' && this->cartValue[this->i] != '8' && this->cartValue[this->i] != '9')
	{
		return 0;
	}
	this->j = 0;
	while(this->cartValue[this->i] == '1' || this->cartValue[this->i] == '2' || this->cartValue[this->i] == '3'
		|| this->cartValue[this->i] == '4' || this->cartValue[this->i] == '5' || this->cartValue[this->i] == '6'
		|| this->cartValue[this->i] == '7' || this->cartValue[this->i] == '8' || this->cartValue[this->i] == '9'
		|| this->cartValue[this->i] == '0')
	{
		this->strCartValue[this->j] = this->cartValue[this->i];
		(this->i)++;
		(this->j)++;
	}
	this->strCartValue[this->j] = '\0';
	if(this->cartValue[this->i] != ' ' && this->cartValue[this->i] != '\t' && this->cartValue[this->i] != '0'
		 && this->cartValue[this->i] != '\0' && this->cartValue[this->i] != ']')
	{
		return 0;
	}
	if(this->cartValue[this->i] == ' ' || this->cartValue[this->i] == '\t' || this->cartValue[this->i] == '0')
	{
		while(this->cartValue[this->i] == ' ' || this->cartValue[this->i] == '\t' || this->cartValue[this->i] == '0')
		{
			this->i++;
		}
	}
	if(this->cartValue[this->i] != ']')
	{
		return 0;
	}
	switch(this->dimensionType)
	{
	case 1:	//Dimension x
		{
			for(this->j = this->k ; this->j < this->k + atoi(this->strCartNo) ; this->j++)
			{
				for(int m = 0; m < nz ; m++)
				{
					for(int l = 0; l < ny ; l++)
					{
						xThick[this->j][l][m] = atof(this->strCartValue);
						if(this->j == 0)
						{
							xD[this->j][l][m] = atof(this->strCartValue);
						}
						else
						{
							xD[this->j][l][m] = xD[this->j - 1][l][m] + atof(this->strCartValue);
						}
					}
				}
			}
			break;
		}
	case 2:	//Dimension y
		{
			for(this->j = this->k ; this->j < this->k + atoi(this->strCartNo) ; this->j++)
			{
				for(int m = 0; m < nz ; m++)
				{
					for(int l = 0; l < nx ; l++)
					{
						yThick[l][this->j][m] = atof(this->strCartValue);
						if(this->j == 0)
						{
							yD[l][this->j][m] = atof(this->strCartValue);
						}
						else
						{
							yD[l][this->j][m] = yD[l][this->j - 1][m] + atof(this->strCartValue);
						}
					}
				}
			}
			break;
		}
	case 3:	//Dimension z
		{
			for(this->j = this->k ; this->j < this->k + atoi(this->strCartNo) ; this->j++)
			{
				for(int m = 0; m < ny ; m++)
				{
					for(int l = 0; l < nx ; l++)
					{
						zThick[l][m][this->j] = atof(this->strCartValue);
						if(this->j == 0)
						{
							zD[l][m][this->j] = atof(this->strCartValue);
						}
						else
						{
							zD[l][m][this->j] = zD[l][m][this->j - 1] + atof(this->strCartValue);
						}
					}
				}
			}
			break;
		}
	}
	this->k += atoi(this->strCartNo);
	this->i++;
	return this->setCartesian();
}


void GridBuilder::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
}
