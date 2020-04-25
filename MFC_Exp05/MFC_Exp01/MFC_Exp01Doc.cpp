
// MFC_Exp01Doc.cpp : implementation of the CMFC_Exp01Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_Exp01.h"
#endif

#include "MFC_Exp01Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFC_Exp01Doc

IMPLEMENT_DYNCREATE(CMFC_Exp01Doc, CDocument)
//chack14
BEGIN_MESSAGE_MAP(CMFC_Exp01Doc, CDocument)
	ON_COMMAND(ID_32771, &CMFC_Exp01Doc::OnArithmetic)
	ON_COMMAND(ID_Histogram, &CMFC_Exp01Doc::OnHistogram)
	ON_COMMAND(ID_Threshold, &CMFC_Exp01Doc::OnTobinary)
	ON_COMMAND(ID_Gonzalez, &CMFC_Exp01Doc::OnGonzalez)
	ON_COMMAND(ID_Otsu, &CMFC_Exp01Doc::OnOtsu)
	ON_COMMAND(ID_32783, &CMFC_Exp01Doc::OnLowpassfilter)
	ON_COMMAND(ID_32784, &CMFC_Exp01Doc::OnHighpassfilter)
	ON_COMMAND(ID_32785, &CMFC_Exp01Doc::OnMedianpassfilter)
	ON_COMMAND(ID_32786, &CMFC_Exp01Doc::OnGausiansmoodingfilter)
	ON_COMMAND(ID_32788, &CMFC_Exp01Doc::OnPrewittmask)
	ON_COMMAND(ID_32789, &CMFC_Exp01Doc::OnSobelmask)
	ON_COMMAND(ID_32790, &CMFC_Exp01Doc::OnDerivationOfGausian)
	ON_COMMAND(ID_32794, &CMFC_Exp01Doc::OnZoomOut)
	ON_COMMAND(ID_32795, &CMFC_Exp01Doc::OnRotation)
	ON_COMMAND(ID_32796, &CMFC_Exp01Doc::OnBilinearInterpolation)
	ON_COMMAND(ID_32797, &CMFC_Exp01Doc::OnZoomin)
	ON_COMMAND(ID_32799, &CMFC_Exp01Doc::OnHorizontalMirroring)
	ON_COMMAND(ID_32800, &CMFC_Exp01Doc::OnVerticalMirroring)
END_MESSAGE_MAP()


// CMFC_Exp01Doc construction/destruction

CMFC_Exp01Doc::CMFC_Exp01Doc() noexcept
{
	m_InImage = NULL;
	m_OutImage = NULL;
	height = 0;
	width = 0;
}

CMFC_Exp01Doc::~CMFC_Exp01Doc()
{
}

