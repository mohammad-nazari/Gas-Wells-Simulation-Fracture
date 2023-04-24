#pragma once
#include "msflexgrid1.h"
#include "afxwin.h"


// Value dialog

class Value : public CDialogEx
{
	DECLARE_DYNAMIC(Value)

public:
	Value(int from, int to, int i,int k,int s, CWnd* pParent = NULL);   // standard constructor
	virtual ~Value();

// Dialog Data
	enum { IDD = IDD_DIALOGVALUES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CMsflexgrid1 flexGridPressure;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	CComboBox comboLayer;
	int comboLayerNo;
	int PPP;	//set porosity, permability or pressure values
	int fromZ;
	int toZ;
	int permType;	//Set perm Type (X, Y, Z)
	int stepValue;
public:
	virtual BOOL OnInitDialog();
	int swap();
};
