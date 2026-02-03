
// M3da.h : main header file for the M3da application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h" // main symbols
// MoMo_Material_SaveBugV1_05_20_2025_Start
#include <set>
// MoMo_Material_SaveBugV1_05_20_2025_End
// momo
#include "EditInfo.h"
// momo

// CM3daApp:
// See M3da.cpp for the implementation of this class
//

class CM3daApp: public CWinAppEx {
	public:
		CM3daApp();
		//  Overrides
	public:
		virtual BOOL InitInstance();
		virtual int ExitInstance();
		// Implementation
		COleTemplateServer m_server;
		// Server object for document creation
		BOOL m_bHiColorIcons;

		virtual void PreLoadState();
		virtual void LoadCustomState();
		virtual void SaveCustomState();
		// momo
		void OnFileNewMain();
		void OnFileOpenMain();
		BOOL AskToSaveIfModified();
		BOOL IsValidFileName(CString strFileName);
		void ReplaceWindowsDirectories(CString& strPath);
		void ReplaceNoCase(CString& strSource, const CString& strFind, CString& strReplace);
		BOOL PrepareAndCheckFolder(const CString& strPath);
		// BOOL UseFolderInExePath(const CString subFoldername, int warnByWindow, CString& strFullPath);
		BOOL TheFileExists(const CString& strFilePath);
		BOOL FolderExists(const CString& strFolderPath);
		CString ExeFolderPath();
		// momo
		// momo save by old versions
		void OnFileSaveMain();
		void OnFileSaveAsMain();
		bool LoadConfigFile(CString fileName, const CString stMode);
		// momo save by old versions

		afx_msg void OnAppAbout();
		// momo add type id form
		afx_msg void OnShowInfoDialog();
		afx_msg void OnShowInfoDialogShortcutKeys();
		// momo add type id form
		DECLARE_MESSAGE_MAP()
		afx_msg void OnFileRunscriptfile();

		// Esp_Mod_Config_File_Mod_Start//
	private:
		// momo save by old versions
		// momo// void LoadConfiguration();
		// momo save by old versions
		// Esp_Mod_Config_File_Mod_End//
};
// momo
// momo// void outtext1(CString AAA);
// momo// void outtext2(CString AAA);
void outtext1(const CString& AAA);
void outtext1(const char* AAA);
void outtext2(const CString& AAA);
void outtext2(const char* AAA);
// momo
// MoMo_Material_SaveBugV1_05_20_2025_Start
void outtextSprintf(const CString& formatString, int intValue, double floatValue, CString stringValue, int valueNumber, int nText);
void outtextMultiLine(const CString& AAA, int nText);
void outtextMultiLine(const char* AAA, int nText);
// MoMo_Material_SaveBugV1_05_20_2025_End
void SendMsg(CString AAA);
void SetFocus();
void outtextMSG(CString AAA);
// momo
// momo// void outtextMSG2(CString AAA);
void outtextMSG2(const CString& AAA);
void outtextMSG2(const char* AAA);
CFont* CreatePointFont(int pointSize, LPCTSTR fontName, int weight = FW_NORMAL, BOOL italic = FALSE);
// momo
//// momo ModernOpenGL_Start
////CString ReadText();
////void SetText(CString sIn);
//// momo ModernOpenGL_End
// momo change command box color
void CheckCommandEditColor(bool bForceToCheck);
// momo change command box color
// momo on off button and menu
void CheckPushedButtons(const char* sMode);
// momo on off button and menu

// momo make main buttons
void OnCancelClicked();
void OnDoneClicked();
// momo make main buttons

extern CM3daApp theApp;

// momo add type id form
class InfoDialog: public CDialogEx {
		DECLARE_DYNAMIC(InfoDialog)

	public:
		int formKind;
		InfoDialog(CWnd* pParent = nullptr)
		    : CDialogEx(IDD_INFO_DIALOG, pParent) {}

	protected:
		// virtual void DoDataExchange(CDataExchange* pDX) {
		//	CDialogEx::DoDataExchange(pDX);
		// }
		virtual BOOL OnInitDialog();
		virtual void DoDataExchange(CDataExchange* pDX);
		afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
		afx_msg void OnCloseButtonClick();
		afx_msg void OnExportButtonClick();
		afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		// afx_msg void OnEditSetFocus();
		// afx_msg void OnEditKillFocus();
		afx_msg void OnCheckNeedLeftClick_Clicked();
		afx_msg void OnComboRightDragAction_SelChange();
		afx_msg void OnComboMiddleDragAction_SelChange();
		afx_msg void OnRadioClickAll();
		afx_msg void OnRadioClickExecutive();
		afx_msg void OnRadioClickCase();
		afx_msg void OnRadioClickBulk();
		afx_msg void OnRadioClickBrief();
		afx_msg void OnRadioClickDetailed();
		DECLARE_MESSAGE_MAP()

	private:
		CEditInfo editInfo;
		CButton buttonClose;
		CButton buttonExport;
		CBrush m_brWhite;
		CButton checkNeedLeftClick;
		CComboBox comboRightDragAction;
		CStatic labelRightDragAction;
		CComboBox comboMiddleDragAction;
		CStatic labelMiddleDragAction;
		CFont m_monoFont;
		CButton radioAll;
		CButton radioExecutive;
		CButton radioCase;
		CButton radioBulk;
		CString AllDeckText;
		int nLastRadio;
		CButton radioDescriptionBrief;
		CButton radioDescriptionDetailed;
		CString DescriptionBriefText;
		CString DescriptionDetailedText;
		// int editInfoSelStart;
		// int editInfoSelEnd;
		// int editInfoFirstVisibleLine;

	public:
		bool LoadFileIntoEdit(CEdit& edit, const CString& path);
		void ApplyMonospaceFont(CEdit& edit, int pointSize /*=10*/);
};
// momo add type id form
