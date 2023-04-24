#pragma once


// NumericalMethod dialog

class NumericalMethod : public CDialog
{
	DECLARE_DYNAMIC(NumericalMethod)

public:
	NumericalMethod(CWnd* pParent = NULL);   // standard constructor
	virtual ~NumericalMethod();

// Dialog Data
	enum { IDD = IDD_DIALOGNUMERICAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	int textTimestep;
	int textEndsimilation;
	int textMaxerror;
	int textMaxsw;
	CString textOutput;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	double textMaxiteration;
private:
	CString textOutputf;
public:
	afx_msg void OnBnClickedButton3();
};
