
// PaintbrushView.cpp: CPaintbrushView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Paintbrush.h"
#endif

#include "PaintbrushDoc.h"
#include "PaintbrushView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintbrushView

IMPLEMENT_DYNCREATE(CPaintbrushView, CView)

BEGIN_MESSAGE_MAP(CPaintbrushView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CPaintbrushView 생성/소멸

CPaintbrushView::CPaintbrushView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPaintbrushView::~CPaintbrushView()
{
}

BOOL CPaintbrushView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPaintbrushView 그리기

void CPaintbrushView::OnDraw(CDC* pDC)
{
	CPaintbrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	if (pDoc->m_arrayShape.size())
	{
		for (const auto shape : pDoc->m_arrayShape)
		{
			shape->draw(pDC);
		}
	}
}


// CPaintbrushView 인쇄

BOOL CPaintbrushView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPaintbrushView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPaintbrushView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPaintbrushView 진단

#ifdef _DEBUG
void CPaintbrushView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintbrushView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintbrushDoc* CPaintbrushView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintbrushDoc)));
	return (CPaintbrushDoc*)m_pDocument;
}
#endif //_DEBUG


// CPaintbrushView 메시지 처리기


void CPaintbrushView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPaintbrushDoc* pDoc = GetDocument();
	if (pDoc->m_mode == 1)
	{
		pDoc->m_pDrawShape = new DrawLine();
		static_cast<DrawLine*>(pDoc->m_pDrawShape)->m_logPen(pDoc->m_logPen);
		static_cast<DrawLine*>(pDoc->m_pDrawShape)->m_arrayLine.push_back(point);
	}
	else if (pDoc->m_mode == 2)
	{
		pDoc->m_pDrawShape = new DrawBmp();
		static_cast<DrawBmp*>(pDoc->m_pDrawShape)->rect_TopLeft(point);
		static_cast<DrawBmp*>(pDoc->m_pDrawShape)->m_bmpId(pDoc->m_lpcwstrBmpId);
	}
	else if (pDoc->m_mode == 3)
	{
		pDoc->m_pDrawShape = new DrawRect();
		static_cast<DrawRect*>(pDoc->m_pDrawShape)->m_logPen(pDoc->m_logPen);
		static_cast<DrawRect*>(pDoc->m_pDrawShape)->rect_TopLeft(point);
	}
	else if (pDoc->m_mode == 4)
	{
		pDoc->m_pDrawShape = new DrawCircle();
		static_cast<DrawCircle*>(pDoc->m_pDrawShape)->m_logPen(pDoc->m_logPen);
		static_cast<DrawCircle*>(pDoc->m_pDrawShape)->circle_TopLeft(point);
	}
	else if (pDoc->m_mode == 0)
	{
		for (DrawShape* bmp : pDoc->m_arrayShape) {
			if (bmp->check_bmp == true) {
				DrawBmp* bmp2 = new DrawBmp;
				bmp2 = (DrawBmp*)bmp;
				CRect rect(bmp2->rect.right - 30, bmp2->rect.bottom - 30, bmp2->rect.right + 30, bmp2->rect.right + 30);
				bmp2->isClicked = rect.PtInRect(point);

				//if (bmp2.isClicked) {
				//	m_pDrawBmp = &bmp;
				//	break;
				//}
			}
		}
	}

	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CPaintbrushView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPaintbrushDoc* pDoc = GetDocument();
	CClientDC dc(this);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON && pDoc->m_mode == 1)
	{
		pDoc->m_pDrawShape->draw(&dc);

		if (pDoc->m_pen_straight == 0) {
			static_cast<DrawLine*>(pDoc->m_pDrawShape)->m_arrayLine.push_back(point);
		}
	}

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->SetMousePositionOutput(point);

	CView::OnMouseMove(nFlags, point);
}


void CPaintbrushView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CPaintbrushDoc* pDoc = GetDocument();
	CClientDC dc(this);

	if (pDoc->m_mode == 1)
	{
		static_cast<DrawLine*>(pDoc->m_pDrawShape)->m_arrayLine.push_back(point);

		pDoc->m_arrayShape.push_back(pDoc->m_pDrawShape);
		pDoc->m_pDrawShape->draw(&dc);

	}
	else if (pDoc->m_mode == 2)
	{
		static_cast<DrawBmp*>(pDoc->m_pDrawShape)->rect_BottomRight(point);
		pDoc->m_pDrawShape->draw(&dc);
		pDoc->m_arrayShape.push_back(pDoc->m_pDrawShape);
	}
	else if (pDoc->m_mode == 3)
	{
		static_cast<DrawRect*>(pDoc->m_pDrawShape)->rect_BottomRight(point);
		pDoc->m_pDrawShape->draw(&dc);
		pDoc->m_arrayShape.push_back(pDoc->m_pDrawShape);
	}
	else if (pDoc->m_mode == 4)
	{
		static_cast<DrawCircle*>(pDoc->m_pDrawShape)->circle_BottomRight(point);
		pDoc->m_pDrawShape->draw(&dc);
		pDoc->m_arrayShape.push_back(pDoc->m_pDrawShape);
	}
	else if (pDoc->m_mode == 0)
	{
		for (DrawShape* bmp : pDoc->m_arrayShape) 
		{
			if (bmp->check_bmp == true) {
				DrawBmp* bmp2 = new DrawBmp;
				bmp2 = (DrawBmp*)bmp;
				if (bmp2->isClicked)
				{
					bmp2->rect.right = point.x;
					bmp2->rect.bottom = point.y;
					bmp2->isClicked = false;
				}
			}
		}
		pDoc->UpdateAllViews(NULL);
	}

	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}
