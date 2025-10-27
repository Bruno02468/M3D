
// stdafx.cpp : source file that includes just the standard includes
// M3da.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
// momo
#include "M3daView.h"
#include "resource.h"
// momo

// momo
void SetViewCursor(UINT cursorId) {
	if (cursorId == 0) {
		CPoint pt;
		::GetCursorPos(&pt);
		CWnd* pWnd = CWnd::WindowFromPoint(pt);
		if (pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CM3daView))) {
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		} else if (pWnd) {
			::SendMessage(pWnd->GetSafeHwnd(), WM_SETCURSOR, (WPARAM) pWnd->GetSafeHwnd(), MAKELPARAM(HTCLIENT, WM_MOUSEMOVE));
		}
	} else {
		CPoint pt;
		::GetCursorPos(&pt);
		CWnd* pWnd = CWnd::WindowFromPoint(pt);
		if (pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CM3daView))) {
			UINT cursorIdNew = cursorId;
			if (cursorId == 1) {
				cursorIdNew = IDC_MOUSE_CURSOR_MOVE;
			} else if (cursorId == 2) {
				cursorIdNew = IDC_MOUSE_CURSOR_ZOOM_IN_OUT;
			} else if (cursorId == 3) {
				cursorIdNew = IDC_MOUSE_CURSOR_ROTATE;
			}
			::SetCursor(AfxGetApp()->LoadCursor(cursorIdNew));
		}
	}
}
// momo