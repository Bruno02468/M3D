
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "M3da.h"

#include "MainFrm.h"

// MoMo_Start
#include <afxstr.h>
#include <vector>
#include "AppSettings.h"
// MoMo_End
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
CEditBasic* Edit1; // momo: "Command Report Text Box"
CEditBasic* Edit2; // momo: "Information Text Box"
CMyEdit* Edit3; // momo: "Command Entry Text Box"
// momo make main buttons
CMFCButton* buttonCancel;
CMFCButton* buttonDone;
// momo make main buttons
//// momo ModernOpenGL_Start
////CMyEdit* EditViewScales;
//// momo ModernOpenGL_End
CString sText;
CString sTextMSG;
CString sTextMSG2;
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

// momo
// momo// const int iMaxUserToolbars = 10;
const int iMaxUserToolbars = 20;
// momo
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
ON_WM_CREATE()
ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
ON_WM_SIZE()
// ON_UPDATE_COMMAND_UI(ID_INDC_LC, &CMainFrame::OnUpdatePage)
//  ON_COMMAND(ID_MESH_FREETRIMESH, &CMainFrame::OnMeshFreetrimesh)
// ON_COMMAND(ID_TOOLS_ELEMENTMASSSUMMATION, &CMainFrame::OnToolsElementmasssummation)
// momo
ON_COMMAND(IDR_BOUNDARYCONDITIONS_TOOLBAR_MENU, OnViewToolbarBC)
ON_UPDATE_COMMAND_UI(IDR_BOUNDARYCONDITIONS_TOOLBAR_MENU, OnUpdateViewToolbarBC)
// momo
END_MESSAGE_MAP()

static UINT indicators[] =
    {
        ID_SEPARATOR, // status line indicator
        ID_INDC_LC,
        ID_INDC_BC,
        ID_INDICATOR_TS,
};
// ID_INDC_LC,
// ID_INDC_BC,
//  CMainFrame construction/destruction

