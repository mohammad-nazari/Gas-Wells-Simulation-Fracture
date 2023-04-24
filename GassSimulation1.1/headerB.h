// Fracture Gas reservoir Simulation.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include <iostream>

using std::cout;
using std::cin;

//********************************
int nteta, nr, wellSet=0, startSimulation=0, simulationSet=0, reservoirMaked=0, gridMaked=0, reservoirMakedfirst=0, gridMakedfirst=0, firstTime=0, i=0, j=0, k=0, l=0, m=0, n=0, o=0, im, ip, jm, jp, km, kp, gridType=0, ok;
char outputTextFile[100], outputTextFilef[100], outputTextFilem[100];
double Lambdagmf[100][100][100], sigma, Lambdawmf[100][100][100],
	T1[100][100][100],T2[100][100][100],T3[100][100][100],
	T4[100][100][100], pcgw[100][100][100],pc[100],
	dpcgw1[100][100][100], dpcgw2[100][100][100], dpcgw3[100][100][100],
	dpcgw4[100][100][100], dpcgw5[100][100][100], dpcgw6[100][100][100],
	C[100][100][100],B[100][100][100], c[100][100][100],b[100][100][100];
//Matrix
double dp1[100][100][100], dp2[100][100][100], dp3[100][100][100],
		dp4[100][100][100], dp5[100][100][100], dp6[100][100][100];
int nx, ny, nz, startZ, endZ;	//Number of matrix grid blocks and their sizes
double Xsize, Ysize, Zsize;
double xD[100][100][100], yD[100][100][100], zD[100][100][100],
	dx[100][100][100], dy[100][100][100], dz[100][100][100];	//Matrix Grid dimensions
double xThick[100][100][100], yThick[100][100][100], zThick[100][100][100];

//Rock properties
double poro[100][100][100], perm[100][100][100], permX[100][100][100],
	permY[100][100][100], permZ[100][100][100], Cf, TW[100][100][100],
	TE[100][100][100], TN[100][100][100], TS[100][100][100], TT[100][100][100],
	TB[100][100][100], PV[100][100][100], PV1[100][100][100], PoreVol,
	PoreVolTime[100][100][100];

//Well properties
double rw[100][100][100], Skin[100][100][100], Pwf[100][100][100],
	ro[100][100][100], QW[100][100][100], QG[100][100][100],
	QT[100][100][100], MinBHP[100][100][100], JMODEL[100][100][100], rw_read[100],
	Skin_read[100], QT_read[100], QW_read[100],
	QG_read[100], Pwf_read[100], MinBHP_read[100],
	LambdaW[100][100][100], LambdaG[100][100][100], LambdaT[100][100][100];
int nwell,XCoor[100], YCoor[100], ZCoor[100];
char Wellname[100][100], TypeWell[100][100][100][100],
	WellConstraint[100][100][100][100], TypeWell_read[100][100];
int BCW, BCE, BCN, BCS, BCT, BCB;	//Boundary conditions
int npvt, npvt_f, nkr, nkr_f, nkrg, nkrg_f;	//Number of PVT/Kr input data

//Fluid properties
double Ppvt[100], BW[100], BG[100], UW[100], UG[100], CW[100], CG[100], Ppvt_f[100], BW_f[100], BG_f[100], UW_f[100], UG_f[100], CW_f[100], CG_f[100], CT;
double BWI[100][100][100], BGI[100][100][100], UWI[100][100][100], UGI[100][100][100],
	CWI[100][100][100], CGI[100][100][100],	CTOT[100][100][100], BWI1[100][100][100],
	BGI1[100][100][100], dRdP;

//Average properties for Matrix coefficients
double UWavw[100][100][100], UGavw[100][100][100], BWavw[100][100][100],
	BGavw[100][100][100], UWave[100][100][100], UGave[100][100][100],
	BWave[100][100][100], BGave[100][100][100], UWavs[100][100][100],
	UGavs[100][100][100], BWavs[100][100][100], BGavs[100][100][100],
	UWavn[100][100][100], UGavn[100][100][100], BWavn[100][100][100],
	BGavn[100][100][100], UWavb[100][100][100], UGavb[100][100][100],
	BWavb[100][100][100], BGavb[100][100][100], UWavt[100][100][100],
	UGavt[100][100][100], BWavt[100][100][100], BGavt[100][100][100];

//Relative Permeabilities parameters
double SW[100], SG[100], SL[100][100][100], KRW[100],
	KRG[100],SW_f[100], SG_f[100], KRW_f[100], KRG_f[100],
	SWI[100][100][100], SGI[100][100][100], SLI[100][100][100],
	KRWI[100][100][100], KRGI[100][100][100], KRWUPS, KRGUPS, SWI1[100][100][100],
	SGI1[100][100][100], SLI1[100][100][100], KROG[100][100][100], SWC,
	KROW[100][100][100], KROWI[100][100][100], KROGI[100][100][100], KROI[100][100][100];

//Matrix Elements
double aW[100000], aww[100][100][100], agw[100][100][100], ac[100000],at3[100000],at1[100000],at2[100000],at4[100000],
	awc[100][100][100], agc[100][100][100], aE[100000], awe[100][100][100],
	age[100][100][100], aN[100000], awn[100][100][100], agn[100][100][100], 
	aSt[100000], aws[100][100][100], ags[100][100][100], aT[100000],
	awt[100][100][100], agt[100][100][100], aB[100000], awb[100][100][100],
	agb[100][100][100], MB[100000], betha[100][100][100];
double press[100][100][100], p[100][100][100], pn[100][100][100];	//PRESSURE terms
double Pinit, PSum, minPressure, pressurStepsvalue[100000][100], pminmax[2] = {100000,0}, gasStepsvalue[100000][100], gminmax[2] = {1,0}, waterStepsvalue[100000][100], wminmax[2] = {1,0};	//Initial conditions

//To check stability and accuracy of solution and time step control
double Sat_diff[100][100][100], dt1, dt, Satmax;
int Count, ncuts, Check, timep, tmax;

//Fluids in place and cumulative production
double OWIP[100][100][100], OGIP[100][100][100], TotalWIP, TotalGIP, CumWater, CumGas;
double poroChart[4][100][100][100], permXChart[4][100][100][100], permYChart[4][100][100][100], permZChart[4][100][100][100], pChart[4][100][100][100], SGI1Chart[4][100][100][100], SWI1Chart[4][100][100][100];
//**********************************
//Matrix Solver Elements
double TOL;
int II, JJ, KKK;
long int IJKM, ITMAX, IT;
double QI[100][100000], AQI[100][100000],
	AL3[100000], AL2[100000], AL1[100000],
	AD[100000], AU1[100000], AU2[100000],
	AU3[100000], QN[100000], AQN[100000],
	RN[100000], DXN[100000],
	ADX[100000], Psim[100000];
//Report variables
int rc, MyCount;
//***************************
//***************************
void Read_data();
//void MemAlloc();
void Wells();
void Initial();
void Properties();
void Rates_con_rate();
void MatrixB();
void MatrixA();
void Matrix_Solver();
void Rates_con_bhp();
void Saturations();
void Cum_production();
void Update();
//void Report();
void SgUpdate();
void InterpolaPVT();
void Fluids_In_Place();
void Matrix_Initial();
void InterpolaKr();
void Mobilities();
void Comp_Total();
void Trans();
void Avg_PVT();
void Check_WellConstraints();
void Calc_dxdydz();
void Identify_constraints();
void Saturations_check();
void Chord_slope();
void Print_Report();
void CMAT(double [],double [],double [],double [],
	double [],double [],double [],double [],double ,
	int ,int ,int ,long int ,double ,double [][100000],
	double [][100000],double [],double [],double [],double [],
	double [],double [],double [],double [],double [],
	double [],double [],double [],double [],long int );
void ORTH(double [],double [],double [],double [],
	double [],double [],double [],double ,int ,
	int ,long int ,double ,double [],double [],
	double [],double [][100000],double [][100000],double [],
	double [],double [],long int );
void MSOLVE(double [],double [],double [],double [],
	double [],double [],double [],double [],int , 
	int ,long int ,double []);
