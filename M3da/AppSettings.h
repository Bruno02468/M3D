
// MoMo_Start

// AppSettings.h
#pragma once
#include <Windows.h>
#include <VersionHelpers.h>
#include "GLOBAL_VARS.h"

class CAppSettings {
	public:
		CAppSettings(const CString& section = _T("Settings"))
		    : m_section(section) {}

		void WriteBool(const CString& key, BOOL value) {
			AfxGetApp()->WriteProfileInt(m_section, key, value ? 1 : 0);
			return;
		}

		BOOL ReadBool(const CString& key, BOOL defaultValue = TRUE) {
			int val = AfxGetApp()->GetProfileInt(m_section, key, defaultValue ? 1 : 0);
			return (val != 0);
		}

		void WriteInt(const CString& key, int value) {
			AfxGetApp()->WriteProfileInt(m_section, key, value);
			return;
		}

		int ReadInt(const CString& key, int defaultValue) {
			int returnValue = AfxGetApp()->GetProfileInt(m_section, key, defaultValue);
			return returnValue;
		}

		CString OnRestartName() {
			int onRestartMode = ReadInt(_T("DoubleBufferModeNew"), 2);
			CString onRestartName = ModeName(onRestartMode);
			return onRestartName;
		}

		int ToggleDoubleBuffer(int newValue) {
			WriteInt(_T("DoubleBufferModeNew"), newValue);
			int returnValue = ReadInt(_T("DoubleBufferModeCurrent"), 2);
			return returnValue;
		}

		CString ModeName(int modeValue) {
			CString modeName;
			if (modeValue == 0) {
				modeName = "Single";
			} else if (modeValue == 1) {
				modeName = "Double";
			} else {
				modeName = "Auto";
			}
			return modeName;
		}

		void CurrentBuffer(int& currentValue, int& resultValue) {
			currentValue = ReadInt(_T("DoubleBufferModeCurrent"), 2);
			resultValue = BufferResult(currentValue);
			return;
		}

		int ReadDoubleBuffer() {
			int newValue = ReadInt(_T("DoubleBufferModeNew"), 2);
			WriteInt(_T("DoubleBufferModeCurrent"), newValue);
			int returnValue = BufferResult(newValue);
			CurrentBufferResult = returnValue;
			return returnValue;
		}

		int ReadNeedLeftClick() {
			int returnValue = ReadInt(_T("NeedLeftClick"), 0);
			return returnValue;
		}

		void WriteNeedLeftClick() {
			WriteInt(_T("NeedLeftClick"), NeedLeftClick);
			return;
		}

		int ReadRightDragAction() {
			int returnValue = ReadInt(_T("RightDragAction"), 3);
			return returnValue;
		}

		void WriteRightDragAction() {
			WriteInt(_T("RightDragAction"), RightDragAction);
			return;
		}

		int ReadMiddleDragAction() {
			int returnValue = ReadInt(_T("MiddleDragAction"), 1);
			return returnValue;
		}

		void WriteMiddleDragAction() {
			WriteInt(_T("MiddleDragAction"), MiddleDragAction);
			return;
		}

		int ReadDeckModsExecutiveControl() {
			int returnValue = ReadInt(_T("DeckModsExecutiveControl"), 1);
			return returnValue;
		}

		void WriteDeckModsExecutiveControl() {
			WriteInt(_T("DeckModsExecutiveControl"), DeckModsExecutiveControl);
			return;
		}

		int ReadDeckModsCaseControl() {
			int returnValue = ReadInt(_T("DeckModsCaseControl"), 1);
			return returnValue;
		}

		void WriteDeckModsCaseControl() {
			WriteInt(_T("DeckModsCaseControl"), DeckModsCaseControl);
			return;
		}

		int ReadDeckModsBulkData() {
			int returnValue = ReadInt(_T("DeckModsBulkData"), 1);
			return returnValue;
		}

		void WriteDeckModsBulkData() {
			WriteInt(_T("DeckModsBulkData"), DeckModsBulkData);
			return;
		}

