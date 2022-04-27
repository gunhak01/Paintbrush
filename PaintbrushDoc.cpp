
// PaintbrushDoc.cpp: CPaintbrushDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Paintbrush.h"
#endif

#include "PaintbrushDoc.h"

#include <propkey.h>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPaintbrushDoc

IMPLEMENT_DYNCREATE(CPaintbrushDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaintbrushDoc, CDocument)
	ON_COMMAND(IDM_PEN_COLOR_BLACK, &CPaintbrushDoc::OnPenColorBlack)
	ON_COMMAND(IDM_PEN_COLOR_BLUE, &CPaintbrushDoc::OnPenColorBlue)
	ON_COMMAND(IDM_PEN_COLOR_GREEN, &CPaintbrushDoc::OnPenColorGreen)
	ON_COMMAND(IDM_PEN_COLOR_RED, &CPaintbrushDoc::OnPenColorRed)
	ON_UPDATE_COMMAND_UI(IDM_PEN_COLOR_BLACK, &CPaintbrushDoc::OnUpdatePenColorBlack)
	ON_UPDATE_COMMAND_UI(IDM_PEN_COLOR_BLUE, &CPaintbrushDoc::OnUpdatePenColorBlue)
	ON_UPDATE_COMMAND_UI(IDM_PEN_COLOR_GREEN, &CPaintbrushDoc::OnUpdatePenColorGreen)
	ON_UPDATE_COMMAND_UI(IDM_PEN_COLOR_RED, &CPaintbrushDoc::OnUpdatePenColorRed)
	ON_COMMAND(IDM_PEN_SIZE_1, &CPaintbrushDoc::OnPenSize1)
	ON_COMMAND(IDM_PEN_SIZE_5, &CPaintbrushDoc::OnPenSize5)
	ON_COMMAND(IDM_PEN_SIZE_10, &CPaintbrushDoc::OnPenSize10)
	ON_UPDATE_COMMAND_UI(IDM_PEN_SIZE_1, &CPaintbrushDoc::OnUpdatePenSize1)
	ON_UPDATE_COMMAND_UI(IDM_PEN_SIZE_5, &CPaintbrushDoc::OnUpdatePenSize5)
	ON_UPDATE_COMMAND_UI(IDM_PEN_SIZE_10, &CPaintbrushDoc::OnUpdatePenSize10)
	ON_COMMAND(IDM_PEN_STYLE_DASH, &CPaintbrushDoc::OnPenStyleDash)
	ON_COMMAND(IDM_PEN_STYLE_DOT, &CPaintbrushDoc::OnPenStyleDot)
	ON_COMMAND(IDM_PEN_STYLE_SOLID, &CPaintbrushDoc::OnPenStyleSolid)
	ON_UPDATE_COMMAND_UI(IDM_PEN_STYLE_DASH, &CPaintbrushDoc::OnUpdatePenStyleDash)
	ON_UPDATE_COMMAND_UI(IDM_PEN_STYLE_DOT, &CPaintbrushDoc::OnUpdatePenStyleDot)
	ON_UPDATE_COMMAND_UI(IDM_PEN_STYLE_SOLID, &CPaintbrushDoc::OnUpdatePenStyleSolid)
	ON_COMMAND(IDM_MODE_CURSUR, &CPaintbrushDoc::OnModeCursur)
	ON_COMMAND(IDM_MODE_PEN, &CPaintbrushDoc::OnModePen)
	ON_COMMAND(IDM_SELECT_BMP1, &CPaintbrushDoc::OnSelectBmp1)
	ON_COMMAND(IDM_SELECT_BMP2, &CPaintbrushDoc::OnSelectBmp2)
	ON_UPDATE_COMMAND_UI(IDM_SELECT_BMP1, &CPaintbrushDoc::OnUpdateSelectBmp1)
	ON_UPDATE_COMMAND_UI(IDM_SELECT_BMP2, &CPaintbrushDoc::OnUpdateSelectBmp2)
	ON_UPDATE_COMMAND_UI(IDM_MODE_PICTURE, &CPaintbrushDoc::OnUpdateModePicture)
	ON_COMMAND(IDM_FIGURE_STRAIGHT, &CPaintbrushDoc::OnFigureStraight)
	ON_COMMAND(IDM_MODE_PICTURE, &CPaintbrushDoc::OnModePicture)
	ON_COMMAND(IDM_FIGURE_SQUARE, &CPaintbrushDoc::OnFigureSquare)
	ON_COMMAND(IDM_FIGURE_CIRCLE, &CPaintbrushDoc::OnFigureCircle)
END_MESSAGE_MAP()


// CPaintbrushDoc 생성/소멸

