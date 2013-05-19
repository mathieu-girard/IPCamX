// IPCamXCtrl.cpp : implémentation de la classe du contrôle ActiveX CIPCamXCtrl.

#include "stdafx.h"
#include "IPCamX.h"
#include "IPCamXCtrl.h"
#include "IPCamXPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CIPCamXCtrl, COleControl)



// Table des messages

BEGIN_MESSAGE_MAP(CIPCamXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// Table de dispatch

BEGIN_DISPATCH_MAP(CIPCamXCtrl, COleControl)
	DISP_FUNCTION_ID(CIPCamXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CIPCamXCtrl, "Width", dispidWidth, GetWidth, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX_ID(CIPCamXCtrl, "Height", dispidHeight, GetHeight, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX_ID(CIPCamXCtrl, "Playing", dispidPlaying, GetPlaying, SetNotSupported, VT_BOOL)
	DISP_FUNCTION_ID(CIPCamXCtrl, "Initialize", dispidInitialize, Initialize, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CIPCamXCtrl, "Finalize", dispidFinalize, Finalize, VT_I4, VTS_NONE)
	DISP_PROPERTY_EX_ID(CIPCamXCtrl, "FPS", dispidFPS, GetFPS, SetNotSupported, VT_R8)	
	DISP_FUNCTION_ID(CIPCamXCtrl, "GetImageOpenCV", dispidGetImageOpenCV, GetImageOpenCV, VT_I4, VTS_NONE)	
	DISP_PROPERTY_EX_ID(CIPCamXCtrl, "Index", dispidIndex, GetIndex, SetNotSupported, VT_I4)
	DISP_FUNCTION_ID(CIPCamXCtrl, "Configure", dispidConfigure, Configure, VT_I4, VTS_I4)
	DISP_PROPERTY_NOTIFY_ID(CIPCamXCtrl, "Source", dispidSource, m_Source, OnSourceChanged, VT_BSTR)	
	DISP_PROPERTY_EX_ID(CIPCamXCtrl, "Update", dispidUpdate, GetUpdate, SetUpdate, VT_BOOL)

	DISP_PROPERTY_ID(CIPCamXCtrl, "Timeout", dispidTimeout, m_Timeout, VT_I4)
	DISP_PROPERTY_EX_ID(CIPCamXCtrl, "Wait", dispidWait, GetWait, SetWait, VT_BOOL)
	DISP_FUNCTION_ID(CIPCamXCtrl, "Unconfigure", dispidUnconfigure, Unconfigure, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CIPCamXCtrl, "GetImageLabVIEW", dispidGetImageLabVIEW, GetImageLabVIEW, VT_I4, VTS_PI4)
END_DISPATCH_MAP()



// Table d'événements

BEGIN_EVENT_MAP(CIPCamXCtrl, COleControl)
END_EVENT_MAP()



// Pages de propriétés

// TODO : ajoutez autant de pages de propriétés que nécessaire. N'oubliez pas d'augmenter le compteur !
BEGIN_PROPPAGEIDS(CIPCamXCtrl, 1)
	PROPPAGEID(CIPCamXPropPage::guid)
END_PROPPAGEIDS(CIPCamXCtrl)



// Initialisation de la fabrique de classe et du guid

IMPLEMENT_OLECREATE_EX(CIPCamXCtrl, "IPCAMX.IPCamXCtrl.1",
	0xe9fbb53f, 0x3373, 0x4568, 0xa7, 0xd3, 0xd0, 0xe1, 0x60, 0xea, 0xf9, 0x12)



// ID et version de bibliothèque de types

IMPLEMENT_OLETYPELIB(CIPCamXCtrl, _tlid, _wVerMajor, _wVerMinor)



// ID d'interface

const IID BASED_CODE IID_DIPCamX =
		{ 0x45D7D8C8, 0xE87B, 0x4799, { 0x9E, 0x4B, 0x4A, 0xB5, 0x4, 0xE6, 0x4F, 0x8E } };
const IID BASED_CODE IID_DIPCamXEvents =
		{ 0x9D08856C, 0x694B, 0x4170, { 0x9F, 0xD4, 0x41, 0xBF, 0x76, 0x12, 0xA9, 0x9C } };



// Informations de type du contrôle

static const DWORD BASED_CODE _dwIPCamXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CIPCamXCtrl, IDS_IPCAMX, _dwIPCamXOleMisc)


void * lock(void *data, void **p_pixels)
{
	CIPCamXCtrl *IPCamXCtrl;
	IPCamXCtrl = static_cast<CIPCamXCtrl*>(data);//(CIPCamXCtrl *) data;
	
	if (IPCamXCtrl->m_Ready)
		*p_pixels = IPCamXCtrl->m_pBuffer;	
	else
		*p_pixels = NULL;
    return NULL;
}


void unlock(void *data, void *id, void *const *p_pixels)
{
	CIPCamXCtrl *IPCamXCtrl;
	IPCamXCtrl = static_cast<CIPCamXCtrl*>(data);

	if (IPCamXCtrl->m_Ready)
	{
		EnterCriticalSection(&(IPCamXCtrl->m_CritSecImage));
		memcpy(IPCamXCtrl->m_Image->imageData, *p_pixels, IPCamXCtrl->GetWidth() * IPCamXCtrl->GetHeight() * 3); 
		LeaveCriticalSection(&(IPCamXCtrl->m_CritSecImage));
		IPCamXCtrl->m_FrameCount++;
	}
}

void display(void *data, void *id)
{
	CIPCamXCtrl *IPCamXCtrl;
	IPCamXCtrl = static_cast<CIPCamXCtrl*>(data);
	
	if (IPCamXCtrl->m_Ready == TRUE)
	{
		IPCamXCtrl->m_TimeEnd = GetTickCount();
		//IPCamXCtrl->m_FrameCount++;
		IPCamXCtrl->m_Index++;
		IPCamXCtrl->m_FPS = IPCamXCtrl->m_FrameCount / ((IPCamXCtrl->m_TimeEnd - IPCamXCtrl->m_TimeStart) / 1000);

		// Set event
		if (IPCamXCtrl->m_Index > IPCamXCtrl->m_IndexLast)
			SetEvent(IPCamXCtrl->m_hEvNewFrame);
	}
	else
	{
		if ( (IPCamXCtrl->GetWidth() != 0) && (IPCamXCtrl->GetHeight() != 0) )
			IPCamXCtrl->m_FrameCount++;
	}	

	// If Update properties is set, we force the redrawn
	if (IPCamXCtrl->m_Update == VARIANT_TRUE)
		IPCamXCtrl->Invalidate();

}

// Thread d'Initialisation
UINT CIPCamXCtrl::ThreadInitialization(LPVOID lpParameter)
{	
	CIPCamXCtrl *IPCamXCtrl;
	IPCamXCtrl = static_cast<CIPCamXCtrl*>(lpParameter);

	const int eval_ms = 1000;

	// Init the media player and media
	IPCamXCtrl->m_media = NULL;
	IPCamXCtrl->m_mp = NULL;

    IPCamXCtrl->m_media = libvlc_media_new_path(IPCamXCtrl->m_libvlc, IPCamXCtrl->m_szSource);
    IPCamXCtrl->m_mp = libvlc_media_player_new_from_media(IPCamXCtrl->m_media);
    libvlc_media_release(IPCamXCtrl->m_media);

	libvlc_video_set_callbacks(IPCamXCtrl->m_mp, lock, unlock, display, IPCamXCtrl);	
    libvlc_media_player_play(IPCamXCtrl->m_mp);

    // try to find the size
	unsigned int size_x = 0;
	unsigned int size_y = 0;

	while((size_x == 0) || (size_y == 0)) 
	{
		libvlc_video_get_size(IPCamXCtrl->m_mp, 0, &size_x, &size_y);	
		if (IPCamXCtrl->m_StopThreadInit)
		{
			if (IPCamXCtrl->m_mp != NULL)
			{
				EnterCriticalSection(&(IPCamXCtrl->m_CritSecInit));				
				if (IPCamXCtrl->m_mp != NULL)
				{
					// stop and release mp
					libvlc_media_player_stop(IPCamXCtrl->m_mp);
					libvlc_media_player_release(IPCamXCtrl->m_mp);
					IPCamXCtrl->m_mp = NULL;
				}
				LeaveCriticalSection(&(IPCamXCtrl->m_CritSecInit));				
				return EC_TIMEOUT;
			}			
		}
    }

	// Copy size
	IPCamXCtrl->m_Width = (LONG) size_x;
	IPCamXCtrl->m_Height = (LONG) size_y;

	// Wait 1 sec and count how much frames we get (for estimating)
	IPCamXCtrl->m_TimeStart = GetTickCount();
	Sleep(eval_ms);
	 
	// Copy FPS
	IPCamXCtrl->m_FPS = (1000 * IPCamXCtrl->m_FrameCount) / ((double)eval_ms);

	// stop and release mp
    libvlc_media_player_stop(IPCamXCtrl->m_mp);
    libvlc_media_player_release(IPCamXCtrl->m_mp);
	IPCamXCtrl->m_mp = NULL;

	return 0;
} // ThreadInitialization

// CIPCamXCtrl::CIPCamXCtrlFactory::UpdateRegistry -
// Ajoute ou supprime les entrées de la base de registres pour CIPCamXCtrl

BOOL CIPCamXCtrl::CIPCamXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO : vérifiez que votre contrôle suit les règles du modèle de thread apartment.
	// Reportez-vous à MFC TechNote 64 pour plus d'informations.
	// Si votre contrôle ne se conforme pas aux règles du modèle apartment, vous
	// devez modifier le code ci-dessous, en modifiant le 6è paramètre de
	// afxRegApartmentThreading en 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_IPCAMX,
			IDB_IPCAMX,
			afxRegApartmentThreading,
			_dwIPCamXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CIPCamXCtrl::CIPCamXCtrl - Constructeur

CIPCamXCtrl::CIPCamXCtrl()
{
	InitializeIIDs(&IID_DIPCamX, &IID_DIPCamXEvents);

	SetThreadPriority(GetCurrentProcess(), THREAD_PRIORITY_HIGHEST);
	
	//
	InitializeCriticalSection(&m_CritSecImage);
	InitializeCriticalSection(&m_CritSecInit);

    // Build bitmap info RGB
    m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255*sizeof(RGBQUAD)];
    m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    m_pBitmapInfo->bmiHeader.biPlanes = 1;
    m_pBitmapInfo->bmiHeader.biBitCount = 24;
    m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
    m_pBitmapInfo->bmiHeader.biSizeImage = 0;
    m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
    m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
    m_pBitmapInfo->bmiHeader.biClrUsed = 0;
    m_pBitmapInfo->bmiHeader.biClrImportant = 0;
    for (int i = 0 ; i < 256 ; i++)
    {
        m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
        m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
        m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
        m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
    }
    m_pBitmapInfo->bmiHeader.biWidth = 0;
    m_pBitmapInfo->bmiHeader.biHeight = 0;	

	m_Index			= 0;
	m_IndexLast		= 0;
	m_Timeout		= 0;
	m_Width			= 0;
	m_Height		= 0;
	m_libvlc		= NULL;
	m_media			= NULL;
	m_mp			= NULL;
	m_hEvNewFrame	= NULL;
	m_hThInit		= NULL;
	m_CvCapture		= NULL;
	m_Image			= NULL;
	m_ImageRGB32	= NULL;
	m_Ready			= FALSE;
	m_TimeStart		= 0;
	m_TimeEnd		= 0;
	m_FrameCount	= 0;
	m_pBuffer		= 0;	
	*m_szSource		= NULL;
}

// CIPCamXCtrl::~CIPCamXCtrl - Destructeur

CIPCamXCtrl::~CIPCamXCtrl()
{
	DeleteCriticalSection(&m_CritSecImage);
	DeleteCriticalSection(&m_CritSecInit);
}


// CIPCamXCtrl::OnDraw - Fonction de dessin

void CIPCamXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	if ((m_Playing == VARIANT_TRUE) && (m_Update == VARIANT_TRUE))
	{
		EnterCriticalSection(&m_CritSecImage);
		if (m_Image != NULL)
		{
			pdc->SetStretchBltMode(HALFTONE);
			StretchDIBits(pdc->GetSafeHdc(), 
				0, 0, rcBounds.Width(), rcBounds.Height(), 
				0, 0, m_Width, m_Height,
				reinterpret_cast<void*>(m_Image->imageData), 
				m_pBitmapInfo, 
				DIB_RGB_COLORS, 
				SRCCOPY);
		}
		LeaveCriticalSection(&m_CritSecImage);
	}
	else
	{
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	}

	if (!IsOptimizedDraw())
	{
		// Le conteneur ne prend pas en charge le dessin optimisé.

		// TODO : si vous avez sélectionné un objet GDI quelconque dans le contexte de périphérique *pdc,
		//		restaurez ici les objets précédemment sélectionnés.
	}
}



