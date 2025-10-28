
// M3da.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "M3da.h"
#include "MainFrm.h"

#include "M3daDoc.h"
#include "M3daView.h"

// Esp_Mod_Config_File_Mod_Start
#include "GLOBAL_VARS.h"
// Esp_Mod_Config_File_Mod_End

// momo
#include "AppSettings.h"
// momo

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MoMo_Start
SeedValues SeedVals;
CString LastRequest = _T("");
BOOL CurrentBufferResult = false;
BOOL leftIsDraggingForSelect = false;
BOOL leftIsDraggingForZoomBox = false;
BOOL rightIsDraggingForZoomBox = false;
BOOL rightIsDraggingForZoomBoxCanceled = false;
BOOL DeSelectAll = false;
BOOL StartLoad = true;
int m_x1 = 0;
int m_y1 = 0;
int m_x2 = 0;
int m_y2 = 0;
bool DeselectCadrMode = true;
int SelectMode = 3;
int MainDrawState = 0;
bool AxisOrigin = false;
bool AxisCorner = false;
int m_iFuncKey = 0;
bool NeedLeftClick = false;
int RightDragAction = 3;
int MiddleDragAction = 1;
bool MouseLeftDown = false;
bool MouseRightDown = false;
bool MouseMiddleDown = false;
// MoMo_End
// momo
int SelRowsCurrent[MAX_RESSETS][2];
int SelRowsNew[MAX_RESSETS][2];
// for (int i = 0; i < MAX_RESSETS; i++) {
//	for (int j = 0; j < 2; j++) {
//		SelRowsCurrent[i][j] = 0;
//		SelRowsNew[i][j] = 0;
//	}
// }
// momo
// momo change command box color
CommandIsActive CommIsActive;
// momo change command box color
// momo on off button and menu
ButtonPushed ButtonPush;
DisplayFlags DspFlagsMain;
// momo on off button and menu
// momo gdi to og2
ClickPoint mClickPoint;
// momo gdi to og2
// momo save by old versions
int FileFormatIndex = 1;
bool MakingNewFile = false;
// momo save by old versions
// momo close for LNC
CPoint m_PointOld; // old move point
CPoint m_PointNew; // new move point
// momo close for LNC
// momo random color change bug
bool bUseDoubleBuffer = false;
// momo random color change bug
// momo
extern double Pi = 3.1415926535;
// momo

// CM3daApp

BEGIN_MESSAGE_MAP(CM3daApp, CWinAppEx)
ON_COMMAND(ID_APP_ABOUT, &CM3daApp::OnAppAbout)
// momo add type id form
ON_COMMAND(ID_HELP_TYPEID, &CM3daApp::OnShowInfoDialog)
// momo add type id form
// momo
ON_COMMAND(ID_HELP_SHORTCUT_KEYS, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_PROPERTY, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_ELEMENTMODIFIY, &CM3daApp::OnShowInfoDialog)
// momo
// Standard file based document commands
// momo
// momo// ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
// momo// ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
// momo
// Standard print setup command
ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
ON_COMMAND(ID_FILE_RUNSCRIPTFILE, &CM3daApp::OnFileRunscriptfile)
END_MESSAGE_MAP()

// CM3daApp construction

