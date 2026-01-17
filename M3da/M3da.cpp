
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
int DeckModsExecutiveControl = 1;
int DeckModsCaseControl = 1;
int DeckModsBulkData = 1;
int DeckModsParamBailout = 1;
int DeckModsParamAutoSpc = 1;
int DeckModsParamPost = -1;
int DeckModsParamFiles = 0;
int DeckModsParamQuad4typ = 0;
CString TemporaryDeckFilePath = _T("");
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
CommandLine_State CommandLineState;
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
bool ResetVariables = true;
// momo save by old versions
// momo close for LNC
CPoint m_PointOld; // old move point
CPoint m_PointNew; // new move point
// momo close for LNC
// momo random color change bug
bool bUseDoubleBuffer = false;
// momo random color change bug
// momo
double Pi = 3.1415926535;
CString SolutionTypeNames[] = {
    _T("SOL 101 - Linear Static"), // iType = 3
    _T("SOL 103 - Natural Frequency - General Card"), // iType = 4
    _T("SOL 105 - Buckling - General Card"), // iType = 5
    _T("Lin Static (Internal M3D Solver)"), // iType = 0
    _T("Heat (Internal M3D Solver)"), // iType = 1
    _T("Sparse (Internal M3D Solver)")}; // iType = 2
int SolutionTypeNumbers[] = {
    3, // iType = 3
    4, // iType = 4
    5, // iType = 5
    0, // iType = 0
    1, // iType = 1
    2}; // iType = 2
bool TemporaryChangeFlagCleared = false;
CString sSpliter = _T(",");
CString DataPath = _T("");
CString ModelFileName = _T("");
bool ModelFileNameChanged = false;
bool DatFileOverwritePrompt = true;
CString TextViewerExe = _T("");
// momo

// CM3daApp

BEGIN_MESSAGE_MAP(CM3daApp, CWinAppEx)
ON_COMMAND(ID_APP_ABOUT, &CM3daApp::OnAppAbout)
// momo add type id form
ON_COMMAND(ID_HELP_TYPEID, &CM3daApp::OnShowInfoDialog)
// momo add type id form
// momo
ON_COMMAND(ID_HELP_SOLUTION_SETUP, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_SHORTCUT_KEYS, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_PROPERTY, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_ELEMENTMODIFIY, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_OVERALL_PROCESS, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_LOADSBC, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_SOLUTION, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_ASSIGN_PROPERTIES, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_CONFIG_FILES, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_BC_SETS, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_CREATE_FE, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_REGISTRY_LOCATION, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_M3D_SHORTCOMING, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_SOLID_ELEMENT_SUPPORT, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_IGES_IMPORT, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_SOLVER_OPTIONS, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_WORKPLANE, &CM3daApp::OnShowInfoDialog)
ON_COMMAND(ID_HELP_MESHMANAGEMENT, &CM3daApp::OnShowInfoDialog)
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
	if (!AskToSaveIfModified())
		return;
	ResetVariables = true;
	OnFileNew();
}

void CM3daApp::OnFileOpenMain() {
	// if (!AskToSaveIfModified())
	//	return;
	// ResetVariables = false;
	// OnFileOpen();

	if (!AskToSaveIfModified()) {
		// if current document changed and for "Save changes ..." windows
		// user selected "Cancel"
		// or user selected "Yes" but not saved successfully
		return;
	}
	// if current document not changed or changed but for "Save changes ..." windows
	// user selected "No"
	// or user selected "Yes" and saved successfully
	ResetVariables = false;
	CFileDialog dlg(TRUE, _T("m3d"), nullptr, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("M3D Files (*.m3d)|*.m3d|All Files (*.*)|*.*||"));
	if (dlg.DoModal() != IDOK) {
		// if user selected "Cancel" in open window
		return;
	}
	// if user selected a file in open window
	CString strPath = dlg.GetPathName();
	if (strPath.IsEmpty()) {
		return;
	}
	CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd();
	CDocument* pActiveDoc = pFrame ? pFrame->GetActiveDocument() : nullptr;
	// Check and reload current opened file
	if (pActiveDoc) {
		CString activePath = pActiveDoc->GetPathName();
		if (!activePath.IsEmpty() && activePath.CompareNoCase(strPath) == 0) {
			pActiveDoc->DeleteContents();
			ResetVariables = true;
			if (!pActiveDoc->OnOpenDocument(strPath)) {
				AfxMessageBox(_T("Failed to reload document."));
				return;
			}
			pActiveDoc->UpdateAllViews(NULL);
			return;
		}
	}
	// if "selected document" != "current document"
	POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
	while (pos) {
		CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate(pos);
		if (pTemplate) {
			ResetVariables = true;
			CDocument* pDoc = pTemplate->OpenDocumentFile(strPath);
			if (pDoc != nullptr) {
				return;
			}
		}
	}
	AfxMessageBox(_T("Could not open the selected file."));
}

BOOL CM3daApp::AskToSaveIfModified() {
	CFrameWnd* pMainWnd = (CFrameWnd*) AfxGetMainWnd();
	if (!pMainWnd)
		return TRUE;
	CDocument* pDoc = pMainWnd->GetActiveDocument();
	if (!pDoc)
		return TRUE;
	if (!pDoc->IsModified() && !TemporaryChangeFlagCleared)
		return TRUE;
	CString fileName = pDoc->GetTitle();
	if (fileName.IsEmpty()) {
		fileName = _T("Untitled");
	}
	CString msg;
	msg.Format(_T("Save changes to %s?"), fileName);
	int res = AfxMessageBox(msg, MB_YESNOCANCEL | MB_ICONQUESTION);
	switch (res) {
		case IDYES:
			if (!pDoc->DoFileSave())
				return FALSE;
			return TRUE;
		case IDNO:
			pDoc->SetModifiedFlag(FALSE);
			TemporaryChangeFlagCleared = true;
			return TRUE;
		case IDCANCEL:
		default:
			return FALSE;
	}
}

BOOL CM3daApp::IsValidFileName(CString strFileName) {
	if (strFileName.IsEmpty())
		return FALSE;
	const CString strInvalidChars = _T("\\/:*?\"<>|");
	if (strFileName.FindOneOf(strInvalidChars) != -1) {
		return FALSE;
	}
	CString strUpper = strFileName;
	strUpper.MakeUpper();
	int nDot = strUpper.Find('.');
	if (nDot != -1)
		strUpper = strUpper.Left(nDot);
	if (strUpper == _T("CON") || strUpper == _T("PRN") || strUpper == _T("AUX") ||
	    strUpper == _T("NUL") ||
	    (strUpper.GetLength() == 4 && strUpper.Left(3) == _T("COM") && isdigit(strUpper[3])) ||
	    (strUpper.GetLength() == 4 && strUpper.Left(3) == _T("LPT") && isdigit(strUpper[3]))) {
		return FALSE;
	}
	return TRUE;
}

void CM3daApp::ReplaceWindowsDirectories(CString& strPath) {
	/*
	====================================================================================================
	  Windows Path-Based Environment Variables (Folders & Files Only)
	====================================================================================================
	  Variable                  Default Value (Example)             Description
	----------------------------------------------------------------------------------------------------
	  [System Directories]
	  %SystemRoot%              C:\Windows                          Windows installation directory
	  %windir%                  C:\Windows                          Same as %SystemRoot%
	  %SystemDrive%             C:                                  Drive containing Windows
	  %ProgramFiles%            C:\Program Files                    Default program installation folder
	  %ProgramFiles(x86)%       C:\Program Files (x86)              32-bit programs folder (on x64 OS)
	  %ProgramData%             C:\ProgramData                      Data shared by all users
	  %CommonProgramFiles%      C:\Program Files\Common Files       Shared components folder
	  %Public%                  C:\Users\Public                     Public user profile folder

	  [System Files]
	  %ComSpec%                 C:\Windows\System32\cmd.exe         Path to Command Prompt executable

	  [User Directories]
	  %UserProfile%             C:\Users\{User}                     Current user's profile folder
	  %AppData%                 C:\Users\{User}\AppData\Roaming     Roaming application data folder
	  %LocalAppData%            C:\Users\{User}\AppData\Local       Local application data folder
	  %Temp%                    C:\Users\{User}\AppData\Local\Temp  Temporary files folder
	  %HomeDrive%               C:                                  User's home drive location
	  %HomePath%                \Users\{User}                       User's home directory path
	====================================================================================================
	*/
	DWORD nSize = ::ExpandEnvironmentStrings(strPath, NULL, 0);
	if (nSize > 0) {
		CString strResult;
		LPTSTR pBuffer = strResult.GetBuffer(nSize);
		::ExpandEnvironmentStrings(strPath, pBuffer, nSize);
		strResult.ReleaseBuffer();
		strPath = strResult;
		CString ProgramExeFolder = ExeFolderPath();
		ReplaceNoCase(strPath, _T("%MyExeFolder%"), ProgramExeFolder);
	}
}

