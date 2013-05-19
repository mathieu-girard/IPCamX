// IPCamXPropPage.cpp : implémentation de la classe de la page de propriétés CIPCamXPropPage.

#include "stdafx.h"
#include "IPCamX.h"
#include "IPCamXPropPage.h"
#include "IPCamXCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CIPCamXPropPage, COlePropertyPage)



// Table des messages

BEGIN_MESSAGE_MAP(CIPCamXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialisation de la fabrique de classe et du guid

IMPLEMENT_OLECREATE_EX(CIPCamXPropPage, "IPCAMX.IPCamXPropPage.1",
	0xd5a09ac1, 0xdadb, 0x4fdb, 0x9f, 0xb1, 0xbd, 0xcd, 0x9, 0xbd, 0x3c, 0xf4)



// CIPCamXPropPage::CIPCamXPropPageFactory::UpdateRegistry -
// Ajoute ou supprime des entrées de la base de registres pour CIPCamXPropPage

BOOL CIPCamXPropPage::CIPCamXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_IPCAMX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CIPCamXPropPage::CIPCamXPropPage - Constructeur

CIPCamXPropPage::CIPCamXPropPage() :
	COlePropertyPage(IDD, IDS_IPCAMX_PPG_CAPTION)
	{
}



// CIPCamXPropPage::DoDataExchange - Transfère les données entre la page et les propriétés

void CIPCamXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// Gestionnaires de messages de CIPCamXPropPage
