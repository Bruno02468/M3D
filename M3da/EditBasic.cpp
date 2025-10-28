// EditBasic.cpp : implementation file
//

#include "stdafx.h"
#include "M3da.h"
#include "EditBasic.h"
// MoMo_Start
#include "GLOBAL_VARS.h"
// MoMo_End

// CEditBasic

IMPLEMENT_DYNAMIC(CEditBasic, CEdit)

// momo change command box color
// CEditBasic::CEditBasic() {
//}
CEditBasic::CEditBasic()
    : m_bgColor(::GetSysColor(COLOR_WINDOW)) {
	m_brush.CreateSolidBrush(m_bgColor);
}
// momo change command box color

CEditBasic::~CEditBasic() {
}

BEGIN_MESSAGE_MAP(CEditBasic, CEdit)
// momo change command box color
ON_WM_CTLCOLOR_REFLECT()
// momo change command box color
// momo custom right click for edit text
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_EDIT12_RIGHTCLICK_UNDO, &CEditBasic::OnEdit12RightClickUndo)
ON_COMMAND(ID_EDIT12_RIGHTCLICK_CUT, &CEditBasic::OnEdit12RightClickCut)
ON_COMMAND(ID_EDIT12_RIGHTCLICK_COPY, &CEditBasic::OnEdit12RightClickCopy)
ON_COMMAND(ID_EDIT12_RIGHTCLICK_PASTE, &CEditBasic::OnEdit12RightClickPaste)
ON_COMMAND(ID_EDIT12_RIGHTCLICK_DELETE, &CEditBasic::OnEdit12RightClickDelete)
ON_COMMAND(ID_EDIT12_RIGHTCLICK_SELECTALL, &CEditBasic::OnEdit12RightClickSelectAll)
ON_COMMAND(ID_EDIT12_RIGHTCLICK_CLEARALL, &CEditBasic::OnEdit12RightClickClearAll)
ON_COMMAND(ID_EDIT12_RIGHTCLICK_LOCK, &CEditBasic::OnEdit12RightClickLock)
ON_COMMAND(ID_EDIT12_RIGHTCLICK_UNLOCK, &CEditBasic::OnEdit12RightClickUnlock)
// momo custom right click for edit text
END_MESSAGE_MAP()

// CEditBasic message handlers

// MoMo_Start
// BOOL CEditBasic::PreTranslateMessage(MSG* pMsg)
//{
//  // TODO: Add your specialized code here and/or call the base class
//
//  if (pMsg->wParam == VK_ESCAPE)
//  {
//    return TRUE;
//  }
//  else
//  {
//    return CEdit::PreTranslateMessage(pMsg);
//  }
//}