BOOL CMFC_Exp01Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFC_Exp01Doc serialization
void CMFC_Exp01Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

		if (width != 0 && height != 0)
		{
			ar.Write(m_OutImage, width*height);
		}
	}
	else
	{

		CString strTemp = ar.m_strFileName.Right(3);
		if (toupper(strTemp[0]) == 'B' &&
			toupper(strTemp[1]) == 'M' &&
			toupper(strTemp[2]) == 'P')
		{
			CImage m_Image;
			m_Image.Load(ar.m_strFileName);
			width = m_Image.GetWidth();
			height = m_Image.GetHeight();
			m_InImage = (unsigned char*)malloc(sizeof(unsigned char)* width * height);
			m_OutImage = (unsigned char*)malloc(sizeof(unsigned	char) * width * height);
			int ws = width * (m_Image.GetBPP() / 8);
			unsigned char *m_tmpImage = (unsigned char*)malloc(sizeof(unsigned char) * ws * height);
			if (m_Image.GetBPP() == 1)
			{
				AfxMessageBox((LPCTSTR)"읽을 수 있는 파일 형식이 아닙니다.");
				return;
			}
			else if (m_Image.GetBPP() == 8)
			{
				for (int y = 0; y < height; y++) {
					BYTE* srcImg = NULL;
					srcImg = (BYTE*)m_Image.GetPixelAddress(0, y);
					memcpy(&m_InImage[y * ws], srcImg, ws);
				}
			}
			else if (m_Image.GetBPP() == 24) {
				for (int y = 0; y < height; y++) {
					BYTE * srcImg = NULL;
					srcImg = (BYTE *)m_Image.GetPixelAddress(0, y);
					memcpy(&m_tmpImage[y * ws], srcImg, ws);


				}
				int iter = 0;
				for (int y = 0; y < height; y++) {
					for (int x = 0; x < width; x++) {
						m_InImage[(y * width) + x] = (m_tmpImage[iter] * 0.21 + m_tmpImage[iter + 1] * 0.72 + m_tmpImage[iter + 2] * 0.07);
						iter += 3;
					}
				}
			}
		}
		else
		{
			AfxMessageBox((LPCTSTR)"읽을 수 있는 파일 형식이 아닙니다.");
			return;
		}

	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFC_Exp01Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFC_Exp01Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFC_Exp01Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFC_Exp01Doc diagnostics

#ifdef _DEBUG
void CMFC_Exp01Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFC_Exp01Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFC_Exp01Doc commands


void CMFC_Exp01Doc::OnArithmetic()
{
	// TODO: Add your command handler code here
	int i, j; // 인덱스 처리릉 위한 변수
	int temp; // 임시 데이터 저장을 위한 변수
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			temp = m_InImage[(i*width) + j] + 40; 
				if (temp > 255) m_OutImage[(i*width) + j] = 255; 
				else if (temp < 0) m_OutImage[(i*width) + j] = 0;
				else
					m_OutImage[(i*width) + j] = (unsigned char)temp;
		}
	}
	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnHistogram()
{
	// TODO: Add your command handler code here
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int Hist[256]; // 히스토그램을 저장하기 위한 배열
	int MaxVal = 0; // 히스토그램의 최대값 변수
	int i, j;
	// 히스토그램 내용을 모두 0으로 초기화
	memset(Hist, 0, sizeof(int) * 256);
	/***************************************************/
	// 1. 히스토그램 계산
	/***************************************************/
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			Hist[m_InImage[(i*width) + j]]++; 
				if (MaxVal < Hist[m_InImage[(i*width) + j]])
					MaxVal = Hist[m_InImage[(i*width) + j]]; 
		}
	}
	/***************************************************/
	// 2. 히스토그램을 출력화면에 디스플레이 하기
	/***************************************************/
	// 출력화면 전체를 모두 하얗게(255 값으로) 초기화 한다.
	m_OutImage = (unsigned char*)malloc(sizeof(char) * height * width);
	memset(m_OutImage, 255, sizeof(unsigned char) * height * width);
	float w_ratio = (float)255 / (width - 1);
	float h_ratio = (float)(height - 1) / MaxVal;
	// X축은 밝기값으로 Y축은 히스토그램의 값으로 출력한다.
	for (i = 0; i < width; i++) {
		int idx = i * w_ratio;
		int value = Hist[idx] * h_ratio;
			for (j = 0; j < value; j++)
				m_OutImage[(height - j - 1)*width + i] = 0; 
	}
	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnTobinary()
{
	// TODO: Add your command handler code here0
	// 사용자가 임의의 임계값을 직접 결정해서 입력할 경우
	m_Threshold = 130; // 원하는 임계값을 결정
	// 영상 이진화: 밝기값이 임계값 보다 크면 255로
	// 밝기값이 임계값보다 작으면 0으로 이진화 처리한다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (m_InImage[(i*width) + j] >= m_Threshold)
				m_OutImage[(i*width) + j] = 255;
			else
				m_OutImage[(i*width) + j] = 0;
		}
	}
	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnGonzalez()
{
	int hist[256];
	memset(hist, 0, sizeof(int) * 256);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			hist[m_InImage[(i*width) + j]]++; 
		}
	}
	int T, min, max;
	for (int i = 0; i < 256; i++) {
		if (hist[i] > 0) {
			min = i; // 입력영상에서 가장 밝기값이 작은 값
			i = 257;
		}

	}
	for (int i = 255; i > 0; i--) {
		if (hist[i] > 0) {
			max = i; // 입력영상에서 가장 밝기값 큰 값
			i = -1;
		}
	}
	T = (min + max) / 2; // 초기 임계값 : 최소 밝기값과 최대 밝기값의 평균값
	int Diff = 5; //새롭게 계산된 임계값과 이전임계값과의 차이에 대한 초기값
	while (Diff >= 1)
	{
		int nSum = 0, nCnt = 0; // nSum: 그룹 1에 속하는 전체 화소밝기값
			// nCnt: 그룹 1의 전체 화소수
			for (int i = 0; i < T; i++) {
				nSum += hist[i] * i;
				nCnt += hist[i];
			}
		double Mu_1 = (double)(nSum / nCnt); // 그룹 1의 밝기값 평균
		nSum = 0, nCnt = 0; // nSum: 그룹 2에 속하는 전체 화소 밝기값,
			// nCnt: 그룹 2의 전체 화소수
			for (int i = T; i < 256; i++)
			{
				nSum += hist[i] * i;
				nCnt += hist[i];
			}
		double Mu_2 = (double)(nSum / nCnt); // 그룹 2의 밝기값 평균
		int T_Last = (int)((Mu_1 + Mu_2) / 2);
		Diff = abs(T - T_Last); 
			T = T_Last;
	}
	m_Threshold = T; // 최종 Gonzalez 임계값 결정
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (m_InImage[(i*width) + j] >= m_Threshold)
				m_OutImage[(i*width) + j] = 255;
			else
				m_OutImage[(i*width) + j] = 0;
		}
	}
	UpdateAllViews(NULL);
	CString strTemp;
	strTemp.Format(_T("Gonzalez 임계값 = %d"), m_Threshold);
	AfxMessageBox(strTemp);
}


