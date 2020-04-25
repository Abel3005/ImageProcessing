
// MFC_Exp01Doc.h : interface of the CMFC_Exp01Doc class
//


#pragma once


class CMFC_Exp01Doc : public CDocument
{
protected: // create from serialization only
	CMFC_Exp01Doc() noexcept;
	DECLARE_DYNCREATE(CMFC_Exp01Doc)
// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFC_Exp01Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// store image
	unsigned char* m_InImage;
	unsigned char* m_OutImage;
	unsigned int height;
	unsigned int width;
	afx_msg void OnArithmetic();
	afx_msg void OnHistogram();
	afx_msg void OnTobinary();
	unsigned char m_Threshold;
	afx_msg void OnGonzalez();
	afx_msg void OnOtsu();
	afx_msg void OnLowpassfilter();
	afx_msg void OnHighpassfilter();
	afx_msg void OnMedianpassfilter();
	afx_msg void OnGausiansmoodingfilter();
	afx_msg void OnPrewittmask();
	afx_msg void OnSobelmask();
	afx_msg void OnDerivationOfGausian();
	afx_msg void OnZoomOut();
	afx_msg void OnRotation();
	afx_msg void OnBilinearInterpolation();
	afx_msg void OnZoomin();
	afx_msg void OnHorizontalMirroring();
	afx_msg void OnVerticalMirroring();
	afx_msg void OnBinDilate();
	afx_msg void OnBinErode();
	afx_msg void OnGrayDilate();
	afx_msg void OnGrayErode();
	afx_msg void OnBinOpen();
	afx_msg void OnBinClose();
	afx_msg void OnBlackTopHat();
	afx_msg void OnWhiteTopHat();
	afx_msg void OnHarisCorner();
	unsigned char m_refImage[20][20];
	afx_msg void OnMAD();
	afx_msg void OnMadSurface();
	afx_msg void On32816();
	afx_msg void On32817();
	afx_msg void OnFdct();
	double* m_Dct;
	afx_msg void OnIdct();
};