		int ReadDeckModsParamBailout() {
			int returnValue = ReadInt(_T("DeckModsParamBailout"), 1);
			return returnValue;
		}

		void WriteDeckModsParamBailout() {
			WriteInt(_T("DeckModsParamBailout"), DeckModsParamBailout);
			return;
		}

		int ReadDeckModsParamAutoSpc() {
			int returnValue = ReadInt(_T("DeckModsParamAutoSpc"), 1);
			return returnValue;
		}

		void WriteDeckModsParamAutoSpc() {
			WriteInt(_T("DeckModsParamAutoSpc"), DeckModsParamAutoSpc);
			return;
		}

		int ReadDeckModsParamPost() {
			int returnValue = ReadInt(_T("DeckModsParamPost"), -1);
			return returnValue;
		}

		void WriteDeckModsParamPost() {
			WriteInt(_T("DeckModsParamPost"), DeckModsParamPost);
			return;
		}

		int ReadDeckModsParamFiles() {
			int returnValue = ReadInt(_T("DeckModsParamFiles"), 0);
			return returnValue;
		}

		void WriteDeckModsParamFiles() {
			WriteInt(_T("DeckModsParamFiles"), DeckModsParamFiles);
			return;
		}

		int ReadDeckModsParamQuad4typ() {
			int returnValue = ReadInt(_T("DeckModsParamQuad4typ"), 0);
			return returnValue;
		}

		void WriteDeckModsParamQuad4typ() {
			WriteInt(_T("DeckModsParamQuad4typ"), DeckModsParamQuad4typ);
			return;
		}

		bool ReadWindowState() {
			int windowState = ReadInt(_T("WindowState"), 1); // 0:Restore 1:Maximize
			return windowState;
		}

		void WriteWindowState(int windowState) {
			WriteInt(_T("WindowState"), windowState);
			return;
		}

		bool ReadDeselectCadrMode() {
			int CadrMode = ReadInt(_T("DeselectCadrMode"), 0); // 0:Disable 1:Enable
			return CadrMode;
		}

		void WriteDeselectCadrMode(int CadrMode) {
			WriteInt(_T("DeselectCadrMode"), CadrMode);
			return;
		}

		int ReadSelectMode() {
			int SelectMode = ReadInt(_T("SelectMode"), 3); // 1:Circle 2:Color 3:CircleAndColor
			return SelectMode;
		}

		void WriteSelectMode(int SelectMode) {
			WriteInt(_T("SelectMode"), SelectMode);
			return;
		}

		void ReadAxisMode(bool& bAxisOrigin, bool& bAxisCorner) {
			int iAxisOrigin = ReadInt(_T("AxisOrigin"), 2); // 1:Off 2:On
			iAxisOrigin--;
			bAxisOrigin = (bool) iAxisOrigin;
			int iAxisCorner = ReadInt(_T("AxisCorner"), 2); // 1:Off 2:On
			iAxisCorner--;
			bAxisCorner = (bool) iAxisCorner;
			return;
		}

		void WriteAxisMode(bool bAxisOrigin, bool bAxisCorner) {
			WriteInt(_T("AxisOrigin"), (int) bAxisOrigin + 1);
			WriteInt(_T("AxisCorner"), (int) bAxisCorner + 1);
			return;
		}

	private:
		CString m_section;

		bool IsWindows11OrGreater() {
			typedef LONG(WINAPI * RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
			HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
			if (hMod) {
				RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
				if (fxPtr != nullptr) {
					RTL_OSVERSIONINFOW rovi = {0};
					rovi.dwOSVersionInfoSize = sizeof(rovi);
					if (fxPtr(&rovi) == 0) // STATUS_SUCCESS == 0
					{
						return (rovi.dwMajorVersion == 10 && rovi.dwBuildNumber >= 22000);
					}
				}
			}
			return false;
		}

		int BufferResult(int newValue) {
			if (newValue == 0 || newValue == 1) {
				return newValue;
			} else {
				if (IsWindows11OrGreater()) {
					return 1;
				} else {
					return 0;
				}
			}
		}
};

// MoMo_End