// CIPCamXCtrl::DoPropExchange - Prise en charge de la persistance

void CIPCamXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	//COleControl::DoPropExchange(pPX);

	//PX_Long(pPX, TEXT("Live"), *((long*)(&m_Live)), (long)VARIANT_FALSE); // Bug of Death -.-'
	PX_String(pPX, TEXT("Source"), m_Source, TEXT(""));
}



// CIPCamXCtrl::GetControlFlags -
// Indicateurs permettant de personnaliser l'implémentation MFC des contrôles ActiveX.
//
DWORD CIPCamXCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();

	dwFlags |= noFlickerActivate;
	dwFlags |= canOptimizeDraw;

	return dwFlags;
}

// CIPCamXCtrl::OnResetState - Réinitialise le contrôle à son état par défaut

void CIPCamXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Réinitialise les valeurs par défaut trouvées dans DoPropExchange

	m_Source = "";
	m_Playing = VARIANT_FALSE;
	m_Update = VARIANT_FALSE;
	m_Width = 0;
	m_Height = 0;
	m_FPS = 0;
}


// CIPCamXCtrl::AboutBox - Affiche une boîte de dialogue "À propos de" à l'utilisateur

void CIPCamXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_IPCAMX);
	dlgAbout.DoModal();
}

LONG CIPCamXCtrl::GetWidth(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_Width;
}

