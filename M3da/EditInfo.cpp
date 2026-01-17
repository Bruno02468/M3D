
// EditInfo.cpp

#include "stdafx.h"
#include "EditInfo.h"

BEGIN_MESSAGE_MAP(CEditInfo, CEdit)
ON_WM_SETFOCUS()
ON_WM_KILLFOCUS()
ON_WM_VSCROLL()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

void CEditInfo::OnSetFocus(CWnd* pOldWnd) {
	SetRedraw(FALSE);
	CWnd::OnSetFocus(pOldWnd);
	SetSel(selStart, selEnd);
	int currentFirstVisibleLine = GetFirstVisibleLine();
	int deltaLine = firstVisibleLine - currentFirstVisibleLine;
	if (deltaLine != 0) {
		LineScroll(deltaLine);
	}
	SetRedraw(TRUE);
	Invalidate();
	UpdateWindow();
}

void CEditInfo::OnKillFocus(CWnd* pNewWnd) {
	GetSel(selStart, selEnd);
	firstVisibleLine = GetFirstVisibleLine();
	CEdit::OnKillFocus(pNewWnd);
}

void CEditInfo::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	bool hadFocus = (GetFocus() == this);
	int oldFirst = GetFirstVisibleLine();
	CEdit::OnVScroll(nSBCode, nPos, pScrollBar);
	int newFirst = GetFirstVisibleLine();
	if (newFirst != oldFirst) {
		firstVisibleLine = GetFirstVisibleLine();
		if (!hadFocus) {
		} else {
		}
	}
}

BOOL CEditInfo::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	bool hadFocus = (GetFocus() == this);
	int oldFirst = GetFirstVisibleLine();
	BOOL result = CEdit::OnMouseWheel(nFlags, zDelta, pt);
	int newFirst = GetFirstVisibleLine();
	if (newFirst != oldFirst) {
		firstVisibleLine = GetFirstVisibleLine();
		if (hadFocus) {
		} else {
		}
	}

	return result;
}