void CM3daApp::ReplaceNoCase(CString& strSource, const CString& strFind, CString& strReplace) {
	if (strSource.IsEmpty() || strFind.IsEmpty())
		return;
	CString strSourceLower = strSource;
	strSourceLower.MakeLower();
	CString strFindLower = strFind;
	strFindLower.MakeLower();
	int nFindLen = strFind.GetLength();
	int nReplaceLen = strReplace.GetLength();
	int nPos = 0;
	while ((nPos = strSourceLower.Find(strFindLower, nPos)) != -1) {
		strSource.Delete(nPos, nFindLen);
		strSource.Insert(nPos, strReplace);
		strSourceLower.Delete(nPos, nFindLen);
		CString strReplaceLower = strReplace;
		strReplaceLower.MakeLower();
		strSourceLower.Insert(nPos, strReplaceLower);
		nPos += nReplaceLen;
	}
}

// #include <shlobj.h>
BOOL CM3daApp::PrepareAndCheckFolder(const CString& strPath) {
	int nRet = ::SHCreateDirectoryEx(NULL, strPath, NULL);
	if (nRet != ERROR_SUCCESS &&
	    nRet != ERROR_FILE_EXISTS &&
	    nRet != ERROR_ALREADY_EXISTS) {
		return FALSE;
	}
	if (nRet == ERROR_SUCCESS) {
		outtext1(_T("\"") + strPath + _T("\"  was created."));
	}
	CString strTestFilePath = strPath;
	if (strTestFilePath.Right(1) != _T("\\"))
		strTestFilePath += _T("\\");
	CString strTempName;
	strTempName.Format(_T("__WriteTest_%u.tmp"), ::GetTickCount());
	strTestFilePath += strTempName;
	CFile file;
	CFileException ex;
	if (file.Open(strTestFilePath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone, &ex)) {
		file.Close();
		::DeleteFile(strTestFilePath);
		return TRUE;
	}
	return FALSE;
}

// BOOL CM3daApp::UseFolderInExePath(const CString subFoldername, int warnMode, CString& strFullPath) {
//	// 1) Resolve "<exe-folder>\subFoldername"
//	TCHAR exePath[MAX_PATH] = {0};
//	GetModuleFileName(NULL, exePath, MAX_PATH);
//	PathRemoveFileSpec(exePath);
//	strFullPath.Format(_T("%s\\%s"), exePath, subFoldername);
//	// 2) Ensure subFoldername exists
//	DWORD attr = GetFileAttributes(strFullPath);
//	if (attr == INVALID_FILE_ATTRIBUTES) {
//		int r = SHCreateDirectoryEx(NULL, strFullPath, NULL);
//		if (r != ERROR_SUCCESS && r != ERROR_ALREADY_EXISTS) {
//			CString warnMessage = _T("Failed to create '") + subFoldername + _T("' folder next to the executable. Operation aborted.");
//			if (warnMode == 1) {
//				AfxMessageBox(warnMessage, MB_ICONERROR);
//			} else if (warnMode == 2) {
//				outtextMultiLine(warnMessage, 1);
//			}
//			return FALSE;
//		}
//	} else if ((attr & FILE_ATTRIBUTE_DIRECTORY) == 0) {
//		CString warnMessage = subFoldername + _T("' exists but is not a directory. Operation aborted.");
//		if (warnMode == 1) {
//			AfxMessageBox(warnMessage, MB_ICONERROR);
//		} else if (warnMode == 2) {
//			outtextMultiLine(warnMessage, 1);
//		}
//		return FALSE;
//	}
//	return TRUE;
// }

CString CM3daApp::ExeFolderPath() {
	TCHAR szPath[MAX_PATH];
	if (::GetModuleFileName(NULL, szPath, MAX_PATH) == 0) {
		return _T("");
	}
	CString strPath = szPath;
	int nPos = strPath.ReverseFind(_T('\\'));
	if (nPos != -1) {
		strPath = strPath.Left(nPos);
	}
	return strPath;
}

BOOL CM3daApp::TheFileExists(const CString& strFilePath) {
	DWORD dwAttrib = ::GetFileAttributes(strFilePath);
	if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
	    !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
		return TRUE;
	}
	return FALSE; // File not exists or it is a Folder
}