void CMFC_Exp01Doc::OnOtsu()
{
	int hist[256]; // 밝기 히스토그램
	memset(hist, 0, sizeof(int) * 256);
	// 히스토그램 계산
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			hist[m_InImage[(i*width) + j]]++;
		}
	int N = width * height; // 영상의 총 화소수
	int L = 256; // 밝기 최대값 0, 1, 2 ~ L-1
	int temp_threshold; // 1차 임계값 검색과정에서 결정된 임계값
	double Mu_1, Mu_2; // 두 클래스 각각의 밝기값 평균:
	double Mu_T; // 밝기값 전체 평균 :
	double W1, W2; // 두 클래스 발생 확률 :
	double Sigma_B; // 클래스 간 분산(between class variance) :
	double Sigma_Bmax = 0; // 클래스 간 분산 최대값 초기화 : 의 최대값
	double H_m[256], H_cdf[256]; // H_m[i]: 밝기값 0~i 까지의 전체 총 누적밝기값
	H_m[0] = 0; H_cdf[0] = hist[0]; // 밝기값 0 에서의 초기값 설정
	for (int i = 1; i < L; i++) {
		H_m[i] = H_m[i - 1] + hist[i] * (double)i;
		H_cdf[i] = H_cdf[i - 1] + hist[i];
	}
	Mu_T = H_m[255] / N; // 전체 밝기값에 대한 평균 계산 :
	for (int k = 3; k < L; k += 4) {
		W1 = H_cdf[k] / N; // 그룹 1 확률 계산
		W2 = 1. - W1; // 그룹 2 확률 계산
		if (H_cdf[k] == 0.) continue;
		Mu_1 = H_m[k] / H_cdf[k];
		if ((N - H_cdf[k]) == 0.) continue;
		Mu_2 = (H_m[L - 1] - H_m[k]) / (N - H_cdf[k]); // 그룹 2의 밝기값 평균
		Sigma_B = W1 * (Mu_1 - Mu_T)*(Mu_1 - Mu_T) +
			W2 * (Mu_2 - Mu_T)*(Mu_2 - Mu_T);
		// 가 최대가 되는 때의 밝기값 k를 찾는 과정
		if (Sigma_B > Sigma_Bmax) {
			Sigma_Bmax = Sigma_B;
			temp_threshold = k;
		}
	}

	for (int k = temp_threshold - 3; k <= temp_threshold + 3; k++) {
		W1 = H_cdf[k] / N; // 그룹 1의 확률
		W2 = 1. - W1; // 그룹 2의 확률
		Mu_1 = H_m[k] / H_cdf[k]; // 그룹 1의 밝기값 평균
		Mu_2 = (H_m[L - 1] - H_m[k]) / (N - H_cdf[k]); // 그룹 2의  밝기값 평균
		Sigma_B = W1 * (Mu_1 - Mu_T)*(Mu_1 - Mu_T) +
			W2 * (Mu_2 - Mu_T)*(Mu_2 - Mu_T);
		if (Sigma_B > Sigma_Bmax) {
			Sigma_Bmax = Sigma_B;
			m_Threshold = k; // 최종 임계값 결정
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (m_InImage[(i*width) + j] >= m_Threshold)
				m_OutImage[(i*width) + j] = 255;
			else
				m_OutImage[(i*width) + j] = 0;
		}
	}
	UpdateAllViews(NULL);
	CString strTemp;
	strTemp.Format(_T("Otsu 임계값 = %d"), m_Threshold);
	AfxMessageBox(strTemp);
}


