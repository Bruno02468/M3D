
// EditInfo.h

#pragma once

#include "afxwin.h"

class CEditInfo : public CEdit {
public:
    int selStart;
    int selEnd;
    int firstVisibleLine;

public:
    CEditInfo() {
        selStart = 0;
        selEnd = 0;
        firstVisibleLine = 0;
    }

protected:
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    DECLARE_MESSAGE_MAP()
};
