// InitialCondition.cpp : implementation file
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "InitialCondition.h"

extern int i, j, k, reservoirMakedfirst, gridMakedfirst, l, m, o, n, nr, nteta, nx, ny, nz, type, reservoirMaked, gridMaked, firstTime;
extern char krgFile[100], krwFile[100];
extern double Pinit, SWC, Cf, sigma, pc[100];
extern int npvt, nkr, nkrg, npvt_f, nkr_f, nkrg_f;	//Number of PVT/Kr input data
//Fluid properties
extern double Ppvt[100], BW[100], BG[100], UW[100], UG[100], CW[100], CG[100], Ppvt_f[100], BW_f[100], BG_f[100], UW_f[100], UG_f[100], CW_f[100], CG_f[100];
extern double SW[100], SG[100], KRW[100],KRG[100], SW_f[100], SG_f[100], KRW_f[100],KRG_f[100];

IMPLEMENT_DYNAMIC(InitialCondition, CDialog)

InitialCondition::InitialCondition(CWnd* pParent /*=NULL*/)
	: CDialog(InitialCondition::IDD, pParent)
	, textPvt(_T(""))
	, textPsi(0)
	, textSwc(0)
	, textCf(0)
	, textBwi(_T(""))
	, textBgi(_T(""))
	, textUwi(_T(""))
	, textUgi(_T(""))
	, textCwi(_T(""))
	, textCgi(_T(""))
	, textKrg(_T(""))
	, textKrw(_T(""))
	, textSwi(0)
	, textPvt_f(_T(""))
	, textKrg_f(_T(""))
	, textKrw_f(_T(""))
	, textSigma(0)
	, textCpillaryfile(_T(""))
	, textCapillaryfile(_T(""))
{

}

InitialCondition::~InitialCondition()
{
}

void InitialCondition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITPVT, textPvt);
	DDX_Text(pDX, IDC_EDITPSI, textPsi);
	DDX_Text(pDX, IDC_EDITSWC, textSwc);
	DDX_Text(pDX, IDC_EDITCF, textCf);
	DDX_Text(pDX, IDC_EDITKRG, textKrg);
	DDX_Text(pDX, IDC_EDITKRW, textKrw);
	DDX_Text(pDX, IDC_EDIT1, textSwi);
	DDX_Text(pDX, IDC_EDITPVT2, textPvt_f);
	DDX_Text(pDX, IDC_EDITKRG2, textKrg_f);
	DDX_Text(pDX, IDC_EDITKRW2, textKrw_f);
	DDX_Text(pDX, IDC_EDITSIGMA, textSigma);
	DDX_Text(pDX, IDC_EDITCAPILLARY, textCapillaryfile);
}

BEGIN_MESSAGE_MAP(InitialCondition, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &InitialCondition::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &InitialCondition::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &InitialCondition::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &InitialCondition::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON8, &InitialCondition::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &InitialCondition::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &InitialCondition::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON3, &InitialCondition::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTONCAPILLARY, &InitialCondition::OnBnClickedButtoncapillary)
END_MESSAGE_MAP()


// InitialCondition message handlers

void InitialCondition::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textPvt = file.GetPathName();
		UpdateData(false);
	}
}

void InitialCondition::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	bool ok=true;
	// TODO: Add extra validation here
	if (textPvt != "" && textPsi != 0.0 && textKrw != "" && textKrg != ""
		&& textSwc != 0.0 && textCf != 0.0 && textSwi != 0.0
		&& textPvt_f != "" && textKrw_f != "" && textKrg_f != "" && textSigma > 0 
		&& textCapillaryfile != "")
	{
		Pinit = textPsi;
		SWC = textSwc;
		//connatew = textSwi;
		Cf = textCf;
		sigma = textSigma;
		//***********************
		//Initial Bwi,Bgi,Uwi,Ugi,Cwi and Cgi values with Pinit Value
		if(this->InitialPVTdata())
		{
			if(this->InitialPVTdata_f())
			{
				if(this->InitialKRG())
				{
					if(this->InitialKRW())
					{
						if(this->InitialKRG_f())
						{
							if(this->InitialKRW_f())
							{
								if(this->InitialCapillary())
								{
									CDialog::OnOK();
								}
								else
								{
									MessageBox(L"Format of Capillary file is incorrect",L"Error",MB_OK|MB_ICONERROR);
								}
							}
							else
							{
								MessageBox(L"Format of KRW_f file is incorrect",L"Error",MB_OK|MB_ICONERROR);
							}
						}
						else
						{
							MessageBox(L"Format of KRG_f file is incorrect",L"Error",MB_OK|MB_ICONERROR);
						}
					}
					else
					{
						MessageBox(L"Format of KRW file is incorrect",L"Error",MB_OK|MB_ICONERROR);
					}
				}
				else
				{
					MessageBox(L"Format of KRG file is incorrect",L"Error",MB_OK|MB_ICONERROR);
				}
			}
			else
			{
				MessageBox(L"Format of PVT_f file is incorrect",L"Error",MB_OK|MB_ICONERROR);
			}
		}
		else
		{
			MessageBox(L"Format of PVT file is incorrect",L"Error",MB_OK|MB_ICONERROR);
		}
	}
	else
	{
		MessageBox(L"Pleas Fill the required fields",L"Error",MB_OK|MB_ICONERROR);
	}
}

