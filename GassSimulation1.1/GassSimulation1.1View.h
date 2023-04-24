// GassSimulation1.1View.h : interface of the CGassSimulation11View class
//


#pragma once


class CGassSimulation11View : public CView
{
protected: // create from serialization only
	CGassSimulation11View();
	DECLARE_DYNCREATE(CGassSimulation11View)

// Attributes
public:
	void OnLine(CDC *,CPoint,CPoint,int);
	void OnGridDraw(CDC *);
	void OnReservoirDraw(CDC *);
	void OnWellDraw(CDC* pDC);
	CGassSimulation11Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGassSimulation11View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void OnPressuerDraw(CDC* pDC);
	int setChartBox(int *setX, int *setY);
	int getMax(void);
	void setRGB(int inPut/*it is a value between 0 to 1000*/, int *r, int *g, int *b);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
	afx_msg void OnFileSetreservoir();
	afx_msg void OnSimulationSetdata();
	afx_msg void OnSimulationStartsimulation();
	afx_msg void OnFileSetwells();
	afx_msg void OnChartsPressure();
	afx_msg void OnChartsPermability();
	afx_msg void OnChartsPorosity();
	afx_msg void OnChartsGasssaturation();
	afx_msg void OnChartsWatersatu();
	afx_msg void OnGraphPressure();
	afx_msg void OnGraphGasssaturatio();
	afx_msg void OnGraphWatersaturatio();
};

#ifndef _DEBUG  // debug version in GassSimulation1.1View.cpp
inline CGassSimulation11Doc* CGassSimulation11View::GetDocument() const
   { return reinterpret_cast<CGassSimulation11Doc*>(m_pDocument); }
#endif