CM3daApp::CM3daApp() {
	m_bHiColorIcons = TRUE;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// momo
void CM3daApp::OnFileNewMain() {
	MakingNewFile = true;
	OnFileNew();
}

void CM3daApp::OnFileOpenMain() {
	OnFileOpen();
}
// momo
// momo save by old versions
void CM3daApp::OnFileSaveMain() {
	bool SavedOk;
	CString dlgPath, pDocPath;
	CDocument* pDoc = ((CFrameWnd*) AfxGetMainWnd())->GetActiveDocument();
	if (pDoc) {
		pDocPath = pDoc->GetPathName();
		CString strFilter =
		    _T("M3da Files - Version 7.90 (*.m3d)|*.m3d|")
		    _T("M3da Files - Version 7.80 (*.m3d)|*.m3d||");
		if (pDocPath.IsEmpty()) {
			pDocPath = _T("Untitled.m3d");
			CFileDialog dlg(FALSE, _T(".m3d"), pDocPath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, AfxGetMainWnd());
			dlg.m_ofn.nFilterIndex = FileFormatIndex;
			if (dlg.DoModal() != IDOK) {
				SavedOk = false;
			} else {
				SavedOk = true;
				dlgPath = dlg.GetPathName();
				FileFormatIndex = dlg.m_ofn.nFilterIndex;
			}
		} else {
			SavedOk = true;
			dlgPath = pDocPath;
		}
	} else {
		SavedOk = false;
	}

	if (SavedOk) {
		pDoc->DoSave(dlgPath);
		int iVERInner = VERSIONS[FileFormatIndex - 1];
		outtextSprintf(_T("File Saved successfully. (Version = %.2f)"), 0, abs(iVERInner / 10.0), false, 1);
	} else {
		outtext1("File Save failed or was Canceled.");
	}
}

void CM3daApp::OnFileSaveAsMain() {
	bool SavedOk;
	CString dlgPath, pDocPath;
	CDocument* pDoc = ((CFrameWnd*) AfxGetMainWnd())->GetActiveDocument();
	if (pDoc) {
		pDocPath = pDoc->GetPathName();
		CString strFilter =
		    _T("M3da Files - Version 7.90 (*.m3d)|*.m3d|")
		    _T("M3da Files - Version 7.80 (*.m3d)|*.m3d||");
		if (pDocPath.IsEmpty()) {
			pDocPath = _T("Untitled.m3d");
			CFileDialog dlg(FALSE, _T(".m3d"), pDocPath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, AfxGetMainWnd());
			dlg.m_ofn.nFilterIndex = FileFormatIndex;
			if (dlg.DoModal() != IDOK) {
				SavedOk = false;
			} else {
				SavedOk = true;
				dlgPath = dlg.GetPathName();
				FileFormatIndex = dlg.m_ofn.nFilterIndex;
			}
		} else {
			CFileDialog dlg(FALSE, _T(".m3d"), pDocPath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, AfxGetMainWnd());
			dlg.m_ofn.nFilterIndex = FileFormatIndex;
			if (dlg.DoModal() != IDOK) {
				SavedOk = false;
			} else {
				SavedOk = true;
				dlgPath = dlg.GetPathName();
				FileFormatIndex = dlg.m_ofn.nFilterIndex;
			}
			//	SavedOk = true;
			//	dlgPath = pDocPath;
		}
	} else {
		SavedOk = false;
	}

	if (SavedOk) {
		pDoc->DoSave(dlgPath);
		int iVERInner = VERSIONS[FileFormatIndex - 1];
		outtextSprintf(_T("File Saved successfully. (Version = %.2f)"), 0, abs(iVERInner / 10.0), false, 1);
	} else {
		outtext1("File Save failed or was Canceled.");
	}
}
// momo save by old versions

// The one and only CM3daApp object

CM3daApp theApp;
// This identifier was generated to be statistically unique for your app
// You may change it if you prefer to choose a specific identifier

// {A7226713-7CA7-4243-8B24-4C7AA36D1FA3}
static const CLSID clsid =
    {0xA7226713, 0x7CA7, 0x4243, {0x8B, 0x24, 0x4C, 0x7A, 0xA3, 0x6D, 0x1F, 0xA3}};

const GUID CDECL BASED_CODE _tlid =
    {0x28298EED, 0x2921, 0x46EF, {0x91, 0x77, 0x73, 0x8, 0x5F, 0x11, 0x18, 0x28}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

// Esp_Mod_Config_File_Mod_Start

// Global variables for configuration settings
void CM3daApp::LoadConfiguration() {
	CStdioFile file;
	if (file.Open(_T("config.txt"), CFile::modeRead | CFile::shareDenyWrite)) {
		CString strLine;
		while (file.ReadString(strLine)) {
			strLine.Trim(); // Remove leading/trailing whitespace

			// Skip empty lines or comment lines that start with '*'
			if (strLine.IsEmpty() || strLine.Left(1) == _T("*"))
				continue;

			// Expecting "key, value" format
			int commaPos = strLine.Find(_T(","));
			if (commaPos != -1) {
				CString key = strLine.Left(commaPos);
				CString value = strLine.Mid(commaPos + 1);
				key.Trim();
				value.Trim();

				// Update settings based on key
				if (key.CompareNoCase(_T("background_color")) == 0) {
					gBACKGRD_COL = _ttoi(value);
				} else if (key.CompareNoCase(_T("zoom_scale_factor")) == 0) {
					gZOOM_SCL = _ttof(value);
				} else if (key.CompareNoCase(_T("point_size")) == 0) {
					gPT_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("node_size")) == 0) {
					gND_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("lump_mass_size")) == 0) {
					gLM_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("element_edge_size")) == 0) {
					gEL_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("free_edge_size")) == 0) {
					gED_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("free_face_size")) == 0) {
					gFC_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("workplane_line_weight")) == 0) {
					gWP_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("beam_section_size")) == 0) {
					gBM_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("text_size")) == 0) {
					gTXT_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("drawing_scale_for_dims")) == 0) {
					gDIM_SCALE = _ttof(value);
				} else if (key.CompareNoCase(_T("fillet_size")) == 0) {
					gDIM_FILSZ = _ttof(value);
				} else if (key.CompareNoCase(_T("line_offset")) == 0) {
					gDIM_OFFSZ = _ttof(value);
				} else if (key.CompareNoCase(_T("text_height")) == 0) {
					gTXT_HEIGHT = _ttof(value);
				} else if (key.CompareNoCase(_T("circle_radius_for_circr")) == 0) {
					gDIM_RADSZ = _ttof(value);
				} else if (key.CompareNoCase(_T("spline_order")) == 0) {
					gDIM_CVORD = _ttoi(value);
				} else if (key.CompareNoCase(_T("dimesion_precision")) == 0) {
					gDIM_PREC = _ttoi(value);
				} else if (key.CompareNoCase(_T("dimension_size")) == 0) {
					gDIM_SIZE = _ttof(value);
				} else if (key.CompareNoCase(_T("trim_curve_on_surface_resolution")) == 0) {
					gCUR_RES = _ttoi(value);
				} else if (key.CompareNoCase(_T("shell_drilling_k_value")) == 0) {
					gDRILL_KS = _ttof(value);
				} else if (key.CompareNoCase(_T("stiffness_multiplier_for_m3d_dummy_rigid")) == 0) {
					gRIGID_MULTIPLIER = _ttof(value);
				} else if (key.CompareNoCase(_T("k_for_restraints")) == 0) {
					gVSTIFF_KS = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_E")) == 0) {
					gDEF_E = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_v")) == 0) {
					gDEF_V = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_density")) == 0) {
					gDEF_DEN = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_thermal_conductivity")) == 0) {
					gDEF_COND = _ttof(value);
				} else if (key.CompareNoCase(_T("default_siff_beam_diameter")) == 0) {
					gSTIFF_BDIA = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_cte")) == 0) {
					gDEF_CTE = _ttof(value);
				} else if (key.CompareNoCase(_T("default_thermal_link_coeff")) == 0) {
					gDEF_THERM_LNK = _ttof(value);
				} else if (key.CompareNoCase(_T("default_iterative_solver_toleranace")) == 0) {
					gDEF_SOL_TOL = _ttof(value);
				}
			}
		}
		file.Close();
	} else {
		AfxMessageBox(_T("Failed to open config.txt."));
	}
}
// Esp_Mod_Config_File_Mod_End