void CMFC_Exp01Doc::OnLowpassfilter()
{
	// TODO: Add your command handler code here
	/************************************************************
// 1. 저역통과 필터링 마스크 처리
**********************************************************/
	static int mask[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
	int temp;
	// 1.1 마스크 처리가 가능한 영역
	for (int i = 1; i < height; i++) {
		for (int j = 1; j < width; j++) {
			temp = 0; // 0으로 초기화
			for (int r = 0; r < 3; r++) {
				for (int c = 0; c < 3; c++)
					temp += (mask[r][c] * m_InImage[((i + r - 1) *
						width) + j + c - 1]);
			}
			m_OutImage[(i*width) + j] = (unsigned char)(temp / 9);
		}
	}
	// 1.2 영상의 최외각 라인 및 행에 대한 처리
	for (int i = 0; i < width; i++) {
		m_OutImage[i] = m_InImage[i];
		m_OutImage[((height - 2)*width) + i] = m_InImage[((height - 2)*width) + i];
	}
	for (int i = 0; i < height; i++) {
		m_OutImage[((i)*width)] = m_InImage[((i)*width)];
		m_OutImage[((i + 1)*width - 1)] = m_InImage[((i + 1)*width - 1)];
	}
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			m_InImage[i*width + j] = m_OutImage[i*width + j];

	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnHighpassfilter()
{
	// TODO: Add your command handler code here
	/************************************************************
// 1. 고역통과 필터링 마스크 처리
**********************************************************/
	
	static int mask[3][3] = { {-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1} };
	int temp, Max = -256 * 256, Min = 256 * 256; // 마스크 처리을 위해 필요한 변수,
	int i, j, r, c;
	int *Result = (int*)malloc(sizeof(int) * width * height); //[256][256]; // 마스크 처리된 이미지를 저장하는 배열
		// 1.1 마스크 처리가 가능한 영역 처리
	for (i = 1; i < height; i++) {
		for (j = 1; j < width; j++) {
			temp = 0; // 0으로 초기화
			for (r = 0; r < 3; r++) {
				for (c = 0; c < 3; c++)
					temp +=
					(mask[r][c] * m_InImage[((i + r - 1)*width) + j + c - 1]); //마스크 처리
			}
			if (temp > Max) Max = temp;//마스크 처리된 값 중 최대값 검색
			if (temp < Min) Min = temp;//마스크 처리된 값 중 최소값 검색
			Result[(i*width) + j] = temp;
		}
	}
	int size = width * height;
	// 1.2 영상의 최외각 라인 및 행에 대한 처리
	for (int i = 0; i < width; i++) {
		m_OutImage[i] = m_InImage[i];
		m_OutImage[size - i - 1] = m_InImage[size - i - 1];
	}
	for (int i = 0; i < height; i++) {
		m_OutImage[((i)*width)] = m_InImage[((i)*width)];
		m_OutImage[((i + 1)*width - 1)] = m_InImage[((i + 1)*width - 1)];
	}
	// 1.3 마스크 처리된 결과를 화면에 출력하는 방법
	// 1) 결과를 그대로 출력해 보자.
	/*for(i = 0 ; i < height; i++){
		for(j = 0 ; j < width ; j++){
			m_OutImage[(i*width)+j] = (unsigned
			char)Result[(i*width)+j];
		}
	}*/
	// 2) 화면 출력을 위해 출력 화소값을 0~255로 클리핑(Clipping) 한다.
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (Result[(i*width) + j] > 255) m_OutImage[(i*width) + j] =
				255;
			else if (Result[(i*width) + j] < 0) m_OutImage[(i*width) + j] =
				0;
			else
				m_OutImage[(i*width) + j] = (unsigned char)Result[(i*width) + j];
		}
	}
	//3) 화면 출력을 위해 출력화소값을 0~255로 매핑시킨다.
	// 상수값 미리 계산
	double C1 = (double)(255.0/(Max-Min));
	double C2 = (double)(-255.0*Min/(Max-Min));
	for(i = 0 ; i < height; i++){
		for(j = 0 ; j < width ; j++){
			m_OutImage[(i*width)+j] = (unsigned	char)(C1*Result[(i*width)+j]+C2);
		}
	}
	//이때 마스크 처리된 최대값과 최소값이 어떻게 되는지 화면에 출력해보자
	CString strTemp;
	strTemp.Format( _T("최대값 = %d , 최소값 = %d"), Max, Min);
	AfxMessageBox(strTemp ); 
	UpdateAllViews(NULL);
}