//********************************
void writAandB()
{
	FILE *aFile, *bFile;
	if(fopen_s(&aFile, "a.txt", "w"))
	{
		return;
	}
	if(fopen_s(&bFile, "b.txt", "w"))
	{
		return;
	}
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				fprintf(bFile,"%f",MB[i+(nx*j)+(nx*ny*k)]);
				fprintf(bFile,"\n");
				for (k = 0;k < nz;k++)
				{
					for (j = 0;j < ny;j++)
					{
						for (i = 0;i < nx;i++)
						{
							if(i != 0)
							{
								fprintf(aFile,"%f",aW[i+(nx*j)+(nx*ny*k)]);
							}
							else if(j != 0)
							{
								fprintf(aFile,"%f",aSt[i+(nx*j)+(nx*ny*k)]);
							}
							else if(k != 0)
							{
								fprintf(aFile,"%f",aT[i+(nx*j)+(nx*ny*k)]);
							}
							else if(i != nx - 1)
							{
								fprintf(aFile,"%f",aE[i+(nx*j)+(nx*ny*k)]);
							}
							else if(j != ny - 1)
							{
								fprintf(aFile,"%f",aN[i+(nx*j)+(nx*ny*k)]);
							}
							else if(k != nz - 1)
							{
								fprintf(aFile,"%f",aB[i+(nx*j)+(nx*ny*k)]);
							}
							else
							{
								fprintf(aFile,"0");
							}
							fprintf(aFile," ");
						}
					}
				}
				fprintf(aFile,"\n");
			}
		}
	}
}
//********************************
void StartSimulation()
{
	int i, j, k;
	bool ok = true;
	//Read_data();
	Wells();
	Initial();
	timep = 0;
	rc = 0;
	do
	{
		rc = rc + 1;
		Properties();
		Rates_con_rate();
		Count = 0;
		do
		{
			MatrixB();
			MatrixA();
			Matrix_Solver();
			Rates_con_bhp();
			Saturations();
			if (Count <= ncuts && Check == 0)
			{
				dt1 = dt1 / (2 + Count);
				for (k = 0;k < nz;k++)
				{
					for (j = 0;j < ny;j++)
					{
						for (i = 0;i < nx;i++)
						{
							p[i][j][k] = pn[i][j][k];
							SWI1[i][j][k] = SWI[i][j][k];
							SGI1[i][j][k] = SGI[i][j][k];
							PV1[i][j][k] = PV[i][j][k];
						}
					}
				}
				Count = Count + 1;
			}
			else
			{
				timep = timep + dt1;
				Cum_production();
				dt1 = dt;
				break;
			}
		}while(1);
		Update();
		Print_Report();
		SgUpdate();
	}while(timep <= tmax);
}
//****************************************
void Initial()
{
	//Initial conditions for simulation
	int i, j, k;
	PoreVol = 0;
	CumWater = 0;
	CumGas = 0;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				pn[i][j][k] = Pinit;
				SWI[i][j][k] = SWC;
				SGI[i][j][k] = 1 - SWC;
				SWI1[i][j][k] = SWI[i][j][k];
				SGI1[i][j][k] = SGI[i][j][k];
				PV[i][j][k] = poro[i][j][k] * dx[i][j][k] * dy[i][j][k] * dz[i][j][k];
			}
		}
	}
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				PoreVol = PoreVol + PV[i][j][k] / 5615;
			}
		}
	}
	InterpolaPVT();
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				BWI1[i][j][k] = BWI[i][j][k];
				BGI1[i][j][k] = BGI[i][j][k];
				OWIP[i][j][k] = 0.1779685 * PV[i][j][k] * SWI[i][j][k] / BWI[i][j][k];	//Unit conversion of 2.294E-5 acre/ft^2 * coeffifient of 7758
				OGIP[i][j][k] = 0.1779685 * PV[i][j][k] * SGI[i][j][k] / BGI[i][j][k];
			}
		}
	}
	Fluids_In_Place();
	Matrix_Initial();
	CumWater = 0;
	CumGas = 0;
	dt1 = dt;
	Check = 1;
}
//**************************************************
void Properties()
{
	InterpolaPVT();
	InterpolaKr();
	Mobilities();
	Comp_Total();
	Trans();
	Avg_PVT();
}
//***************************************************
void Update()
{
	int i, j, k;
	//Update properties for the new timep step
	PSum = 0;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				pn[i][j][k] = p[i][j][k];
				SWI[i][j][k] = SWI1[i][j][k];
				SGI[i][j][k] = SGI1[i][j][k];
				PV[i][j][k] = PV1[i][j][k];
				//PoreVol = PoreVol + PV[i][j][k] / 5615;
				PSum = PSum + pn[i][j][k];
			}
		}
	}
	Check_WellConstraints();
}
//****************************************
void Wells()
{
	int i, j, k, m;
	Calc_dxdydz();
	for(m = 0;m < nwell;m++)
	{
		for (k = 0;k < nz;k++)
		{
			if(k == ZCoor[m])
			{
				for (j = 0;j < ny;j++)
				{
					if(j == YCoor[m])
					{
						for (i = 0;i < nx;i++)
						{
							if(i == XCoor[m])
							{
								strcpy_s(TypeWell[i][j][k], TypeWell_read[m]);
								_strupr_s(TypeWell[i][j][k]);
								rw[i][j][k] = rw_read[m];
								Skin[i][j][k] = Skin_read[m];
								QW[i][j][k] = QW_read[m] * 5.615;
								QG[i][j][k] = QG_read[m] * 1000;
								Pwf[i][j][k] = Pwf_read[m];
								MinBHP[i][j][k] = MinBHP_read[m];
							}
						}
					}
				}
			}
		}
	}
	Identify_constraints();
	for(m = 0;m < nwell;m++)
	{
		for (k = 0;k < nz;k++)
		{
			if(k == ZCoor[m])
			{
				for (j = 0;j < ny;j++)
				{
					if(j == YCoor[m])
					{
						for (i = 0;i < nx;i++)
						{
							if(i == XCoor[m])
							{
								ro[i][j][k] = 0.28 * (pow((pow((permY[i][j][k] / permX[i][j][k]) , 0.5) * pow(dx[i][j][k] , 2) +
									pow((permX[i][j][k] / permY[i][j][k]) , 0.5) * pow(dy[i][j][k] , 2)) , 0.5)) /
									(pow((permY[i][j][k] / permX[i][j][k]) , 0.25) + pow((permX[i][j][k] / permY[i][j][k]) , 0.25));
								JMODEL[i][j][k] = 0.039772562 * pow((permX[i][j][k] * permY[i][j][k]) , 0.5) * dz[i][j][k] /
									(log(ro[i][j][k] / rw[i][j][k]) + Skin[i][j][k]);
							}
						}
					}
				}
			}
		}
	}
}
//**********************************************
double Interpolation(double x,double a[100],double b[100],int n)
{
	//x, the value of reference for interpolation
	//a[] the array of reference
	//b[] the array of values for interpolation
	int i;
	double A1, A2, B1, B2;
	if(a[0] > a[n - 1])
	{
		for(i = 0;i < n - 1;i++)
		{
			if(x <= a[i] && x > a[i + 1])
			{
				A1 = a[i];
				A2 = a[i + 1];
				B1 = b[i];
				B2 = b[i + 1];
			}
			if(x > a[0])
			{
				A1 = a[0];
				A2 = a[1];
				B1 = b[0];
				B2 = b[1];
			}
			if(x < a[n - 1])
			{
				A1 = a[n - 1];
				A2 = a[n - 2];
				B1 = b[n - 1];
				B2 = b[n - 2];
			}
		}
	}
	else
	{
		for(i = 0;i < n - 1;i++)
		{
			if(x >= a[i] && x <= a[i + 1])
			{
				A1 = a[i];
				A2 = a[i + 1];
				B1 = b[i];
				B2 = b[i + 1];
			}
			if(x < a[0])
			{
				A1 = a[0];
				A2 = a[1];
				B1 = b[0];
				B2 = b[0];
			}
			if(x > a[n - 1])
			{
				A1 = a[n - 1];
				A2 = a[n - 2];
				B1 = b[n - 1];
				B2 = b[n - 1];
			}
		}
	}
	return (B1 + (B2 - B1) / (A2 - A1) * (x - A1));
}
//************************************************
double MaxValue(double a[100][100][100])
{
	int i, j, k;
	double MaxValue = a[0][0][0];
	for(k = 0;k < nz;k++)
	{
		for(j = 0;j < ny;j++)
		{
			for(i = 1;i < nx;i++)
			{
				if(a[i][j][k] > MaxValue)
				{
					MaxValue = a[i][j][k];
				}
			}
		}
	}
	return MaxValue;
}
//*******************************************
double MinValue(double a[100])
{
	int i;
	double MinValue = a[99];
	for(i = 0;i < 100;i++)
	{
		if(a[i] < MinValue)
		{
			MinValue = a[i];
		}
	}
	return MinValue;
}
//*******************************************
double AritAvg(double a,double b)
{
	return (a + b) / 2;
}
//******************************************
double HarmAvg(double a,double b)
{
	return (2 * a * b / (a + b));
}
//*******************************************
void Calc_dxdydz()
{
	int i, im, ip;
	int j, jm, jp;
	int k, km, kp;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				im = i - 1;
				ip = i + 1;
				jm = j - 1;
				jp = j + 1;
				km = k - 1;
				kp = k + 1;
				if(i == 0)
				{
					im = i;
				}
				if(i == nx - 1)
				{
					ip = nx - 1;
				}
				if(j == 0)
				{
					jm = j;
				}
				if(j == ny - 1)
				{
					jp = ny - 1;
				}
				if(k == 0)
				{
					km = k;
				}
				if(k == nz-1)
				{
					kp = nz - 1;
				}
				dx[i][j][k] = (xD[i][j][k] - xD[im][j][ k]) / 2 +
					(xD[ip][j][k] - xD[i][j][k]) / 2;
				if(ny == 0)
				{
					dy[i][j][k] = yD[i][j][k];
				}
				else
				{
					dy[i][j][k] = (yD[i][j][k] - yD[i][jm][k]) / 2 +
						(yD[i][jp][k] - yD[i][j][k]) / 2;
				}
				if(nz == 0)
				{
					dz[i][j][k] = zD[i][j][k];
				}
				else
				{
					dz[i][j][k] = (zD[i][j][k] - zD[i][j][km]) / 2 +
						(zD[i][j][kp] - zD[i][j][k]) / 2;
				}
			}
		}
	}
}
//***********************************
void InterpolaPVT()
{
	int i, j, k;
	for (k = 0;k < nz/2;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				BWI[i][j][k] = Interpolation(pn[i][j][k], Ppvt, BW, npvt);
				BGI[i][j][k] = Interpolation(pn[i][j][k], Ppvt, BG, npvt);
				UWI[i][j][k] = Interpolation(pn[i][j][k], Ppvt, UW, npvt);
				UGI[i][j][k] = Interpolation(pn[i][j][k], Ppvt, UG, npvt);
				CWI[i][j][k] = Interpolation(pn[i][j][k], Ppvt, CW, npvt);
				CGI[i][j][k] = Interpolation(pn[i][j][k], Ppvt, CG, npvt);
			}
		}
	}
	for (k = nz/2;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				BWI[i][j][k] = Interpolation(pn[i][j][k], Ppvt_f, BW_f, npvt_f);
				BGI[i][j][k] = Interpolation(pn[i][j][k], Ppvt_f, BG_f, npvt_f);
				UWI[i][j][k] = Interpolation(pn[i][j][k], Ppvt_f, UW_f, npvt_f);
				UGI[i][j][k] = Interpolation(pn[i][j][k], Ppvt_f, UG_f, npvt_f);
				CWI[i][j][k] = Interpolation(pn[i][j][k], Ppvt_f, CW_f, npvt_f);
				CGI[i][j][k] = Interpolation(pn[i][j][k], Ppvt_f, CG_f, npvt_f);
			}
		}
	}
}
//**********************************
void InterpolaKr()
{
	int i, j, k;
	for (k = 0;k < nz/2;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				KRWI[i][j][k] = Interpolation(SWI[i][j][k], SW, KRW, nkr);
				KRGI[i][j][k] = Interpolation(SGI[i][j][k], SG, KRG, nkrg);
			}
		}
	}
	for (k = nz/2;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				KRWI[i][j][k] = Interpolation(SWI[i][j][k], SW_f, KRW_f, nkr_f);
				KRGI[i][j][k] = Interpolation(SGI[i][j][k], SG_f, KRG_f, nkrg_f);
			}
		}
	}
}
//***********************************
void Chord_slope()
{
	int i, j, k;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				PV1[i][j][k] = PV[i][j][k] * (1 + Cf * (p[i][j][k] - pn[i][j][k]));
				BWI1[i][j][k] = BWI[i][j][k] * (1 - CWI[i][j][k] * (p[i][j][k] - pn[i][j][k]));
				BGI1[i][j][k] = BGI[i][j][k] * (1 - CGI[i][j][k] * (p[i][j][k] - pn[i][j][k]));
			}
		}
	}
}
//*****************************
void Saturations()
{
	int i, j, k;
	/*double dp1[100][100][100], dp2[100][100][100], dp3[100][100][100],
		dp4[100][100][100], dp5[100][100][100], dp6[100][100][100];*/
	Chord_slope();
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				if(i != 0)
				{
					dp1[i][j][k] = p[i - 1][j][k] - p[i][j][k];
				}
				if(i != nx - 1)
				{
					dp2[i][j][k] = p[i + 1][j][k] - p[i][j][k];
				}
				if(j != 0)
				{
					dp3[i][j][k] = p[i][j - 1][k] - p[i][j][k];
				}
				if(j != ny - 1)
				{
					dp4[i][j][k] = p[i][j + 1][k] - p[i][j][k];
				}
				if(k != 0)
				{
					dp5[i][j][k] = p[i][j][k - 1] - p[i][j][k];
				}
				if(k != nz - 1)
				{
					dp6[i][j][k] = p[i][j][k + 1] - p[i][j][k];
				}
				SWI1[i][j][k] = BWI1[i][j][k] / PV1[i][j][k] * (dt1 * (aww[i][j][k] * dp1[i][j][k] +
					awe[i][j][k] * dp2[i][j][k] + aws[i][j][k] * dp3[i][j][k] + awn[i][j][k] * dp4[i][j][k] +
					awt[i][j][k] * dp5[i][j][k] + awb[i][j][k] * dp6[i][j][k] - QW[i][j][k]) + PV[i][j][k] * SWI[i][j][k] / BWI[i][j][k]);
				SGI1[i][j][k] = BGI1[i][j][k] / PV1[i][j][k] * (dt1 * (agw[i][j][k] * dp1[i][j][k] +
					age[i][j][k] * dp2[i][j][k] + ags[i][j][k] * dp3[i][j][k] + agn[i][j][k] * dp4[i][j][k] +
					agt[i][j][k] * dp5[i][j][k] + agb[i][j][k] * dp6[i][j][k] - QG[i][j][k]) + PV[i][j][k] * SGI[i][j][k] / BGI[i][j][k]);
			}
		}
	}
	Saturations_check();
}
//*********************************
void Saturations_check()
{
	int i, j, k;
	double maxdiff;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				Sat_diff[i][j][k] = abs(1 - SWI1[i][j][k] - SGI1[i][j][k]);
			}
		}
	}
	maxdiff = MaxValue(Sat_diff); 
	if( maxdiff >= Satmax )
	{
		Check = 0;
	}
	else
	{
		Check = 1;
	}
}
//*********************************
void SgUpdate()
{
	int i, j, k;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				SGI[i][j][k] = 1 - SWI[i][j][k];
			}
		}
	}
}
//*********************************
void Comp_Total()
{
	//Calculate total compressibility
	int i, j, k;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				CTOT[i][j][k] = Cf + CWI[i][j][k] * SWI[i][j][k] + CGI[i][j][k] * SGI[i][j][k];
			}
		}
	}
}
//*********************************
void Mobilities()
{
	int i, j, k;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				LambdaW[i][j][k] = KRWI[i][j][k] / (UWI[i][j][k] * BWI[i][j][k]);
				LambdaG[i][j][k] = KRGI[i][j][k] / (UGI[i][j][k] * BGI[i][j][k]);
				LambdaT[i][j][k] = LambdaW[i][j][k] * BWI1[i][j][k] + LambdaG[i][j][k] * BGI1[i][j][k];
			}
		}
	}
}
//*********************************
void Kr_upstream(int a,int b,int c,int d,int e,int f)
{
	if( pn[a][b][c] >= pn[d][e][f] )
	{
		KRWUPS = KRWI[a][b][c];
		KRGUPS = KRGI[a][b][c];
	}
	else
	{
		KRWUPS = KRWI[d][e][f];
		KRGUPS = KRGI[d][e][f];
	}
}
//*********************************
void Rates_con_rate()
{
	int i, j, k, m;
	for(m = 0;m < nwell;m++)
	{
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					if(!strcmp(TypeWell[i][j][k], "PROD"))
					{
						if( !strcmp(WellConstraint[i][j][k], "WRATE"))
						{
							QG[i][j][k] = QW[i][j][k] * LambdaG[i][j][k] / LambdaW[i][j][k];	//SCF/d
							QT[i][j][k] = QW[i][j][k] * BWI1[i][j][k] + BGI1[i][j][k] * QG[i][j][k];	//rcf/d
						}
						else if(!strcmp(WellConstraint[i][j][k], "GRATE"))
						{
							QW[i][j][k] = QG[i][j][k] * LambdaW[i][j][k] / LambdaG[i][j][k];	//SCF/d
							QT[i][j][k] = QW[i][j][k] * BWI1[i][j][k] + BGI1[i][j][k] * QG[i][j][k]; //rcf/d
						}
						else if(!strcmp(WellConstraint[i][j][k], "2RATE"))
						{
							QT[i][j][k] = QW[i][j][k] * BWI1[i][j][k] + BGI1[i][j][k] * QG[i][j][k]; //rcf/d
						}
					}
					else if(!strcmp(TypeWell[i][j][k], "WINJ"))
					{
						if(!strcmp(WellConstraint[i][j][k], "WRATE"))
						{
							QT[i][j][k] = QW[i][j][k] * BWI1[i][j][k]; //rcf/d
						}
						else if(!strcmp(WellConstraint[i][j][k], "GRATE"))
						{
							QT[i][j][k] = QG[i][j][k] * BGI1[i][j][k]; //rcf/d
						}
					}
				}
			}
		}
	}
}
//*********************************
void Rates_con_bhp()
{
	int i, j, k;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				if(!strcmp(TypeWell[i][j][k], "PROD"))
				{
					if(!strcmp(WellConstraint[i][j][k], "PRESSURE"))
					{
						QW[i][j][k] = JMODEL[i][j][k] * LambdaW[i][j][k] * (p[i][j][k] - Pwf[i][j][k]); //SCF/day
						QG[i][j][k] = JMODEL[i][j][k] * LambdaG[i][j][k] * (p[i][j][k] - Pwf[i][j][k]); //SCF/day
						QT[i][j][k] = QW[i][j][k] * BWI1[i][j][k] + BGI1[i][j][k] * QG[i][j][k]; //rcf/day
					}
					else if(!strcmp(WellConstraint[i][j][k], "WRATE") || !strcmp(WellConstraint[i][j][k], "GRATE") || !strcmp(WellConstraint[i][j][k], "2RATE"))
					{
						Pwf[i][j][k] = p[i][j][k] - QT[i][j][k] / (JMODEL[i][j][k] * LambdaT[i][j][k]);
					}
				}
				else if(!strcmp(TypeWell[i][j][k], "WINJ"))
				{
					if(!strcmp(WellConstraint[i][j][k], "PRESSURE"))
					{
						QW[i][j][k] = JMODEL[i][j][k] * LambdaW[i][j][k] * (p[i][j][k] - Pwf[i][j][k]); //SCF/day
						QT[i][j][k] = QW[i][j][k] * BWI1[i][j][k];
					}
					else if(!strcmp(WellConstraint[i][j][k], "WRATE"))
					{
						Pwf[i][j][k] = p[i][j][k] + QT[i][j][k] / (JMODEL[i][j][k] * LambdaT[i][j][k] * BWI1[i][j][k]);
					}
				}
			}
		}
	}
}
//*********************************
void Check_WellConstraints()
{
	//Check whether the minimum constraints are reached, if so change the constraints
	int i, j, k;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				if(!strcmp(WellConstraint[i][j][k], "WRATE") || !strcmp(WellConstraint[i][j][k], "GRATE") || !strcmp(WellConstraint[i][j][k] ,"2RATE"))
				{
					if( Pwf[i][j][k] <= MinBHP[i][j][k] )
					{
						strcpy_s(WellConstraint[i][j][k], "PRESSURE");
						_strupr_s(WellConstraint[i][j][k]);
						Pwf[i][j][k] = MinBHP[i][j][k];
					}
				}
			}
		}
	}
}
//*********************************
void Cum_production()
{
	int i, j, k;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				CumWater = CumWater + QW[i][j][k] * dt1;
				CumGas = CumGas + QG[i][j][k] * dt1;
			}
		}
	}
}
//*********************************
void Trans()
{
	//Calculates transmisibilities for each phase
	int i, j, k;
	double kavw, kave;
	double kavn, kavs;
	double kavt, kavb;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				if(i != 0)
				{
					kavw = HarmAvg(permX[i][j][k], permX[i - 1][j][k]);
					TW[i][j][k] = 0.00633 * kavw * dy[i][j][k] * dz[i][j][k] / (xD[i][j][k] - xD[i - 1][j][k]);
				}
				if(j != 0)
				{
					kavs = HarmAvg(permY[i][j][k], permY[i][j - 1][k]);
					TS[i][j][k] = 0.00633 * kavs * dx[i][j][k] * dz[i][j][k] / (yD[i][j][k] - yD[i][j - 1][k]);
				}
				if(k != 0)
				{
					kavt = HarmAvg(permZ[i][j][k], permZ[i][j][k - 1]);
					TT[i][j][k] = 0.00633 * kavt * dy[i][j][k] * dx[i][j][k] / (zD[i][j][k] - zD[i][j][k - 1]);
				}
				if(i != nx - 1)
				{
					kave = HarmAvg(permX[i][j][k], permX[i + 1][j][k]);
					TE[i][j][k] = 0.00633 * kave * dy[i][j][k] * dz[i][j][k] / (xD[i + 1][j][k] - xD[i][j][k]);
				}
				if(j != ny - 1)
				{
					kavn = HarmAvg(permY[i][j][k], permY[i][j + 1][k]);
					TN[i][j][k] = 0.00633 * kavn * dx[i][j][k] * dz[i][j][k] / (yD[i][j + 1][k] - yD[i][j][k]);
				}
				if(k != nz - 1)
				{
					kavb = HarmAvg(permZ[i][j][k], permZ[i][j][k + 1]);
					TB[i][j][k] = 0.00633 * kavb * dy[i][j][k] * dx[i][j][k] / (zD[i][j][k + 1] - zD[i][j][k]);
				}
			}
		}
	}
}
//*********************************
void Avg_PVT()
{
	int i, j, k;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				if(i != 0)
				{
					UWavw[i][j][k] = AritAvg(UWI[i][j][k], UWI[i - 1][j][k]);
					UGavw[i][j][k] = AritAvg(UGI[i][j][k], UGI[i - 1][j][k]);
					BWavw[i][j][k] = AritAvg(BWI[i][j][k], BWI[i - 1][j][k]);
					BGavw[i][j][k] = AritAvg(BGI[i][j][k], BGI[i - 1][j][k]);
				}
				if(j != 0)
				{
					UWavs[i][j][k] = AritAvg(UWI[i][j][k], UWI[i][j - 1][k]);
					UGavs[i][j][k] = AritAvg(UGI[i][j][k], UGI[i][j - 1][k]);
					BWavs[i][j][k] = AritAvg(BWI[i][j][k], BWI[i][j - 1][k]);
					BGavs[i][j][k] = AritAvg(BGI[i][j][k], BGI[i][j - 1][k]);
				}
				if(k != 0)
				{
					UWavt[i][j][k] = AritAvg(UWI[i][j][k], UWI[i][j][k - 1]);
					UGavt[i][j][k] = AritAvg(UGI[i][j][k], UGI[i][j][k - 1]);
					BWavt[i][j][k] = AritAvg(BWI[i][j][k], BWI[i][j][k - 1]);
					BGavt[i][j][k] = AritAvg(BGI[i][j][k], BGI[i][j][k - 1]);
				}
				if(i != nx - 1)
				{
					UWave[i][j][k] = AritAvg(UWI[i][j][k], UWI[i + 1][j][k]);
					UGave[i][j][k] = AritAvg(UGI[i][j][k], UGI[i + 1][j][k]);
					BWave[i][j][k] = AritAvg(BWI[i][j][k], BWI[i + 1][j][k]);
					BGave[i][j][k] = AritAvg(BGI[i][j][k], BGI[i + 1][j][k]);
				}
				if(j != ny - 1)
				{
					UWavn[i][j][k] = AritAvg(UWI[i][j][k], UWI[i][j + 1][k]);
					UGavn[i][j][k] = AritAvg(UGI[i][j][k], UGI[i][j + 1][k]);
					BWavn[i][j][k] = AritAvg(BWI[i][j][k], BWI[i][j + 1][k]);
					BGavn[i][j][k] = AritAvg(BGI[i][j][k], BGI[i][j + 1][k]);
				}
				if(k != nz - 1)
				{
					UWavb[i][j][k] = AritAvg(UWI[i][j][k], UWI[i][j][k + 1]);
					UGavb[i][j][k] = AritAvg(UGI[i][j][k], UGI[i][j][k + 1]);
					BWavb[i][j][k] = AritAvg(BWI[i][j][k], BWI[i][j][k + 1]);
					BGavb[i][j][k] = AritAvg(BGI[i][j][k], BGI[i][j][k + 1]);
				}
			}
		}
	}
}
//*********************************
void MatrixA()
{
	int i, j, k, MH;
	MH = -1;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				MH = MH + 1;
				if(i != 0)
				{
					Kr_upstream(i, j, k, i - 1, j, k);
					aww[i][j][k] = TW[i][j][k] * KRWUPS / (UWavw[i][j][k] * BWavw[i][j][k]);
					agw[i][j][k] = TW[i][j][k] * KRGUPS / (UGavw[i][j][k] * BGavw[i][j][k]);
					aW[MH] = aww[i][j][k] * BWI1[i][j][k] + agw[i][j][k] * BGI1[i][j][k];
				}
				if(j != 0)
				{
					Kr_upstream(i, j, k, i, j - 1, k);
					aws[i][j][k] = TS[i][j][k] * KRWUPS / (UWavs[i][j][k] * BWavs[i][j][k]);
					ags[i][j][k] = TS[i][j][k] * KRGUPS / (UGavs[i][j][k] * BGavs[i][j][k]);
					aSt[MH] = aws[i][j][k] * BWI1[i][j][k] + ags[i][j][k] * BGI1[i][j][k];
				}
				if(k != 0)
				{
					Kr_upstream(i, j, k, i, j, k - 1);
					awt[i][j][k] = TT[i][j][k] * KRWUPS / (UWavt[i][j][k] * BWavt[i][j][k]);
					agt[i][j][k] = TT[i][j][k] * KRGUPS / (UGavt[i][j][k] * BGavt[i][j][k]);
					aT[MH] = awt[i][j][k] * BWI1[i][j][k] + agt[i][j][k] * BGI1[i][j][k];
				}
				if(i != nx - 1)
				{
					Kr_upstream(i, j, k, i + 1, j, k);
					awe[i][j][k] = TE[i][j][k] * KRWUPS / (UWave[i][j][k] * BWave[i][j][k]);
					age[i][j][k] = TE[i][j][k] * KRGUPS / (UGave[i][j][k] * BGave[i][j][k]);
					aE[MH] = awe[i][j][k] * BWI1[i][j][k] + age[i][j][k] * BGI1[i][j][k];
				}
				if(j != ny - 1)
				{
					Kr_upstream(i, j, k, i, j + 1, k);
					awn[i][j][k] = TN[i][j][k] * KRWUPS / (UWavn[i][j][k] * BWavn[i][j][k]);
					agn[i][j][k] = TN[i][j][k] * KRGUPS / (UGavn[i][j][k] * BGavn[i][j][k]);
					aN[MH] = awn[i][j][k] * BWI1[i][j][k] + agn[i][j][k] * BGI1[i][j][k];
				}
				if(k != nz - 1)
				{
					Kr_upstream(i, j, k, i, j, k + 1);
					awb[i][j][k] = TB[i][j][k] * KRWUPS / (UWavb[i][j][k] * BWavb[i][j][k]);
					agb[i][j][k] = TB[i][j][k] * KRGUPS / (UGavb[i][j][k] * BGavb[i][j][k]);
					aB[MH] = awb[i][j][k] * BWI1[i][j][k] + agb[i][j][k] * BGI1[i][j][k];
				}
				if(!strcmp(WellConstraint[i][j][k], "GRATE") || !strcmp(WellConstraint[i][j][k], "WRATE") || !strcmp(WellConstraint[i][j][k], "2RATE"))
				{
					ac[MH] = -aW[MH] - aSt[MH] - aB[MH] - aE[MH] - aN[MH] - aT[MH] - betha[i][j][k];
				}
				else if(!strcmp(WellConstraint[i][j][k], "PRESSURE"))
				{
					ac[MH] = -aW[MH] - aSt[MH] - aB[MH] - aE[MH] - aN[MH] - aT[MH] - betha[i][j][k] - JMODEL[i][j][k] * LambdaT[i][j][k];
				}
				else
				{
					ac[MH] = -aW[MH] - aSt[MH] - aB[MH] - aE[MH] - aN[MH] - aT[MH] - betha[i][j][k];
				}
				if(i == 0)
				{
					if(BCW == 0)
					{
						// Keep the same values
					}
					else if(BCW == 1)
					{
						ac[MH] = 1;
						awe[i][j][k] = 0;
						age[i][j][k] = 0;
						aE[MH] = 0;
						awn[i][j][k] = 0;
						agn[i][j][k] = 0;
						aN[MH] = 0;
						aws[i][j][k] = 0;
						ags[i][j][k] = 0;
						aSt[MH] = 0;
						awt[i][j][k] = 0;
						agt[i][j][k] = 0;
						aT[MH] = 0;
						awb[i][j][k] = 0;
						agb[i][j][k] = 0;
						aB[MH] = 0;
					}
				}
				if(j == 0)
				{
					if(BCS == 0)
					{
						// Keep the same values
					}
					else if(BCS == 1)
					{
						ac[MH] = 1;
						awn[i][j][k] = 0;
						agn[i][j][k] = 0;
						aN[MH] = 0;
						aww[i][j][k] = 0;
						agw[i][j][k] = 0;
						aW[MH] = 0;
						awe[i][j][k] = 0;
						age[i][j][k] = 0;
						aE[MH] = 0;
						awt[i][j][k] = 0;
						agt[i][j][k] = 0;
						aT[MH] = 0;
						awb[i][j][k] = 0;
						agb[i][j][k] = 0;
						aB[MH] = 0;
					}
				}
				if(k == 0)
				{
					if(BCT == 0)
					{
						// Keep the same values
					}
					else if(BCT == 1)
					{
						ac[MH] = 1;
						awb[i][j][k] = 0;
						agb[i][j][k] = 0;
						aB[MH] = 0;
						aww[i][j][k] = 0;
						agw[i][j][k] = 0;
						aW[MH] = 0;
						awe[i][j][k] = 0;
						age[i][j][k] = 0;
						aE[MH] = 0;
						awn[i][j][k] = 0;
						agn[i][j][k] = 0;
						aN[MH] = 0;
						aws[i][j][k] = 0;
						ags[i][j][k] = 0;
						aSt[MH] = 0;
					}
				}
				if(i == nx - 1)
				{
					if(BCE == 0)
					{
						// Keep the same values
					}
					else if(BCE == 1)
					{
						ac[MH] = 1;
						aww[i][j][k] = 0;
						agw[i][j][k] = 0;
						aW[MH] = 0;
						awn[i][j][k] = 0;
						agn[i][j][k] = 0;
						aN[MH] = 0;
						aws[i][j][k] = 0;
						ags[i][j][k] = 0;
						aSt[MH] = 0;
						awt[i][j][k] = 0;
						agt[i][j][k] = 0;
						aT[MH] = 0;
						awb[i][j][k] = 0;
						agb[i][j][k] = 0;
						aB[MH] = 0;
					}
				}
				if(j == ny - 1)
				{
					if(BCN == 0)
					{
						// Keep the same values
					}
					else if (BCN == 1)
					{
						ac[MH] = 1;
						aws[i][j][k] = 0;
						ags[i][j][k] = 0;
						aSt[MH] = 0;
						aww[i][j][k] = 0;
						agw[i][j][k] = 0;
						aW[MH] = 0;
						awe[i][j][k] = 0;
						age[i][j][k] = 0;
						aE[MH] = 0;
						awt[i][j][k] = 0;
						agt[i][j][k] = 0;
						aT[MH] = 0;
						awb[i][j][k] = 0;
						agb[i][j][k] = 0;
						aB[MH] = 0;
					}
				}
				if(k == nz - 1)
				{
					if(BCB == 0)
					{
						// Keep the same values
					}
					else if(BCB == 1)
					{
						ac[MH] = 1;
						awt[i][j][k] = 0;
						agt[i][j][k] = 0;
						aT[MH] = 0;
						aww[i][j][k] = 0;
						agw[i][j][k] = 0;
						aW[MH] = 0;
						awe[i][j][k] = 0;
						age[i][j][k] = 0;
						aE[MH] = 0;
						awn[i][j][k] = 0;
						agn[i][j][k] = 0;
						aN[MH] = 0;
						aws[i][j][k] = 0;
						ags[i][j][k] = 0;
						aSt[MH] = 0;
					}
				}
			}
		}
	}
}
//*********************************
void MatrixB()
{
	int i, j, k, MH;
	MH = -1;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				MH = MH + 1;
				betha[i][j][k] = PV[i][j][k] * CTOT[i][j][k] / dt1;
				//Well Constraints
				if(!strcmp(WellConstraint[i][j][k], "WRATE") ||
					!strcmp(WellConstraint[i][j][k], "GRATE") ||
					!strcmp(WellConstraint[i][j][k], "2RATE"))
				{
					MB[MH] = -betha[i][j][k] * pn[i][j][k] + QT[i][j][k];
				}
				else if(!strcmp(WellConstraint[i][j][k], "PRESSURE"))
				{
					MB[MH] = -betha[i][j][k] * pn[i][j][k] - JMODEL[i][j][k] * LambdaT[i][j][k] * Pwf[i][j][k];
				}
				else
				{
					MB[MH] = -betha[i][j][k] * pn[i][j][k];
				}
				//Boundary conditions
				if(i == 0)
				{
					if(BCW == 0)
					{
						// Keep the same values
					}
					else if(BCW == 1)
					{
						MB[MH] = Pinit;
					}
				}
				if(j == 0)
				{
					if(BCS == 0)
					{
						// Keep the same values
					}
					else if(BCS == 1)
					{
						MB[MH] = Pinit;
					}
				}
				if(k == 0)
				{
					if(BCT == 0)
					{
						// Keep the same values
					}
					else if(BCT == 1)
					{
						MB[MH] = Pinit;
					}
				}
			}
			if(i == nx - 1)
			{
				if(BCE == 0)
				{
					// Keep the same values
				}
				else if(BCE == 1)
				{
					MB[MH] = Pinit;
				}
			}
			if(j == ny - 1)
			{
				if(BCN == 0)
				{
					// Keep the same values
				}
				else if(BCN == 1)
				{
					MB[MH] = Pinit;
				}
			}
			if(k == nz-1)
			{
				if(BCB == 0)
				{
					// Keep the same values
				}
				else if(BCB == 1)
				{
					MB[MH] = Pinit;
				}
			}
		}
	}
}
//*********************************
/*void MemAlloc()
{
	//Allocate memory for variables after reading data
	ReDim p(nx, ny, nz), pn(nx, ny, nz)
ReDim BOI(nx, ny, nz), BWI(nx, ny, nz), BGI(nx, ny, nz), RSOI(nx, ny, nz), BOI1(nx, ny, nz), BWI1(nx, ny, nz), _
BGI1(nx, ny, nz), RSOI1(nx, ny, nz)
ReDim UOI(nx, ny, nz), UWI(nx, ny, nz), UGI(nx, ny, nz)
ReDim COI(nx, ny, nz), CWI(nx, ny, nz), CGI(nx, ny, nz), CTOT(nx, ny, nz)
ReDim UOavw(nx, ny, nz), UWavw(nx, ny, nz), UGavw(nx, ny, nz), _
UOavs(nx, ny, nz), UWavs(nx, ny, nz), UGavs(nx, ny, nz), _
UOavb(nx, ny, nz), UWavb(nx, ny, nz), UGavb(nx, ny, nz)
ReDim BOavw(nx, ny, nz), BWavw(nx, ny, nz), BGavw(nx, ny, nz), _
BOavs(nx, ny, nz), BWavs(nx, ny, nz), BGavs(nx, ny, nz), _
BOavb(nx, ny, nz), BWavb(nx, ny, nz), BGavb(nx, ny, nz)
ReDim UOave(nx, ny, nz), UWave(nx, ny, nz), UGave(nx, ny, nz), _
UOavn(nx, ny, nz), UWavn(nx, ny, nz), UGavn(nx, ny, nz), _
UOavt(nx, ny, nz), UWavt(nx, ny, nz), UGavt(nx, ny, nz)
ReDim BOave(nx, ny, nz), BWave(nx, ny, nz), BGave(nx, ny, nz), _
BOavn(nx, ny, nz), BWavn(nx, ny, nz), BGavn(nx, ny, nz), _
BOavt(nx, ny, nz), BWavt(nx, ny, nz), BGavt(nx, ny, nz)
ReDim RSOavw(nx, ny, nz), RSOave(nx, ny, nz), _
RSOavs(nx, ny, nz), RSOavn(nx, ny, nz), _
RSOavb(nx, ny, nz), RSOavt(nx, ny, nz)
ReDim KRWI(nx, ny, nz), KROWI(nx, ny, nz), KRGI(nx, ny, nz), KROGI(nx, ny, nz), KROI(nx, ny, nz)
ReDim SOI(nx, ny, nz), SWI(nx, ny, nz), SGI(nx, ny, nz), SLI(nx, ny, nz)
ReDim SOI1(nx, ny, nz), SWI1(nx, ny, nz), SGI1(nx, ny, nz), SLI1(nx, ny, nz)
ReDim PV(nx, ny, nz), PV1(nx, ny, nz), OOIP(nx, ny, nz), OWIP(nx, ny, nz), OGIP(nx, ny, nz)
ReDim TypeWell(nx, ny, nz), WellConstraint(nx, ny, nz), rw(nx, ny, nz), Skin(nx, ny, nz), Pwf(nx, ny, nz)
ReDim MinBHP(nx, ny, nz), QO(nx, ny, nz), QW(nx, ny, nz), QG(nx, ny, nz)
ReDim QT(nx, ny, nz), JMODEL(nx, ny, nz), ro(nx, ny, nz), dx(nx, ny, nz), dy(nx, ny, nz), dz(nx, ny, nz)
ReDim LambdaO(nx, ny, nz), LambdaW(nx, ny, nz), LambdaG(nx, ny, nz), LambdaT(nx, ny, nz)
ReDim TW(nx, ny, nz), TE(nx, ny, nz), TN(nx, ny, nz), TS(nx, ny, nz), TT(nx, ny, nz), TB(nx, ny, nz), _
aow(nx, ny, nz), aww(nx, ny, nz), agw(nx, ny, nz), aoe(nx, ny, nz), awe(nx, ny, nz), age(nx, ny, nz), _
aon(nx, ny, nz), awn(nx, ny, nz), agn(nx, ny, nz), aos(nx, ny, nz), aws(nx, ny, nz), ags(nx, ny, nz), _
aot(nx, ny, nz), awt(nx, ny, nz), agt(nx, ny, nz), aob(nx, ny, nz), awb(nx, ny, nz), agb(nx, ny, nz)
ReDim betha(nx, ny, nz) As Double
ReDim Sat_diff(nx, ny, nz) As Double
}*/
//*********************************
void Matrix_Solver()
{
	int i, j, k;
	long int MH;
	CMAT(aW, aE, aSt, aN, aT, aB, ac, MB, TOL, II, JJ, KKK,
		IJKM, ITMAX, QI, AQI, AL3, AL2, AL1, AD, AU1, AU2,
		AU3, QN, AQN, RN, DXN, ADX, Psim, IT);
	//Update pressure at i,j,k coordinates
	MH = -1;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				MH = MH + 1;
				p[i][j][k] = Psim[MH];
			}
		}
	}
}
//*********************************
void AllocateMemory_Matrix(int IJKM)
{}
	/*ReDim aW(1 To IJKM)
ReDim aE(1 To IJKM)
ReDim aSt(1 To IJKM)
ReDim aN(1 To IJKM)
ReDim aT(1 To IJKM)
ReDim aB(1 To IJKM)
ReDim ac(1 To IJKM)
ReDim MB(1 To IJKM)
ReDim r(1 To IJKM)
ReDim Psim(1 To IJKM)
ReDim AL3(1 To IJKM)
ReDim AL2(1 To IJKM)
ReDim AL1(1 To IJKM)
ReDim AD(1 To IJKM)
ReDim AU1(1 To IJKM)
ReDim AU2(1 To IJKM)
ReDim AU3(1 To IJKM)
ReDim QI(1 To 15, 1 To IJKM)
ReDim AQI(1 To 15, 1 To IJKM)
ReDim QN(1 To IJKM)
ReDim AQN(1 To IJKM)
ReDim RN(1 To IJKM)
ReDim DXN(1 To IJKM)
ReDim ADX(1 To IJKM)*/
//*********************************
void Matrix_Initial()
{
	//Orthomin Matrix Solver//s Parameter
	II = nx;
	JJ = ny;
	KKK = nz;
	IJKM = II;
	IJKM = IJKM * JJ;
	IJKM = IJKM * KKK;
	ITMAX = 50;
	AllocateMemory_Matrix(IJKM);
	TOL = 0.000001;
}
//*********************************
void CMAT(double aW[],double aE[],double aSt[],double aN[],
	double aT[],double aB[],double ac[],double MB[],double TOL,
	int II,int JJ,int KKK,long int IJKM,double ITMAX,double QI[][100000],
	double AQI[][100000],double AL3[],double AL2[],double AL1[],double AD[],
	double AU1[],double AU2[],double AU3[],double QN[],double AQN[],
	double RN[],double DXN[],double ADX[],double Psim[],long int IT)
{
	int INX;
	int i, j, k;
	double FAC;
	double TERM;
	int INXY;
	long int IB;
	// ORTHOMIN SPARSE MATRIX SOLVER BASED ON PAPER BY P. K. W. VINSOME
	// FOUTH SYMPOSIUM ON RESERVOIR SIMULATION
	// LOS ANGELES, CALIFORNIA FEBRUARY 19-20,1976
	INX = II;
	INXY = II * JJ;
	IB = -1;
	for(k = 0;k < KKK;k++)
	{
		for(j = 0;j < JJ;j++)
		{
			for(i = 0;i < II;i++)
			{
				IB = IB + 1;
				FAC = 1 / ac[IB];
				if(i != 0)
				{
					AL1[IB] = FAC * aW[IB];
				}
				if(i != II - 1)
				{
					AU1[IB] = FAC * aE[IB];
				}
				if(j != 0)
				{
					AL2[IB] = FAC * aSt[IB];
				}
				if(j != JJ - 1)
				{
					AU2[IB] = FAC * aN[IB];
				}
				if(k != 0)
				{
					AL3[IB] = FAC * aT[IB];
				}
				if(k != KKK - 1)
				{
					AU3[IB] = FAC * aB[IB];
				}
				RN[IB] = FAC * MB[IB];
			}
		}
	}
	// APPROXIMATE LDU FACTORIZATION
	AD[0] = 1;
	for(i = 1;i < INX;i++)
	{
		TERM = 1 - AL1[i] * AD[i - 1] * AU1[i - 1];
		AD[i] = 1 / TERM;
	}
	for(i = INX ;i < INXY;i++)
	{
		TERM = 1 - AL1[i] * AD[i - 1] * AU1[i - 1] -
			AL2[i] * AD[i - INX] * AU2[i - INX];
		AD[i] = 1 / TERM;
	}
	for(i = INXY;i < IJKM;i++)
	{
		TERM = 1 - AL1[i] * AD[i - 1] * AU1[i - 1] -
			AL2[i] * AD[i - INX] * AU2[i - INX] -
			AL3[i] * AD[i - INXY] * AU3[i - INXY];
		AD[i] = 1 / TERM;
	}
	ORTH(AL3, AL2, AL1, AD, AU1, AU2, AU3, TOL,
		INX, INXY, IJKM, ITMAX, RN, DXN, ADX, QI,
		AQI, QN, AQN, Psim, IT);
}
//*********************************
void MVEC(double AL3[],double AL2[],double AL1[],double AU1[],
	double AU2[],double AU3[],double r[],int INX,int INXY,
	long int IJKM,double c[])
{
	long int i;
	for(i = 0;i < IJKM;i++)
	{
		c[i] = r[i];
	}
	for(i = 0;i < IJKM - 1;i++)
	{
		c[i] = c[i] + AU1[i] * r[i + 1];
	}
	for(i = 0;i < IJKM - INX;i++)
	{
		c[i] = c[i] + AU2[i] * r[i + INX];
	}
	for(i = 0;i < IJKM - INXY;i++)
	{
		c[i] = c[i] + AU3[i] * r[i + INXY];
	}
	for( i = 1;i < IJKM;i++)
	{
		c[i] = c[i] + AL1[i] * r[i - 1];
	}
	for(i = INX;i < IJKM;i++)
	{
		c[i] = c[i] + AL2[i] * r[i - INX];
	}
	for(i = INXY;i < IJKM;i++)
	{
		c[i] = c[i] + AL3[i] * r[i - INXY];
	}
}
//*********************************
void ORTH(double AL3[],double AL2[],double AL1[],double AD[],
	double AU1[],double AU2[],double AU3[],double TOL,int INX,
	int INXY,long int IJKM,double ITMAX,double RN[],double DXN[],
	double ADX[],double QI[][100000],double AQI[][100000],double QN[],
	double AQN[],double DP[],long int IT)
{
	double Rsq;
	long int nmax;
	long int N;
	double CONV, CONV1;
	long int NM1;
	long int IB;
	long int ITER;
	long int i;
	double omega;
	double AI;
	double AQIAQI[100];
	double AQIADX;
	double AQNAQN;
	double AQNRN;
	//ReDim AQIAQI(IJKM)
	// ======== temp
	nmax = 14;
	// ======== temp
	CONV1 = TOL * TOL;
	if(CONV1 > 0.0001)
	{
		CONV1 = 0.0001;
	}
	Rsq = 0;
	for(IB = 0;IB < IJKM;IB++)
	{
		DP[IB] = 0;
		Rsq = Rsq + RN[IB] * RN[IB];
	}
	CONV = CONV1 * Rsq;
	N = -1;
	for(ITER = 0;ITER < ITMAX;ITER++)
	{
		IT = ITER;
		if(N == nmax)
		{
			N = -1;
		}
		N = N + 1;
		NM1 = N - 1;
		MSOLVE(AL3, AL2, AL1, AD, AU1, AU2, AU3, RN, INX, INXY, IJKM, DXN);
		MVEC(AL3, AL2, AL1, AU1, AU2, AU3, DXN, INX, INXY, IJKM, ADX);
		if(N == 0)
		{
			for(IB = 0;IB < IJKM;IB++)
			{
				QN[IB] = DXN[IB];
				AQN[IB] = ADX[IB];
				QI[0][IB] = QN[IB];
				AQI[0][IB] = AQN[IB];
			}
		}
		else
		{
			for(IB = 0;IB < IJKM;IB++)
			{
				QN[IB] = DXN[IB];
			}
			for(i = 0;i < NM1 + 1;i++)
			{
				AQIADX = 0;
				for(IB = 0;IB < IJKM;IB++)
				{
					AQIADX = AQIADX + AQI[i][IB] * ADX[IB];
				}
				AI = AQIADX / AQIAQI[i];
				for(IB = 0;IB < IJKM;IB++)
				{
					QN[IB] = QN[IB] - AI * QI[i][IB];
				}
			}
			MVEC(AL3, AL2, AL1, AU1, AU2, AU3, QN,
				INX, INXY, IJKM, AQN);
			for(IB = 0;IB < IJKM;IB++)
			{
				QI[N][IB] = QN[IB];
				AQI[N][IB] = AQN[IB];
			}
		}
		AQNAQN = 0;
		AQNRN = 0;
		for(IB = 0;IB < IJKM;IB++)
		{
			AQNAQN = AQNAQN + AQN[IB] * AQN[IB];
			AQNRN = AQNRN + AQN[IB] * RN[IB];
		}
		AQIAQI[N] = AQNAQN;
		omega = AQNRN / AQNAQN;
		Rsq = 0;
		for(IB = 0;IB < IJKM;IB++)
		{
			DP[IB] = DP[IB] + omega * QN[IB];
			RN[IB] = RN[IB] - omega * AQN[IB];
			Rsq = Rsq + RN[IB] * RN[IB];
		}
		if(Rsq <= CONV)
		{
			break;	//GoTo line900
		}
	}
	// MsgBox " ORTHOMIN DID NOT CONVERGE IN " & ITER & " ITERATIONS"
	//line900:
}
//*********************************
void MSOLVE(double AL3[],double AL2[],double AL1[],double AD[],
	double AU1[],double AU2[],double AU3[],double r[],int INX, 
	int INXY,long int IJKM,double XX[])
{
	long int i;
	XX[0] = AD[0] * r[0];
	for(i = 1;i < INX;i++)
	{
		XX[i] = AD[i] * (r[i] - AL1[i] * XX[i - 1]);
	}
	for(i = INX;i < INXY;i++)
	{
		XX[i] = AD[i] * (r[i] - AL1[i] * XX[i - 1] - AL2[i] * XX[i - INX]);
	}
	for(i = INXY;i < IJKM;i++)
	{
		XX[i] = AD[i] * (r[i] - AL1[i] * XX[i - 1] - AL2[i] * XX[i - INX] -
			AL3[i] * XX[i - INXY]);
	}
	for(i = 0;i < IJKM;i++)
	{
		XX[i] = XX[i] / AD[i];
	}
	//
	// BACK SUBSTITUTION
	//
	for(i = IJKM - 2;i >= IJKM - INX;i--)
	{
		XX[i] = AD[i] * (XX[i] - AU1[i] * XX[i + 1]);
	}
	for(i = IJKM - INX - 1;i >= IJKM - INXY;i--)
	{
		XX[i] = AD[i] * (XX[i] - AU1[i] * XX[i + 1] - AU2[i] * XX[i + INX]);
	}
	for(i = IJKM - INXY - 1;i >= 0;i--)
	{
		XX[i] = AD[i] * (XX[i] - AU1[i] * XX[i + 1] - AU2[i] * XX[i + INX] -
			AU3[i] * XX[i + INXY]);
	}
}
//*********************************
void Read_data()
{
	char InputFile[100];
	char Tablename[100], text[100];
	double PR[100];
	int i, j, k, m;
	char convar[100];
	char c;
	FILE *Input;
	strcpy_s(InputFile,"InputOutput\\3D2PH_2.txt");
	if(fopen_s(&Input, InputFile, "r"))
	{
		return;
	}
	//line #1
	while(fgetc(Input) != '\n');
	//line #2
	while(fgetc(Input) != '\n');
	//line #3 nx
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t');
	text[i] = '\0';
	nx = atoi(text);
	//line #3 space
	c = fgetc(Input);
	while(c == ' ' || c == '\t')
	{
		c = fgetc(Input);
	}
	//line #3 ny
	i = 0;
	text[i] = c;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t');
	text[i] = '\0';
	ny = atoi(text);
	//line #3 space
	c = fgetc(Input);
	while(c == ' ' || c == '\t')
	{
		c = fgetc(Input);
	}
	//line #3 nz
	i=0;
	text[i] = c;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	nz = atoi(text);
	//GRID BLOCKS GENERATION*/
	//line #4
	while(fgetc(Input) != '\n');
	//line #5 xtype
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	strcpy_s(convar, text);
	_strupr_s(convar);
	if(!strcmp(convar, "CONST"))
	{
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != '\n');
		text[i] = '\0';
		Xsize = atof(text);
		xD[0][0][0] = Xsize;
		for(m = 1;m < nx;m++)
		{
			xD[m][0][0] = xD[m - 1][0][0] + Xsize;
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					xD[i][j][k] = xD[i][0][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "IVARIABLE"))
	{
		for (m = 0;m < nx;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			xThick[m][0][0] = atof(text);
		}
		xD[0][0][0] = xThick[0][0][0];
		for(m = 1;m < nx;m++)
		{
			xD[m][0][0] = xD[m - 1][0][0] + xThick[m][0][0];
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					xD[i][j][k] = xD[i][0][0];
				}
			}
		}
	}
	//line #6
	while(fgetc(Input) != '\n');
	//line #7 ytype
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	strcpy_s(convar, text);
	_strupr_s(convar);
	if(!strcmp(convar, "CONST"))
	{
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != '\n');
		text[i] = '\0';
		Ysize = atof(text);
		yD[0][0][0] = Ysize;
		for(m = 1;m < ny;m++)
		{
			yD[0][m][0] = yD[0][m - 1][0] + Ysize;
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					yD[i][j][k] = yD[0][j][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "JVARIABLE"))
	{
		for (m = 0;m < ny;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			yThick[0][m][0] = atof(text);
		}
		yD[0][0][0] = yThick[0][0][0];
		for(m = 1;m < ny;m++)
		{
			yD[0][m][0] = yD[0][m - 1][0] + yThick[0][m][0];
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					yD[i][j][k] = yD[0][j][0];
				}
			}
		}
	}
	//line #8
	while(fgetc(Input) != '\n');
	//line #9 ztype
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	strcpy_s(convar, text);
	_strupr_s(convar);
	if(!strcmp(convar, "CONST"))
	{
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != '\n');
		text[i] = '\0';
		Zsize = atof(text);
		zD[0][0][0] = Zsize;
		for(m = 1;m < nz;m++)
		{
			zD[0][0][m] = zD[0][0][m - 1] + Zsize;
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					zD[i][j][k] = zD[0][0][k];
				}
			}
		}
	}
	else if(!strcmp(convar, "KVARIABLE"))
	{
		for (m = 0;m < nz;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			zThick[0][0][m] = atof(text);
		}
		zD[0][0][0] = zThick[0][0][0];
		for(m = 1;m < nz;m++)
		{
			zD[0][0][m] = zD[0][0][m - 1] + zThick[0][0][m];
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					zD[i][j][k] = zD[0][0][k];
				}
			}
		}
	}
	//POROSITY ENTRIES
	//line #10
	while(fgetc(Input) != '\n');
	//line #11 POROSITY
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	strcpy_s(convar, text);
	_strupr_s(convar);
	if(!strcmp(convar, "CONST"))
	{
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != '\n');
		text[i] = '\0';
		poro[0][0][0] = atof(text);
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					poro[i][j][k] = poro[0][0][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "IVARIABLE"))
	{
		for (m = 0;m < nx;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			poro[m][0][0] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					poro[i][j][k] = poro[i][0][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "JVARIABLE"))
	{
		for (m = 0;m < ny;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			poro[0][m][0] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					poro[i][j][k] = poro[0][j][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "KVARIABLE"))
	{
		for (m = 0;m < nz;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			poro[0][0][m] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					poro[i][j][k] = poro[0][0][k];
				}
			}
		}
	}
	//PERMEABILITY ENTRIES
	//I DIRECTION PERMEABILITY
	//line #12
	while(fgetc(Input) != '\n');
	//line #13 permX
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	strcpy_s(convar, text);
	_strupr_s(convar);
	if(!strcmp(convar, "CONST"))
	{
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != '\n');
		text[i] = '\0';
		permX[0][0][0] = atof(text);
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permX[i][j][k] = permX[0][0][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "IVARIABLE"))
	{
		for (m = 0;m < nx;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			permX[m][0][0] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permX[i][j][k] = permX[i][0][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "JVARIABLE"))
	{
		for (m = 0;m < ny;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			permX[0][m][0] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permX[i][j][k] = permX[0][j][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "KVARIABLE"))
	{
		for (m = 0;m < nz;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			permX[0][0][m] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permX[i][j][k] = permX[0][0][k];
				}
			}
		}
	}
	//J DIRECTION PERMEABILITY
	//line #14
	while(fgetc(Input) != '\n');
	//line #15 permY
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	strcpy_s(convar, text);
	_strupr_s(convar);
	if(!strcmp(convar, "CONST"))
	{
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != '\n');
		text[i] = '\0';
		permY[0][0][0] = atof(text);
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permY[i][j][k] = permY[0][0][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "IVARIABLE"))
	{
		for (m = 0;m < nx;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			permY[m][0][0] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permY[i][j][k] = permY[i][0][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "JVARIABLE"))
	{
		for (m = 0;m < ny;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			permY[0][m][0] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permY[i][j][k] = permY[0][j][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "KVARIABLE"))
	{
		for (m = 0;m < nz;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			permY[0][0][m] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permY[i][j][k] = permY[0][0][k];
				}
			}
		}
	}
	//K DIRECTION PERMEABIITY
	//line #16
	while(fgetc(Input) != '\n');
	//line #17 permZ
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	strcpy_s(convar, text);
	_strupr_s(convar);
	if(!strcmp(convar, "CONST"))
	{
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != '\n');
		text[i] = '\0';
		permZ[0][0][0] = atof(text);
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permZ[i][j][k] = permZ[0][0][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "IVARIABLE"))
	{
		for (m = 0;m < nx;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			permZ[m][0][0] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permZ[i][j][k] = permZ[i][0][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "JVARIABLE"))
	{
		for (m = 0;m < ny;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			permZ[0][m][0] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permZ[i][j][k] = permZ[0][j][0];
				}
			}
		}
	}
	else if(!strcmp(convar, "KVARIABLE"))
	{
		for (m = 0;m < nz;m++)
		{
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n' && text[i] != ' ' && text[i] != '\t');
			text[i] = '\0';
			permZ[0][0][m] = atof(text);
		}
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permZ[i][j][k] = permZ[0][0][k];
				}
			}
		}
	}
	else if(!strcmp(convar, "EQUALI"))
	{
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permZ[i][j][k] = permX[i][j][k];
				}
			}
		}
	}
	else if(!strcmp(convar, "EQUALJ"))
	{
		for (k = 0;k < nz;k++)
		{
			for (j = 0;j < ny;j++)
			{
				for (i = 0;i < nx;i++)
				{
					permZ[i][j][k] = permY[i][j][k];
				}
			}
		}
	}
	//Cf
	//line #18
	while(fgetc(Input) != '\n');
	//line #19 Cf
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
	text[i] = '\0';
	Cf = atof(text);
	//PVT
	//line #20 TableName
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
	text[i] = '\0';
	strcpy_s(Tablename, text);
	_strupr_s(Tablename);
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
	text[i] = '\0';
	npvt = atoi(text);
	//line #21
	while(fgetc(Input) != '\n');
	for(m = 0;m < npvt;m++)
	{
		//line #22 Ppvt
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t');
		text[i] = '\0';
		Ppvt[m] = atof(text);
		//line #22 space
		c = fgetc(Input);
		while(c == ' ' || c == '\t')
		{
			c = fgetc(Input);
		}
		//line #22 BW
		i = 0;
		text[i] = c;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t');
		text[i] = '\0';
		BW[m] = atof(text);
		//line #22 space
		c = fgetc(Input);
		while(c == ' ' || c == '\t')
		{
			c = fgetc(Input);
		}
		//line #22 UW
		i = 0;
		text[i] = c;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t');
		text[i] = '\0';
		UW[m] = atof(text);
		//line #22 space
		c = fgetc(Input);
		while(c == ' ' || c == '\t')
		{
			c = fgetc(Input);
		}
		//line #22 CW
		i = 0;
		text[i] = c;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t');
		text[i] = '\0';
		CW[m] = atof(text);
		//line #22 space
		c = fgetc(Input);
		while(c == ' ' || c == '\t')
		{
			c = fgetc(Input);
		}
		//line #22 BG
		i = 0;
		text[i] = c;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t');
		text[i] = '\0';
		BG[m] = atof(text);
		//line #22 space
		c = fgetc(Input);
		while(c == ' ' || c == '\t')
		{
			c = fgetc(Input);
		}
		//line #22 UG
		i = 0;
		text[i] = c;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t');
		text[i] = '\0';
		UG[m] = atof(text);
		//line #22 space
		c = fgetc(Input);
		while(c == ' ' || c == '\t')
		{
			c = fgetc(Input);
		}
		//line #22 CG
		i = 0;
		text[i] = c;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
		c = text[i];
		text[i] = '\0';
		CG[m] = atof(text);
		if(c != '\n')
		{
			//line #22 space
			c = fgetc(Input);
			while(c == ' ' || c == '\t' || text[i] == '\n');
			{
				c = fgetc(Input);
			}
		}
	}
	//line #23
	while(fgetc(Input) != '\n');
	//line #24
	while(fgetc(Input) != '\n');
	//RELATIVE PERM
	//line #25 nkr
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
	text[i] = '\0';
	nkr = atoi(text);
	//line #26
	while(fgetc(Input) != '\n');
	for(m = 0;m < nkr;m++)
	{
		//line #27 SW
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t');
		text[i] = '\0';
		SW[m] = atof(text);
		//line #27 space
		c = fgetc(Input);
		while(c == ' ' || c == '\t')
		{
			c = fgetc(Input);
		}
		//line #27 KRW
		i = 0;
		text[i] = c;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
		c = text[i];
		text[i] = '\0';
		KRW[m] = atof(text);
		if(c != '\n')
		{
			//line #27 space
			c = fgetc(Input);
			while(c == ' ' || c == '\t' || text[i] == '\n');
			{
				c = fgetc(Input);
			}
		}
	}
	//line #28
	while(fgetc(Input) != '\n');
	//line #29 nkrg
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
	text[i] = '\0';
	nkrg = atoi(text);
	//line #30
	while(fgetc(Input) != '\n');
	for(m = 0;m < nkrg;m++)
	{
		//line #31 SG
		i = -1;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t');
		text[i] = '\0';
		SG[m] = atof(text);
		//line #31 space
		c = fgetc(Input);
		while(c == ' ' || c == '\t')
		{
			c = fgetc(Input);
		}
		//line #31 KRG
		i = 0;
		text[i] = c;
		do
		{
			i++;
			text[i] = fgetc(Input);
		}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
		c = text[i];
		text[i] = '\0';
		KRG[m] = atof(text);
		if(c != '\n')
		{
			//line #31 space
			c = fgetc(Input);
			while(c == ' ' || c == '\t' || text[i] == '\n');
			{
				c = fgetc(Input);
			}
		}
	}
	//line #32
	while(fgetc(Input) != '\n');
	//line #33
	while(fgetc(Input) != '\n');
	//line #34 SWF
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
	text[i] = '\0';
	SWC = atof(text);
	//line #35
	while(fgetc(Input) != '\n');
	//line #36 Pinit
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
	text[i] = '\0';
	Pinit = atof(text);
	//line #37
	while(fgetc(Input) != '\n');
	//line #38
	while(fgetc(Input) != '\n');
	//line #39 BCW
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	BCW = atoi(text);
	//line #39 BCE
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	BCE = atoi(text);
	//line #39 BCS
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	BCS = atoi(text);
	//line #39 BCN
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	BCN = atoi(text);
	//line #39 BCB
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	BCB = atoi(text);
	//line #39 BCT
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	c = text[i];
	text[i] = '\0';
	BCT = atoi(text);
	//line #40
	while(fgetc(Input) != '\n');
	//line #41 dt
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	dt = atof(text);
	//line #41 tmax
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	tmax = atoi(text);
	//line #41 Satmax
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	text[i] = '\0';
	Satmax = atof(text);
	//line #41 ncuts
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != '\n');
	c = text[i];
	text[i] = '\0';
	ncuts = atoi(text);
	//line #42
	while(fgetc(Input) != '\n');
	//line #43 nwells
	i = -1;
	do
	{
		i++;
		text[i] = fgetc(Input);
	}while(text[i] != ' ' && text[i] != '\t' && text[i] != '\n');
	text[i] = '\0';
	nwell = atoi(text);
	if(nwell != 0)
	{
		while(fgetc(Input) != '\n');
		for(m = 0;m < nwell;m++)
		{
			//line #44 Wellname
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			strcpy_s(Wellname[m], text);
			_strupr_s(Wellname[m]);
			//line #44 XCoor
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			XCoor[m] = atoi(text) - 1;
			//line #44 YCoor
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			YCoor[m] = atoi(text) - 1;
			//line #44 ZCoor
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			ZCoor[m] = atoi(text) - 1;
			//line #44 rw_read
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			rw_read[m] = atof(text);
			//line #44 Skin_read
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			Skin_read[m] = atof(text);
			//line #44 TypeWell
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			c = text[i];
			text[i] = '\0';
			strcpy_s(TypeWell_read[m], text);
			_strupr_s(TypeWell_read[m]);
		}
		while(fgetc(Input) != '\n');
		for(m = 0;m < nwell;m++)
		{
			//line #45 PR
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			PR[m] = atof(text);
			//line #39 BCE
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			QW_read[m] = atoi(text);
			//line #39 BCS
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			QG_read[m] = atoi(text);
			//line #39 BCN
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			text[i] = '\0';
			Pwf_read[m] = atoi(text);
			//line #39 BCB
			i = -1;
			do
			{
				i++;
				text[i] = fgetc(Input);
			}while(text[i] != '\n');
			c = text[i];
			text[i] = '\0';
			MinBHP_read[m] = atof(text);
		}
	}
	fclose(Input);
}
//*********************************
void Identify_constraints()
{
	int i, j, k;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				if(QW[i][j][k] != 0)
				{
					strcpy_s(WellConstraint[i][j][k], "WRATE");
					_strupr_s(WellConstraint[i][j][k]);
				}
				if(QG[i][j][k] != 0)
				{
					strcpy_s(WellConstraint[i][j][k], "GRATE");
					_strupr_s(WellConstraint[i][j][k]);
				}
				if(QG[i][j][k] != 0 && QW[i][j][k] != 0)
				{
					strcpy_s(WellConstraint[i][j][k], "2RATE");
					_strupr_s(WellConstraint[i][j][k]);
				}
				if(Pwf[i][j][k] != 0)
				{
					strcpy_s(WellConstraint[i][j][k], "PRESSURE");
					_strupr_s(WellConstraint[i][j][k]);
				}
			}
		}
	}
}
//*********************************
void Fluids_In_Place()
{
	int i, j, k;
	TotalWIP = 0;
	TotalGIP = 0;
	for (k = 0;k < nz;k++)
	{
		for (j = 0;j < ny;j++)
		{
			for (i = 0;i < nx;i++)
			{
				TotalWIP = TotalWIP + OWIP[i][j][k];
				TotalGIP = TotalGIP + OGIP[i][j][k];
			}
		}
	}
	//Cleare content of output file
	//char OutputFile[100];
	FILE *Output;
	//strcpy_s(OutputFile,"InputOutput\\3D2PH_2.out");
	if(fopen_s(&Output,outputTextFilem, "w"))
	{
		return;
	}
	fprintf(Output, "Simulation Output Results");
	fprintf(Output, "\n");
	fprintf(Output, "\nFluids in place");
	fprintf(Output, "\nOWIP =\t%10.2f MMSTB",TotalWIP / (1000000 * 5.615));
	fprintf(Output, "\nOGIP =\t%10.2f MMSCF",TotalGIP / 1000000);
	fprintf(Output, "\n");
	fclose(Output);
}
//*********************************
void Print_Report()
{
	int i, j, k, m;
	double AverageVar = 0;	//Stor Average of Pressure , Gas Saturation or water Saturation per step
	//char OutputFile[100];
	FILE *Output;
	//strcpy_s(OutputFile,"InputOutput\\3D2PH_2.out");
	if(fopen_s(&Output,outputTextFilem, "a"))
	{
		return;
	}
	printf("\nTime step: %d", timep);
	fprintf(Output, "\nTime step: %d", timep);
	fprintf(Output, "\n");
	//Print pressure at grid blocks
	fprintf(Output, "\nPressure");
	AverageVar = 0;	//Initial to 0
	for (k = 0;k < nz;k++)
	{
		fprintf(Output, "\nk= %d", k+1);
		for (j = 0;j < ny;j++)
		{
			fprintf(Output, "\n");
			for (i = 0;i < nx;i++)
			{
				fprintf(Output, "%8.2f\t", pn[i][j][k]);
				pChart[(((rc * (int)dt) / (tmax / 4)) % 4)][i][j][k] = pn[i][j][k];
				AverageVar += pn[i][j][k];
			}
		}
		pressurStepsvalue[rc - 1][k] = AverageVar / (nx * ny);
		AverageVar = 0;
		if(pminmax[0] > pressurStepsvalue[rc - 1][k])
		{
			pminmax[0] = pressurStepsvalue[rc - 1][k];
		}
		if(pminmax[1] < pressurStepsvalue[rc - 1][k])
		{
			pminmax[1] = pressurStepsvalue[rc - 1][k];
		}
	}
	
	//Print Water saturation at every grid block
	fprintf(Output, "\n");
	fprintf(Output, "\nWater Saturation");
	AverageVar = 0;	//Initial to 0
	for (k = 0;k < nz;k++)
	{
		fprintf(Output, "\nk= %d", k+1);
		for (j = 0;j < ny;j++)
		{
			fprintf(Output, "\n");
			for (i = 0;i < nx;i++)
			{
				fprintf(Output, "%8.10f\t", SWI1[i][j][k]);
				SWI1Chart[(((rc * (int)dt) / (tmax / 4)) % 4)][i][j][k] = SWI1[i][j][k];
				AverageVar += SWI1[i][j][k];
			}
		}
		waterStepsvalue[rc - 1][k] = AverageVar / (nx * ny);
		AverageVar = 0;
		if(wminmax[0] > waterStepsvalue[rc - 1][k])
		{
			wminmax[0] = waterStepsvalue[rc - 1][k];
		}
		if(wminmax[1] < waterStepsvalue[rc - 1][k])
		{
			wminmax[1] = waterStepsvalue[rc - 1][k];
		}
	}
	//Print Gas Saturation at every grid block
	fprintf(Output, "\n");
	fprintf(Output, "\nGas Saturation");
	AverageVar = 0;	//Initial to 0
	for (k = 0;k < nz;k++)
	{
		fprintf(Output, "\nk= %d ", k+1);
		for (j = 0;j < ny;j++)
		{
			fprintf(Output, "\n");
			for (i = 0;i < nx;i++)
			{
				fprintf(Output, "%8.10f\t", SGI1[i][j][k]);
				SGI1Chart[(((rc * (int)dt) / (tmax / 4)) % 4)][i][j][k] = SGI1[i][j][k];
				AverageVar += SGI1[i][j][k];
			}
		}
		gasStepsvalue[rc - 1][k] = AverageVar / (nx * ny);
		AverageVar = 0;
		if(gminmax[0] > gasStepsvalue[rc - 1][k])
		{
			gminmax[0] = gasStepsvalue[rc - 1][k];
		}
		if(gminmax[1] < gasStepsvalue[rc - 1][k])
		{
			gminmax[1] = gasStepsvalue[rc - 1][k];
		}
	}
	//Print Sum Saturation Verification
	fprintf(Output, "\n");
	fprintf(Output, "\nVerification Sum Sat");
	for (k = 0;k < nz;k++)
	{
		fprintf(Output, "\nk= %d", k+1);
		for (j = 0;j < ny;j++)
		{
			fprintf(Output, "\n");
			for (i = 0;i < nx;i++)
			{
				fprintf(Output, "%8.8f\t", (SWI1[i][j][k] + SGI1[i][j][k]));
			}
		}
	}
	//Print production for wells, if any
	if(nwell != 0)
	{
		fprintf(Output, "\n");
		fprintf(Output, "\nWell Name\tLayer\tQw STB/D\t\tQg MSCF/D\tPwf psi");		
		for(m = 0;m < nwell;m++)
		{
			fprintf(Output, "\n");
			for (k = 0;k < nz;k++)
			{
				if( k == ZCoor[m] )
				{
					for (j = 0;j < ny;j++)
					{
						if( j == YCoor[m] )
						{
							for (i = 0;i < nx;i++)
							{
								if( i == XCoor[m] )
								{
									fprintf(Output, "%s\t\t%d\t\t%5.3f\t\t%5.3f\t%5.3f",Wellname[m], ZCoor[m]+1, QW[i][j][k] / 5.615, QG[i][j][k] / 1000, Pwf[i][j][k]);
								}
							}
						}
					}
				}
			}
		}
		fprintf(Output, "\n");
		fprintf(Output, "\nCum Water Production (MSTB) : %5.3f\t", CumWater / 5615);
		fprintf(Output, "\nCum Gas Production (MMSCF) : %5.3f\t", CumGas / 1000000);
		fprintf(Output, "\n");
		fclose(Output);
	}
}
//*********************************