BOOL CM3daApp::FolderExists(const CString& strFolderPath) {
	DWORD dwAttrib = ::GetFileAttributes(strFolderPath);
	if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
	    (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
		return TRUE;
	}
	return FALSE; // Folder not exists or it is a File
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
		    _T("M3da Files - Version 8.0 (*.m3d)|*.m3d|")
		    _T("M3da Files - Version 7.9 (*.m3d)|*.m3d|")
		    _T("M3da Files - Version 7.8 (*.m3d)|*.m3d||");
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
		outtextSprintf(_T("File Saved successfully. (Version = %.1f)"), 0, abs(iVERInner / 10.0), false, 1);
		if (!ModelFileNameChanged) {
			CString strPureFileName = dlgPath;
			int nSlashPos = strPureFileName.ReverseFind('\\');
			strPureFileName = strPureFileName.Mid(nSlashPos + 1);
			int nDotPos = strPureFileName.ReverseFind('.');
			strPureFileName = strPureFileName.Left(nDotPos);
			ModelFileName = strPureFileName;
		}
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
		    _T("M3da Files - Version 8.0 (*.m3d)|*.m3d|")
		    _T("M3da Files - Version 7.9 (*.m3d)|*.m3d|")
		    _T("M3da Files - Version 7.8 (*.m3d)|*.m3d||");
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
		outtextSprintf(_T("File Saved successfully. (Version = %.1f)"), 0, abs(iVERInner / 10.0), false, 1);
		if (!ModelFileNameChanged) {
			CString strPureFileName = dlgPath;
			int nSlashPos = strPureFileName.ReverseFind('\\');
			strPureFileName = strPureFileName.Mid(nSlashPos + 1);
			int nDotPos = strPureFileName.ReverseFind('.');
			strPureFileName = strPureFileName.Left(nDotPos);
			ModelFileName = strPureFileName;
		}
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
// momo
// void CM3daApp::LoadConfiguration() {
//	CStdioFile file;
//	if (file.Open(_T("config.txt"), CFile::modeRead | CFile::shareDenyWrite)) {
bool CM3daApp::LoadConfigFile(CString fileName, const CString stMode) {
	CStdioFile file;
	if (file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite)) {
		CM3daApp* pApp = (CM3daApp*) AfxGetApp();
		// momo
		CString strLine;
		while (file.ReadString(strLine)) {
			// momo
			int nPos = strLine.Find(_T("*"));
			if (nPos != -1) {
				strLine = strLine.Left(nPos);
			}
			nPos = strLine.Find(_T("$"));
			if (nPos != -1) {
				strLine = strLine.Left(nPos);
			}
			// momo
			strLine.Trim(); // Remove leading/trailing whitespace

			// Skip empty lines or comment lines that start with '*'
			if (strLine.IsEmpty() || strLine.Left(1) == _T("*") || strLine.Left(1) == _T("$"))
				continue;

			// Expecting "key, value" format
			int commaPos = strLine.Find(_T(","));
			if (commaPos != -1) {
				CString key = strLine.Left(commaPos);
				CString value = strLine.Mid(commaPos + 1);
				key.Trim();
				value.Trim();
				// momo
				key.MakeLower();
				// momo

				// Update settings based on key
				// momo
				// if (key.CompareNoCase(_T("background_color")) == 0) {
				//	gBACKGRD_COL = _ttoi(value);
				//} else if (key.CompareNoCase(_T("zoom_scale_factor")) == 0) {
				//	gZOOM_SCL = _ttof(value);
				//} else if (key.CompareNoCase(_T("point_size")) == 0) {
				//	gPT_SIZE = _ttoi(value);
				//} else if (key.CompareNoCase(_T("node_size")) == 0) {
				//	gND_SIZE = _ttoi(value);
				//} else if (key.CompareNoCase(_T("lump_mass_size")) == 0) {
				//	gLM_SIZE = _ttoi(value);
				//} else if (key.CompareNoCase(_T("element_edge_size")) == 0) {
				//	gEL_SIZE = _ttoi(value);
				//} else if (key.CompareNoCase(_T("free_edge_size")) == 0) {
				//	gED_SIZE = _ttoi(value);
				//} else if (key.CompareNoCase(_T("free_face_size")) == 0) {
				//	gFC_SIZE = _ttoi(value);
				//} else if (key.CompareNoCase(_T("workplane_line_weight")) == 0) {
				//	gWP_SIZE = _ttoi(value);
				//} else if (key.CompareNoCase(_T("beam_section_size")) == 0) {
				//	gBM_SIZE = _ttoi(value);
				//} else if (key.CompareNoCase(_T("text_size")) == 0) {
				//	gTXT_SIZE = _ttoi(value);
				//} else if (key.CompareNoCase(_T("drawing_scale_for_dims")) == 0) {
				//	gDIM_SCALE = _ttof(value);
				//} else if (key.CompareNoCase(_T("fillet_size")) == 0) {
				//	gDIM_FILSZ = _ttof(value);
				//} else if (key.CompareNoCase(_T("line_offset")) == 0) {
				//	gDIM_OFFSZ = _ttof(value);
				//} else if (key.CompareNoCase(_T("text_height")) == 0) {
				//	gTXT_HEIGHT = _ttof(value);
				//} else if (key.CompareNoCase(_T("circle_radius_for_circr")) == 0) {
				//	gDIM_RADSZ = _ttof(value);
				//} else if (key.CompareNoCase(_T("spline_order")) == 0) {
				//	gDIM_CVORD = _ttoi(value);
				//} else if (key.CompareNoCase(_T("dimesion_precision")) == 0) {
				//	gDIM_PREC = _ttoi(value);
				//} else if (key.CompareNoCase(_T("dimension_size")) == 0) {
				//	gDIM_SIZE = _ttof(value);
				//} else if (key.CompareNoCase(_T("trim_curve_on_surface_resolution")) == 0) {
				//	gCUR_RES = _ttoi(value);
				//} else if (key.CompareNoCase(_T("shell_drilling_k_value")) == 0) {
				//	gDRILL_KS = _ttof(value);
				//} else if (key.CompareNoCase(_T("stiffness_multiplier_for_m3d_dummy_rigid")) == 0) {
				//	gRIGID_MULTIPLIER = _ttof(value);
				//} else if (key.CompareNoCase(_T("k_for_restraints")) == 0) {
				//	gVSTIFF_KS = _ttof(value);
				//} else if (key.CompareNoCase(_T("default_material_E")) == 0) {
				//	gDEF_E = _ttof(value);
				//} else if (key.CompareNoCase(_T("default_material_v")) == 0) {
				//	gDEF_V = _ttof(value);
				//} else if (key.CompareNoCase(_T("default_material_density")) == 0) {
				//	gDEF_DEN = _ttof(value);
				//} else if (key.CompareNoCase(_T("default_material_thermal_conductivity")) == 0) {
				//	gDEF_COND = _ttof(value);
				//} else if (key.CompareNoCase(_T("default_siff_beam_diameter")) == 0) {
				//	gSTIFF_BDIA = _ttof(value);
				//} else if (key.CompareNoCase(_T("default_material_cte")) == 0) {
				//	gDEF_CTE = _ttof(value);
				//} else if (key.CompareNoCase(_T("default_thermal_link_coeff")) == 0) {
				//	gDEF_THERM_LNK = _ttof(value);
				//} else if (key.CompareNoCase(_T("default_iterative_solver_toleranace")) == 0) {
				//	gDEF_SOL_TOL = _ttof(value);
				//}
				if (stMode == _T("Color")) {
					if (key.CompareNoCase(_T("color_background")) == 0) {
						gBACKGRD_COL = _ttoi(value);
					} else if (key.CompareNoCase(_T("color_node")) == 0) {
					} else {
						outtext1(_T("Warning: Wrong key in config_color.txt file: \"") + key + _T("\""));
					}
				} else if (stMode == _T("ColorPicked")) {
					if (key.CompareNoCase(_T("color_picked_node")) == 0) {
					} else {
						outtext1(_T("Warning: Wrong key in config_color_picked.txt file: \"") + key + _T("\""));
					}
				} else if (stMode == _T("Material")) {
					if (key.CompareNoCase(_T("default_material_E")) == 0) {
						gDEF_E = _ttof(value);
					} else if (key.CompareNoCase(_T("default_material_v")) == 0) {
						gDEF_V = _ttof(value);
					} else if (key.CompareNoCase(_T("default_material_density")) == 0) {
						gDEF_DEN = _ttof(value);
					} else if (key.CompareNoCase(_T("default_material_thermal_conductivity")) == 0) {
						gDEF_COND = _ttof(value);
					} else if (key.CompareNoCase(_T("default_material_cte")) == 0) {
						gDEF_CTE = _ttof(value);
					} else if (key.CompareNoCase(_T("default_material_thermal_link_coeff")) == 0) {
						gDEF_THERM_LNK = _ttof(value);
					} else {
						outtext1(_T("Warning: Wrong key in config_default_material.txt file: \"") + key + _T("\""));
					}
				} else if (stMode == _T("Dimension")) {
					if (key.CompareNoCase(_T("dimension_drawing_scale")) == 0) {
						gDIM_SCALE = _ttof(value);
					} else if (key.CompareNoCase(_T("dimension_precision")) == 0) {
						gDIM_PREC = _ttoi(value);
					} else if (key.CompareNoCase(_T("dimension_size")) == 0) {
						gDIM_SIZE = _ttof(value);
					} else {
						outtext1(_T("Warning: Wrong key in config_dimension.txt file: \"") + key + _T("\""));
					}
				} else if (stMode == _T("General")) {
					if (key.CompareNoCase(_T("general_zoom_scale_factor")) == 0) {
						gZOOM_SCL = _ttof(value);
					} else if (key.CompareNoCase(_T("general_fillet_size")) == 0) {
						gDIM_FILSZ = _ttof(value);
					} else if (key.CompareNoCase(_T("general_line_offset")) == 0) {
						gDIM_OFFSZ = _ttof(value);
					} else if (key.CompareNoCase(_T("general_text_height")) == 0) {
						gTXT_HEIGHT = _ttof(value);
					} else if (key.CompareNoCase(_T("general_circle_radius_for_circr")) == 0) {
						gDIM_RADSZ = _ttof(value);
					} else if (key.CompareNoCase(_T("general_spline_order")) == 0) {
						gDIM_CVORD = _ttoi(value);
					} else if (key.CompareNoCase(_T("general_trim_curve_on_surface_resolution")) == 0) {
						gCUR_RES = _ttoi(value);
					} else if (key.CompareNoCase(_T("general_shell_drilling_k_value")) == 0) {
						gDRILL_KS = _ttof(value);
					} else if (key.CompareNoCase(_T("general_stiffness_multiplier_for_m3d_dummy_rigid")) == 0) {
						gRIGID_MULTIPLIER = _ttof(value);
					} else if (key.CompareNoCase(_T("general_k_for_restraints")) == 0) {
						gVSTIFF_KS = _ttof(value);
					} else if (key.CompareNoCase(_T("general_default_siff_beam_diameter")) == 0) {
						gSTIFF_BDIA = _ttof(value);
					} else if (key.CompareNoCase(_T("general_default_iterative_solver_toleranace")) == 0) {
						gDEF_SOL_TOL = _ttof(value);
					} else {
						outtext1(_T("Warning: Wrong key in config_general.txt file: \"") + key + _T("\""));
					}
				} else if (stMode == _T("LineWeights")) {
					if (key.CompareNoCase(_T("line_weight_workplane")) == 0) {
						gWP_SIZE = _ttoi(value);
					} else {
						outtext1(_T("Warning: Wrong key in config_line_weights.txt file: \"") + key + _T("\""));
					}
				} else if (stMode == _T("Size")) {
					if (key.CompareNoCase(_T("size_point")) == 0) {
						gPT_SIZE = _ttoi(value);
					} else if (key.CompareNoCase(_T("size_node")) == 0) {
						gND_SIZE = _ttoi(value);
					} else if (key.CompareNoCase(_T("size_lump_mass")) == 0) {
						gLM_SIZE = _ttoi(value);
					} else if (key.CompareNoCase(_T("size_element_edge")) == 0) {
						gEL_SIZE = _ttoi(value);
					} else if (key.CompareNoCase(_T("size_free_edge")) == 0) {
						gED_SIZE = _ttoi(value);
					} else if (key.CompareNoCase(_T("size_free_face")) == 0) {
						gFC_SIZE = _ttoi(value);
					} else if (key.CompareNoCase(_T("size_beam_section")) == 0) {
						gBM_SIZE = _ttoi(value);
					} else if (key.CompareNoCase(_T("size_text")) == 0) {
						gTXT_SIZE = _ttoi(value);
					} else {
						outtext1(_T("Warning: Wrong key in config_size.txt file: \"") + key + _T("\""));
					}
				} else if (stMode == _T("Solve")) {
					if (key.CompareNoCase(_T("solve_dat_path")) == 0) {
						value.Replace(_T("\""), _T(""));
						pApp->ReplaceWindowsDirectories(value);
						if (!pApp->PrepareAndCheckFolder(value)) {
							CString try1, try2, try3;
							try1 = value;
							value = _T("%SystemDrive%\\M3D_Runs");
							pApp->ReplaceWindowsDirectories(value);
							try2 = value;
							if (!pApp->PrepareAndCheckFolder(value)) {
								value = _T("%MyExeFolder%\\M3D_Runs");
								pApp->ReplaceWindowsDirectories(value);
								try3 = value;
								if (!pApp->PrepareAndCheckFolder(value)) {
									value = _T("");
								}
							}
							if (value.IsEmpty()) {
								outtext1(_T("Warning: The program searched the following paths for the variable \"solve_dat_path\" to use as writable folders:"));
								outtext1(_T("\"") + try1 + _T("\""));
								outtext1(_T("\"") + try2 + _T("\""));
								outtext1(_T("\"") + try3 + _T("\""));
								outtext1(_T("But this was not successful."));
								outtext1(_T("Please fix this problem."));
							} else {
								outtext1(_T("Warning: The path specified for solve_dat_path in config_solve.txt is not writable:"));
								outtext1(_T("\"") + try1 + _T("\""));
								outtext1(_T("It was replaced with:"));
								outtext1(_T("\"") + value + _T("\""));
							}
						}
						DataPath = value;
					} else if (key.CompareNoCase(_T("solve_default_model_name")) == 0) {
						value.Replace(_T("\""), _T(""));
						if (value.IsEmpty()) {
							value = _T("Untitled");
							ModelFileNameChanged = false;
						} else if (!pApp->IsValidFileName(value)) {
							outtext1(_T("Warning: Wrong value for solve_default_model_name in config_solve.txt file:"));
							outtext1(_T("\"") + value + _T("\""));
							value = _T("Untitled");
							outtext1(_T("It was replaced with:"));
							outtext1(_T("\"") + value + _T("\""));
							ModelFileNameChanged = false;
						} else {
							ModelFileNameChanged = true;
						}
						ModelFileName = value;
					} else if (key.CompareNoCase(_T("solve_dat_auto_overwrite")) == 0) {
						value.MakeLower();
						if (value.IsEmpty() || value == "yes") {
							DatFileOverwritePrompt = true;
						} else {
							DatFileOverwritePrompt = false;
						}
					} else if (key.CompareNoCase(_T("solve_solver_dir")) == 0) {
					} else {
						outtext1(_T("Warning: Wrong key in config_solve.txt file: \"") + key + _T("\""));
					}
				} else if (stMode == _T("Viewer")) {
					if (key.CompareNoCase(_T("text_viewer_exe")) == 0) {
						value.Replace(_T("\""), _T(""));
						pApp->ReplaceWindowsDirectories(value);
						if (!pApp->TheFileExists(value)) {
							CString try1, try2, try3, try4;
							try1 = value;
							value = _T("%ProgramFiles%\\Notepad++\\notepad++.exe");
							pApp->ReplaceWindowsDirectories(value);
							try2 = value;
							if (!pApp->TheFileExists(value)) {
								value = _T("%MyExeFolder%\\Notepad++\\notepad++.exe");
								pApp->ReplaceWindowsDirectories(value);
								try3 = value;
								if (!pApp->TheFileExists(value)) {
									value = _T("%windir%\\system32\\notepad.exe");
									pApp->ReplaceWindowsDirectories(value);
									try4 = value;
									if (!pApp->TheFileExists(value)) {
										value = _T("");
									}
								}
							}
							if (value.IsEmpty()) {
								outtext1(_T("Warning: The program searched for the following files to use as variable \"text_viewer_exe\":"));
								outtext1(_T("\"") + try1 + _T("\""));
								outtext1(_T("\"") + try2 + _T("\""));
								outtext1(_T("\"") + try3 + _T("\""));
								outtext1(_T("\"") + try4 + _T("\""));
								outtext1(_T("But this was not successful."));
								outtext1(_T("Please fix this problem."));
							} else {
								outtext1(_T("Warning: Wrong value for text_viewer_exe in config_viewer.txt file:"));
								outtext1(_T("\"") + try1 + _T("\""));
								outtext1(_T("It was replaced with:"));
								outtext1(_T("\"") + value + _T("\""));
							}
						}
						TextViewerExe = value;
					} else {
						outtext1(_T("Warning: Wrong key in config_viewer.txt file: \"") + key + _T("\""));
					}
				}
				// momo
			}
		}
		file.Close();
		// momo
		//} else {
		//	AfxMessageBox(_T("Failed to open config.txt."));
		return true;
		// momo
	}
	// momo
	return false;
	// momo
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
	SetRegistryKey(_T("M3D-DevM-Reg-38"));
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
	DspFlagsMain.DSP_MATERIALDIRECTION = false;
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
	CommandLineState.CurrentStateIsActive = false;
	CommandLineState.NewStateIsActive = false;
	CommandLineState.AlsoChangeEdit1Color = false;
	// momo change command box color
	// momo
	CAppSettings settings;
	DeselectCadrMode = settings.ReadDeselectCadrMode();
	SelectMode = settings.ReadSelectMode();
	settings.ReadAxisMode(AxisOrigin, AxisCorner);
	NeedLeftClick = settings.ReadNeedLeftClick();
	RightDragAction = settings.ReadRightDragAction();
	MiddleDragAction = settings.ReadMiddleDragAction();
	DeckModsExecutiveControl = settings.ReadDeckModsExecutiveControl();
	DeckModsCaseControl = settings.ReadDeckModsCaseControl();
	DeckModsBulkData = settings.ReadDeckModsBulkData();
	DeckModsParamBailout = settings.ReadDeckModsParamBailout();
	DeckModsParamAutoSpc = settings.ReadDeckModsParamAutoSpc();
	DeckModsParamPost = settings.ReadDeckModsParamPost();
	DeckModsParamFiles = settings.ReadDeckModsParamFiles();
	DeckModsParamQuad4typ = settings.ReadDeckModsParamQuad4typ();
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
	// momo
	// if (finder.FindFile(_T("config.txt"))) {
	//	LoadConfiguration();
	//} else {
	//	// TODO: If file no found, for example, set default values and make config.txt based on it
	//}
	// if (!LoadConfiguration(_T("config.txt"))) {
	// TODO: If file no found, for example, set default values and make config.txt based on it
	//}
	// momo
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

//**************************************************************************
//****************************** InfoDialog ********************************
//**************************************************************************

IMPLEMENT_DYNAMIC(InfoDialog, CDialogEx)
BEGIN_MESSAGE_MAP(InfoDialog, CDialogEx)
ON_WM_CTLCOLOR()
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_CLOSE_BUTTON, &InfoDialog::OnCloseButtonClick)
ON_BN_CLICKED(IDC_DECKPREVIEW_BTN_EXPORT, &InfoDialog::OnExportButtonClick)
// ON_EN_SETFOCUS(IDC_INFO_EDIT, &InfoDialog::OnEditSetFocus)
// ON_EN_KILLFOCUS(IDC_INFO_EDIT, &InfoDialog::OnEditKillFocus)
ON_BN_CLICKED(IDC_CONTROLS_CHK_NEED_LEFT_CLICK, &InfoDialog::OnCheckNeedLeftClick_Clicked)
ON_CBN_SELCHANGE(IDC_CONTROLS_CBO_RIGHT_MOUSE_DRAG, &InfoDialog::OnComboRightDragAction_SelChange)
ON_CBN_SELCHANGE(IDC_CONTROLS_CBO_MIDDLE_MOUSE_DRAG, &InfoDialog::OnComboMiddleDragAction_SelChange)
ON_BN_CLICKED(IDC_DECKPREVIEW_RAD_ALL, &InfoDialog::OnRadioClickAll)
ON_BN_CLICKED(IDC_DECKPREVIEW_RAD_EXECUTIVE, &InfoDialog::OnRadioClickExecutive)
ON_BN_CLICKED(IDC_DECKPREVIEW_RAD_CASE, &InfoDialog::OnRadioClickCase)
ON_BN_CLICKED(IDC_DECKPREVIEW_RAD_BULK, &InfoDialog::OnRadioClickBulk)
ON_BN_CLICKED(ID_HELP_SOLUTION_RAD_BRIEF, &InfoDialog::OnRadioClickBrief)
ON_BN_CLICKED(ID_HELP_SOLUTION_RAD_DETAILED, &InfoDialog::OnRadioClickDetailed)
END_MESSAGE_MAP()

