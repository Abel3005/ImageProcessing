
// MFC_Exp01View.h : interface of the CMFC_Exp01View class
//

#pragma once


class CMFC_Exp01View : public CView
{
protected: // create from serialization only
	CMFC_Exp01View() noexcept;
	DECLARE_DYNCREATE(CMFC_Exp01View)

// Attributes
public:
	CMFC_Exp01Doc* GetDocument() const;

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
	virtual ~CMFC_Exp01View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFC_Exp01View.cpp
inline CMFC_Exp01Doc* CMFC_Exp01View::GetDocument() const
   { return reinterpret_cast<CMFC_Exp01Doc*>(m_pDocument); }
#endif

