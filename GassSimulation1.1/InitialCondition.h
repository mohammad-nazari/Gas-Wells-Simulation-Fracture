#pragma once


// InitialCondition dialog

class InitialCondition : public CDialog
{
	DECLARE_DYNAMIC(InitialCondition)

private:
	int InitialPVTdata(void);
	int InitialPVTdata_f(void);
	int getValues(void);
	int bufferFile(CString);
	int InitialKRG(void);
	int InitialKRW(void);
	int InitialKRG_f(void);
	int InitialKRW_f(void);

public:
	InitialCondition(CWnd* pParent = NULL);   // standard constructor
	virtual ~InitialCondition();

// Dialog Data
	enum { IDD = IDD_DIALOGINITIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditpvt();
	CString textPvt;
	float textPsi;
	float textSwc;
	float textCf;
	afx_msg void OnEnChangeEditpvt4();
	afx_msg void OnEnChangeEditpvt5();
	CString textBwi;
	CString textBgi;
	CString textUwi;
	CString textUgi;
	CString textCwi;
	CString textCgi;
//	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	CString textKrg;
	CString textKrw;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnEnChangeEdit1();
	float textSwi;
	float pvtValus;
	int i;
	int counterNo;
	int rowCounter;
	char textFile[10000];
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
private:
	CString textPvt_f;
	CString textKrg_f;
	CString textKrw_f;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit5();
private:
	float textSigma;
	CString textCpillaryfile;
public:
	afx_msg void OnBnClickedButtoncapillary();
private:
	CString textCapillaryfile;
	int InitialCapillary(void);
};