// CM3daApp initialization

// MoMo: program start from here (int main() or main.cpp)

BOOL CM3daApp::InitInstance() {
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit()) {
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	// MoMo_Start
	// MoMo// SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	SetRegistryKey(_T("M3D-DevM-Reg-29"));
	// MoMo_End
	// momo
	SelRowsCurrent[0][0] = -1;
	SeedVals.IsSeedMode = false;
	SeedVals.SelectSurface = true;
	SeedVals.SelectSurfaceCurves = false;
	SeedVals.SelectLock = false;
	SeedVals.InputedMeshElementSize = 1.0;
	SeedVals.InputedSeedNumbers = 0;

	ButtonPush.WireFrame = false;
	DspFlagsMain.DSP_WIREFRAME = false;
	ButtonPush.DrawModeCurrent = 2;
	ButtonPush.DrawModeOut = 3;
	ButtonPush.ShadedWithEdges = true;
	DspFlagsMain.DSP_SHADED_WITH_EDGES = true;
	ButtonPush.ShadedWithoutEdges = false;
	ButtonPush.AllFiniteOn = true;
	DspFlagsMain.DSP_NODES = true;
	DspFlagsMain.DSP_ELEMENTS_ALL = true;
	DspFlagsMain.DSP_BOUNDARYCONDITIONS = true;
	ButtonPush.AllGeomOn = true;
	DspFlagsMain.DSP_POINTS = true;
	DspFlagsMain.DSP_CONTROLPOINTS = false;
	DspFlagsMain.DSP_CURVES = true;
	DspFlagsMain.DSP_SURFACES = true;
	DspFlagsMain.DSP_COORDINATE_SYSTEMS = true;
	ButtonPush.OnlySelectedOn = false;
	DspFlagsMain.DSP_WORKPLANE = true;
	DspFlagsMain.DSP_SHELLTHICKNESS = false;
	DspFlagsMain.DSP_ELEMENTCOORDSYS = false;
	DspFlagsMain.DSP_SURFACEDIRECTIONMARKERS = false;
	DspFlagsMain.DSP_GRADIENT_BACKGROUND = false;
	DspFlagsMain.DSP_ELEMENTS_0D = true;
	DspFlagsMain.DSP_ELEMENTS_MASS = true;
	DspFlagsMain.DSP_ELEMENTS_1D = true;
	DspFlagsMain.DSP_ELEMENTS_ROD = true;
	DspFlagsMain.DSP_ELEMENTS_BEAM = true;
	DspFlagsMain.DSP_ELEMENTS_TRANSLATIONALSPRING = true;
	DspFlagsMain.DSP_ELEMENTS_ROTATIONALSPRING = true;
	DspFlagsMain.DSP_ELEMENTS_RIGID = true;
	DspFlagsMain.DSP_ELEMENTS_BUSH = true;
	DspFlagsMain.DSP_ELEMENTS_2D = true;
	DspFlagsMain.DSP_ELEMENTS_TRI = true;
	DspFlagsMain.DSP_ELEMENTS_QUAD = true;
	DspFlagsMain.DSP_ELEMENTS_3D = true;
	DspFlagsMain.DSP_ELEMENTS_TET = true;
	DspFlagsMain.DSP_ELEMENTS_WEDGE = true;
	DspFlagsMain.DSP_ELEMENTS_BRICK = true;

	ButtonPush.QfilterNodesOn = false;
	ButtonPush.QfilterElementsOn = false;
	ButtonPush.QfilterPointsOn = false;
	ButtonPush.QfilterCurvesOn = false;
	ButtonPush.QfilterSurfacesOn = false;
	ButtonPush.FullBody = true;
	ButtonPush.PartOfBody = false;
	ButtonPush.CenterOfBody = true;
	DspFlagsMain.DSP_NODESSQUAREASTERISK = true;
	DspFlagsMain.DSP_ELEMENTOFFSETS = true;
	DspFlagsMain.DSP_SURFACECURVES = true;
	DspFlagsMain.DSP_BLACKWHITE = true;
	DspFlagsMain.DSP_ASSEMBLIES = true;
	DspFlagsMain.DSP_CONTOURRAWRESULTS = true;
	DspFlagsMain.DSP_RESULTSLABLES = true;
	DspFlagsMain.DSP_DEFORMEDRESULTS = true;
	DspFlagsMain.DSP_MATERIALDIRECTION = true;
	DspFlagsMain.DSP_ANIMATERESULTS = false;
	DspFlagsMain.DSP_ANIMATEPOSITIVENEGATIVE = true;
	DspFlagsMain.DSP_VECTORS = true;
	// momo
	// momo gdi to og2
	mClickPoint.IsClicked = false;
	mClickPoint.x = 0;
	mClickPoint.y = 0;
	// momo gdi to og2
	// momo change command box color
	CommIsActive.CurrentState = false;
	CommIsActive.NewState = false;
	CommIsActive.ChangeEdit1 = false;
	// momo change command box color
	// momo
	CAppSettings settings;
	DeselectCadrMode = settings.ReadDeselectCadrMode();
	SelectMode = settings.ReadSelectMode();
	settings.ReadAxisMode(AxisOrigin, AxisCorner);
	NeedLeftClick = settings.ReadNeedLeftClick();
	RightDragAction = settings.ReadRightDragAction();
	MiddleDragAction = settings.ReadMiddleDragAction();
	// momo
	// momo random color change bug
	bUseDoubleBuffer = settings.ReadDoubleBuffer();
	// momo random color change bug

	LoadStdProfileSettings(4); // Load standard INI file options (including MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
	                                             RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	////Esp_Mod_Config_File_Mod_Start//
	// Check if "config.txt" exists in the working directory
	CFileFind finder;
	if (finder.FindFile(_T("config.txt"))) {
		LoadConfiguration();
	} else {
		// TODO: If file no found, for example, set default values and make config.txt based on it
	}
	////Esp_Mod_Config_File_Mod_End//

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
	    IDR_MAINFRAME,
	    RUNTIME_CLASS(CM3daDoc),
	    RUNTIME_CLASS(CMainFrame), // main SDI frame window
	    RUNTIME_CLASS(CM3daView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// Connect the COleTemplateServer to the document template
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
	// Note: SDI applications register server objects only if /Embedding
	//   or /Automation is present on the command line

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated) {
		// Register all OLE server factories as running.  This enables the
		//  OLE libraries to create objects from other applications
		COleTemplateServer::RegisterAll();

		// Don't show the main window
		// return TRUE;
	}
	// App was launched with /Unregserver or /Unregister switch.  Unregister
	// typelibrary.  Other unregistration occurs in ProcessShellCommand().
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister) {
		UnregisterShellFileTypes();
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
	}
	// App was launched standalone or with other switches (e.g. /Register
	// or /Regserver).  Update registry entries, including typelibrary.
	else {
		COleTemplateServer::RegisterAll();
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
	}
	// Roy
	// COleTemplateServer::RegisterAll();
	// m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
	// COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	// momo
	bool windowMaximized = settings.ReadWindowState();
	if (windowMaximized) {
		m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	} else {
		m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	}
	// momo
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

