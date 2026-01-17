#pragma once

// MoMo_Start
#include <windows.h>
#include <afx.h>
class DSP_Triad;
class Symbol;
class PropTable;
class MatTable;
// MoMo_End

extern int gBACKGRD_COL;
extern bool gDOUBLEBUFF;
extern double gZOOM_SCL;
extern double gPT_SIZE;
extern double gND_SIZE;
extern double gLM_SIZE;
extern double gEL_SIZE;
extern double gED_SIZE;
extern double gFC_SIZE;
extern double gWP_SIZE;
extern double gBM_SIZE;
extern double gTXT_SIZE;
extern double gDIM_SCALE;
extern double gDIM_FILSZ;
extern double gDIM_OFFSZ;
extern double gTXT_HEIGHT;
extern double gDIM_RADSZ;
extern double gDIM_CVORD;
// momo change Display Flags Method
// momo// extern BOOL gDSP_CPTS;
// momo change Display Flags Method
extern BOOL gDSP_CIRS;
// MoMo_Start
struct SeedValues {
		BOOL IsSeedMode;
		BOOL SelectSurface;
		BOOL SelectSurfaceCurves;
		BOOL SelectLock;
		double InputedMeshElementSize = 1.0;
		int InputedSeedNumbers = 0;
};
extern SeedValues SeedVals;
extern CString LastRequest;
extern BOOL CurrentBufferResult;
extern BOOL leftIsDraggingForSelect;
extern BOOL leftIsDraggingForZoomBox;
extern BOOL rightIsDraggingForZoomBox;
extern BOOL rightIsDraggingForZoomBoxCanceled;
extern int m_x1;
extern int m_y1;
extern int m_x2;
extern int m_y2;
extern BOOL DeSelectAll;
extern BOOL StartLoad;
// MoMo_End
// momo
const int MAX_RESSETS = 10000;
extern int SelRowsCurrent[MAX_RESSETS][2];
extern int SelRowsNew[MAX_RESSETS][2];
extern bool DeselectCadrMode;
extern int SelectMode;
extern int MainDrawState;
extern bool AxisOrigin;
extern bool AxisCorner;
extern int m_iFuncKey;
extern bool NeedLeftClick;
extern int RightDragAction;
extern int MiddleDragAction;
extern bool MouseLeftDown;
extern bool MouseRightDown;
extern bool MouseMiddleDown;
extern int DeckModsExecutiveControl;
extern int DeckModsCaseControl;
extern int DeckModsBulkData;
extern int DeckModsParamBailout;
extern int DeckModsParamAutoSpc;
extern int DeckModsParamPost;
extern int DeckModsParamFiles;
extern int DeckModsParamQuad4typ;
extern CString TemporaryDeckFilePath;
// momo
// momo change command box color
struct CommandLine_State {
		bool CurrentStateIsActive;
		bool NewStateIsActive;
		bool AlsoChangeEdit1Color;
};
extern CommandLine_State CommandLineState;
// momo change command box color
// momo on off button and menu
struct ButtonPushed {
		bool WireFrame;
		bool ShadedWithEdges;
		bool ShadedWithoutEdges;
		int DrawModeCurrent;
		int DrawModeOut;
		bool AllFiniteOn;
		bool AllGeomOn;
		bool OnlySelectedOn;
		bool QfilterNodesOn;
		bool QfilterElementsOn;
		bool QfilterPointsOn;
		bool QfilterCurvesOn;
		bool QfilterSurfacesOn;
		bool FullBody;
		bool PartOfBody;
		bool CenterOfBody;
};
extern ButtonPushed ButtonPush;
// momo on off button and menu
// momo gdi to og2
struct ClickPoint {
		bool IsClicked;
		int x;
		int y;
};
extern ClickPoint mClickPoint;
// momo gdi to og2
// momo change Display Flags Method
struct DisplayFlags {
		bool DSP_WIREFRAME;
		bool DSP_SHADED_WITH_EDGES;
		bool DSP_NODES;
		bool DSP_ELEMENTS_ALL;
		bool DSP_BOUNDARYCONDITIONS;
		bool DSP_POINTS;
		bool DSP_CONTROLPOINTS;
		bool DSP_CURVES;
		bool DSP_SURFACES;
		bool DSP_COORDINATE_SYSTEMS;
		bool DSP_WORKPLANE;
		bool DSP_SHELLTHICKNESS;
		bool DSP_ELEMENTCOORDSYS;
		bool DSP_SURFACEDIRECTIONMARKERS;
		bool DSP_GRADIENT_BACKGROUND;
		bool DSP_ELEMENTS_0D;
		bool DSP_ELEMENTS_MASS;
		bool DSP_ELEMENTS_1D;
		bool DSP_ELEMENTS_ROD;
		bool DSP_ELEMENTS_BEAM;
		bool DSP_ELEMENTS_TRANSLATIONALSPRING;
		bool DSP_ELEMENTS_ROTATIONALSPRING;
		bool DSP_ELEMENTS_RIGID;
		bool DSP_ELEMENTS_BUSH;
		bool DSP_ELEMENTS_2D;
		bool DSP_ELEMENTS_TRI;
		bool DSP_ELEMENTS_QUAD;
		bool DSP_ELEMENTS_3D;
		bool DSP_ELEMENTS_TET;
		bool DSP_ELEMENTS_WEDGE;
		bool DSP_ELEMENTS_BRICK;