void InitialCondition::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

int InitialCondition::InitialPVTdata()
{
	UpdateData(true);
	this->i = 0;	//Index Of buffer variable texFile
	npvt = 0;	//Number of file rows and Index of Ppvt,BW,UW,CW,BG,UG,CG variables
	char ch;
	if(bufferFile(this->textPvt))	// Buffer component of file into a string variable
	{
		this->i = 0;	//Initial i to zero
		while(this->textFile[this->i] !=EOF)
		{
			if(this->getValues())
			{
				Ppvt[npvt] = this->pvtValus;	//Set Ppvt data
				if(this->getValues())
				{
					BW[npvt] = this->pvtValus;	//Set BW data
					if(this->getValues())
					{
						UW[npvt] = this->pvtValus;	//Set UW data
						if(this->getValues())
						{
							CW[npvt] = this->pvtValus;	//Set CW data
							if(this->getValues())
							{
								BG[npvt] = this->pvtValus;	//Set BG data
								if(this->getValues())
								{
									UG[npvt] = this->pvtValus;	//Set UG data
									if(this->getValues())
									{
										CG[npvt] = this->pvtValus;	//Set CG data
										npvt++;	//Increase number Of rows
									}
									else
									{
										return 0;
									}
								}
								else
								{
									return 0;
								}
							}
							else
							{
								return 0;
							}
						}
						else
						{
							return 0;
						}
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int InitialCondition::InitialPVTdata_f()
{
	UpdateData(true);
	this->i = 0;	//Index Of buffer variable texFile
	npvt_f = 0;	//Number of file rows and Index of Ppvt,BW,UW,CW,BG,UG,CG variables
	char ch;
	if(bufferFile(this->textPvt_f))	// Buffer component of file into a string variable
	{
		this->i = 0;	//Initial i to zero
		while(this->textFile[this->i] != EOF)
		{
			if(this->getValues())
			{
				Ppvt_f[npvt_f] = this->pvtValus;	//Set Ppvt data
				if(this->getValues())
				{
					BW_f[npvt_f] = this->pvtValus;	//Set BW data
					if(this->getValues())
					{
						UW_f[npvt_f] = this->pvtValus;	//Set UW data
						if(this->getValues())
						{
							CW_f[npvt_f] = this->pvtValus;	//Set CW data
							if(this->getValues())
							{
								BG_f[npvt_f] = this->pvtValus;	//Set BG data
								if(this->getValues())
								{
									UG_f[npvt_f] = this->pvtValus;	//Set UG data
									if(this->getValues())
									{
										CG_f[npvt_f] = this->pvtValus;	//Set CG data
										npvt_f++;	//Increase number Of rows
									}
									else
									{
										return 0;
									}
								}
								else
								{
									return 0;
								}
							}
							else
							{
								return 0;
							}
						}
						else
						{
							return 0;
						}
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int InitialCondition::getValues()
{
	char strValue[20];
	int j = 0;
	while(this->textFile[this->i] == ' ' || this->textFile[this->i] == '\t' || this->textFile[this->i] == '\n')
	{
		this->i++;
	}
	if(isdigit(this->textFile[this->i]))
	{
		while(isdigit(this->textFile[this->i]))
		{
			strValue[j] = this->textFile[this->i];
			this->i++;
			j++;
		}
		if(this->textFile[this->i] == '.')
		{
			strValue[j] = this->textFile[this->i];	//It have real format
			this->i++;
			j++;
			if(isdigit(this->textFile[this->i]))	//Must have at least a digit after '.'
			{
				while(isdigit(this->textFile[this->i]))
				{
					strValue[j] = this->textFile[this->i];
					this->i++;
					j++;
				}
				this->pvtValus = atof(strValue);
			}
			else
			{
				return 0;	//It dos not have numeric format
			}
		}
		else
		{
			this->pvtValus = atof(strValue);
			return 1;	//It just have integer format
		}
	}
	else
	{
		return 0;	//It dos not have numeric format
	}
	return 1;
}

int InitialCondition::bufferFile(CString textFilepath)
{
	char messageText[100];
	this->i = 0;
	do{
		textFile[this->i] = textFilepath[this->i];
		this->i++;
	}while(textFilepath[this->i] != '\0');
	textFile[i] = textFilepath[this->i];
	FILE *inputFile;
	if(fopen_s(&inputFile, textFile, "r"))
	{
		strcpy_s(messageText,"Can not open file ");
		strcat_s(messageText,textFile);
		MessageBox((LPCTSTR)messageText,L"Error",MB_OK|MB_ICONERROR);
		return 0;
	}
	this->i = 0;
	this->textFile[this->i] = fgetc(inputFile);
	if(this->textFile[this->i] == EOF)
	{
		return 0;
	}
	while(this->textFile[this->i] != EOF)
	{
		if(this->textFile[this->i] != EOF && this->textFile[this->i] != ' '
			&& this->textFile[this->i] != '\n' && this->textFile[this->i] != '\t'
			&& !isdigit(this->textFile[this->i]) && this->textFile[this->i] != '.')
		{
			return 0;
		}
		this->i++;
		this->textFile[this->i] = fgetc(inputFile);
	}
	return strlen(textFile); 
}

void InitialCondition::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textCwi = file.GetPathName();
		UpdateData(false);
	}
}

void InitialCondition::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textCgi = file.GetPathName();
		UpdateData(false);
	}
}

void InitialCondition::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textUwi = file.GetPathName();
		UpdateData(false);
	}
}

void InitialCondition::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textUgi = file.GetPathName();
		UpdateData(false);
	}
}

void InitialCondition::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textKrg = file.GetPathName();
		UpdateData(false);
	}
}

void InitialCondition::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textKrw = file.GetPathName();
		UpdateData(false);
	}
}