// CAboutDlg dialog used for App About

int CM3daApp::ExitInstance() {
	// If you initialized COM, uninitialize it
	CoUninitialize();

	// Ensure base class cleanup is performed
	return CWinAppEx::ExitInstance();
}

class CAboutDlg: public CDialog {
	public:
		CAboutDlg();

		// Dialog Data
		enum { IDD = IDD_ABOUTBOX };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
		// momo add link
		virtual BOOL OnInitDialog();
		// CMFCLinkCtrl WebsiteLinkControl;
		// CMFCLinkCtrl GithubLinkControl;
		afx_msg void OnLinkClick(NMHDR* pNMHDR, LRESULT* pResult);
		// momo add link

		// Implementation
	protected:
		DECLARE_MESSAGE_MAP()
	public:
};

// momo add link
BOOL CAboutDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	GetDlgItem(IDC_WEBSITE_LINK)->SetWindowText(L"Website: <a href=\"https://www.m3dfea.com/\">www.m3dfea.com</a>");
	GetDlgItem(IDC_GITHUB_LINK)->SetWindowText(L"Github: <a href=\"https://github.com/ClassicalFEA\">www.github.com/ClassicalFEA</a>");
	CFont* BoldFont = CreatePointFont(12, _T("Microsoft Sans Serif"), FW_BOLD);
	GetDlgItem(IDC_STATIC_BOLD)->SetFont(BoldFont);
	return TRUE;
}