BOOL CEditBasic::PreTranslateMessage(MSG* pMsg) {
	static bool ctrl_shift_down = false;
	static bool ctrl_down = false;
	static bool shift_down = false;
	static bool f1_down = false;
	static bool f2_down = false;
	static bool f3_down = false;
	static bool f4_down = false;
	if (pMsg->wParam == VK_ESCAPE && pMsg->message == WM_KEYDOWN) {
		// Escape down
		if (!SeedVals.IsSeedMode) {
			outtextMSG2("C");
		} else {
			outtextMSG2("Cancel");
		}
		return TRUE;
	} else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F1) {
		if (!f1_down) {
			// F1 down
			f1_down = true;
			SetViewCursor(IDC_MOUSE_CURSOR_MOVE);
			m_iFuncKey = 1;
		}
		return TRUE;
	} else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2) {
		if (!f2_down) {
			// F2 down
			f2_down = true;
			SetViewCursor(IDC_MOUSE_CURSOR_ZOOM_IN_OUT);
			m_iFuncKey = 2;
		}
		return TRUE;
	} else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F3) {
		if (!f3_down) {
			// F3 down
			f3_down = true;
			SetViewCursor(IDC_MOUSE_CURSOR_ROTATE);
			m_iFuncKey = 3;
		}
		return TRUE;
	} else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F4) {
		if (!f4_down) {
			// F4 down
			f4_down = true;
			SetViewCursor(IDC_MOUSE_CURSOR_ZOOM_BOX);
			m_iFuncKey = 7;
		}
		return TRUE;
	} else if (pMsg->message == WM_KEYDOWN && (::GetKeyState(VK_CONTROL) & 0x8000) && toupper((int) pMsg->wParam) == 'C') {
		// Ctrl+C
		Copy();
		return TRUE;
	} else if (pMsg->message == WM_KEYDOWN && (::GetKeyState(VK_CONTROL) & 0x8000) && toupper((int) pMsg->wParam) == 'X') {
		// Ctrl+X
		Cut();
		return TRUE;
	} else if (pMsg->message == WM_KEYDOWN && (::GetKeyState(VK_CONTROL) & 0x8000) && toupper((int) pMsg->wParam) == 'V') {
		// Ctrl+V
		Paste();
		return TRUE;
	} else if (pMsg->message == WM_KEYDOWN && (::GetKeyState(VK_CONTROL) & 0x8000) && toupper((int) pMsg->wParam) == 'A') {
		// Ctrl+A
		SetSel(0, -1);
		return TRUE;
	} else if (pMsg->message == WM_KEYDOWN && (::GetKeyState(VK_CONTROL) & 0x8000) && (::GetKeyState(VK_SHIFT) & 0x8000)) {
		if (!ctrl_shift_down) {
			// Ctrl+Shift down
			ctrl_shift_down = true;
			SetViewCursor(IDC_MOUSE_CURSOR_ZOOM_BOX);
			m_iFuncKey = 7;
		}
	} else if (pMsg->message == WM_KEYDOWN && (::GetKeyState(VK_CONTROL) & 0x8000)) {
		if (!ctrl_down) {
			// Ctrl down
			ctrl_down = true;
			SetViewCursor(IDC_MOUSE_CURSOR_MOVE);
			m_iFuncKey = 1;
		}
	} else if (pMsg->message == WM_KEYDOWN && (::GetKeyState(VK_SHIFT) & 0x8000)) {
		if (!shift_down) {
			// Shift down
			shift_down = true;
			SetViewCursor(IDC_MOUSE_CURSOR_ROTATE);
			m_iFuncKey = 3;
		}
	} else if (pMsg->message == WM_KEYUP && pMsg->wParam == VK_F1) {
		// F1 up
		f1_down = false;
		SetViewCursor(0);
		m_iFuncKey = 0;
		return TRUE;
	} else if (pMsg->message == WM_KEYUP && pMsg->wParam == VK_F2) {
		// F2 up
		f2_down = false;
		SetViewCursor(0);
		m_iFuncKey = 0;
		return TRUE;
	} else if (pMsg->message == WM_KEYUP && pMsg->wParam == VK_F3) {
		// F3 up
		f3_down = false;
		SetViewCursor(0);
		m_iFuncKey = 0;
		return TRUE;
	} else if (pMsg->message == WM_KEYUP && pMsg->wParam == VK_F4) {
		// F4 up
		f4_down = false;
		SetViewCursor(0);
		m_iFuncKey = 0;
		return TRUE;
	} else if (pMsg->message == WM_KEYUP && pMsg->wParam == VK_CONTROL) {
		// Ctrl up
		ctrl_down = false;
		if (ctrl_shift_down) {
			SetViewCursor(IDC_MOUSE_CURSOR_ROTATE);
			m_iFuncKey = 3;
		} else {
			SetViewCursor(0);
			m_iFuncKey = 0;
		}
		ctrl_shift_down = false;
	} else if (pMsg->message == WM_KEYUP && pMsg->wParam == VK_SHIFT) {
		// Shift up
		shift_down = false;
		if (ctrl_shift_down) {
			SetViewCursor(IDC_MOUSE_CURSOR_MOVE);
			m_iFuncKey = 1;
		} else {
			SetViewCursor(0);
			m_iFuncKey = 0;
		}
		ctrl_shift_down = false;
	}
	return CEdit::PreTranslateMessage(pMsg);
}
//  MoMo_End

// momo change command box color
void CEditBasic::SetBgColor(COLORREF clr) {
	m_bgColor = clr;
	if (m_brush.GetSafeHandle())
		m_brush.DeleteObject();
	m_brush.CreateSolidBrush(m_bgColor);
	Invalidate();
}

