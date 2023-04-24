#pragma once


// Reservoir dialog

class Reservoir : public CDialog
{
	DECLARE_DYNAMIC(Reservoir)

public:
	Reservoir(CWnd* pParent = NULL);   // standard constructor
	virtual ~Reservoir();

// Dialog Data
	enum { IDD = IDD_DIALOGRESERVOIR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioporosity();
	afx_msg void OnBnClickedRadioporofile();
	afx_msg void OnBnClickedRadioperm();
	afx_msg void OnBnClickedRadiopermfile();
	int radioPorosity;
	int radioPermeability;
	float textPorosity;
	CString textPorofile;
	float textpermX;
	float textpermY;
	float textpermZ;
	CString textPermfile;
	afx_msg void OnBnClickedButtonporo();
	afx_msg void OnBnClickedButtonperm();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditpermx2();
	afx_msg void OnBnClickedRadioporosity2();
	afx_msg void OnBnClickedRadioporofile2();
	afx_msg void OnBnClickedRadioperm2();
	afx_msg void OnBnClickedRadiopermfile2();
private:
	float textPorosity_f;
	CString textPorofile_f;
	float textpermX_f;
	float textpermY_f;
	float textpermZ_f;
	CString textPermfile_f;
public:
	afx_msg void OnBnClickedButtonporo2();
	afx_msg void OnBnClickedButtonperm2();
private:
	int radioPorosity_f;
	int radioPermeability_f;
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadiocapillary();
	afx_msg void OnBnClickedRadiocapillaryfile();
	afx_msg void OnBnClickedButtoncapillary();
	int radioCapillary;
private:
	float textCapillary;
	CString textCapillaryfile;
};