void CAboutDlg::OnLinkClick(NMHDR* pNMHDR, LRESULT* pResult) {
	PNMLINK pNMLink = (PNMLINK) pNMHDR;
	if (pNMLink && pNMLink->item.szUrl[0] != 0) {
		ShellExecute(0, L"open", pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL);
	}
	*pResult = 0;
}
// momo add link

CAboutDlg::CAboutDlg()
    : CDialog(CAboutDlg::IDD) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
// momo add link
ON_NOTIFY(NM_CLICK, IDC_WEBSITE_LINK, &CAboutDlg::OnLinkClick)
ON_NOTIFY(NM_RETURN, IDC_WEBSITE_LINK, &CAboutDlg::OnLinkClick)
ON_NOTIFY(NM_CLICK, IDC_GITHUB_LINK, &CAboutDlg::OnLinkClick)
ON_NOTIFY(NM_RETURN, IDC_GITHUB_LINK, &CAboutDlg::OnLinkClick)
// momo add link
END_MESSAGE_MAP()

// App command to run the dialog
void CM3daApp::OnAppAbout() {
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// momo add type id form
IMPLEMENT_DYNAMIC(InfoDialog, CDialogEx)
BEGIN_MESSAGE_MAP(InfoDialog, CDialogEx)
ON_WM_CTLCOLOR()
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_CLOSE_BUTTON, &InfoDialog::OnCloseButtonClick)
ON_EN_SETFOCUS(IDC_INFO_EDIT, &InfoDialog::OnEditSetFocus)
ON_BN_CLICKED(1001, &InfoDialog::OnCheckNeedLeftClick_Clicked)
ON_CBN_SELCHANGE(1002, &InfoDialog::OnComboRightDragAction_SelChange)
ON_CBN_SELCHANGE(1003, &InfoDialog::OnComboMiddleDragAction_SelChange)
END_MESSAGE_MAP()

