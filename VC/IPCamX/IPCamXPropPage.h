#pragma once

// IPCamXPropPage.h : déclaration de la classe de page de propriétés CIPCamXPropPage.


// CIPCamXPropPage : consultez IPCamXPropPage.cpp pour l'implémentation.

class CIPCamXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CIPCamXPropPage)
	DECLARE_OLECREATE_EX(CIPCamXPropPage)

// Constructeur
public:
	CIPCamXPropPage();

// Données de boîte de dialogue
	enum { IDD = IDD_PROPPAGE_IPCAMX };

// Implémentation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Tables des messages
protected:
	DECLARE_MESSAGE_MAP()
public:
};