void CMFC_Exp01Doc::OnMedianpassfilter()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	//미디언 필터를¸ 적용할 정방형 마스크의 가로화소
	const int winSize = 3; // 영역처리하는 마스크 크기
	//마스크의 전체 크기의 배열을 할당한다. Sorting 된 밝기값을 저장하기 위해
	unsigned char* arr = new unsigned char[winSize * winSize];
	//영상 각각의 픽셀에 대해
	for (int y = 0 + winSize / 2; y < height - winSize / 2; y++)
	{
		for (int x = 0 + winSize / 2; x < width - winSize / 2; x++)
		{
			int total = 0; // 정렬되는 화소수의 Index 값
			for (int by = 0; by < winSize; by++)
			{
				for (int bx = 0; bx < winSize; bx++)
				{
					arr[total] = m_InImage[((y + (by -
						winSize / 2)) * width) + x + (bx - winSize / 2)];
					for (int i = total; i > 0; i--)
					{
						//새롭게 추가된 화소의 밝기값을 정렬한다.
						if (arr[i] < arr[i - 1])
						{
							unsigned char temp = arr[i];
							arr[i] = arr[i - 1];
							arr[i - 1] = temp;
						}
					}
					total++;
				}
			}
			//정렬된 밝기값의 중간값을 출력이미지로 처리한다.
			m_OutImage[(y*width) + x] = arr[winSize * winSize / 2];
		}
	}
	delete[] arr; // 정렬을 위해 할당된 메모리를 해제한다.
	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnGausiansmoodingfilter()
{
	const double PI = 3.141592;
	double sigma = 5.0;
	int m = (int)(6.0 * sigma) + 1;
	int temp = 0;
	double ** Mask = new double*[m];
	for (int i = 0; i < m; i++) {
		Mask[i] = new double[m];
	}
	int center = (int)(m / 2) + 1;
	for(int i =0; i<m; i++)
		for(int j =0; j < m; j++)
			Mask[i][j] = (1.0 / (2.0*PI*sigma*sigma))*exp(-((i - center)*(i - center) + (j - center)*(j - center))*
			(1.0 / (2.0*sigma*sigma)));
	for (int i = 1; i < height; i++) {
		for (int j = 1; j < width; j++) {
			temp = 0; // 0으로 초기화
			for (int r = 0; r < 3; r++) {
				for (int c = 0; c < 3; c++)
					temp += (Mask[r][c] * m_InImage[((i + r - 1) *
						width) + j + c - 1]);
			}
			m_OutImage[(i*width) + j] = (unsigned char)(temp / 9);
		}
	}

	

}