BOOL InfoDialog::OnInitDialog() {
	CDialogEx::OnInitDialog();
	buttonClose.SubclassDlgItem(IDC_CLOSE_BUTTON, this);
	editInfo.SubclassDlgItem(IDC_INFO_EDIT, this);
	CString strText, strCaption;
	double kWidth, kHeight;
	if (formKind == 1) {
		strCaption = _T("Type ID Numbers");
		kWidth = 0.3;
		kHeight = 0.65;
		strText = _T("Type ID Numbers\r\n")
		          _T("\r\n")
		          _T("OD\r\n")
		          _T("---\r\n")
		          _T("Lumped Mass = 161\r\n")
		          _T("\r\n")
		          _T("1D\r\n")
		          _T("---\r\n")
		          _T("Rod = 11\r\n")
		          _T("Beam = 21\r\n")
		          _T("Translational Spring = 136\r\n")
		          _T("Rotational Spring = 137\r\n")
		          _T("RBE = 122\r\n")
		          _T("Bush = 138\r\n")
		          _T("\r\n")
		          _T("2D\r\n")
		          _T("---\r\n")
		          _T("Tri = 91\r\n")
		          _T("Quad = 94\r\n")
		          _T("\r\n")
		          _T("3D\r\n")
		          _T("---\r\n")
		          _T("Tel = 111\r\n")
		          _T("Wedge = 112\r\n")
		          _T("Brick = 115");
	} else if (formKind == 2) {
		strCaption = _T("Properties Help");
		kWidth = 0.4;
		kHeight = 0.4;
		strText = _T("- For Nastran/MYSTRAN, these are the formal properties, which are associated with entries/cards that start with the letter \"P\".\r\n")
		          _T("\r\n")
		          _T("- Note that the \"Element Modify\" menu also affects model \"properties\", but those \"properties\" are stored in entries/cards that begin with \"C\". For example, a CBAR entry contains the bar's orientation vector. Offsets may also be present in the CBAR entry. Similarly, the CQUAD4 stores the offsets (offsets are not stored in the \"P\" cards, such as PBAR and PSHELL).\r\n");
	} else if (formKind == 3) {
		strCaption = _T("Element Modify Help");
		kWidth = 0.4;
		kHeight = 0.33;
		strText = _T("-Some of these menus are modifiers to the elements, but may also be considered informal \"properties\" of the element.\r\n")
		          _T("\r\n")
		          _T("-The modifiers affect the Nastran/MYSTRAN entries/cards that begin with a \" C \". For example, a CBAR entry contains the bar's orientation vector. Offsets may also be present in the CBAR entry. Similarly, the CQUAD4 stores the offsets (offsets are not stored in the \"P\" cards, such as PBAR and PSHELL).");
	} else if (formKind == 4) {
		strCaption = _T("Pan/Zoom/Spin Controls Help");
		kWidth = 0.39;
		kHeight = 0.38;
		strText = _T("Pan  = (option below) or (Ctrl) or (F1)\r\n")
		          _T("Zoom = (option below) or (Mouse Wheel) or (F2)\r\n")
		          _T("Spin = (option below) or (Shift) or (F3)\r\n\r\n")
		          _T("Zoom Box = (Ctrl + Shift) or (F4)\r\n\r\n")
		          _T("Fit All = (Double Middle Click) or (Right Click/Fit All) or Icon");
	}
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int elementSpacing = 20;
	int dlgWidth, dlgHeight;
	dlgWidth = (int) (kWidth * screenWidth);
	dlgHeight = (int) (kHeight * screenHeight);
	SetWindowPos(nullptr, 0, 0, dlgWidth, dlgHeight, SWP_NOMOVE | SWP_NOZORDER);
	CRect client;
	GetClientRect(&client);
	dlgWidth = client.Width();
	dlgHeight = client.Height();
	int btnCloWidth = 75;
	int btnCloHeight = 35;
	int editInfW = dlgWidth - 2 * elementSpacing;
	int editInfH = dlgHeight - btnCloHeight - 3 * elementSpacing;
	int editInfX = elementSpacing;
	int editInfY = elementSpacing;
	int btnCloX = (dlgWidth - btnCloWidth) / 2;
	int btnCloY = editInfY + editInfH + elementSpacing;
	if (formKind == 4) {
		int chkNlcWidth = 180;
		int chkNlcHeight = 20;
		int labelRdaWidth = 150;
		int labelRdaHeight = 20;
		int comboRdaWidth = 150;
		int comboRdaHeight = 300;
		int labelMdaWidth = 150;
		int labelMdaHeight = 20;
		int comboMdaWidth = 150;
		int comboMdaHeight = 300;
		editInfH = editInfH - chkNlcHeight - labelRdaHeight - labelMdaHeight - elementSpacing - elementSpacing / 2;
		int chkX = editInfX;
		int chkY = editInfY + editInfH + elementSpacing / 2;
		checkNeedLeftClick.Create(_T("Need Left Click"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, CRect(chkX, chkY, chkX + chkNlcWidth, chkY + chkNlcHeight), this, 1001);
		checkNeedLeftClick.SetCheck(NeedLeftClick ? BST_CHECKED : BST_UNCHECKED);
		int labelRdaX = editInfX;
		int labelRdaY = chkY + chkNlcHeight + elementSpacing / 2;
		int comboRdaX = labelRdaX + labelRdaWidth + elementSpacing / 2;
		int comboRdaY = labelRdaY - 1;
		labelRightDragAction.Create(_T("Right Mouse Drag:"), WS_CHILD | WS_VISIBLE, CRect(labelRdaX, labelRdaY, labelRdaX + labelRdaWidth, labelRdaY + labelRdaHeight), this, 1004);
		comboRightDragAction.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, CRect(comboRdaX, comboRdaY, comboRdaX + comboRdaWidth, comboRdaY + comboRdaHeight), this, 1002);
		comboRightDragAction.AddString(_T("Pan"));
		comboRightDragAction.AddString(_T("Zoom"));
		comboRightDragAction.AddString(_T("Spin"));
		comboRightDragAction.SetCurSel(RightDragAction - 1);
		int labelMdaX = editInfX;
		int labelMdaY = labelRdaY + labelRdaHeight + elementSpacing / 2;
		int comboMdaX = labelMdaX + labelMdaWidth + elementSpacing / 2;
		int comboMdaY = labelMdaY - 1;
		labelMiddleDragAction.Create(_T("Middle Mouse Drag:"), WS_CHILD | WS_VISIBLE, CRect(labelMdaX, labelMdaY, labelMdaX + labelMdaWidth, labelMdaY + labelMdaHeight), this, 1005);
		comboMiddleDragAction.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, CRect(comboMdaX, comboMdaY, comboMdaX + comboMdaWidth, comboMdaY + comboMdaHeight), this, 1003);
		comboMiddleDragAction.AddString(_T("Pan"));
		comboMiddleDragAction.AddString(_T("Zoom"));
		comboMiddleDragAction.AddString(_T("Spin"));
		comboMiddleDragAction.SetCurSel(MiddleDragAction - 1);
		btnCloY = labelMdaY + labelMdaHeight + elementSpacing;
	}
	buttonClose.MoveWindow(btnCloX, btnCloY, btnCloWidth, btnCloHeight, TRUE);
	editInfo.MoveWindow(editInfX, editInfY, editInfW, editInfH, TRUE);
	SetWindowText(strCaption);
	editInfo.SetWindowText(strText);
	m_brWhite.CreateSolidBrush(RGB(255, 255, 255));
	return FALSE;
}

