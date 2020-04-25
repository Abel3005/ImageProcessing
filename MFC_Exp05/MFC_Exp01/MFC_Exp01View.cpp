
// MFC_Exp01View.cpp : implementation of the CMFC_Exp01View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_Exp01.h"
#endif

#include "MFC_Exp01Doc.h"
#include "MFC_Exp01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_Exp01View

IMPLEMENT_DYNCREATE(CMFC_Exp01View, CView)

BEGIN_MESSAGE_MAP(CMFC_Exp01View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFC_Exp01View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFC_Exp01View construction/destruction

CMFC_Exp01View::CMFC_Exp01View() noexcept
{
	// TODO: add construction code here

}

CMFC_Exp01View::~CMFC_Exp01View()
{
}

BOOL CMFC_Exp01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFC_Exp01View drawing

void CMFC_Exp01View::OnDraw(CDC* pDC)
{
	CMFC_Exp01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	for (unsigned int i = 0; i < pDoc->height; i++)
	{
		for (unsigned int j = 0; j < pDoc->width; j++)
		{
			unsigned char InVal = pDoc->m_InImage[(i * pDoc->width) + j];
			printf("%d", pDoc->width);
			unsigned char OutVal = pDoc->m_OutImage[(i * pDoc->width) + j];
			pDC->SetPixel(j, i, RGB(InVal, InVal, InVal));
			pDC->SetPixel(j + pDoc->width + 50, i, RGB(OutVal, OutVal, OutVal));
		}
	}
}


// CMFC_Exp01View printing


void CMFC_Exp01View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFC_Exp01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFC_Exp01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFC_Exp01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFC_Exp01View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC_Exp01View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC_Exp01View diagnostics

#ifdef _DEBUG
void CMFC_Exp01View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_Exp01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_Exp01Doc* CMFC_Exp01View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_Exp01Doc)));
	return (CMFC_Exp01Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_Exp01View message handlers
