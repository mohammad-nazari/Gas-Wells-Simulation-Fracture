#pragma once


// Welldata dialog

class Welldata : public CDialog
{
	DECLARE_DYNAMIC(Welldata)

public:
	Welldata(CWnd* pParent = NULL);   // standard constructor
	virtual ~Welldata();

// Dialog Data
	enum { IDD = IDD_DIALOGWELLDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int textNwell;
	CString textWelldata;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int comboNwell;
	afx_msg void OnCbnSelchangeCombonwell();
	afx_msg void OnCbnSelchangeCombo17();
	afx_msg void OnCbnSelchangeCombo51();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit39();
	afx_msg void OnEnChangeEdit45();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit4();
private:
	int Nwell;
public:
	int comboXwell1;
	int comboXwell2;
	int comboXwell3;
	int comboXwell4;
	int comboXwell5;
	int comboXwell6;
	int comboXwell7;
	int comboXwell8;
	int comboXwell9;
	int comboXwell10;
	int comboYwell1;
	int comboYwell2;
	int comboYwell3;
	int comboYwell4;
	int comboYwell5;
	int comboYwell6;
	int comboYwell7;
	int comboYwell8;
	int comboYwell9;
	int comboYwell10;
	int comboZwell10;
	int comboZwell9;
	int comboZwell8;
	int comboZwell7;
	int comboZwell6;
	int comboZwell5;
	int comboZwell4;
	int comboZwell3;
	int comboZwell2;
	int comboZwell1;
	int comboKind1;
	int comboKind2;
	int comboKind3;
	int comboKind4;
	int comboKind5;
	int comboKind6;
	int comboKind7;
	int comboKind8;
	int comboKind9;
	int comboKind10;
	int comboType1;
	int comboType2;
	int comboType3;
	int comboType4;
	int comboType5;
	int comboType6;
	int comboType7;
	int comboType8;
	int comboType9;
	int comboType10;
	double Qw10;
	double Qw9;
	double Qw8;
	double Qw7;
	double Qw6;
	double Qw5;
	double Qw4;
	double Qw3;
	double Qw2;
	double Qw1;
	double Qg1;
	double Qg2;
	double Qg3;
	double Qg4;
	double Qg5;
	double Qg6;
	double Qg7;
	double Qg8;
	double Qg9;
	double Qg10;
	double Pwf10;
	double Pwf9;
	double Pwf8;
	double Pwf7;
	double Pwf6;
	double Pwf5;
	double Pwf4;
	double Pwf3;
	double Pwf2;
	double Pwf1;
	double Rw1;
	double Rw2;
	double Rw3;
	double Rw4;
	double Rw5;
	double Rw6;
	double Rw7;
	double Rw8;
	double Rw9;
	double Rw10;
	double Skin1;
	double Skin2;
	double Skin3;
	double Skin4;
	double Skin5;
	double Skin6;
	double Skin7;
	double Skin8;
	double Skin9;
	double Skin10;
	double minBhp1;
	double minBhp2;
	double minBhp3;
	double minBhp4;
	double minBhp5;
	double minBhp6;
	double minBhp7;
	double minBhp8;
	double minBhp9;
	double minBhp10;
public:
	CComboBox comboNx1;
	CComboBox comboNx2;
	CComboBox comboNx3;
	CComboBox comboNx4;
	CComboBox comboNx5;
	CComboBox comboNx6;
	CComboBox comboNx7;
	CComboBox comboNx8;
	CComboBox comboNx9;
	CComboBox comboNx10;
	CComboBox comboNy1;
	CComboBox comboNy2;
	CComboBox comboNy3;
	CComboBox comboNy4;
	CComboBox comboNy5;
	CComboBox comboNy6;
	CComboBox comboNy7;
	CComboBox comboNy8;
	CComboBox comboNy9;
	CComboBox comboNy10;
	CComboBox comboNz1;
	CComboBox comboNz2;
	CComboBox comboNz3;
	CComboBox comboNz4;
	CComboBox comboNz5;
	CComboBox comboNz6;
	CComboBox comboNz7;
	CComboBox comboNz8;
	CComboBox comboNz9;
	CComboBox comboNz10;
	virtual BOOL OnInitDialog();
};