void InfoDialog::OnShowWindow(BOOL bShow, UINT nStatus) {
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow) {
		editInfo.SetSel(0, 0);
		buttonClose.SetFocus();
	}
}

void InfoDialog::OnEditSetFocus() {
	editInfo.SetSel(0, 0);
}

void CM3daApp::OnShowInfoDialog() {
	InfoDialog dlgInfo;
	const MSG* pMsg = AfxGetCurrentMessage();
	UINT nID = (UINT) pMsg->wParam;
	if (nID == ID_HELP_TYPEID) {
		dlgInfo.formKind = 1;
	} else if (nID == ID_HELP_PROPERTY) {
		dlgInfo.formKind = 2;
	} else if (nID == ID_HELP_ELEMENTMODIFIY) {
		dlgInfo.formKind = 3;
	} else if (nID == ID_HELP_SHORTCUT_KEYS) {
		dlgInfo.formKind = 4;
	}
	dlgInfo.DoModal();
}

void InfoDialog::OnCloseButtonClick() {
	EndDialog(IDOK);
}

HBRUSH InfoDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_INFO_EDIT) {
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_brWhite;
	}
	return hbr;
}

void InfoDialog::OnCheckNeedLeftClick_Clicked() {
	NeedLeftClick = (checkNeedLeftClick.GetCheck() == BST_CHECKED);
	CAppSettings settings;
	settings.WriteNeedLeftClick();
}