BOOL InfoDialog::OnInitDialog() {
	CDialogEx::OnInitDialog();
	buttonClose.SubclassDlgItem(IDC_CLOSE_BUTTON, this);
	// editInfo.SubclassDlgItem(IDC_INFO_EDIT, this);
	CString strText, strCaption;
	double kWidth, kHeight;
	int elementSpacing = 20;
	int editInfX = elementSpacing;
	int editInfY = elementSpacing;
	int editInfYAdd = 0;
	nLastRadio = 0;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	if (formKind == 1) {
		strCaption = _T("Type ID Numbers");
		kWidth = 0.375;
		kHeight = 0.65;
		strText = _T("---------------------------\r\n")
		          _T("----- Type ID Numbers -----\r\n")
		          _T("---------------------------\r\n")
		          _T("\r\n")
		          _T("0D\r\n")
		          _T("-----------\r\n")
		          _T("Lumped Mass = 161\r\n")
		          _T("\r\n")
		          _T("1D\r\n")
		          _T("-----------\r\n")
		          _T("Rod = 11\r\n")
		          _T("Beam = 21\r\n")
		          _T("Translational Spring = 136\r\n")
		          _T("Rotational Spring = 137\r\n")
		          _T("RBE2 = 122\r\n")
		          _T("Bush = 138\r\n")
		          _T("\r\n")
		          _T("2D\r\n")
		          _T("-----------\r\n")
		          _T("Tri = 91\r\n")
		          _T("Quad = 94\r\n")
		          _T("\r\n")
		          _T("3D\r\n")
		          _T("-----------\r\n")
		          _T("Tet = 111\r\n")
		          _T("Wedge = 112\r\n")
		          _T("Brick = 115");
	} else if (formKind == 2) {
		strCaption = _T("Properties Help");
		kWidth = 0.5;
		kHeight = 0.36;
		strText = _T("• For Nastran/MYSTRAN, these are the formal properties, which are associated with entries/cards that start with the letter \"P\".\r\n")
		          _T("\r\n")
		          _T("• Note that the \"Element Modify\" menu also affects model \"properties\", but those \"properties\" are stored in entries/cards that begin with \"C\". For example, a CBAR entry contains the bar's orientation vector. Offsets may also be present in the CBAR entry. Similarly, the CQUAD4 stores the offsets (offsets are not stored in the \"P\" cards, such as PBAR and PSHELL).");
	} else if (formKind == 3) {
		strCaption = _T("Element Modify Help");
		kWidth = 0.5;
		kHeight = 0.33;
		strText = _T("• Some of these menus are modifiers to the elements, but may also be considered informal \"properties\" of the element.\r\n")
		          _T("\r\n")
		          _T("• The modifiers affect the Nastran/MYSTRAN entries/cards that begin with a \" C \". For example, a CBAR entry contains the bar's orientation vector. Offsets may also be present in the CBAR entry. Similarly, the CQUAD4 stores the offsets (offsets are not stored in the \"P\" cards, such as PBAR and PSHELL).");
	} else if (formKind == 4) {
		strCaption = _T("Pan/Zoom/Spin Controls");
		kWidth = 0.4875;
		kHeight = 0.38;
		strText = _T("Pan  = (option below) or (Ctrl) or (F1)\r\n")
		          _T("Zoom = (option below) or (Mouse Wheel) or (F2)\r\n")
		          _T("Spin = (option below) or (Shift) or (F3)\r\n\r\n")
		          _T("Zoom Box = (Left + Right) or (Ctrl + Shift) or (F4)\r\n\r\n")
		          _T("Fit All = (Double Middle Click) or (Right Click/Fit All) or Icon");
	} else if (formKind == 5) {
		strCaption = _T("Solution Setup");
		kWidth = 0.6;
		kHeight = 0.45;
		strText = _T("Process to Create: Boundary Conditions, Loads, Temperature\r\n")
		          _T("1 - Create a Set\r\n")
		          _T("2 - Activate the Set\r\n")
		          _T("3 - Create the B.C., Load, Temperature\r\n\r\n")
		          _T("Process to Create Solution and Solution Step:\r\n")
		          _T("1. Create the Solution Type\r\n")
		          _T("    101 - Linear Static\r\n")
		          _T("    103 - Normal Modes (Natural Frequency)\r\n")
		          _T("    105 - Bulcking\r\n")
		          _T("2. Activate Solution Type\r\n")
		          _T("3. Create the Solution Step\r\n")
		          _T("    Apply B.C., Loads, Temperature (these are applied to the solution type)\r\n")
		          _T("4. Activate the Solution Step");
	} else if (formKind == 6) {
		strCaption = _T("Overall FEA process for M3D");
		kWidth = 0.72;
		kHeight = 0.55;
		DescriptionBriefText = _T("Overall FEA process for M3D:\r\n")
		                       _T("• Create Geometry (Optional)\r\n")
		                       _T("• Create Nodes/Elements\r\n")
		                       _T("• Create Materials\r\n")
		                       _T("• Create Properties\r\n")
		                       _T("• Assign Properties to Elements\r\n")
		                       _T("• If Required, Modify Elements (Beam Pin Flags, Shell Offsets, etc.)\r\n")
		                       _T("• Create SPC/LOAD/TEMPERATURE Sets (and Activate)\r\n")
		                       _T("• Add SPC/FORCE/MOMENT/PLOAD/TEMP/etc. to SPC/LOAD/TEMPERATURE Sets\r\n")
		                       _T("• Create Solution Type (and Activate)\r\n")
		                       _T("• Create Case(s) - (Add SPC/LOAD/TEMPERATURE Sets to a Solution Type)\r\n")
		                       _T("• If Required, Use \"Deck - Master Overrides\" within the M3D Menu\r\n")
		                       _T("• Create Deck (DAT or BDF)\r\n")
		                       _T("• If Required, Manually Modify the Deck\r\n")
		                       _T("• Run Deck (via Nastran or MYSTRAN)\r\n")
		                       _T("• Read Results (OP2)\r\n\r\n")
		                       _T("NOTE: An \"entry\" is also called a \"card\". For example, the CROD and PROD entries are also known as cards. This goes back to the days of punch cards. A set of cards is known as a \"deck\" (a deck of cards). The deck is an ASCII file, composed of all the finite element information for the model, that is passed to the solver. A deck may either be a DAT or BDF file (both are valid).");
		DescriptionDetailedText = _T("Overall FEA process for M3D:\r\n\r\n")
		                          _T("• Create Geometry (Optional)\r\n\r\n")
		                          _T("• Create Nodes/Elements (GRIDS and \"C\" Cards - CROD, CTRIA3, etc.) - Based on:\r\n")
		                          _T(" (Geometry, Directly Created, or Imported via Deck)\r\n\r\n")
		                          _T("• Create Materials (MAT1, MAT8, etc.)\r\n\r\n")
		                          _T("• Create Properties (\"P\" Cards - PROD, PSHELL, etc.) - Material ID's are Entered in the \"P\" Card\r\n\r\n")
		                          _T("• Assign Properties to Elements (Assign \"P\" Card ID to the \"C\" Card Entry - 3rd Field)\r\n\r\n")
		                          _T("• If Required, Modify Elements (Beam DOF Release aka Pin Flags, Shell Offsets, etc.). Modifications take place on the \"C\" Card (Not the \"P\" Card)\r\n\r\n")
		                          _T("• Create SPC/LOAD/TEMPERATURE Sets (and Activate) - Reside in Case Control\r\n\r\n")
		                          _T("• Add SPC/FORCE/MOMENT/PLOAD/TEMP/etc. (Reside in the Bulk Data Section) to SPC/LOAD/TEMPERATURE Sets. Sets are containers for SPC/FORCE/MOMENT/PLOAD/TEMP/etc.\r\n\r\n")
		                          _T("• Create Solution Type (and Activate) - Executive Control - SOL 101, 103, 105\r\n\r\n")
		                          _T("• Create Case(s) - (Add SPC/LOAD/TEMPERATURE Sets to a Solution Type) - In M3D, these will all be SUBCASES in the Case Control Section, even if there is only one case.\r\n\r\n")
		                          _T("• If Required, Use \"Deck - Master Overrides\" within the M3D Menu\r\n\r\n")
		                          _T("• Create Deck (DAT or BDF) - ASCII File of the Finite Element Model and Solution Setup\r\n\r\n")
		                          _T("• If Required, Manually Modify the Deck\r\n\r\n")
		                          _T("• Run Deck (via Nastran or MYSTRAN). This may be done automatically via the M3D Solve menu or by manually exporting a deck and running Nastran/MYSTRAN in a CMD window.\r\n\r\n")
		                          _T("• Read Results (OP2) - Binary File with Results (Result Types Requested in Case Control)\r\n\r\n")
		                          _T("NOTE: An \"entry\" is also called a \"card\". For example, the CROD and PROD entries are also known as cards. This goes back to the days of punch cards. A set of cards is known as a \"deck\" (a deck of cards). The deck is an ASCII file, composed of all the finite element information for the model, that is passed to the solver. A deck may either be a DAT or BDF file (both are valid).");
		strText = DescriptionBriefText;
	} else if (formKind == 7) {
		strCaption = _T("BC (Boundary Conditions) Help");
		kWidth = 0.45;
		kHeight = 0.325;
		strText = _T("• First, create a set (SPC/FORCE/TEMPERATURE) and activate it. Then add to the set (SPC/FORCE/TEMPERATURE).\r\n\r\n")
		          _T("• Each new SPC/FORCE/TEMPERATURE addition is added to the activated set (but they are not individually identified). In a later M3D edition, each addition to the set will be uniquely identified (allowing for each to be added/removed to a given set).");
	} else if (formKind == 8) {
		strCaption = _T("Solution Setup Help");
		kWidth = 0.61;
		kHeight = 0.36;
		strText = _T("• Create a Solution Type and activate it.\r\n\r\n")
		          _T("• Add a single case or multiple cases via \"Case Control (SPC/LOAD/TEMP)\".\r\n\r\n")
		          _T("• If there is only one case, it will still be listed as SUBCASE 1 in the deck. Note tha Nastran/MYSTRAN does not need a SUBCASE for a single case.\r\n\r\n")
		          _T("• The 3 Legacy M3D Solution Types are not currently supported, but are used with the Internal M3D Solver. Recent changes to M3D have not considered legacy solutions. Note that a heat transfer solution is present as a legacy solution (currently, no heat transfer solution is officially supported).");
	} else if (formKind == 9) {
		strCaption = _T("Assign Properties Help");
		kWidth = 0.47;
		kHeight = 0.42;
		strText = _T("• When an element is created (a \"C\" card such as CROD, CTRIA3), the PID (Property ID) is initally set to \"-1\" (no association to a property).\r\n\r\n")
		          _T("• After a property is created (a \"P\" card such as PROD, PSHELL), the property exists and is part of the deck, but is not yet associated to an element.\r\n\r\n")
		          _T("• The \"Change Element Prop ID\" menu is used to associate a property to an element (the PID will then be populated in the 3rd field of the element card).\r\n\r\n")
		          _T("• The assocation is shown in the deck (via export deck) or deck preview.");
	} else if (formKind == 10) {
		strCaption = _T("Config Files Help");
		kWidth = 0.47;
		kHeight = 0.5;
		strText = _T("All config files must reside in the directory that M3D is launched from. There are two \"types\" of config files.\r\n\r\n")
		          _T("Type 1: General Setup (Optional). The config file is read when M3D starts. If a variable in a config file is changed, the program must be restarted. Applicable to:\r\n")
		          _T("config_general.txt\r\n")
		          _T("config_color.txt\r\n")
		          _T("config_color_picked.txt\r\n")
		          _T("config_size.txt\r\n")
		          _T("config_line_weight.txt\r\n")
		          _T("config_default_material.txt\r\n\r\n")
		          _T("Type 2: Computer Specific (Usually Requires Changes). The config file is read upon the individual request. This allows the user to change the config file without needing to restart M3D. Applicable to:\r\n")
		          _T("config_solve.txt\r\n")
		          _T("config_deck_mods.txt\r\n")
		          _T("config_notepad.txt\r\n")
		          _T("config_f06csv.txt");
	} else if (formKind == 11) {
		strCaption = _T("BC Sets Help");
		kWidth = 0.55;
		kHeight = 0.46;
		strText = _T("• A Set is a container, with a defined Set ID, and is located in the Case Control Section (Example: SPC = 100, LOAD = 200, TEMPERATURE = 300)\r\n\r\n")
		          _T("• SPC Set: SPC (Single Point Constraint) entries (cards) can be added to the set, referenced by the Set ID. Thes SPC entries are located in the Bulk Data Section.\r\n\r\n")
		          _T("• LOAD Set: FORCE, MOMENT, PLOAD, etc. entries (cards) can be added to the set, referenced by the Set ID. These FORCE, MOMENT, PLOAD, etc. entries are located in the Bulk Data Section.\r\n\r\n")
		          _T("• TEMPERATURE Set: TEMP (temperature) entries (cards) can be added to the set, referenced by the Set ID. The TEMP entries are located in the Bulk Data Section.\r\n\r\n")
		          _T("• The Active Set is stated on the bottom view bar (bottom right), provided the bar is turned on (View/Bottom View Bar)\r\n\r\n")
		          _T("NOTE: Nastran/MYSTRAN supports other entries (such as SPCD - Single Point Constraint Displacement) that are not currently supported by M3D.");
	} else if (formKind == 12) {
		strCaption = _T("Create FE Help");
		kWidth = 0.40;
		kHeight = 0.20;
		strText = _T("If creating an element \"node-by-node\", first Set the Element Type (Set Element).");
	} else if (formKind == 13) {
		strCaption = _T("Registry Location Help");
		kWidth = 0.61;
		kHeight = 0.22;
		strText = _T("Registry Location = Computer\\HKEY_CURRENT_USER\\Software\\M3D-X\r\n\r\n")
		          _T("• New versions may require old registry entries to be deleted.");
	} else if (formKind == 14) {
		strCaption = _T("M3D Shortcomings Help");
		kWidth = 0.49;
		kHeight = 0.346;
		strText = _T("Currently, M3D has no support (or limited support) for:\r\n\r\n")
		          _T("• STEP file import\r\n")
		          _T("• Geometric solid creation\r\n")
		          _T("• Geometric solid meshing (See \"Help/Solid Elements\" for support options)\r\n")
		          _T("• Surface stitching\r\n")
		          _T("• Quad paver mesh (quad mapped meshing is supported)\r\n")
		          _T("• Boundary conditions can not be applied to geometry. They must be applied to the nodes/elements.");
	} else if (formKind == 15) {
		strCaption = _T("Solid Element Support Help");
		kWidth = 0.5;
		kHeight = 0.524;
		strText = _T("Currently, M3D does not support (or has limited support) to import and create geometric solids and mesh them with solid elements. To address this, some options are:\r\n\r\n")
		          _T("• Use any software that supports CalculiX solid element creation. Some options are Mecway and PrePoMax. Then convert the INP file into a DAT file. An INP to DAT converter is available at https://github.com/ClassicalFEA/. Then import the DAT file (the deck).\r\n\r\n")
		          _T("• Mecway, which can import STEP files and create solid element meshes, has the native ability to export a DAT file. This DAT file can be imported into M3D.\r\n\r\n")
		          _T("• Use any other software (commercial or open source) that can create a DAT/BDF and import the DAT/BDF file to M3D.\r\n\r\n")
		          _T("NOTE: Although this is atypical, solid elements may also be created one-by-one in M3D.");
	} else if (formKind == 16) {
		strCaption = _T("IGES Import Help");
		kWidth = 0.5;
		kHeight = 0.33;
		strText = _T("• M3D can import IGES files. However, for most IGES file types, the curves/surfaces/etc. are not \"stitched\" together. Therefore, the individual entities may be imported in various positions (not consistent with the original positions when it was exported from the given program).\r\n\r\n")
		          _T("• Autodesk supports \"shell and part data structures\", which will allow an IGES file to be properly imported into M3D. However, most CAD programs do not support this feature.");
	} else if (formKind == 17) {
		strCaption = _T("Solver Options - Primary and Alternate Help");
		kWidth = 0.5;
		kHeight = 0.329;
		strText = _T("There are two solver options for M3D. For Versions 9.0+ :\r\n\r\n")
		          _T("• Primary Option: External Solver (Nastran or MYSTRAN). Linear static, natural frequency, and buckling solutions are supported.\r\n\r\n")
		          _T("• Alternate Option: Internal M3D Solver. This solver is no longer officially supported and is considered a legacy solver. Linear static and heat transfer solutions exist.");
	} else if (formKind == 18) {
		strCaption = _T("Workplane Help");
		kWidth = 0.40;
		kHeight = 0.20;
		strText = _T("Node/Points/Etc. are created with respect to the Workplane (Local X,Y,Z), which may or may not be aligned with the Global X,Y,Z.");
	} else if (formKind == 19) {
		strCaption = _T("Mesh Management Help");
		kWidth = 0.5;
		kHeight = 0.304;
		strText = _T("• Most general FE model only require a single mesh (typical). The Mesh Management menu will typically not be needed.\r\n")
		          _T("• However, M3D can read in multiple DAT/BDF files, each with their own mesh. These can used as include files, which is a Nastran/MYSTRAN feature. Note that Materials and Properties have a \"File No.\", which is the include file number.\r\n")
		          _T("• The meshes can be combined via \"Build Assembly Mesh\" and double clicking the meshes.");
	} else if (formKind == -1) {
		strCaption = _T("Deck Preview");
		kWidth = 0.8375;
		kHeight = 0.70;
		strText = _T("");
	}
	int dlgWidth, dlgHeight;
	dlgWidth = (int) (kWidth * screenHeight); // screenWidth);
	dlgHeight = (int) (kHeight * screenHeight);
	SetWindowPos(nullptr, 0, 0, dlgWidth, dlgHeight, SWP_NOMOVE | SWP_NOZORDER);
	CRect client;
	GetClientRect(&client);
	dlgWidth = client.Width();
	dlgHeight = client.Height();
	int btnCloWidth = 75;
	int btnCloHeight = 35;
	int btnExpWidth = 100;
	int editInfW = dlgWidth - 2 * elementSpacing;
	int editInfH = dlgHeight - btnCloHeight - 3 * elementSpacing;
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
		checkNeedLeftClick.Create(_T("Need Left Click"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, CRect(chkX, chkY, chkX + chkNlcWidth, chkY + chkNlcHeight), this, IDC_CONTROLS_CHK_NEED_LEFT_CLICK);
		checkNeedLeftClick.SetCheck(NeedLeftClick ? BST_CHECKED : BST_UNCHECKED);
		int labelRdaX = editInfX;
		int labelRdaY = chkY + chkNlcHeight + elementSpacing / 2;
		int comboRdaX = labelRdaX + labelRdaWidth + elementSpacing / 2;
		int comboRdaY = labelRdaY - 1;
		labelRightDragAction.Create(_T("Right Mouse Drag:"), WS_CHILD | WS_VISIBLE, CRect(labelRdaX, labelRdaY, labelRdaX + labelRdaWidth, labelRdaY + labelRdaHeight), this, IDC_CONTROLS_LBL_RIGHT_MOUSE_DRAG);
		comboRightDragAction.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, CRect(comboRdaX, comboRdaY, comboRdaX + comboRdaWidth, comboRdaY + comboRdaHeight), this, IDC_CONTROLS_CBO_RIGHT_MOUSE_DRAG);
		comboRightDragAction.AddString(_T("Pan"));
		comboRightDragAction.AddString(_T("Zoom"));
		comboRightDragAction.AddString(_T("Spin"));
		comboRightDragAction.SetCurSel(RightDragAction - 1);
		int labelMdaX = editInfX;
		int labelMdaY = labelRdaY + labelRdaHeight + elementSpacing / 2;
		int comboMdaX = labelMdaX + labelMdaWidth + elementSpacing / 2;
		int comboMdaY = labelMdaY - 1;
		labelMiddleDragAction.Create(_T("Middle Mouse Drag:"), WS_CHILD | WS_VISIBLE, CRect(labelMdaX, labelMdaY, labelMdaX + labelMdaWidth, labelMdaY + labelMdaHeight), this, IDC_CONTROLS_LBL_MIDDLE_MOUSE_DRAG);
		comboMiddleDragAction.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, CRect(comboMdaX, comboMdaY, comboMdaX + comboMdaWidth, comboMdaY + comboMdaHeight), this, IDC_CONTROLS_CBO_MIDDLE_MOUSE_DRAG);
		comboMiddleDragAction.AddString(_T("Pan"));
		comboMiddleDragAction.AddString(_T("Zoom"));
		comboMiddleDragAction.AddString(_T("Spin"));
		comboMiddleDragAction.SetCurSel(MiddleDragAction - 1);
		btnCloY = labelMdaY + labelMdaHeight + elementSpacing;
	} else if (formKind == 6) {
		CRect rc(editInfX + elementSpacing / 2, editInfY - elementSpacing / 2, 250, 35);
		radioDescriptionBrief.Create(_T("Brief Description"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON | WS_GROUP, rc, this, ID_HELP_SOLUTION_RAD_BRIEF);
		int dx = editInfW / 2;
		rc.OffsetRect(dx, 0);
		radioDescriptionDetailed.Create(_T("Detailed Description"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON, rc, this, ID_HELP_SOLUTION_RAD_DETAILED);
		radioDescriptionBrief.SetCheck(BST_CHECKED);
		radioDescriptionDetailed.SetCheck(BST_UNCHECKED);
		editInfYAdd = 23;
	} else if (formKind == -1) {
		ApplyMonospaceFont(editInfo, 12);
		LoadFileIntoEdit(editInfo, TemporaryDeckFilePath);
		CRect rc(editInfX + elementSpacing / 2, editInfY - elementSpacing / 2, 250, 35);
		radioAll.Create(_T("All"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON | WS_GROUP, rc, this, IDC_DECKPREVIEW_RAD_ALL);
		int dy = rc.Height() + 2;
		rc.OffsetRect(0, dy);
		radioExecutive.Create(_T("Executive Control"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON, rc, this, IDC_DECKPREVIEW_RAD_EXECUTIVE);
		rc.OffsetRect(0, dy);
		radioCase.Create(_T("Case Control"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON, rc, this, IDC_DECKPREVIEW_RAD_CASE);
		rc.OffsetRect(0, dy);
		radioBulk.Create(_T("Bulk Data"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON, rc, this, IDC_DECKPREVIEW_RAD_BULK);
		radioAll.SetCheck(BST_CHECKED);
		radioExecutive.SetCheck(BST_UNCHECKED);
		radioCase.SetCheck(BST_UNCHECKED);
		radioBulk.SetCheck(BST_UNCHECKED);
		editInfYAdd = 105;
		buttonExport.Create(_T("Export Deck"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, rc, this, IDC_DECKPREVIEW_BTN_EXPORT);
	} else if (formKind == 1) {
		ApplyMonospaceFont(editInfo, 12);
	}
	buttonClose.MoveWindow(btnCloX, btnCloY, btnCloWidth, btnCloHeight, TRUE);
	editInfo.MoveWindow(editInfX, editInfY + editInfYAdd, editInfW, editInfH - editInfYAdd, TRUE);
	SetWindowText(strCaption);
	if (formKind == -1) {
		buttonExport.MoveWindow(editInfX + editInfW - btnExpWidth - elementSpacing / 2, editInfY + editInfYAdd - btnCloHeight - elementSpacing / 2, btnExpWidth, btnCloHeight, TRUE);
	} else {
		editInfo.SetWindowText(strText);
	}
	m_brWhite.CreateSolidBrush(RGB(255, 255, 255));
	return FALSE;
}

void InfoDialog::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFO_EDIT, editInfo);
}

void InfoDialog::OnShowWindow(BOOL bShow, UINT nStatus) {
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow) {
		// editInfoSelStart = 0;
		// editInfoSelEnd = 0;
		// editInfoFirstVisibleLine = 0;
		// editInfo.SetSel(editInfoSelStart, editInfoSelEnd);
		editInfo.selStart = 0;
		editInfo.selEnd = 0;
		editInfo.firstVisibleLine = 0;
		editInfo.SetSel(0, 0);
		editInfo.SetFocus();
	}
}

// void InfoDialog::OnEditSetFocus() {
//	editInfo.SetRedraw(FALSE);
//	editInfo.SetSel(editInfoSelStart, editInfoSelEnd);
//	int currentFirstVisibleLine = editInfo.GetFirstVisibleLine();
//	int deltaChangeLine = editInfoFirstVisibleLine - currentFirstVisibleLine;
//	if (deltaChangeLine != 0) {
//		editInfo.LineScroll(deltaChangeLine);
//	}
//	editInfo.SetRedraw(TRUE);
//	editInfo.Invalidate();
//	editInfo.UpdateWindow();
// }
//
// void InfoDialog::OnEditKillFocus() {
//	editInfo.GetSel(editInfoSelStart, editInfoSelEnd);
//	editInfoFirstVisibleLine = editInfo.GetFirstVisibleLine();
// }

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
	} else if (nID == ID_HELP_SOLUTION_SETUP) {
		dlgInfo.formKind = 5;
	} else if (nID == ID_HELP_OVERALL_PROCESS) {
		dlgInfo.formKind = 6;
	} else if (nID == ID_HELP_LOADSBC) {
		dlgInfo.formKind = 7;
	} else if (nID == ID_HELP_SOLUTION) {
		dlgInfo.formKind = 8;
	} else if (nID == ID_HELP_ASSIGN_PROPERTIES) {
		dlgInfo.formKind = 9;
	} else if (nID == ID_HELP_CONFIG_FILES) {
		dlgInfo.formKind = 10;
	} else if (nID == ID_HELP_BC_SETS) {
		dlgInfo.formKind = 11;
	} else if (nID == ID_HELP_CREATE_FE) {
		dlgInfo.formKind = 12;
	} else if (nID == ID_HELP_REGISTRY_LOCATION) {
		dlgInfo.formKind = 13;
	} else if (nID == ID_HELP_M3D_SHORTCOMING) {
		dlgInfo.formKind = 14;
	} else if (nID == ID_HELP_SOLID_ELEMENT_SUPPORT) {
		dlgInfo.formKind = 15;
	} else if (nID == ID_HELP_IGES_IMPORT) {
		dlgInfo.formKind = 16;
	} else if (nID == ID_HELP_SOLVER_OPTIONS) {
		dlgInfo.formKind = 17;
	} else if (nID == ID_HELP_WORKPLANE) {
		dlgInfo.formKind = 18;
	} else if (nID == ID_HELP_MESHMANAGEMENT) {
		dlgInfo.formKind = 19;
	} else {
		dlgInfo.formKind = -1;
	}
	dlgInfo.DoModal();
}

void InfoDialog::OnCloseButtonClick() {
	EndDialog(IDOK);
}

void InfoDialog::OnExportButtonClick() {
	CWnd* pMain = AfxGetMainWnd();
	if (pMain) {
		pMain->SendMessage(WM_COMMAND, ID_EXPORT_CURRENTMESTTONAS);
	}
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

void InfoDialog::OnRadioClickAll() {
	if (nLastRadio != 0) {
		nLastRadio = 0;
		editInfo.SetWindowText(AllDeckText);
	}
}

void InfoDialog::OnRadioClickExecutive() {
	if (nLastRadio != 1) {
		nLastRadio = 1;
		CString startTag = _T("*** EXECUTIVE CONTROL ***");
		CString endTag = _T("CEND");
		int startPos = AllDeckText.Find(startTag);
		int endPos = AllDeckText.Find(endTag);
		CString findResult;
		if (startPos != -1 && endPos != -1 && endPos > startPos) {
			startPos = startPos - 124;
			endPos = endPos + 7;
			startPos += startTag.GetLength();
			int len = endPos - startPos;
			findResult = AllDeckText.Mid(startPos, len);
		} else {
			findResult = _T("");
		}
		editInfo.SetWindowText(findResult);
	}
}

void InfoDialog::OnRadioClickCase() {
	if (nLastRadio != 2) {
		nLastRadio = 2;
		CString startTag = _T("*** CASE CONTROL ***");
		CString endTag = _T("*** BULK DATA ***");
		int startPos = AllDeckText.Find(startTag);
		int endPos = AllDeckText.Find(endTag);
		CString findResult;
		if (startPos != -1 && endPos != -1 && endPos > startPos) {
			startPos = startPos - 119;
			endPos = endPos - 182;
			startPos += startTag.GetLength();
			int len = endPos - startPos;
			findResult = AllDeckText.Mid(startPos, len);
		} else {
			findResult = _T("");
		}
		editInfo.SetWindowText(findResult);
	}
}

void InfoDialog::OnRadioClickBulk() {
	if (nLastRadio != 3) {
		nLastRadio = 3;
		// CString startTag = _T("*** BULK DATA ***");
		// CString endTag = _T("*** SOL 103 AND SOL 105 EIGEN CARD ***");
		// int startPos = AllDeckText.Find(startTag);
		// int endPos = AllDeckText.Find(endTag);
		// int endPosDelta = 100;
		// if (endPos == -1){
		//	endTag = _T("*** PARAMETERS ***");
		//	endPos = AllDeckText.Find(endTag);
		//	endPosDelta = 101;
		//	if (endPos == -1){
		//		endTag = _T("*** MATERIALS ***");
		//		endPos = AllDeckText.Find(endTag);
		//		endPosDelta = 101;
		//	}
		// }
		// CString findResult;
		// if (startPos != -1 && endPos != -1 && endPos > startPos) {
		//	startPos = startPos - 117;
		//	endPos = endPos - endPosDelta;
		//	startPos += startTag.GetLength();
		//	int len = endPos - startPos;
		//	findResult = AllDeckText.Mid(startPos, len);
		// } else {
		//	findResult = _T("");
		// }
		CString startTag = _T("*** BULK DATA ***");
		int startPos = AllDeckText.Find(startTag);
		int endPos = AllDeckText.GetLength();
		CString findResult;
		if (startPos != -1 && endPos != -1 && endPos > startPos) {
			startPos = startPos - 117;
			startPos += startTag.GetLength();
			int len = endPos - startPos;
			findResult = AllDeckText.Mid(startPos, len);
		} else {
			findResult = _T("");
		}
		editInfo.SetWindowText(findResult);
	}
}

void InfoDialog::OnRadioClickBrief() {
	if (nLastRadio != 0) {
		nLastRadio = 0;
		editInfo.SetWindowText(DescriptionBriefText);
	}
}

void InfoDialog::OnRadioClickDetailed() {
	if (nLastRadio != 1) {
		nLastRadio = 1;
		editInfo.SetWindowText(DescriptionDetailedText);
	}
}

// Load a text file into a CEdit control (normalize to CRLF)
bool InfoDialog::LoadFileIntoEdit(CEdit& edit, const CString& path) {
	FILE* file = _tfopen(path, _T("r"));
	if (!file)
		return false;

	AllDeckText = _T("");
	TCHAR buffer[4096];

	// Read line by line, strip trailing \r or \n, then append CRLF
	while (_fgetts(buffer, _countof(buffer), file)) {
		size_t n = _tcslen(buffer);
		while (n > 0 && (buffer[n - 1] == _T('\n') || buffer[n - 1] == _T('\r'))) {
			buffer[--n] = _T('\0');
		}
		AllDeckText += buffer;
		AllDeckText += _T("\r\n");
	}
	fclose(file);

	edit.SetLimitText(0x7FFFFFFF);
	edit.SetWindowText(AllDeckText);
	// editInfoSelStart = 0;
	// editInfoSelEnd = 0;
	// editInfo.SetSel(editInfoSelStart, editInfoSelEnd);
	if (&edit == &editInfo) {
		editInfo.selStart = 0;
		editInfo.selEnd = 0;
		editInfo.firstVisibleLine = 0;
	}
	edit.SetSel(0, 0);

	return true;
}

void InfoDialog::ApplyMonospaceFont(CEdit& edit, int pointSize /*=10*/) {
	// Calculate logical height from point size
	CClientDC dc(this);
	const int dpiY = dc.GetDeviceCaps(LOGPIXELSY);
	const int lfHeight = -MulDiv(pointSize, dpiY, 72);

	LOGFONT lf = {};
	lf.lfHeight = lfHeight;
	lf.lfWeight = FW_NORMAL;
	lf.lfPitchAndFamily = FIXED_PITCH | FF_MODERN; // request fixed-width family

	// Try Consolas first (clear modern monospace on Windows)
	wcscpy_s(lf.lfFaceName, L"Consolas");
	if (m_monoFont.CreateFontIndirect(&lf)) {
		edit.SetFont(&m_monoFont);
		return;
	}

	// Fallback: Courier New
	m_monoFont.DeleteObject();
	wcscpy_s(lf.lfFaceName, L"Courier New");
	if (m_monoFont.CreateFontIndirect(&lf)) {
		edit.SetFont(&m_monoFont);
		return;
	}

	// Last resort: use stock ANSI_FIXED_FONT (do not delete stock objects)
	HFONT hStock = (HFONT)::GetStockObject(ANSI_FIXED_FONT);
	edit.SendMessage(WM_SETFONT, (WPARAM) hStock, MAKELPARAM(TRUE, 0));
	// Note: no CFont::Attach to stock object unless you manage lifetime carefully
}
//**************************************************************************
//****************************** InfoDialog ********************************
//**************************************************************************

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
