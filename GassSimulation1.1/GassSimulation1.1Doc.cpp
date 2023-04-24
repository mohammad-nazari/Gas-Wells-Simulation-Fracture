// GassSimulation1.1Doc.cpp : implementation of the CGassSimulation11Doc class
//

#include "stdafx.h"
#include "GassSimulation1.1.h"
#include "GassSimulation1.1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGassSimulation11Doc
extern int gridMaked,gridType;
extern void Initial_data();
extern void RInitial_data();

IMPLEMENT_DYNCREATE(CGassSimulation11Doc, CDocument)

BEGIN_MESSAGE_MAP(CGassSimulation11Doc, CDocument)
	ON_COMMAND(ID_FILE_NEW, &CGassSimulation11Doc::OnFileNew)
END_MESSAGE_MAP()


// CGassSimulation11Doc construction/destruction

CGassSimulation11Doc::CGassSimulation11Doc()
{
	// TODO: add one-time construction code here

}

CGassSimulation11Doc::~CGassSimulation11Doc()
{
}

BOOL CGassSimulation11Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CGassSimulation11Doc serialization

void CGassSimulation11Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CGassSimulation11Doc diagnostics

#ifdef _DEBUG
void CGassSimulation11Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGassSimulation11Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGassSimulation11Doc commands

void CGassSimulation11Doc::OnFileNew()
{
	// TODO: Add your command handler code here
}