void InfoDialog::OnComboRightDragAction_SelChange() {
	int selIndex = comboRightDragAction.GetCurSel();
	if (selIndex != CB_ERR) {
		RightDragAction = selIndex + 1;
		CAppSettings settings;
		settings.WriteRightDragAction();
	}
}

void InfoDialog::OnComboMiddleDragAction_SelChange() {
	int selIndex = comboMiddleDragAction.GetCurSel();
	if (selIndex != CB_ERR) {
		MiddleDragAction = selIndex + 1;
		CAppSettings settings;
		settings.WriteMiddleDragAction();
	}
}
// momo add type id form

// CM3daApp customization load/save methods

void CM3daApp::PreLoadState() {
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	// ASSERT(bNameValid);
	// momo
	// momo// GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT_MANAGER);
	// momo
}

void CM3daApp::LoadCustomState() {
}

void CM3daApp::SaveCustomState() {
}

// CM3daApp message handlers

void CM3daApp::OnFileRunscriptfile() {
	// TODO: Add your command handler code here
	char s1[200];
	CString Cmd;

	outtext1("RUN SCRIPT FILE");
	FILE* pFile;
	// TODO: Add your command handler code here
	CFileDialog FDia(TRUE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	FDia.DoModal();
	CString sPath = FDia.GetPathName();
	CString sFile = FDia.GetFileName();
	if (!sFile.IsEmpty()) {
		pFile = _tfopen(sPath, _T("r"));
		if (pFile != NULL) {
			while (!feof(pFile)) {
				fgets(s1, 200, pFile);
				Cmd = s1;
				Cmd.Remove('\n');
				SendMsg(Cmd);
			}
		}
		fclose(pFile);
		outtext1("END OF SCRIPT FILE");
	}
}
