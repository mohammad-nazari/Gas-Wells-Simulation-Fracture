#pragma once
#include "afxwin.h"


// Chart dialog

class Chart : public CDialogEx
{
	DECLARE_DYNAMIC(Chart)

public:
	Chart(int i, CWnd* pParent = NULL);   // standard constructor
	virtual ~Chart();

// Dialog Data
	enum { IDD = IDD_DIALOGCHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CComboBox comboLayer;
	int comboLayerNo;
	CComboBox comboLayer2;
	int comboLayerNo2;
	int permType;
	int PPP;	//set porosity, permability or pressure values
	int selectSet;
	bool ok;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonvalue();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
private:
	void onDrawGrid(CDC* pDC);
	void swap(int *from, int *to);
	void setRGB(int inPut, int *r, int *g, int *b);
	void setChartBox(int *setX, int *setY);
	int getMax(void);
	int stepValue;
};
