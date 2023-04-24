#pragma once
#include "afxwin.h"
#include "ntgraphctrl1.h"


// graph2 dialog

class graph2 : public CDialogEx
{
	DECLARE_DYNAMIC(graph2)

public:
	bool ok;
	int PPP;
	graph2(int i,CWnd* pParent = NULL);   // standard constructor
	virtual ~graph2();

// Dialog Data
	enum { IDD = IDD_DIALOGGRAPH2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox comboLayer;
	CNtgraphctrl1 ntgraphVariable;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	int comboLayerValue;
};
