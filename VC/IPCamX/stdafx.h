#pragma once

// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclure les en-têtes Windows rarement utilisés
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // certains constructeurs CString seront explicites

#include <afxctl.h>         // Prise en charge MFC pour les contrôles ActiveX
#include <afxext.h>         // extensions MFC
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Prise en charge MFC pour les contrôles communs Internet Explorer 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // Prise en charge des MFC pour les contrôles communs Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

// Supprimez les deux includes ci-dessous si vous souhaitez utiliser les
//  classes de base de données MFC
#ifndef _WIN64

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // classes de base de données ODBC MFC
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // classes de base de données DAO MFC
#endif // _AFX_NO_DAO_SUPPORT

#endif // _WIN64