void CMFC_Exp01Doc::OnPrewittmask()
{
	// TODO: Add your command handler code here
	// Prewitt 마스크
	static int maskX[3][3] = { -1, 0, 1,-1, 0, 1,-1, 0, 1 };
	static int maskY[3][3] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
	int amplitude; // 에지강도를 위한 변수
	m_Threshold = 50; // 에지검출을 위한 이진화 임계값
	//1.1 Prewitt 마스크 연산
	for (int y = 1; y < height; y++)
	{
		for (int x = 1; x < width; x++)
		{
			//블록단위처리
			int sumX = 0;
			int sumY = 0;
			for (int by = 0; by < 3; by++)
			{
				for (int bx = 0; bx < 3; bx++)
				{
					sumX += maskX[by][bx] * m_InImage[(y + by -
						1)*width + x + bx - 1];
					sumY += maskY[by][bx] * m_InImage[(y + by -
						1)*width + x + bx - 1];
				}
			}
			//계산된 에지 강도값
			//amplitude = (int)sqrt((double)sumX * sumX + sumY * sumY); //방법 1
				amplitude = abs(sumX) + abs(sumY); // 방법2
				//1. 에지강도값을 0~255의 값으로 처리(클리핑)
				/*if (amplitude > 255) m_OutImage[y*width + x] = 255;
				else if (amplitude < 0) m_OutImage[y*width + x] = 0;
				else m_OutImage[y*width + x] = (unsigned char)amplitude;*/
			// 2. 에지강도값을 임의의 임계값으로 이진화
			if (amplitude > m_Threshold) m_OutImage[y*width + x] = 255;
			else m_OutImage[y*width + x] = 0;
		}
	}
	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnSobelmask()
{
	// TODO: Add your command handler code here
	// Prewitt 마스크
	static int maskX[3][3] = { -1, 0, 1,-2, 0, 2,-1, 0, 1 };
	static int maskY[3][3] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	int amplitude; // 에지강도를 위한 변수
	m_Threshold = 130; // 에지검출을 위한 이진화 임계값
	//1.1 Prewitt 마스크 연산
	for (int y = 1; y < height; y++)
	{
		for (int x = 1; x < width; x++)
		{
			//블록단위처리
			int sumX = 0;
			int sumY = 0;
			for (int by = 0; by < 3; by++)
			{
				for (int bx = 0; bx < 3; bx++)
				{
					sumX += maskX[by][bx] * m_InImage[(y + by -
						1)*width + x + bx - 1];
					sumY += maskY[by][bx] * m_InImage[(y + by -
						1)*width + x + bx - 1];
				}
			}
			//계산된 에지 강도값
			//amplitude = (int)sqrt((double)sumX * sumX + sumY * sumY); //방법 1
			amplitude = abs(sumX) + abs(sumY); // 방법2
			//1. 에지강도값을 0~255의 값으로 처리(클리핑)
			if (amplitude > 255) m_OutImage[y*width + x] = 255;
			else if (amplitude < 0) m_OutImage[y*width + x] = 0;
			else m_OutImage[y*width + x] = (unsigned char)amplitude;
			// 2. 에지강도값을 임의의 임계값으로 이진화
			//if (amplitude > m_Threshold) m_OutImage[y*width + x] = 255;
			//else m_OutImage[y*width + x] = 0;
		}
	}
	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnDerivationOfGausian()
{
	// TODO: Add your command handler code here
	const double PI = 3.14159;
	const double sigma = 2.0; // Gaussian 분포의 표준편차, sigma =0.4, 1.0, 2.0
	int y, x, r, c;
	int M = (int)(6.0 * sigma) + 1; // 마스크 크기 M x M
	if (M % 2 == 0) M = M + 1; // 마스크의 크기 M 짝수이면 홀수로 만든다.
	int center = (int)M / 2; // 마스크의 중심
	int scale = 10; // 마스크의 전체 가중치를 Scaling 하는 변수
	int amplitude; // 에지강의 크기를 저장
	//X, Y 마스크를 위한 메모리 크기할당
	double **MaskX = new double*[M];
	double **MaskY = new double*[M];
	for (int i = 0; i < M; i++) {
		MaskX[i] = new double[M];
		MaskY[i] = new double[M];
	}
	//[1] 가우시안함수를 미분한 X 축, Y 축 마스크 계산
	for (y = -center; y <= center; y++) {
		for (x = -center; x <= center; x++) {
			MaskX[y + center][x + center] = scale * (-x * exp(-(x * x + y * y) /
				(2.0 *
					sigma * sigma)) / (2.0 * PI * sigma * sigma * sigma *
						sigma));
			MaskY[y + center][x + center] = scale * (-y * exp(-(x * x + y * y) /
				(2.0 *
					sigma * sigma)) / (2.0 * PI * sigma * sigma * sigma *
						sigma));
		}
	}
	for (y = 0; y < height; y++) for (x = 0; x < width; x++) m_OutImage[y*width + x] = 0;
	// [2] 마스크를 이용한 에지강도 검출
	for (y = center; y < height - center; y++) {
		for (x = center; x < width - center; x++) {
			int sumX = 0;
			int sumY = 0;
			for (r = 0; r < M; r++) {
				for (c = 0; c < M; c++) {
					sumX +=
						MaskX[r][c] * m_InImage[(y + r - (int)(M / 2))*width + x + c - (int)(M / 2)];
					sumY +=
						MaskY[r][c] * m_InImage[(y + r - (int)(M / 2))*width + x + c - (int)(M / 2)];
				}
			}
			//에지강도값 계산
			amplitude = (int)sqrt((double)sumX * sumX + sumY * sumY);
			// 에지강도값을 0 ~ 255로 처리(clipping)
			if (amplitude > 255) m_OutImage[y*width + x] = 255;
			else if (amplitude < 0) m_OutImage[y*width + x] = 0;
			else m_OutImage[y*width + x] = (unsigned char)amplitude;
		}
	}
	delete[] MaskX;
	delete[] MaskY;
	UpdateAllViews(NULL);
}




void CMFC_Exp01Doc::OnZoomOut()
{
	// TODO: Add your command handler code here
	double scale = 0.7; // 영상을 0.7배 축소한다.
	int X_max = (int)(width * scale); // 축소된 영상의 새로운 폭 계산
	int Y_max = (int)(height * scale); // 축소된 영상의 새로운 높이 계산
	double x, y; // 역방향 사상된 좌표의 분수값
	int x_org, y_org; // 역방향 사상된 정수 좌표값
	unsigned char *ZoomImage;
	// 확대된 영상을 임시로 저장할 공간 동적할당
	ZoomImage = new unsigned char[Y_max*X_max];
	for (int y_new = 0; y_new < Y_max; y_new++)
	{
		for (int x_new = 0; x_new < X_max; x_new++)
		{
			x = x_new / scale;
			y = y_new / scale;
			// 가장 인접한 이웃화소 좌표값으로 매핑
			x_org = (int)(x + 0.5);
			y_org = (int)(y + 0.5);
			// 범위 조사: 원영상의 크기 영역을 벗어나는 경우
			if (x_org < 0 || x_org > width || y_org < 0 || y_org > height)
			{
				ZoomImage[y_new*X_max + x_new] = 0;
			}
			// 원 이미지의 범위내에 존재하는 경우 가장 인접한 이웃화소 보간법
			else
				ZoomImage[y_new*X_max + x_new] = m_InImage[y_org*width+x_org];
		}
	}
	// 축소된 영상을 원래크기(256x256)의 영상사이즈 만큼 출력한다.
	for (int i = 0; i < Y_max; i++)
	{
		for (int j = 0; j < X_max; j++)
		{
			m_OutImage[i*width+j] = ZoomImage[i*X_max + j];
		}
	}
	delete[] ZoomImage; // 동적 할당된 메모리 해제
	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnRotation()
{
	// TODO: Add your command handler code here
	double rotationAngle = 45; // 시계방향 영상회전 각도(degree)
	int x_center = width/2; // X축 영상 회전중심
	int y_center = height/2; // Y축 영상 회전중심
	double rotationAngleRad = (rotationAngle*3.14159265 / 180); //영상회전각도 (radian)
	double cosValue, sinValue; // cosValue=cos(rotationAngleRad)이다.
	double x, y; // 역방향 사상된 좌표의 분수값
	int x_org, y_org; // 역방향 사상된 정수 좌표값
	for (int y_new = 0; y_new < height; y_new++)
	{
		for (int x_new = 0; x_new < width; x_new++)
		{
			cosValue = cos(rotationAngleRad);
			sinValue = sin(rotationAngleRad);
			// 영상회전 전의 원영상에서의 좌표값 계산
			x = cosValue * (x_new - x_center) + sinValue * (y_new - y_center) + x_center;
			y = -sinValue * (x_new - x_center) + cosValue * (y_new - y_center) + y_center;
			// 가장 인접한 이웃화소 좌표값으로 매핑
			x_org = (int)(x + 0.5);
			y_org = (int)(y + 0.5);
			// 범위 조사: 원영상의 크기 영역을 벗어나는 경우
			if (x_org < 0 || x_org > width || y_org < 0 || y_org > height)
			{
				m_OutImage[y_new*width+x_new] = 0;
			}
			// 원 이미지의 범위내에 존재하는 경우 가장 인접한 이웃화소 보간법
			else
				m_OutImage[y_new*width + x_new] = m_InImage[y_org*width + x_org];
		}
	}
	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnBilinearInterpolation()
{
	// TODO: Add your command handler code here
	double scale = 2; // 영상을 1.6배 확대한다.
	int X_max = (int)(width * scale); // 확대된 영상의 새로운 폭 계산
	int Y_max = (int)(height * scale); // 확대된 영상의 새로운 높이 계산
	double x, y; // 역방향 사상된 좌표의 분수값
	double x_org, y_org; // 역방향 사상된 정수 좌표값
	unsigned char *ZoomImage;
	// 확대된 영상을 임시로 저장할 공간 동적할당
	ZoomImage = new unsigned char[Y_max*X_max];
	for (int y_new = 0; y_new < Y_max; y_new++)
	{
		for (int x_new = 0; x_new < X_max; x_new++)
		{
			x = x_new / scale;
			y = y_new / scale;
			// 1.1 가장  Bilinear 보간법으로 좌표값을 계산
			x_org = x - (int)x;
			y_org = y - (int)y;
			// 범위 조사: 원영상의 크기 영역을 벗어나는 경우
			if ((int)x <= 0 || int(x) >= width || (int)y <= 0 || (int)y >= height)
			{
				ZoomImage[y_new*X_max + x_new] = ZoomImage[(int)y*width + (int)x];
			}
			// 원 이미지의 범위내에 존재하는 경우 가장 인접한 이웃화소 보간법
			else
				ZoomImage[y_new*X_max + x_new] = m_InImage[(int)y * width + (int)x]*x_org*y_org + m_InImage[((int)y+1) * width + (int)x]*(1-y_org)*x_org
				+ m_InImage[(int)y * width + (int)x+1]*(1-x_org)*(y_org) +m_InImage[((int)y+1) * width + (int)x+1]*(1-y_org)*(1-x_org);
		}
	}
	// 1.2 확대된 영상을 원래크기(256x256)의 영상사이즈 만큼 출력한다.
	int diffX = abs((int)(width - X_max));
	int diffY = abs((int)(height - Y_max));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_OutImage[i*width + j] = ZoomImage[(diffY / 2 + i)*X_max + (j + diffX / 2)];
		}
	}
	delete[] ZoomImage; // 동적 할당된 메모리 해제
	UpdateAllViews(NULL);
}



void CMFC_Exp01Doc::OnZoomin()
{
	// TODO: Add your command handler code here
	/*********************************************************
// 1. 영상 확대
***********************************************************/
	double scale = 2; // 영상을 1.6배 확대한다.
	int X_max = (int)(width * scale); // 확대된 영상의 새로운 폭 계산
	int Y_max = (int)(height * scale); // 확대된 영상의 새로운 높이 계산
	double x, y; // 역방향 사상된 좌표의 분수값
	int x_org, y_org; // 역방향 사상된 정수 좌표값
	unsigned char *ZoomImage;
	// 확대된 영상을 임시로 저장할 공간 동적할당
	ZoomImage = new unsigned char[Y_max*X_max];
	for (int y_new = 0; y_new < Y_max; y_new++)
	{
		for (int x_new = 0; x_new < X_max; x_new++)
		{
			x = x_new / scale;
			y = y_new / scale;
			// 1.1 가장 인접한 이웃화소 보간법으로 좌표값을 계산
			x_org = (int)(x + 0.5);
			y_org = (int)(y + 0.5);
			// 범위 조사: 원영상의 크기 영역을 벗어나는 경우
			if (x_org < 0 || x_org > width || y_org < 0 || y_org > height)
			{
				ZoomImage[y_new*X_max + x_new] = 0;
			}
			// 원 이미지의 범위내에 존재하는 경우 가장 인접한 이웃화소 보간법
			else
				ZoomImage[y_new*X_max + x_new] = m_InImage[y_org*width+x_org];
		}
	}
	// 1.2 확대된 영상을 원래크기(256x256)의 영상사이즈 만큼 출력한다.
	int diffX = abs((int)(width - X_max));
	int diffY = abs((int)(height - Y_max));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_OutImage[i*width+j] = ZoomImage[(diffY/2+i)*X_max+ (j+diffX/2)];
		}
	}
	delete[] ZoomImage; // 동적 할당된 메모리 해제
	UpdateAllViews(NULL);

}




void CMFC_Exp01Doc::OnHorizontalMirroring()
{
	// TODO: Add your command handler code here
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			m_OutImage[(i)*width + (width-1-j)] = m_InImage[(i)*width + j];
	UpdateAllViews(NULL);
}


void CMFC_Exp01Doc::OnVerticalMirroring()
{
	// TODO: Add your command handler code here
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			m_OutImage[(height - 1 - i)*width +  j] = m_InImage[i *width +  j];
	UpdateAllViews(NULL);
}
