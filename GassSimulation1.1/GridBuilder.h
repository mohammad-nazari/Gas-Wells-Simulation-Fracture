#pragma once
#include "reservoir.h"
#include "string.h"


// GridBuilder dialog

class GridBuilder : public CDialog
{
	DECLARE_DYNAMIC(GridBuilder)

public:
	GridBuilder(CWnd* pParent = NULL);   // standard constructor
	virtual ~GridBuilder();

// Dialog Data
	enum { IDD = IDD_DIALOGGRIDBUILDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int cartNx;
	int cartNy;
	int cartNz;
	CString cartDx;
	CString cartDy;
	CString cartDz;
	int radNr;
	int radNt;
	int radNz;
	CString radDr;
	CString radDt;
	CString radDz;
	int gridModel;
	int nCount;
	int i;
	int j;
	int k;
	char strCartNo[20];
	char strCartValue[20];
	char cartValue[1000];
	int dimensionType;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadiocart();
	afx_msg void OnBnClickedRadiorad();
	afx_msg void OnBnClickedRadiocara();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
private:
	Reservoir dlgReservoir;
public:
	int setGridtype;
private:
	int setCartesian(void);
	int pDigit(void);
	int pBracket(void);
public:
	afx_msg void OnBnClickedRadio3();
	int radioReservoir;
private:
	int radioFlowtype;
	int radioModel;
};
