// NumericalMethod.cpp : implementation file
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "NumericalMethod.h"


// NumericalMethod dialog
//Extern variables and functions
extern int startSimulation,simulationSet;
//extern char outputFile[100];
extern char outputTextFile[100], outputTextFilef[100], outputTextFilem[100];
extern int ncuts,tmax;
extern double dt, Satmax;

IMPLEMENT_DYNAMIC(NumericalMethod, CDialog)

NumericalMethod::NumericalMethod(CWnd* pParent /*=NULL*/)
	: CDialog(NumericalMethod::IDD, pParent)
	, textTimestep(0)
	, textEndsimilation(0)
	, textMaxerror(0)
	, textMaxsw(0)
	, textOutput(_T(""))
	, textMaxiteration(0)
{

}

NumericalMethod::~NumericalMethod()
{
}

void NumericalMethod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITTIMESTEP, textTimestep);
	DDX_Text(pDX, IDC_EDITENDSIMULATION, textEndsimilation);
	DDX_Text(pDX, IDC_EDITMAXERROR, textMaxerror);
	DDX_Text(pDX, IDC_EDITMAXETERATION, textMaxiteration);
	DDX_Text(pDX, IDC_EDITMAXSW, textMaxsw);
	DDX_Text(pDX, IDC_EDITOUTPUT, textOutput);
	DDX_Text(pDX, IDC_EDITMAXETERATION, textMaxiteration);
}


BEGIN_MESSAGE_MAP(NumericalMethod, CDialog)
	ON_BN_CLICKED(IDCANCEL, &NumericalMethod::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &NumericalMethod::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &NumericalMethod::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &NumericalMethod::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &NumericalMethod::OnBnClickedButton3)
END_MESSAGE_MAP()


// NumericalMethod message handlers

void NumericalMethod::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void NumericalMethod::OnBnClickedOk()
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	if(textEndsimilation==0 || textMaxerror==0 || textMaxiteration==0
		|| textMaxsw==0 || textTimestep==0 || textOutput=="")
	{
		MessageBox(L"Pleas Fill the required fields",L"Error",MB_OK|MB_ICONERROR);
	}
	else
	{
		FILE *output;
		if(!(output=_wfopen(textOutput,L"r")))
		{
			MessageBox(L"Cannot Open output file",L"Error",MB_OK|MB_ICONERROR);
		}
		else
		{
			int i=0;
			while(textOutput[i]!='\0')
			{
				outputTextFilem[i]=textOutput[i];
				i++;
			}
			outputTextFilem[i]='\0';
			dt=textTimestep;
			tmax=textEndsimilation;
			Satmax=textMaxiteration;
			ncuts=textMaxsw;
			simulationSet=1;
			fclose(output);
			CDialog::OnOK();
		}
	}
}

void NumericalMethod::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CFileDialog file(FALSE);
	if(file.DoModal()==IDOK)
	{
		textOutput = file.GetPathName();
		UpdateData(FALSE);
	}
}

void NumericalMethod::OnBnClickedButton2()
{
	OnBnClickedOk();
	if(simulationSet==1)
	{
		startSimulation = 1;
		CDialog::OnOK();
	}
}


void NumericalMethod::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CFileDialog file(FALSE);
	if(file.DoModal()==IDOK)
	{
		textOutputf = file.GetPathName();
		UpdateData(FALSE);
	}
}
