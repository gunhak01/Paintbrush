
// PaintbrushDoc.h: CPaintbrushDoc 클래스의 인터페이스


#pragma once
#include <vector>
using namespace std;

class DrawShape {
public:
	bool check_bmp = false;
	virtual void draw(CDC* dc) const = 0;
};

class DrawLine : public DrawShape
{
public:
	LOGPEN m_logPen1;
	vector<CPoint> m_arrayLine;

	DrawLine()
	{
		m_arrayLine.clear();
	}

	void m_logPen(LOGPEN& _m_logPen)
	{
		m_logPen1 = _m_logPen;
	}

	virtual void draw(CDC* dc) const override
	{
		dc->MoveTo(m_arrayLine[0]);
		CPen pen(m_logPen1.lopnStyle, m_logPen1.lopnWidth.x, m_logPen1.lopnColor);
		CPen* pOldPen = dc->SelectObject(&pen);
		for (const CPoint& pt : m_arrayLine)
		{
			dc->LineTo(pt);
		}
		dc->SelectObject(pOldPen);
	}
};

class DrawBmp : public DrawShape
{
public:
	LPCWSTR m_lpcwstrBmpId;
	CRect rect;

	bool isClicked = false;

	DrawBmp() { check_bmp = true; }

	void rect_TopLeft(CPoint m_pt)
	{
		rect.left = m_pt.x;
		rect.top = m_pt.y;
	}

	void rect_BottomRight(CPoint m_pt)
	{
		rect.right = m_pt.x;
		rect.bottom = m_pt.y;
	}

	void m_bmpId(LPCWSTR _m_lpcwstrFileName)
	{
		m_lpcwstrBmpId = _m_lpcwstrFileName;
	}

	virtual void draw(CDC* dc) const override
	{
		CDC MemDC;
		BITMAP bmpInfo;
		MemDC.CreateCompatibleDC(dc);

		CBitmap bmp;
		CBitmap* pOldBmp = NULL;
		bmp.LoadBitmap(m_lpcwstrBmpId);

		bmp.GetBitmap(&bmpInfo);
		pOldBmp = MemDC.SelectObject(&bmp);
		dc->StretchBlt(rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top,
			&MemDC,
			0, 0,
			bmpInfo.bmWidth, bmpInfo.bmHeight,
			SRCCOPY);
		MemDC.SelectObject(pOldBmp);
		MemDC.DeleteDC();
	}
};

class DrawRect : public DrawShape
{
public:
	LOGPEN m_logPen2;
	CRect rect;

	DrawRect() { }

	void m_logPen(LOGPEN _m_logPen)
	{
		m_logPen2 = _m_logPen;
	}

	void rect_TopLeft(CPoint m_pt)
	{
		rect.left = m_pt.x;
		rect.top = m_pt.y;
	}

	void rect_BottomRight(CPoint m_pt)
	{
		rect.right = m_pt.x;
		rect.bottom = m_pt.y;
	}

	virtual void draw(CDC* dc) const override
	{
		CPen pen(m_logPen2.lopnStyle, m_logPen2.lopnWidth.x, m_logPen2.lopnColor);
		CPen* pOldPen;
		pOldPen = dc->SelectObject(&pen);
		dc->Rectangle(rect);
		dc->SelectObject(pOldPen);
	}
};

class DrawCircle : public DrawShape
{
public:
	LOGPEN m_logPen3;
	CRect rect;

	DrawCircle() { }

	void m_logPen(LOGPEN _m_logPen)
	{
		m_logPen3 = _m_logPen;
	}

	void circle_TopLeft(CPoint m_pt)
	{
		rect.left = m_pt.x;
		rect.top = m_pt.y;
	}

	void circle_BottomRight(CPoint m_pt)
	{
		rect.right = m_pt.x;
		rect.bottom = m_pt.y;
	}

	virtual void draw(CDC* dc) const override
	{
		CPen pen(m_logPen3.lopnStyle, m_logPen3.lopnWidth.x, m_logPen3.lopnColor);
		CPen* pOldPen;
		pOldPen = dc->SelectObject(&pen);
		dc->Ellipse(rect);
		dc->SelectObject(pOldPen);
	}
};


class CPaintbrushDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CPaintbrushDoc() noexcept;
	DECLARE_DYNCREATE(CPaintbrushDoc)

// 특성입니다.
public:
	DrawShape* m_pDrawShape;
	vector<DrawShape*> m_arrayShape;

	LOGPEN m_logPen;
	LPCWSTR m_lpcwstrBmpId;

	int m_mode;
	int m_pen_straight;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CPaintbrushDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnPenColorBlack();
	afx_msg void OnPenColorBlue();
	afx_msg void OnPenColorGreen();
	afx_msg void OnPenColorRed();
	afx_msg void OnUpdatePenColorBlack(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenColorBlue(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenColorGreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenColorRed(CCmdUI* pCmdUI);
	afx_msg void OnPenSize1();
	afx_msg void OnPenSize5();
	afx_msg void OnPenSize10();
	afx_msg void OnUpdatePenSize1(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenSize5(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenSize10(CCmdUI* pCmdUI);
	afx_msg void OnPenStyleDash();
	afx_msg void OnPenStyleDot();
	afx_msg void OnPenStyleSolid();
	afx_msg void OnUpdatePenStyleDash(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenStyleDot(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenStyleSolid(CCmdUI* pCmdUI);
	afx_msg void OnModeCursur();
	afx_msg void OnModePen();
	afx_msg void OnSelectBmp1();
	afx_msg void OnSelectBmp2();
	afx_msg void OnUpdateSelectBmp1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectBmp2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModePicture(CCmdUI* pCmdUI);
	afx_msg void OnFigureStraight();
	afx_msg void OnModePicture();
	afx_msg void OnFigureSquare();
	afx_msg void OnFigureCircle();
};