LONG CIPCamXCtrl::GetHeight(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_Height;
}

VARIANT_BOOL CIPCamXCtrl::GetPlaying(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_Playing;
}

DOUBLE CIPCamXCtrl::GetFPS(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_FPS;
}

LONG CIPCamXCtrl::GetIndex(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (LONG) m_Index;
}

LONG CIPCamXCtrl::Initialize(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	char *pValue	= NULL;
	size_t len		= 0;
	errno_t err		= 0;

	// Read the system variable
	err = _dupenv_s(&pValue, &len, "VLC_PLUGIN_PATH");
	if ((err == -1) || (len == 0) || (pValue == NULL))
	{
		free(pValue);
		return EC_PLUGIN;
	}
	else
	{		
		if (GetFileAttributesA(pValue) == INVALID_FILE_ATTRIBUTES)
		{
			free(pValue);	
			return EC_PLUGIN;
		}
	}

	// Set parameters to libVLC
    char const *vlc_argv[] = {
        "--no-audio", // Don't play audio.
        "--no-xlib", // Don't use Xlib.
		"--no-osd", // Don't use on-screen display
    };
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);

	// Initialise libVLC
	m_libvlc = libvlc_new(vlc_argc, vlc_argv);
	if(m_libvlc == NULL)
		return EC_LIBVLC;

	return 0;
}