CMainFrame::CMainFrame() {
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame() {
}

// ADDED BY ME
// void CMainFrame::OnUpdatePage(CCmdUI *pCmdUI)
//{
//     pCmdUI->Enable();
//     CString strPage;
//     strPage.Format(_T("LC: %d"), -1);
//     //strPage.Format(_T("Page %d"), m_nPage);
//    pCmdUI->SetText(strPage);
//    this->
//}

// momo
// int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
//	int iIDR;
//	iIDR = IDR_DRAW_TOOLBAR;
//	// momo on off button and menu
//	iIDR = IDR_SHOWHIDE_TOOLBAR;
//	iIDR = IDR_SELECT_TOOLBAR;
//	// momo on off button and menu
//	iIDR = IDR_CREATE_TOOLBAR;
//	iIDR = IDR_EDIT_TOOLBAR;
//	iIDR = IDR_FINITEELEMENS_TOOLBAR;
//	iIDR = IDR_GROUP_TOOLBAR;
//	iIDR = IDR_BOUNDARYCONDITIONS_TOOLBAR;
//	iIDR = IDR_SETELEMENT_TOOLBAR;
//	iIDR = IDR_POSTPROCESSING_TOOLBAR;
//	iIDR = IDR_PROJECTION_TOOLBAR;
//	iIDR = IDR_UTILITIES_TOOLBAR;
//	iIDR = IDR_SELECTFILTERQUICK_TOOLBAR;
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_Start: experimental toolbar
//	iIDR = IDR_EXPERIMENTAL_TOOLBAR;
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_End
//	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//	BOOL bNameValid;
//
//	if (!m_wndMenuBar.Create(this)) {
//		TRACE0("Failed to create menubar\n");
//		return -1; // fail to create
//	}
//
//	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
//
//	// prevent the menu bar from taking the focus on activation
//	CMFCPopupMenu::SetForceMenuFocus(FALSE);
//
//	// momo
//	// if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
//	//    !m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME)) {
//	//	TRACE0("Failed to create toolbar\n");
//	//	return -1; // fail to create
//	//}
//	if (!m_File.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 1) ||
//	    !m_File.LoadToolBar(IDR_MAINFRAME)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//
//	if (!m_MenuCommands.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 17) ||
//	    !m_MenuCommands.LoadToolBar(IDR_MENUCOMMANDS_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	// momo
//
//	// Roy note the new CreateEx calls are not the same as
//	// the first
//	// each new added tool bar requires a new ID
//	// specified on the following line
//	if (!m_Draw.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 2) ||
//	    !m_Draw.LoadToolBar(IDR_DRAW_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//
//	// momo on off button and menu
//	if (!m_ShowHide.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 3) ||
//	    !m_ShowHide.LoadToolBar(IDR_SHOWHIDE_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//
//	if (!m_Selection.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 4) ||
//	    !m_Selection.LoadToolBar(IDR_SELECT_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	// momo on off button and menu
//
//	if (!m_Create.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 5) ||
//	    !m_Create.LoadToolBar(IDR_CREATE_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//
//	if (!m_Edit.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 6) ||
//	    !m_Edit.LoadToolBar(IDR_EDIT_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	if (!m_FE.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 7) ||
//	    !m_FE.LoadToolBar(IDR_FINITEELEMENS_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	if (!m_Group.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 8) ||
//	    !m_Group.LoadToolBar(IDR_GROUP_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	if (!m_BC.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 9) ||
//	    !m_BC.LoadToolBar(IDR_BOUNDARYCONDITIONS_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	if (!m_ELTYPE.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 10) ||
//	    !m_ELTYPE.LoadToolBar(IDR_SETELEMENT_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	if (!m_POST.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 11) ||
//	    !m_POST.LoadToolBar(IDR_POSTPROCESSING_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	if (!m_Projection.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 12) ||
//	    !m_Projection.LoadToolBar(IDR_PROJECTION_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	if (!m_Utils.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 13) ||
//	    !m_Utils.LoadToolBar(IDR_UTILITIES_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	if (!m_QFilter.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 14) ||
//	    !m_QFilter.LoadToolBar(IDR_SELECTFILTERQUICK_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//
//	if (!m_DIMS.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 15) ||
//	    !m_DIMS.LoadToolBar(IDR_DIMENSION_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_Start: create experimental toolbar
//	if (!m_EXP.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 16) ||
//	    !m_EXP.LoadToolBar(IDR_EXPERIMENTAL_TOOLBAR)) {
//		TRACE0("Failed to create toolbar\n");
//		return -1; // fail to create
//	}
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_Start_End
//
//	CString strToolBarName;
//	// momo
//	// momo// bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
//	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_FILE);
//	// momo
//	ASSERT(bNameValid);
//	// momo
//	// momo// m_wndToolBar.SetWindowText(strToolBarName);
//	m_File.SetWindowText(strToolBarName);
//	CString strToolBarName13;
//	bNameValid = strToolBarName13.LoadString(IDR_MENUCOMMANDS_TOOLBAR); // IDS_DRAW
//	m_MenuCommands.SetWindowText(strToolBarName13);
//	// momo
//
//	CString strToolBarName2;
//	int iIDS;
//	iIDS = IDS_DRAW;
//	bNameValid = strToolBarName2.LoadString(IDS_DRAW); // IDS_DRAW
//	// ASSERT(bNameValid);
//	m_Draw.SetWindowText("Draw");
//
//	// momo on off button and menu
//	CString strToolBarName11;
//	bNameValid = strToolBarName11.LoadString(IDS_SHOWHIDE);
//	// ASSERT(bNameValid);
//	m_ShowHide.SetWindowText("Show/Hide");
//
//	CString strToolBarName12;
//	bNameValid = strToolBarName12.LoadString(IDS_SELECTION_TOOLBAR);
//	// ASSERT(bNameValid);
//	m_Selection.SetWindowText("Selection");
//	// momo on off button and menu
//
//	CString strToolBarName3;
//	bNameValid = strToolBarName3.LoadString(IDS_CREATE2);
//	// ASSERT(bNameValid);
//	m_Create.SetWindowText("Create");
//
//	CString strToolBarName4;
//	bNameValid = strToolBarName4.LoadString(IDS_EDIT);
//	// ASSERT(bNameValid);
//	m_Edit.SetWindowText("Edit");
//
//	CString strToolBarName5;
//	bNameValid = strToolBarName5.LoadString(IDS_FE);
//	// ASSERT(bNameValid);
//	m_FE.SetWindowText("F.E.");
//
//	CString strToolBarName6;
//	bNameValid = strToolBarName6.LoadString(IDS_GROUP);
//	// ASSERT(bNameValid);
//	m_Group.SetWindowText("Groups");
//
//	CString strToolBarName7;
//	bNameValid = strToolBarName7.LoadString(IDS_BC);
//	// ASSERT(bNameValid);
//	m_BC.SetWindowText("Boundary Conditions");
//
//	CString strToolBarName8;
//	bNameValid = strToolBarName8.LoadString(IDS_ELTYPE);
//	// ASSERT(bNameValid);
//	m_ELTYPE.SetWindowText("Element Types");
//
//	CString strToolBarName9;
//	bNameValid = strToolBarName9.LoadString(IDS_POST);
//	// ASSERT(bNameValid);
//	m_POST.SetWindowText("Post Processing");
//
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_Start: added experimental toolbar
//	CString strToolBarName10;
//	bNameValid = strToolBarName10.LoadString(IDS_EXPERIMENTAL);
//	// ASSERT(bNameValid);
//	m_EXP.SetWindowText("Experimental");
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_Start: END
//
//	m_Projection.SetWindowText("Project");
//	m_Utils.SetWindowText("Utils");
//	m_QFilter.SetWindowText("Quick Filter");
//	m_DIMS.SetWindowText("Dimension");
//
//	CString strCustomize;
//	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
//	ASSERT(bNameValid);
//	// momo
//	// momo// m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_File.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_MenuCommands.EnableCustomizeButton(TRUE, IDR_MENUCOMMANDS_TOOLBAR, strCustomize);
//	// momo
//	m_Draw.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	// momo on off button and menu
//	m_ShowHide.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_Selection.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	// momo on off button and menu
//	m_Create.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_Edit.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_FE.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_Group.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_BC.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_ELTYPE.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_POST.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_Projection.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_Utils.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_QFilter.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	m_DIMS.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_Start: Added experimental toolbar
//	m_EXP.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_End
//
//	// m_Qwanta.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//	//  Allow user-defined toolbars operations:
//	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);
//
//	if (!mWnd_StatusBar.Create(this)) {
//		TRACE0("Failed to create status bar\n");
//		return -1; // fail to create
//	}
//	mWnd_StatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
//	CRect R;
//	this->GetWindowRect(&R);
//	R.top = 500;
//	// BOOL brc=m_Input.Create("Input",this,R,TRUE,IDD_INPUT,WS_CHILD | WS_VISIBLE ,AFX_CBRS_REGULAR_TABS,AFX_DEFAULT_DOCKING_PANE_STYLE,NULL);
//	// BOOL brc=m_Input.Create("Input", this, R, FALSE, IDD_INPUT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT| CBRS_FLOAT_MULTI);
//	// momo
//	// if (!m_Input.Create("Input", this, CRect(0, 0, 100, 100), FALSE, IDD_INPUT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI)) {
//	//	TRACE0("Failed to create input window\n");
//	//	return FALSE; // failed to create
//	//}
//	if (!mWnd_Input.Create("", this, CRect(0, 0, 100, 100), FALSE, IDD_INPUT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI)) {
//		TRACE0("Failed to create input window\n");
//		return FALSE; // failed to create
//	}
//	// momo
//
//	Edit1 = &mWnd_Input.Edit1;
//	Edit2 = &mWnd_Input.Edit2;
//	Edit3 = &mWnd_Input.Edit3;
//	//// momo ModernOpenGL_Start
//	////EditViewScales = &m_Input.EditViewScales;
//	//// momo ModernOpenGL_End
//	//  MoMo_Start
//	SetFontSpec(m_EditFont, 10, _T("Arial"), true, &mWnd_Input.Edit1);
//	SetFontSpec(m_EditFont, 10, _T("Arial"), true, &mWnd_Input.Edit2);
//	SetFontSpec(m_EditFont, 10, _T("Arial"), true, &mWnd_Input.Edit3);
//	//// momo ModernOpenGL_Start
//	////SetFontSpec(m_EditFont, 10, _T("Arial"), true, &m_Input.EditViewScales);
//	//// momo ModernOpenGL_End
//	//  MoMo_End
//	mWnd_Input.EnableDocking(CBRS_ALIGN_ANY);
//	DockPane(&mWnd_Input);
//
//	// momo move menubar to top
//	m_wndMenuBar.EnableDocking(CBRS_ALIGN_TOP);
//	// momo move menubar to top
//	// momo
//	// momo// m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	m_File.EnableDocking(CBRS_ALIGN_ANY);
//	m_MenuCommands.EnableDocking(CBRS_ALIGN_ANY);
//	// momo
//	m_Draw.EnableDocking(CBRS_ALIGN_ANY);
//	// momo on off button and menu
//	m_ShowHide.EnableDocking(CBRS_ALIGN_ANY);
//	m_Selection.EnableDocking(CBRS_ALIGN_ANY);
//	// momo on off button and menu
//	m_Create.EnableDocking(CBRS_ALIGN_ANY);
//	m_Edit.EnableDocking(CBRS_ALIGN_ANY);
//	m_FE.EnableDocking(CBRS_ALIGN_ANY);
//	m_Group.EnableDocking(CBRS_ALIGN_ANY);
//	m_BC.EnableDocking(CBRS_ALIGN_ANY);
//	m_ELTYPE.EnableDocking(CBRS_ALIGN_ANY);
//	m_POST.EnableDocking(CBRS_ALIGN_ANY);
//	m_Projection.EnableDocking(CBRS_ALIGN_ANY);
//	m_Utils.EnableDocking(CBRS_ALIGN_ANY);
//	m_QFilter.EnableDocking(CBRS_ALIGN_ANY);
//	m_DIMS.EnableDocking(CBRS_ALIGN_ANY);
//
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_Start: dock experimental toolbar
//	m_EXP.EnableDocking(CBRS_ALIGN_ANY);
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_End
//
//	// m_Qwanta.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	// AA.EnableDocking(CBRS_BOTTOM);
//	DockPane(&m_wndMenuBar);
//	// momo
//	// momo// DockPane(&m_wndToolBar);
//	DockPane(&m_File);
//	DockPane(&m_MenuCommands);
//	// momo
//	DockPane(&m_Draw);
//	// momo on off button and menu
//	DockPane(&m_ShowHide);
//	DockPane(&m_Selection);
//	// momo on off button and menu
//	DockPane(&m_Create);
//	DockPane(&m_Edit);
//	DockPane(&m_FE);
//	DockPane(&m_Group);
//	DockPane(&m_BC);
//	DockPane(&m_ELTYPE);
//	DockPane(&m_POST);
//	DockPane(&m_Projection);
//	DockPane(&m_Utils);
//	DockPane(&m_QFilter);
//	DockPane(&m_DIMS);
//
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_Start: added experimental toolbar to docking
//	DockPane(&m_EXP);
//	// Esp_Mod_Experimental_Toolbar_4_10_2025_End
//
//	// DockPane(&m_Qwanta);
//	//  enable Visual Studio 2005 style docking window behavior
//	//	CDockingManager::SetDockingMode(DT_SMART);
//	// enable Visual Studio 2005 style docking window auto-hide behavior
//	EnableAutoHidePanes(CBRS_ALIGN_ANY);
//
//	// Enable toolbar and docking window menu replacement
//	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);
//
//	// enable quick (Alt+drag) toolbar customization
//	CMFCToolBar::EnableQuickCustomization();
//
//	// momo
//	// if (CMFCToolBar::GetUserImages() == NULL) {
//	//	// load user-defined toolbar images
//	//	if (m_UserImages.Load(_T(".\\UserImages.bmp"))) {
//	//		m_UserImages.SetImageSize(CSize(16, 16), FALSE);
//	//		CMFCToolBar::SetUserImages(&m_UserImages);
//	//	}
//	// }
//	// momo
//
//	// enable menu personalization (most-recently used commands)
//	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
//	CList<UINT, UINT> lstBasicCommands;
//
//	lstBasicCommands.AddTail(ID_FILE_NEW);
//	lstBasicCommands.AddTail(ID_FILE_OPEN);
//	lstBasicCommands.AddTail(ID_FILE_SAVE);
//	lstBasicCommands.AddTail(ID_FILE_PRINT);
//	lstBasicCommands.AddTail(ID_APP_EXIT);
//	lstBasicCommands.AddTail(ID_EDIT_CUT);
//	lstBasicCommands.AddTail(ID_EDIT_PASTE);
//	lstBasicCommands.AddTail(ID_EDIT_UNDO);
//	lstBasicCommands.AddTail(ID_APP_ABOUT);
//	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
//	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
//
//	// CMFCToolBar::SetBasicCommands(lstBasicCommands);
//
//	//
//	// DockControlBar(&AA);
//
//	// sizeCbar();
//	return 0;
//}
// momo

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableDocking(CBRS_ALIGN_TOP);
	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_MenuBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP, AFX_IDW_MENUBAR)) {
		TRACE0("Failed to create menubar\n");
		return -1;
	}
	m_MenuBar.SetPaneStyle(m_MenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);
	m_MenuBar.EnableDocking(CBRS_ALIGN_TOP);

	if (!p_Input.Create(_T("Input Panel"), this, CRect(0, 0, 100, 150), FALSE, IDD_INPUT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI)) {
		TRACE0("Failed to create input window\n");
		return FALSE;
	}
	Edit1 = &p_Input.Edit1;
	Edit2 = &p_Input.Edit2;
	Edit3 = &p_Input.Edit3;
	// momo make main buttons
	buttonCancel = &p_Input.buttonCancel;
	buttonDone = &p_Input.buttonDone;
	// momo make main buttons
	p_Input.EnableDocking(CBRS_ALIGN_ANY);

	// Hidden:
	toolbars[0] = {&MenuCommandsToolbar, IDR_MENUCOMMANDS_TOOLBAR, false, 0, 0};
	// Top Row 1:
	// &m_MenuBar
	// Top Row 2:
	toolbars[1] = {&ExperimentalToolbar, IDR_EXPERIMENTAL_TOOLBAR, true, 0, 1};
	toolbars[2] = {&DimensionToolbar, IDR_DIMENSION_TOOLBAR, true, 0, 2};
	toolbars[3] = {&UtilitiesToolbar, IDR_UTILITIES_TOOLBAR, true, 0, 2};
	toolbars[4] = {&GroupToolbar, IDR_GROUP_TOOLBAR, true, 0, 2};
	toolbars[5] = {&FileToolbar, IDR_FILE_TOOLBAR, true, 0, 2};
	// Top Row 3:
	toolbars[6] = {&DrawToolbar, IDR_DRAW_TOOLBAR, true, 0, 1};
	toolbars[7] = {&ProjectionToolbar, IDR_PROJECTION_TOOLBAR, true, 0, 2};
	// Top Row 4:
	toolbars[8] = {&SelectFilterQuickToolbar, IDR_SELECTFILTERQUICK_TOOLBAR, true, 0, 1};
	toolbars[9] = {&SelectToolbar, IDR_SELECT_TOOLBAR, true, 0, 2};
	// Top Row 5:
	toolbars[10] = {&ElementVisibilityToolbar, IDR_ELEMENTVISIBILITY_TOOLBAR, true, 0, 1};
	toolbars[11] = {&GeomVisibilityToolbar, IDR_GEOMVISIBILITY_TOOLBAR, true, 0, 2};
	toolbars[12] = {&ShowHideToolbar, IDR_SHOWHIDE_TOOLBAR, true, 0, -2};
	// Center:
	// &p_Input
	// Left:
	toolbars[13] = {&CreateToolbar, IDR_CREATE_TOOLBAR, true, 2, 1};
	toolbars[14] = {&EditToolbar, IDR_EDIT_TOOLBAR, true, 2, 1};
	// Right:
	toolbars[15] = {&PostProcessingToolbar, IDR_POSTPROCESSING_TOOLBAR, true, 1, 1};
	// Bottom:
	toolbars[16] = {&BoundaryConditionsToolbar, IDR_BOUNDARYCONDITIONS_TOOLBAR, true, 4, 1};
	toolbars[17] = {&FiniteElementsToolbar, IDR_FINITEELEMENS_TOOLBAR, true, 4, 2};
	toolbars[18] = {&SetElementToolbar, IDR_SETELEMENT_TOOLBAR, true, 4, 2};

	CString strCustomize;
	BOOL bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	CString strToolBarName;
	UINT nID = 0;

	for (auto& tb: toolbars) {
		UINT dwDockStyleCreate = CBRS_TOP;
		UINT dwDockStyleDocking = CBRS_ALIGN_TOP;
		switch (tb.Align) {
			case 0: // any
				dwDockStyleCreate = CBRS_TOP;
				dwDockStyleDocking = CBRS_ALIGN_ANY;
				break;
			case 1: // right
				dwDockStyleCreate = CBRS_RIGHT;
				dwDockStyleDocking = CBRS_ALIGN_RIGHT;
				break;
			case 2: // left
				dwDockStyleCreate = CBRS_LEFT;
				dwDockStyleDocking = CBRS_ALIGN_LEFT;
				break;
			case 3: // top
				dwDockStyleCreate = CBRS_TOP;
				dwDockStyleDocking = CBRS_ALIGN_TOP;
				break;
			case 4: // bottom
				dwDockStyleCreate = CBRS_BOTTOM;
				dwDockStyleDocking = CBRS_ALIGN_BOTTOM;
				break;
		}
		if (!tb.pToolbar->CreateEx(this, TBSTYLE_FLAT,
		                           WS_CHILD | dwDockStyleCreate | // CBRS_GRIPPER | WS_VISIBLE |
		                               CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,
		                           CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + nID) ||
		    !tb.pToolbar->LoadToolBar(tb.ResourceID)) {
			TRACE0("Failed to create toolbar\n");
			return -1;
		}
		strToolBarName.LoadString(tb.ResourceID);
		tb.pToolbar->SetWindowText(strToolBarName);
		if (tb.isVisible) {
			tb.pToolbar->EnableDocking(dwDockStyleDocking);
			tb.pToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
			tb.pToolbar->ShowPane(TRUE, FALSE, TRUE);
		} else {
			tb.pToolbar->EnableDocking(0);
			tb.pToolbar->EnableCustomizeButton(FALSE, 0, _T(""));
			tb.pToolbar->ModifyStyle(WS_VISIBLE, 0);
			tb.pToolbar->ShowPane(FALSE, FALSE, FALSE);
		}
		nID++;
	}

	if (!s_StatusBar.Create(this)) {
		TRACE0("Failed to create status bar\n");
		return -1;
	}
	s_StatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	EnableDocking(CBRS_ALIGN_ANY);

	DockPane(&m_MenuBar);
	for (size_t i = 1; i < std::size(toolbars); ++i) {
		auto& tbCurrent = toolbars[i];
		auto& tbBefore = toolbars[i - 1];
		if (abs(tbCurrent.DockCommand) == 1) {
			DockPane(tbCurrent.pToolbar);
		} else if (abs(tbCurrent.DockCommand) == 2) {
			DockPaneLeftOf(tbCurrent.pToolbar, tbBefore.pToolbar);
		}
		if (tbCurrent.DockCommand < 0) {
			DockPane(&p_Input);
		}
	}

	for (auto& tb: toolbars) {
		if (tb.isVisible) {
			tb.pToolbar->EnableDocking(CBRS_ALIGN_ANY);
		}
	}

	// enable Visual Studio 2005 style docking window behavior
	//	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBARS_MENU, 0, 0);
	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;
	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBARS_MENU);
	// CMFCToolBar::SetBasicCommands(lstBasicCommands);
	// DockControlBar(&AA);
	// sizeCbar();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
	if (!CFrameWndEx::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const {
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const {
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG

// CMainFrame message handlers

void CMainFrame::OnViewCustomize() {
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp, LPARAM lp) {
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp, lp);
	if (lres == 0) {
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*) lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) {
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext)) {
		return FALSE;
	}

	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i++) {
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL) {
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

void SetFocus() {
	Edit3->SetFocus();
}

// momo
// void outtext2(CString AAA) {
//	CString strText, strNewText;
//	Edit1->GetWindowText(strText);
//	AAA.Remove(13);
//	strNewText.Format("%s\r\n", AAA);
//	strText += strNewText;
//	Edit1->SetWindowText(strText);
//	int NoOff = Edit1->GetLineCount();
//	Edit1->LineScroll(NoOff, 0);
//}

void outtext2(const CString& AAA) {
	if (!Edit1 || !::IsWindow(Edit1->GetSafeHwnd()))
		return;

	CString line = AAA;
	line.Remove(_T('\r'));
	line.Remove(_T('\n'));
	line += _T("\r\n");

	const int len = Edit1->GetWindowTextLength();
	Edit1->SetSel(len, len);
	Edit1->ReplaceSel(line, TRUE);
	Edit1->LineScroll(Edit1->GetLineCount());
}

void outtext2(const char* AAA) {
	if (!AAA)
		return;
#ifdef UNICODE
	int wlen = ::MultiByteToWideChar(CP_UTF8, 0, AAA, -1, nullptr, 0);
	CStringW w;
	LPWSTR buf = w.GetBuffer(wlen);
	::MultiByteToWideChar(CP_UTF8, 0, AAA, -1, buf, wlen);
	w.ReleaseBuffer();
	outtext2(CString(w));
#else
	outtext2(CString(AAA));
#endif
}
// momo

// momo
// void outtext1(CString AAA) {
//	CString strText, strNewText;
//	Edit2->GetWindowText(strText);
//	// Esp_Mod_ExtraLine_Start: Added a new line before the text
//	strNewText.Format("%s\r\n", AAA); // revert to original
//	// strNewText.Format("%s\r\n\r\n", AAA); // with separate line, but its not "intelligent"
//	//  Esp_Mod_ExtraLine_End
//	strText += strNewText;
//	Edit2->SetWindowText(strText);
//	int NoOff = Edit2->GetLineCount();
//	Edit2->LineScroll(NoOff, 0);
// }

void outtext1(const CString& AAA) {
	if (!Edit2 || !::IsWindow(Edit2->GetSafeHwnd()))
		return;

	CString line = AAA;
	line.Remove(_T('\r'));
	line.Remove(_T('\n'));
	line += _T("\r\n");

	const int len = Edit2->GetWindowTextLength();
	Edit2->SetSel(len, len);
	Edit2->ReplaceSel(line, TRUE);
	Edit2->LineScroll(Edit2->GetLineCount());
}

void outtext1(const char* AAA) {
	if (!AAA)
		return;
#ifdef UNICODE
	int wlen = ::MultiByteToWideChar(CP_UTF8, 0, AAA, -1, nullptr, 0);
	CStringW w;
	LPWSTR buf = w.GetBuffer(wlen);
	::MultiByteToWideChar(CP_UTF8, 0, AAA, -1, buf, wlen);
	w.ReleaseBuffer();
	outtext1(CString(w));
#else
	outtext1(CString(AAA));
#endif
}
// momo

// MoMo_Material_SaveBugV1_05_20_2025_Start
void outtextSprintf(const CString& formatString, int intValue, double floatValue, bool IsInt, int nText) {
	CString StOut;
	if (IsInt)
		StOut.Format(formatString, intValue);
	else
		StOut.Format(formatString, floatValue);
	outtextMultiLine(StOut, nText);
}
// MoMo_Material_SaveBugV1_05_20_2025_End

// MoMo_Material_SaveBugV1_05_20_2025_Start
void outtextMultiLine(const CString& AAA, int nText) {
	CString s = AAA;

	s.Replace(_T("\r\n"), _T("\n"));
	s.Replace(_T("\r"), _T("\n"));

	int start = 0;
	while (true) {
		int pos = s.Find(_T('\n'), start);
		CString line = (pos == -1) ? s.Mid(start) : s.Mid(start, pos - start);

		if (nText == 1)
			outtext1(line);
		else
			outtext2(line);

		if (pos == -1)
			break;
		start = pos + 1;
	}
}

void outtextMultiLine(const char* AAA, int nText) {
	if (!AAA)
		return;
#ifdef UNICODE
	int wlen = ::MultiByteToWideChar(CP_UTF8, 0, AAA, -1, nullptr, 0);
	CStringW w;
	LPWSTR buf = w.GetBuffer(wlen);
	::MultiByteToWideChar(CP_UTF8, 0, AAA, -1, buf, wlen);
	w.ReleaseBuffer();
	outtextMultiLine(CString(w), nText);
#else
	outtextMultiLine(CString(AAA), nText);
#endif
}
// MoMo_Material_SaveBugV1_05_20_2025_End

void outtextMSG(CString AAA) {
	CString a;
	CString b;
	Edit3->GetWindowText(b);
	int iRetPos = b.Find(13);
	while (iRetPos != -1) {
		a = b.Left(iRetPos);
		b = b.Right(b.GetLength() - iRetPos - 2);
		// a.MakeUpper();
		if (a.Find(_T("//")) == -1) {
			outtext2(a);
			SendMsg(a);
		}
		a = "";
		Edit3->SetWindowText(a);
		iRetPos = b.Find(13);
	}
	b = "";
	a = "";
}

// momo
// void outtextMSG2(CString AAA) {
//	CString strNewText;
//	strNewText.Format("%s\r", AAA);
//	outtext2(strNewText);
//	SendMsg(AAA);
//	// momo change command box color
//	CheckCommandEditColor(false);
//	// momo change command box color
// }
void outtextMSG2(const CString& AAA) {
	CString line = AAA;
	line.Remove(_T('\r'));
	line.Remove(_T('\n'));

	outtext2(line);
	SendMsg(line);
	// momo change command box color
	CheckCommandEditColor(false);
	// momo change command box color
}

void outtextMSG2(const char* AAA) {
	if (!AAA)
		return;
#ifdef UNICODE
	int wlen = ::MultiByteToWideChar(CP_UTF8, 0, AAA, -1, nullptr, 0);
	CStringW w;
	LPWSTR buf = w.GetBuffer(wlen);
	::MultiByteToWideChar(CP_UTF8, 0, AAA, -1, buf, wlen);
	w.ReleaseBuffer();
	outtextMSG2(CString(w));
#else
	outtextMSG2(CString(AAA));
#endif
}

CFont* CreatePointFont(int pointSize, LPCTSTR fontName, int weight, BOOL italic) {
	HDC hdc = ::GetDC(NULL);
	int logPixelsY = GetDeviceCaps(hdc, LOGPIXELSY);
	::ReleaseDC(NULL, hdc);
	int height = -MulDiv(pointSize, logPixelsY, 72);
	CFont* pFont = new CFont;
	pFont->CreateFont(
	    height, 0, 0, 0, weight, italic, FALSE, FALSE,
	    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	    DEFAULT_PITCH | FF_SWISS,
	    fontName);

	return pFont;
}
// momo

// momo change command box color
void CheckCommandEditColor(bool bForceToCheck) {
	if (CommIsActive.NewState != CommIsActive.CurrentState || bForceToCheck) {
		CommIsActive.CurrentState = CommIsActive.NewState;
		CMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
		if (pMainFrame) {
			if (CommIsActive.CurrentState) {
				pMainFrame->p_Input.Edit3.SetBgColor(RGB(191, 242, 206));
				SetFocus();
				if (CommIsActive.ChangeEdit1) {
					pMainFrame->p_Input.Edit1.SetBgColor(RGB(191, 242, 206));
				} else {
					pMainFrame->p_Input.Edit1.SetBgColor(RGB(255, 255, 255));
				}
			} else {
				pMainFrame->p_Input.Edit3.SetBgColor(RGB(255, 255, 255));
				pMainFrame->p_Input.Edit1.SetBgColor(RGB(255, 255, 255));
			}
		}
	}
}
// momo change command box color
// momo on off button and menu
void CheckPushedButtons(const char* sMode) {
	if (strcmp(sMode, "AllGeoms") == 0) {
		DspFlagsMain.DSP_POINTS = ButtonPush.AllGeomOn;
		DspFlagsMain.DSP_CONTROLPOINTS = ButtonPush.AllGeomOn;
		DspFlagsMain.DSP_CURVES = ButtonPush.AllGeomOn;
		DspFlagsMain.DSP_SURFACES = ButtonPush.AllGeomOn;
		DspFlagsMain.DSP_COORDINATE_SYSTEMS = ButtonPush.AllGeomOn;
	} else if (strcmp(sMode, "AllFinites") == 0) {
		DspFlagsMain.DSP_NODES = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_BOUNDARYCONDITIONS = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_ALL = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_0D = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_1D = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_2D = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_3D = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_MASS = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_ROD = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_BEAM = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_RIGID = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_BUSH = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_TRI = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_QUAD = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_TET = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_WEDGE = ButtonPush.AllFiniteOn;
		DspFlagsMain.DSP_ELEMENTS_BRICK = ButtonPush.AllFiniteOn;
	} else if (strcmp(sMode, "AllElements") == 0) {
		DspFlagsMain.DSP_ELEMENTS_ALL = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_0D = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_1D = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_2D = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_3D = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_MASS = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_ROD = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_BEAM = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_RIGID = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_BUSH = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_TRI = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_QUAD = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_TET = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_WEDGE = DspFlagsMain.DSP_ELEMENTS_ALL;
		DspFlagsMain.DSP_ELEMENTS_BRICK = DspFlagsMain.DSP_ELEMENTS_ALL;
	} else if (strcmp(sMode, "SetOneElement") == 0) {
		if (DspFlagsMain.DSP_ELEMENTS_MASS) {
			DspFlagsMain.DSP_ELEMENTS_0D = true;
		} else {
			DspFlagsMain.DSP_ELEMENTS_0D = false;
		}
		if (!DspFlagsMain.DSP_ELEMENTS_1D && DspFlagsMain.DSP_ELEMENTS_ROD && DspFlagsMain.DSP_ELEMENTS_BEAM //
		    && DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING && DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING && DspFlagsMain.DSP_ELEMENTS_RIGID //
		    && DspFlagsMain.DSP_ELEMENTS_BUSH) {
			DspFlagsMain.DSP_ELEMENTS_1D = true;
		} else if (DspFlagsMain.DSP_ELEMENTS_1D && !DspFlagsMain.DSP_ELEMENTS_ROD && !DspFlagsMain.DSP_ELEMENTS_BEAM //
		           && !DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING && !DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING && !DspFlagsMain.DSP_ELEMENTS_RIGID //
		           && !DspFlagsMain.DSP_ELEMENTS_BUSH) {
			DspFlagsMain.DSP_ELEMENTS_1D = false;
		}
		if (!DspFlagsMain.DSP_ELEMENTS_2D && DspFlagsMain.DSP_ELEMENTS_TRI && DspFlagsMain.DSP_ELEMENTS_QUAD) {
			DspFlagsMain.DSP_ELEMENTS_2D = true;
		} else if (DspFlagsMain.DSP_ELEMENTS_2D && !DspFlagsMain.DSP_ELEMENTS_TRI && !DspFlagsMain.DSP_ELEMENTS_QUAD) {
			DspFlagsMain.DSP_ELEMENTS_2D = false;
		}
		if (!DspFlagsMain.DSP_ELEMENTS_3D && DspFlagsMain.DSP_ELEMENTS_TET && DspFlagsMain.DSP_ELEMENTS_WEDGE && DspFlagsMain.DSP_ELEMENTS_BRICK) {
			DspFlagsMain.DSP_ELEMENTS_3D = true;
		} else if (DspFlagsMain.DSP_ELEMENTS_3D && !DspFlagsMain.DSP_ELEMENTS_TET && !DspFlagsMain.DSP_ELEMENTS_WEDGE && !DspFlagsMain.DSP_ELEMENTS_BRICK) {
			DspFlagsMain.DSP_ELEMENTS_3D = false;
		}
		if (!DspFlagsMain.DSP_ELEMENTS_ALL && DspFlagsMain.DSP_ELEMENTS_MASS && DspFlagsMain.DSP_ELEMENTS_ROD //
		    && DspFlagsMain.DSP_ELEMENTS_BEAM && DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING && DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING //
		    && DspFlagsMain.DSP_ELEMENTS_RIGID && DspFlagsMain.DSP_ELEMENTS_BUSH && DspFlagsMain.DSP_ELEMENTS_TRI //
		    && DspFlagsMain.DSP_ELEMENTS_QUAD && DspFlagsMain.DSP_ELEMENTS_TET && DspFlagsMain.DSP_ELEMENTS_WEDGE //
		    && DspFlagsMain.DSP_ELEMENTS_BRICK) {
			DspFlagsMain.DSP_ELEMENTS_ALL = true;
		} else if (DspFlagsMain.DSP_ELEMENTS_ALL && !DspFlagsMain.DSP_ELEMENTS_MASS && !DspFlagsMain.DSP_ELEMENTS_ROD //
		           && !DspFlagsMain.DSP_ELEMENTS_BEAM && !DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING && !DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING //
		           && !DspFlagsMain.DSP_ELEMENTS_RIGID && !DspFlagsMain.DSP_ELEMENTS_BUSH && !DspFlagsMain.DSP_ELEMENTS_TRI //
		           && !DspFlagsMain.DSP_ELEMENTS_QUAD && !DspFlagsMain.DSP_ELEMENTS_TET && !DspFlagsMain.DSP_ELEMENTS_WEDGE //
		           && !DspFlagsMain.DSP_ELEMENTS_BRICK) {
			DspFlagsMain.DSP_ELEMENTS_ALL = false;
		}
	} else if (strcmp(sMode, "SetGroupElements0D") == 0) {
		DspFlagsMain.DSP_ELEMENTS_MASS = DspFlagsMain.DSP_ELEMENTS_0D;
	} else if (strcmp(sMode, "SetGroupElements1D") == 0) {
		DspFlagsMain.DSP_ELEMENTS_ROD = DspFlagsMain.DSP_ELEMENTS_1D;
		DspFlagsMain.DSP_ELEMENTS_BEAM = DspFlagsMain.DSP_ELEMENTS_1D;
		DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING = DspFlagsMain.DSP_ELEMENTS_1D;
		DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING = DspFlagsMain.DSP_ELEMENTS_1D;
		DspFlagsMain.DSP_ELEMENTS_RIGID = DspFlagsMain.DSP_ELEMENTS_1D;
		DspFlagsMain.DSP_ELEMENTS_BUSH = DspFlagsMain.DSP_ELEMENTS_1D;
	} else if (strcmp(sMode, "SetGroupElements2D") == 0) {
		DspFlagsMain.DSP_ELEMENTS_TRI = DspFlagsMain.DSP_ELEMENTS_2D;
		DspFlagsMain.DSP_ELEMENTS_QUAD = DspFlagsMain.DSP_ELEMENTS_2D;
	} else if (strcmp(sMode, "SetGroupElements3D") == 0) {
		DspFlagsMain.DSP_ELEMENTS_TET = DspFlagsMain.DSP_ELEMENTS_3D;
		DspFlagsMain.DSP_ELEMENTS_WEDGE = DspFlagsMain.DSP_ELEMENTS_3D;
		DspFlagsMain.DSP_ELEMENTS_BRICK = DspFlagsMain.DSP_ELEMENTS_3D;
	} else if (strcmp(sMode, "SetOneGeom") == 0) {
		if (!ButtonPush.AllGeomOn && DspFlagsMain.DSP_POINTS && DspFlagsMain.DSP_CONTROLPOINTS && DspFlagsMain.DSP_CURVES //
		    && DspFlagsMain.DSP_SURFACES && DspFlagsMain.DSP_COORDINATE_SYSTEMS) {
			ButtonPush.AllGeomOn = true;
		} else if (ButtonPush.AllGeomOn && !DspFlagsMain.DSP_POINTS && !DspFlagsMain.DSP_CONTROLPOINTS && !DspFlagsMain.DSP_CURVES //
		           && !DspFlagsMain.DSP_SURFACES && !DspFlagsMain.DSP_COORDINATE_SYSTEMS) {
			ButtonPush.AllGeomOn = false;
		}
	}
	if (!ButtonPush.AllFiniteOn && DspFlagsMain.DSP_NODES && DspFlagsMain.DSP_BOUNDARYCONDITIONS //
	    && DspFlagsMain.DSP_ELEMENTS_MASS && DspFlagsMain.DSP_ELEMENTS_ROD && DspFlagsMain.DSP_ELEMENTS_BEAM //
	    && DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING && DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING && DspFlagsMain.DSP_ELEMENTS_RIGID //
	    && DspFlagsMain.DSP_ELEMENTS_BUSH && DspFlagsMain.DSP_ELEMENTS_TRI && DspFlagsMain.DSP_ELEMENTS_QUAD //
	    && DspFlagsMain.DSP_ELEMENTS_TET && DspFlagsMain.DSP_ELEMENTS_WEDGE && DspFlagsMain.DSP_ELEMENTS_BRICK) {
		ButtonPush.AllFiniteOn = true;
	} else if (ButtonPush.AllFiniteOn && !DspFlagsMain.DSP_NODES && !DspFlagsMain.DSP_BOUNDARYCONDITIONS //
	           && !DspFlagsMain.DSP_ELEMENTS_MASS && !DspFlagsMain.DSP_ELEMENTS_ROD && !DspFlagsMain.DSP_ELEMENTS_BEAM //
	           && !DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING && !DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING && !DspFlagsMain.DSP_ELEMENTS_RIGID //
	           && !DspFlagsMain.DSP_ELEMENTS_BUSH && !DspFlagsMain.DSP_ELEMENTS_TRI && !DspFlagsMain.DSP_ELEMENTS_QUAD //
	           && !DspFlagsMain.DSP_ELEMENTS_TET && !DspFlagsMain.DSP_ELEMENTS_WEDGE && !DspFlagsMain.DSP_ELEMENTS_BRICK) {
		ButtonPush.AllFiniteOn = false;
	}
}
// momo on off button and menu

void CMainFrame::OnSize(UINT nType, int cx, int cy) {
	CFrameWndEx::OnSize(nType, cx, cy);
	// momo
	CAppSettings settings;
	if (nType == SIZE_MAXIMIZED) {
		settings.WriteWindowState(1);
	} else if (nType == SIZE_RESTORED) {
		settings.WriteWindowState(0);
	}
	// momo
	//  sizeCbar();
	//   TODO: Add your message handler code here
}

// void CMainFrame::OnMeshFreetrimesh()
//{
//	// TODO: Add your command handler code here
// }

// void CMainFrame::OnToolsElementmasssummation()
//{
//   // TODO: Add your command handler code here
// }

// momo make main buttons
void OnCancelClicked() {
	CString CurrentText;
	Edit3->GetWindowText(CurrentText);
	if (CurrentText != _T("")) {
		Edit3->SetWindowText(_T(""));
	}
	if (!SeedVals.IsSeedMode) {
		outtextMSG2("C");
	} else {
		outtextMSG2("Cancel");
	}
	SetFocus();
}

void OnDoneClicked() {
	CString CurrentText;
	Edit3->GetWindowText(CurrentText);
	if (CurrentText == _T("")) {
		if (!SeedVals.IsSeedMode) {
			outtextMSG2("D");
		} else {
			outtextMSG2("Done");
		}
	} else {
		CString NewText;
		NewText = CurrentText + _T("\r\n");
		Edit3->SetWindowText(_T(""));
		outtextMSG2(NewText);
	}
	SetFocus();
}
// momo make main buttons

//// momo ModernOpenGL_Start
////CString ReadText() {
////	CString sOut;
////	EditViewScales->GetWindowText(sOut);
////	return sOut;
////}
////
////void SetText(CString sIn) {
////	EditViewScales->SetWindowText(sIn);
////}
//// momo ModernOpenGL_End

// momo
void CMainFrame::OnViewToolbarBC() {
	BOOL bShow = !BoundaryConditionsToolbar.IsWindowVisible();
	BoundaryConditionsToolbar.ShowPane(bShow, FALSE, TRUE);
	RecalcLayout();
}

void CMainFrame::OnUpdateViewToolbarBC(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(BoundaryConditionsToolbar.IsWindowVisible());
}

void CMainFrame::LockToolbarsDocking(bool lockAll) {
	if (lockAll) {
		outtext1("Lock toolbars.");
	} else {
		outtext1("Unlock toolbars.");
	}
	for (size_t i = 1; i < std::size(toolbars); ++i) {
		auto& tb = toolbars[i];
		tb.pToolbar->ShowPane(TRUE, FALSE, FALSE);
		LONG style = tb.pToolbar->GetPaneStyle();
		if (lockAll) {
			// Lock toolbars
			tb.pToolbar->SetBorders(0, 0, 0, 0);
			tb.pToolbar->EnableDocking(0);
			style &= ~(CBRS_GRIPPER | CBRS_FLOATING | CBRS_SIZE_DYNAMIC |
			           CBRS_BORDER_3D | CBRS_BORDER_LEFT | CBRS_BORDER_TOP | CBRS_BORDER_RIGHT | CBRS_BORDER_BOTTOM);
			tb.pToolbar->SetPaneStyle(style);
		} else {
			// Unlock toolbars
			tb.pToolbar->SetBorders(1, 1, 1, 1);
			tb.pToolbar->EnableDocking(CBRS_ALIGN_ANY);
			style |= (CBRS_GRIPPER | CBRS_FLOATING | CBRS_SIZE_DYNAMIC |
			          CBRS_BORDER_3D | CBRS_BORDER_LEFT | CBRS_BORDER_TOP | CBRS_BORDER_RIGHT | CBRS_BORDER_BOTTOM);
			tb.pToolbar->SetPaneStyle(style);
		}
	}
	RecalcLayout();
}
// momo
