
// MainFrm.h : interface of the CMainFrame class
//
#include "InputPane.h"
// MoMo_Material_SaveBugV1_05_20_2025_Start
#include <vector>
// MoMo_Material_SaveBugV1_05_20_2025_End
#pragma once

class CMainFrame: public CFrameWndEx {
	protected: // create from serialization only
		CMainFrame();
		DECLARE_DYNCREATE(CMainFrame)
		// momo
		void OnViewToolbarBC();
		void OnUpdateViewToolbarBC(CCmdUI* pCmdUI);
		void LockToolbarsDocking(bool lockAll);
		// momo

	public:
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
		// MoMo_Start
		struct ToolBarInfo {
				CMFCToolBar* pToolbar;
				UINT ResourceID;
				BOOL isVisible;
				int Align; // 0:any 1:right 2:left 3:top 4:bottom
				int DockCommand; // 1:DockPane 2:DockPaneLeftOf Negative:DockPane(&p_Input)
		};
		ToolBarInfo toolbars[19];
		//  MoMo// void sizeCbar();
		// MoMo_End
		virtual ~CMainFrame();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

	protected: // control bar embedded members
		// momo
		//// momo// CMFCMenuBar m_wndMenuBar;
		//// momo// CMFCToolBar m_wndToolBar;
		// CMFCMenuBar mWnd_MenuBar;
		// CMFCToolBar m_File;
		// CMFCToolBar m_MenuCommands;
		//// momo
		// CMFCStatusBar mWnd_StatusBar;
		// CMFCStatusBar mWnd_StatusBar;
		////momo
		// CMFCToolBarImages m_UserImages;
		////momo
		// CMFCToolBar m_Draw;
		//// momo on off button and menu
		// CMFCToolBar m_ShowHide;
		// CMFCToolBar m_Selection;
		//// momo on off button and menu
		// CMFCToolBar m_Create;
		// CMFCToolBar m_Edit;
		// CMFCToolBar m_FE;
		// CMFCToolBar m_Group;
		//// momo
		//// momo// CMFCToolBar m_Qwanta;
		//// momo
		// CMFCToolBar m_BC;
		// CMFCToolBar m_ELTYPE;
		// CMFCToolBar m_POST;
		// CMFCToolBar m_Projection;
		// CMFCToolBar m_Utils;
		// CMFCToolBar m_QFilter;
		// CMFCToolBar m_DIMS;

		//// Esp_Mod_Experimental_Toolbar_4_10_2025_Start: experimental toolbar field
		// CMFCToolBar m_EXP;
		//// Esp_Mod_Experimental_Toolbar_4_10_2025_End
		CMFCMenuBar m_MenuBar;
		CMFCStatusBar s_StatusBar;
		CMFCToolBar BoundaryConditionsToolbar;
		CMFCToolBar CreateToolbar;
		CMFCToolBar DimensionToolbar;
		CMFCToolBar DrawToolbar;
		CMFCToolBar EditToolbar;
		CMFCToolBar SetElementToolbar;
		CMFCToolBar ExperimentalToolbar;
		CMFCToolBar FiniteElementsToolbar;
		CMFCToolBar FileToolbar;
		CMFCToolBar GroupToolbar;
		CMFCToolBar MenuCommandsToolbar;
		CMFCToolBar PostProcessingToolbar;
		CMFCToolBar ProjectionToolbar;
		CMFCToolBar SelectFilterQuickToolbar;
		CMFCToolBar SelectToolbar;
		CMFCToolBar ShowHideToolbar;
		CMFCToolBar ElementVisibilityToolbar;
		CMFCToolBar GeomVisibilityToolbar;
		CMFCToolBar UtilitiesToolbar;
		// momo

		// Generated message map functions
	protected:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnViewCustomize();
		afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
		// afx_msg void OnUpdatePage(CCmdUI *pCmdUI);  //ADDED BY ME
		DECLARE_MESSAGE_MAP()

	public:
		afx_msg void OnSize(UINT nType, int cx, int cy);
		//  afx_msg void OnMeshFreetrimesh();
		//  afx_msg void OnToolsElementmasssummation();
		// MoMo_Start
		CFont m_EditFont;
		// MoMo_End
		// momo change command box color
		CInputPane p_Input;
		// momo change command box color

	public:
		inline void SetFontSpec(CFont& fontObj, int fontSize, CString fontName = _T("Tahoma"), bool isBold = false, CWnd* pCtrl = nullptr) {
			if (fontObj.m_hObject != NULL)
				fontObj.DeleteObject();

			CClientDC dc(AfxGetMainWnd());
			int nHeight = -MulDiv(fontSize, dc.GetDeviceCaps(LOGPIXELSY), 72);

			fontObj.CreateFont(
			    nHeight, 0, 0, 0,
			    isBold ? FW_BOLD : FW_NORMAL,
			    FALSE, FALSE, FALSE,
			    DEFAULT_CHARSET,
			    OUT_DEFAULT_PRECIS,
			    CLIP_DEFAULT_PRECIS,
			    DEFAULT_QUALITY,
			    DEFAULT_PITCH | FF_SWISS,
			    fontName);

			if (pCtrl)
				pCtrl->SetFont(&fontObj);
		}

		// MoMo_Start
	public:
		inline void GetCurrentFont(CEdit& editCtrl) {
			LOGFONT lf;
			CFont* pFont = editCtrl.GetFont();

			if (pFont != nullptr) {
				pFont->GetLogFont(&lf);
				CString fontName(lf.lfFaceName);
				int fontSize = abs(lf.lfHeight);
				CString fontSizeStr;
				fontSizeStr.Format(_T("%d"), fontSize);
				AfxMessageBox(_T("Font: ") + fontName + _T(", Size: ") + fontSizeStr);
			} else {
				AfxMessageBox(_T("No font found!"));
			}
		}
		// MoMo_End
};
