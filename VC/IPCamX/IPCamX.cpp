// IPCamX.cpp : implémentation de CIPCamXApp et inscription de DLL.

#include "stdafx.h"
#include "IPCamX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CIPCamXApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x76653516, 0x8B43, 0x46EF, { 0x87, 0xB, 0xED, 0xD2, 0xB1, 0xD, 0x60, 0x7 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CIPCamXApp::InitInstance - Initialisation de la DLL

BOOL CIPCamXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO : ajoutez ici votre propre code d'initialisation de module.
	}

	return bInit;
}



// CIPCamXApp::ExitInstance - Fin de la DLL

int CIPCamXApp::ExitInstance()
{
	// TODO : ajoutez ici votre propre code d'arrêt de module.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Ajoute des entrées à la base de registres

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Supprime les entrées de la base de registres

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