HBRUSH CEditBasic::CtlColor(CDC* cDC, UINT /*nCtlColor*/) {
	cDC->SetBkColor(m_bgColor);
	return (HBRUSH) m_brush.GetSafeHandle();
}
// momo change command box color
// momo custom right click for edit text
void CEditBasic::OnContextMenu(CWnd* pWnd, CPoint point) {
	if (point.x == -1 && point.y == -1) {
		CRect rc;
		GetWindowRect(&rc);
		point = rc.CenterPoint();
	}
	CMenu menu;
	menu.CreatePopupMenu();
	bool bReadOnly = (GetStyle() & ES_READONLY) != 0;
	int nStart = 0, nEnd = 0;
	GetSel(nStart, nEnd);
	bool hasSelection = (nStart != nEnd);
	BOOL canUndo = CanUndo();
	BOOL hasClipboardText = ::IsClipboardFormatAvailable(CF_TEXT) || ::IsClipboardFormatAvailable(CF_UNICODETEXT);
	CString cur;
	GetWindowText(cur);
	menu.AppendMenu(MF_STRING, ID_EDIT12_RIGHTCLICK_UNDO, _T("Undo"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_EDIT12_RIGHTCLICK_CUT, _T("Cut"));
	menu.AppendMenu(MF_STRING, ID_EDIT12_RIGHTCLICK_COPY, _T("Copy"));
	menu.AppendMenu(MF_STRING, ID_EDIT12_RIGHTCLICK_PASTE, _T("Paste"));
	menu.AppendMenu(MF_STRING, ID_EDIT12_RIGHTCLICK_DELETE, _T("Delete"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_EDIT12_RIGHTCLICK_SELECTALL, _T("Select All"));
	menu.AppendMenu(MF_STRING, ID_EDIT12_RIGHTCLICK_CLEARALL, _T("Clear All"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_EDIT12_RIGHTCLICK_LOCK, _T("Lock (Read-only)"));
	menu.AppendMenu(MF_STRING, ID_EDIT12_RIGHTCLICK_UNLOCK, _T("Unlock (Editable)"));
	if (bReadOnly) {
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_UNDO, MF_BYCOMMAND | MF_GRAYED);
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_CUT, MF_BYCOMMAND | MF_GRAYED);
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_PASTE, MF_BYCOMMAND | MF_GRAYED);
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_DELETE, MF_BYCOMMAND | MF_GRAYED);
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_LOCK, MF_BYCOMMAND | MF_GRAYED);
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_UNLOCK, MF_BYCOMMAND | MF_ENABLED);
	} else {
		if (canUndo) {
			menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_UNDO, MF_BYCOMMAND | MF_ENABLED);
		} else {
			menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_UNDO, MF_BYCOMMAND | MF_GRAYED);
		}
		if (hasSelection) {
			menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_CUT, MF_BYCOMMAND | MF_ENABLED);
		} else {
			menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_CUT, MF_BYCOMMAND | MF_GRAYED);
		}
		if (hasClipboardText) {
			menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_PASTE, MF_BYCOMMAND | MF_ENABLED);
		} else {
			menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_PASTE, MF_BYCOMMAND | MF_GRAYED);
		}
		if (hasSelection) {
			menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_DELETE, MF_BYCOMMAND | MF_ENABLED);
		} else {
			menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_DELETE, MF_BYCOMMAND | MF_GRAYED);
		}
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_LOCK, MF_BYCOMMAND | MF_ENABLED);
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_UNLOCK, MF_BYCOMMAND | MF_GRAYED);
	}
	if (!hasSelection) {
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_COPY, MF_BYCOMMAND | MF_GRAYED);
	} else {
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_COPY, MF_BYCOMMAND | MF_ENABLED);
	}
	if (!cur.IsEmpty()) {
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_SELECTALL, MF_BYCOMMAND | MF_ENABLED);
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_CLEARALL, MF_BYCOMMAND | MF_ENABLED);
	} else {
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_SELECTALL, MF_BYCOMMAND | MF_GRAYED);
		menu.EnableMenuItem(ID_EDIT12_RIGHTCLICK_CLEARALL, MF_BYCOMMAND | MF_GRAYED);
	}
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CEditBasic::OnEdit12RightClickUndo() {
	if (CanUndo())
		Undo();
}

void CEditBasic::OnEdit12RightClickCut() {
	Cut();
}

void CEditBasic::OnEdit12RightClickCopy() {
	Copy();
}

void CEditBasic::OnEdit12RightClickPaste() {
	Paste();
}

void CEditBasic::OnEdit12RightClickDelete() {
	SendMessage(WM_CLEAR);
}

void CEditBasic::OnEdit12RightClickSelectAll() {
	SetSel(0, -1);
	SetFocus();
}

void CEditBasic::OnEdit12RightClickClearAll() {
	SetWindowText(_T(""));
}

void CEditBasic::OnEdit12RightClickLock() {
	SetReadOnly(TRUE);
}

void CEditBasic::OnEdit12RightClickUnlock() {
	SetReadOnly(FALSE);
}
// momo custom right click for edit text