LONG CIPCamXCtrl::Finalize(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	libvlc_release(m_libvlc);

	return 0;
}

LONG CIPCamXCtrl::GetImageOpenCV(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return (LONG)m_Image;
}

LONG CIPCamXCtrl::Configure(LONG Timeout)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	

	DWORD dwThread;

	m_Image = NULL;
	m_ImageRGB32 = NULL;
	m_Playing = VARIANT_FALSE;
	m_Ready = FALSE;
	m_Wait = VARIANT_TRUE;
	m_Update = VARIANT_TRUE;
	m_FrameCount = 0;
	m_Index = 0;
	m_IndexLast = 1;
	m_CvCapture = NULL;
	m_Width = 0;
	m_Height = 0;
	m_FPS = 0;	
	m_pBuffer = NULL;
	m_StopThreadInit = FALSE;

	// Create event for waiting for frame
	m_hEvNewFrame = CreateEvent(NULL, FALSE, FALSE, NULL);

	// Create the thread for determining size at least
	m_hThInit = CreateThread(NULL, (DWORD)NULL, (LPTHREAD_START_ROUTINE) ThreadInitialization, (LPVOID)this, (DWORD)NULL, &dwThread);
	if (GetLastError() != 0)
		return EC_UNKNOWN;

	if (WaitForSingleObject(m_hThInit, Timeout) == WAIT_TIMEOUT)
	{
		m_StopThreadInit = TRUE;
		//
		
		if (WaitForSingleObject(m_hThInit, 500) == WAIT_TIMEOUT)
		{
			// stop and release mp
			if (m_mp != NULL)
			{
				EnterCriticalSection(&m_CritSecInit);
				if (m_mp != NULL)
				{
					libvlc_media_player_stop(m_mp);
					libvlc_media_player_release(m_mp);
					m_mp = NULL;
				}
				LeaveCriticalSection(&m_CritSecInit);
			}
			TerminateThread(m_hThInit, FALSE);				
		}
		
		
		m_hThInit = NULL;
		return EC_TIMEOUT;
	}

	// Allocate the image buffer
	m_pBuffer = (void*) calloc(this->GetWidth() * this->GetHeight() * 3, sizeof(unsigned char));	
	if (m_pBuffer == NULL)
		return EC_MEMALLOC;
	
	// Real initialization
	m_media = libvlc_media_new_path(m_libvlc, m_szSource);
	m_mp = libvlc_media_player_new_from_media(m_media);

	libvlc_media_release(m_media);
	libvlc_video_set_callbacks(m_mp, lock, unlock, display, this);	
	libvlc_video_set_format(m_mp, "RV24", m_Width, m_Height, m_Width * 3);
	libvlc_media_player_play(m_mp);
	
	m_Playing = VARIANT_TRUE;
	m_Ready = TRUE;

	// Set the bitmap size
	m_pBitmapInfo->bmiHeader.biWidth = m_Width;
	m_pBitmapInfo->bmiHeader.biHeight = -m_Height;

	// Allocate the DC image
	m_Image = cvCreateImage(cvSize(m_Width, m_Height), IPL_DEPTH_8U, 3);
	if (m_Image == NULL)
		return EC_CREATEIMAGE;
	m_Image->align = 8;

	// Allocate the RGB32 ouput image
	m_ImageRGB32 = cvCreateImage(cvSize(m_Width, m_Height), IPL_DEPTH_8U, 4);
	if (m_ImageRGB32 == NULL)
		return EC_CREATEIMAGE;

	return 0;
}