		bool DSP_NODESSQUAREASTERISK;
		bool DSP_ELEMENTOFFSETS;
		bool DSP_SURFACECURVES;
		bool DSP_BLACKWHITE;
		bool DSP_ASSEMBLIES;
		bool DSP_CONTOURRAWRESULTS;
		bool DSP_RESULTSLABLES;
		bool DSP_DEFORMEDRESULTS;
		bool DSP_MATERIALDIRECTION;
		bool DSP_ANIMATERESULTS;
		bool DSP_ANIMATEPOSITIVENEGATIVE;
		bool DSP_VECTORS;
};
extern DisplayFlags DspFlagsMain;
// momo change Display Flags Method
// momo save by old versions
extern int FileFormatIndex;
extern bool ResetVariables;
// momo save by old versions
// momo close for LNC
extern CPoint m_PointOld; // old move point
extern CPoint m_PointNew; // new move point
// momo close for LNC
// momo random color change bug
extern bool bUseDoubleBuffer;
// momo random color change bug
// momo
extern double Pi;
extern CString SolutionTypeNames[6];
extern int SolutionTypeNumbers[6];
extern bool TemporaryChangeFlagCleared;
extern CString sSpliter;
extern CString DataPath;
extern CString ModelFileName;
extern bool ModelFileNameChanged;
extern bool DatFileOverwritePrompt;
extern CString TextViewerExe;
// momo
extern BOOL gDSP_BACK;
extern BOOL gORTHO;
extern DSP_Triad tOrient;
extern int iNoSymbols;
extern double dAveW;
extern double dAveH;
extern Symbol* pSymTable[10000];
extern int gDIM_PREC;
extern double gDIM_SIZE;
extern int gCUR_RES;
extern double gDRILL_KS; // K value for shell drilling
extern double gRIGID_MULTIPLIER; // multiplier to factor psuedo rigid elemenys K values
extern double gVSTIFF_KS;
extern double gDEF_E;
extern double gDEF_V;
extern double gDEF_DEN;
extern double gDEF_COND;
extern double gSTIFF_BDIA;
extern double gDEF_CTE;
extern double gDEF_THERM_LNK;
extern double gDEF_SOL_TOL;
extern PropTable* PropsT;
extern MatTable* MatT;

// Esp_Mod_Labels_4_27_2025_Start: Added global var for label display
extern bool gLBL_DSP_TRG;
// Esp_Mod_Labels_4_27_2025_End