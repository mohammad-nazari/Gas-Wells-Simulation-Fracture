#pragma once
#include "afxwin.h"
#include "mschart1.h"
#include "ntgraphctrl1.h"


// graph dialog

class graph : public CDialogEx
{
	DECLARE_DYNAMIC(graph)

public:
	graph(int i, CWnd* pParent = NULL);   // standard constructor
	virtual ~graph();

// Dialog Data
	enum { IDD = IDD_DIALOGGRAPH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	bool ok;
	int PPP;
	CComboBox comboLayer;
	int comboLayerValue;
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
private:
	CMschart1 graphVariable;
	CNtgraphctrl1 ntgraphVariable;
};