VARIANT_BOOL CIPCamXCtrl::GetWait(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_Wait;
}

void CIPCamXCtrl::SetWait(VARIANT_BOOL Wait)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (Wait == VARIANT_FALSE)
		m_Wait = VARIANT_FALSE;
	else
		m_Wait = VARIANT_TRUE;

	SetModifiedFlag();
}

VARIANT_BOOL CIPCamXCtrl::GetUpdate(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_Update;
}

void CIPCamXCtrl::SetUpdate(VARIANT_BOOL Update)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (Update == VARIANT_FALSE)
		m_Update = VARIANT_FALSE;
	else
		m_Update = VARIANT_TRUE;

	SetModifiedFlag();
}

void CIPCamXCtrl::OnSourceChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Cast the source string
	wcstombs_s(NULL, m_szSource, 256 * sizeof(char), (wchar_t*) m_Source.GetString(), _TRUNCATE);

	SetModifiedFlag();
}
LONG CIPCamXCtrl::Unconfigure(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_Playing = VARIANT_FALSE;

	if (m_mp != NULL)
	{
		libvlc_media_player_stop(m_mp);	
		libvlc_media_player_release(m_mp);
		m_mp = NULL;
	}

	if (m_Image != NULL)
		cvReleaseImage(&m_Image);

	if (m_ImageRGB32 != NULL)
		cvReleaseImage(&m_ImageRGB32);

	if (m_pBuffer != NULL)
	{
		free(m_pBuffer);	
		m_pBuffer = NULL;
	}

	Invalidate();

	return 0;
}

LONG CIPCamXCtrl::GetImageLabVIEW(LONG* pData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Check pointers
	if ((m_Image == NULL) || (m_ImageRGB32 == NULL) || (libvlc_media_player_get_position(m_mp) == -1))
		return EC_POINTER;

	// Wait for a new buffer if needed
	if (m_Wait == VARIANT_TRUE)
	{
		if (WaitForSingleObject(m_hEvNewFrame, m_Timeout) == WAIT_TIMEOUT)			
			return EC_TIMEOUT;		
		else
			ResetEvent(m_hEvNewFrame);
	}

	EnterCriticalSection(&m_CritSecImage);
	// Normal copy from 24bit to 32bit
	RGBTRIPLE* pSrcPixRGB = (RGBTRIPLE*)m_Image->imageData;
	RGBQUAD* pDstPixRGBQ = (RGBQUAD*)m_ImageRGB32->imageData;

	for (int j=0; j<m_Height; j++)
	{
		pSrcPixRGB = (RGBTRIPLE*) (m_Image->imageData + j * m_Image->widthStep);
		pDstPixRGBQ = (RGBQUAD*) (m_ImageRGB32->imageData + j * m_ImageRGB32->widthStep);
		for (int i=0; i<m_Width; i++)
		{
			(*pDstPixRGBQ).rgbBlue = (*pSrcPixRGB).rgbtBlue;
			(*pDstPixRGBQ).rgbGreen = (*pSrcPixRGB).rgbtGreen;
			(*pDstPixRGBQ).rgbRed = (*pSrcPixRGB).rgbtRed;
			(*pDstPixRGBQ).rgbReserved = 0;
			pDstPixRGBQ++;
			pSrcPixRGB++;
		}
	}
	LeaveCriticalSection(&m_CritSecImage);

	*pData = (LONG) m_ImageRGB32->imageData;

	return 0;
}