int InitialCondition::InitialKRG(void)
{
	UpdateData(true);
	this->i = 0;	//Index Of buffer variable texFile initial to zero
	nkrg = 0;	//Number of file rows and Index of Ppvt,BW,UW,CW,BG,UG,CG variables
	char ch;
	if(bufferFile(this->textKrg))	// Buffer component of file into a string variable
	{
		this->i = 0;	//Initial i to zero
		while(this->textFile[this->i] !=EOF)
		{
			if(this->getValues())
			{
				SG[nkrg] = this->pvtValus;	//Set Ppvt data
				if(this->getValues())
				{
					KRG[nkrg] = this->pvtValus;	//Set BW data
					nkrg++;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int InitialCondition::InitialKRW(void)
{
	UpdateData(true);
	this->i = 0;	//Index Of buffer variable texFile initial to zero
	nkr = 0;	//Number of file rows and Index of Ppvt,BW,UW,CW,BG,UG,CG variables
	char ch;
	if(bufferFile(this->textKrw))	// Buffer component of file into a string variable
	{
		this->i = 0;	//Initial i to zero
		while(this->textFile[this->i] !=EOF)
		{
			if(this->getValues())
			{
				SW[nkr] = this->pvtValus;	//Set Ppvt data
				if(this->getValues())
				{
					KRW[nkr] = this->pvtValus;	//Set BW data
					nkr++;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int InitialCondition::InitialKRG_f(void)
{
	UpdateData(true);
	this->i = 0;	//Index Of buffer variable texFile initial to zero
	nkrg_f = 0;	//Number of file rows and Index of Ppvt,BW,UW,CW,BG,UG,CG variables
	char ch;
	if(bufferFile(this->textKrg_f))	// Buffer component of file into a string variable
	{
		this->i = 0;	//Initial i to zero
		while(this->textFile[this->i] !=EOF)
		{
			if(this->getValues())
			{
				SG_f[nkrg_f] = this->pvtValus;	//Set Ppvt data
				if(this->getValues())
				{
					KRG_f[nkrg_f] = this->pvtValus;	//Set BW data
					nkrg_f++;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int InitialCondition::InitialKRW_f(void)
{
	UpdateData(true);
	this->i = 0;	//Index Of buffer variable texFile initial to zero
	nkr_f = 0;	//Number of file rows and Index of Ppvt,BW,UW,CW,BG,UG,CG variables
	char ch;
	if(bufferFile(this->textKrw_f))	// Buffer component of file into a string variable
	{
		this->i = 0;	//Initial i to zero
		while(this->textFile[this->i] !=EOF)
		{
			if(this->getValues())
			{
				SW_f[nkr_f] = this->pvtValus;	//Set Ppvt data
				if(this->getValues())
				{
					KRW_f[nkr_f] = this->pvtValus;	//Set BW data
					nkr_f++;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

void InitialCondition::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textKrg_f = file.GetPathName();
		UpdateData(false);
	}
}

void InitialCondition::OnBnClickedButton10()
{
	// TODO: Add your control notification handler code 
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textKrw_f = file.GetPathName();
		UpdateData(false);
	}
}

void InitialCondition::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textPvt_f = file.GetPathName();
		UpdateData(false);
	}
}

void InitialCondition::OnBnClickedButtoncapillary()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CFileDialog file(true);
	if(file.DoModal()==IDOK)
	{
		textCapillaryfile = file.GetPathName();
		UpdateData(false);
	}
}

int InitialCondition::InitialCapillary(void)
{
	UpdateData(true);
	this->i = 0;	//Index Of buffer variable texFile initial to zero
	nkrg = 0;	//Number of file rows and Index of Ppvt,BW,UW,CW,BG,UG,CG variables
	char ch;
	if(bufferFile(this->textCapillaryfile))	// Buffer component of file into a string variable
	{
		this->i = 0;	//Initial i to zero
		while(this->textFile[this->i] !=EOF)
		{
			if(this->getValues())
			{
				pc[nkrg] = this->pvtValus;	//Set Ppvt data
				if(this->getValues())
				{
					pc[nkrg] = this->pvtValus;	//Set BW data
					nkrg++;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}
