// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VISIOFORGE_VFP_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VISIOFORGE_VFP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
//#ifdef VISIOFORGE_VFP_EXPORTS
//#define VISIOFORGE_VFP_API __declspec(dllexport)
//#else
//#define VISIOFORGE_VFP_API __declspec(dllimport)
//#endif
//
//// This class is exported from the VisioForge_VFP.dll
//class VISIOFORGE_VFP_API CVisioForge_VFP {
//public:
//	CVisioForge_VFP(void);
//	// TODO: add your methods here.
//};
//
//extern VISIOFORGE_VFP_API int nVisioForge_VFP;
//
//VISIOFORGE_VFP_API int fnVisioForge_VFP(void);

#include <string>

#ifndef WIN32

#include <QtCore/qglobal.h>

#if defined(VISIOFORGE_VFP_QT_LIBRARY)
#  define VFP_EXPORT Q_DECL_EXPORT
#else
#  define VFP_EXPORT Q_DECL_IMPORT
#endif

#define VFP_EXPORT_CALL

#else

#define VFP_EXPORT __declspec(dllexport)
#define VFP_EXPORT_CALL __stdcall
#endif



extern "C" VFP_EXPORT void VFP_EXPORT_CALL VFPSetLicenseKey(wchar_t* licenseKey);
extern "C" VFP_EXPORT void VFP_EXPORT_CALL VFPSearch_Init(int count, void* pDataTmp);
extern "C" VFP_EXPORT void VFP_EXPORT_CALL VFPSearch_Clear(void* pDataTmp);
extern "C" VFP_EXPORT int VFP_EXPORT_CALL VFPSearch_Process(unsigned char* p, int w, int h, int s, double dTime, void* pDataTmp);
extern "C" VFP_EXPORT char* VFP_EXPORT_CALL VFPSearch_Build(int* pLen, void* pDataTmp);
extern "C" VFP_EXPORT int VFP_EXPORT_CALL VFPSearch_Search(const char* pData1, int iLen1, int iSkip1, const char* pData2, int iLen2, int iSkip2, double* pDiff, int maxDiff, void* pDataTmp);
extern "C" VFP_EXPORT void VFP_EXPORT_CALL VFPCompare_Init(int count, void* pDataTmp);
extern "C" VFP_EXPORT void VFP_EXPORT_CALL VFPCompare_Clear(void* pDataTmp);
extern "C" VFP_EXPORT int VFP_EXPORT_CALL VFPCompare_Process(unsigned char* p, int w, int h, int s, double dTime, void* pDataTmp);
extern "C" VFP_EXPORT char* VFP_EXPORT_CALL VFPCompare_Build(int* pLen, void* pDataTmp);
extern "C" VFP_EXPORT double VFP_EXPORT_CALL VFPCompare_Compare(const char* pData1, int iLen1, const char* pData2, int iLen2, int MaxS, void* pDataTmp);


