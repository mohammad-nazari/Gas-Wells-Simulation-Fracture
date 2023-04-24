// GassSimulation1.1Doc.h : interface of the CGassSimulation11Doc class
//


#pragma once
#include "gridbuilder.h"
#include "reservoir.h"
#include "initialcondition.h"
#include "welldata.h"
#include "numericalmethod.h"


class CGassSimulation11Doc : public CDocument
{
protected: // create from serialization only
	CGassSimulation11Doc();
	DECLARE_DYNCREATE(CGassSimulation11Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CGassSimulation11Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
private:
	GridBuilder dlgGridbuilder;
	Reservoir dlgReservoir;
	InitialCondition dlgInitialcondition;
	Welldata dlgWelldata;
	NumericalMethod dlgNumericalmethod;
};