CPaintbrushDoc::CPaintbrushDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CPaintbrushDoc::~CPaintbrushDoc()
{
}

BOOL CPaintbrushDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	m_mode = 0;
	m_logPen.lopnStyle = 0;
	m_logPen.lopnColor = RGB(0, 0, 0);
	m_logPen.lopnWidth.x = 1;

	m_pen_straight = 0;

	m_lpcwstrBmpId = (LPCWSTR)"";
	return TRUE;
}




// CPaintbrushDoc serialization

void CPaintbrushDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CPaintbrushDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CPaintbrushDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPaintbrushDoc::SetSearchContent(const CString& value)
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

// CPaintbrushDoc 진단

#ifdef _DEBUG
void CPaintbrushDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaintbrushDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPaintbrushDoc 명령




void CPaintbrushDoc::OnPenColorBlack()
{
	m_logPen.lopnColor = RGB(0, 0, 0);
}


void CPaintbrushDoc::OnPenColorBlue()
{
	m_logPen.lopnColor = RGB(0, 0, 255);
}


void CPaintbrushDoc::OnPenColorGreen()
{
	m_logPen.lopnColor = RGB(0, 255, 0);
}


void CPaintbrushDoc::OnPenColorRed()
{
	m_logPen.lopnColor = RGB(255, 0, 0);
}


void CPaintbrushDoc::OnUpdatePenColorBlack(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnColor == RGB(0, 0, 0));
}


void CPaintbrushDoc::OnUpdatePenColorBlue(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnColor == RGB(0, 0, 255));
}


void CPaintbrushDoc::OnUpdatePenColorGreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnColor == RGB(0, 255, 0));
}


void CPaintbrushDoc::OnUpdatePenColorRed(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnColor == RGB(255, 0, 0));
}


void CPaintbrushDoc::OnPenSize1()
{
	m_logPen.lopnWidth.x = 1;
}


void CPaintbrushDoc::OnPenSize5()
{
	m_logPen.lopnWidth.x = 5;
}


void CPaintbrushDoc::OnPenSize10()
{
	m_logPen.lopnWidth.x = 10;
}


void CPaintbrushDoc::OnUpdatePenSize1(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnWidth.x == 1);
}


void CPaintbrushDoc::OnUpdatePenSize5(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnWidth.x == 5);
}


void CPaintbrushDoc::OnUpdatePenSize10(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnWidth.x == 10);
}


void CPaintbrushDoc::OnPenStyleDash()
{
	m_logPen.lopnStyle = 1;
	m_mode = 1;
}


void CPaintbrushDoc::OnPenStyleDot()
{
	m_logPen.lopnStyle = 2;
	m_mode = 1;
}


void CPaintbrushDoc::OnPenStyleSolid()
{
	m_logPen.lopnStyle = 0;
	m_mode = 1;
}


void CPaintbrushDoc::OnUpdatePenStyleDash(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnStyle == 1);
	pCmdUI->Enable(m_mode == 1);
}


void CPaintbrushDoc::OnUpdatePenStyleDot(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnStyle == 2);
	pCmdUI->Enable(m_mode == 1);
}


void CPaintbrushDoc::OnUpdatePenStyleSolid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_logPen.lopnStyle == 0);
	pCmdUI->Enable(m_mode == 1);
}


void CPaintbrushDoc::OnModeCursur()
{
	m_mode = 0;
}


void CPaintbrushDoc::OnModePen()
{
	m_mode = 1;
	m_pen_straight = 0;
}


void CPaintbrushDoc::OnSelectBmp1()
{
	m_lpcwstrBmpId = (LPCWSTR)IDB_BITMAP1;
}


void CPaintbrushDoc::OnSelectBmp2()
{
	m_lpcwstrBmpId = (LPCWSTR)IDB_BITMAP2;
}


void CPaintbrushDoc::OnUpdateSelectBmp1(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_lpcwstrBmpId == (LPCWSTR)IDB_BITMAP1);
}


void CPaintbrushDoc::OnUpdateSelectBmp2(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_lpcwstrBmpId == (LPCWSTR)IDB_BITMAP2);
}


void CPaintbrushDoc::OnUpdateModePicture(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!(m_lpcwstrBmpId == (LPCWSTR)""));
}


void CPaintbrushDoc::OnFigureStraight()
{
	m_mode = 1;
	m_pen_straight = 1;
}


void CPaintbrushDoc::OnModePicture()
{
	m_mode = 2;
}


void CPaintbrushDoc::OnFigureSquare()
{
	m_mode = 3;
}


void CPaintbrushDoc::OnFigureCircle()
{
	m_mode = 4;
}
