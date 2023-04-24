#pragma once
#include "msflexgrid1.h"
#include "afxwin.h"


// welldataflx dialog

class welldataflx : public CDialogEx
{
	DECLARE_DYNAMIC(welldataflx)

public:
	welldataflx(CWnd* pParent = NULL);   // standard constructor
	virtual ~welldataflx();

// Dialog Data
	enum { IDD = IDD_DIALOGWELLFLX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
private:
	CMsflexgrid1 wellData;
	int wellNumber;
public:
	afx_msg void OnCbnSelchangeCombonwell();
	DECLARE_EVENTSINK_MAP()
	void DblClickMsflexgrid1();
private:
	CEdit cellVariable;
	CComboBox cellCombo;
public:
	afx_msg void OnCbnKillfocusCombo1();
	afx_msg void OnEnKillfocusEdit1();
private:
	void ComboSetData(int Col);
};
