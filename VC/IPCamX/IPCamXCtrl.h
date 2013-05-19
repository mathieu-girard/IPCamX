#pragma once

// IPCamXCtrl.h : déclaration de la classe du contrôle ActiveX CIPCamXCtrl.
#include "windows.h"
//#include "opencv/cv.h"
#include "opencv/highgui.h"

#include <vlc/vlc.h>

enum ERROR_CODE { 
	EC_UNKNOWN		= -8000, 
	EC_TIMEOUT		= EC_UNKNOWN-1,
	EC_CREATEIMAGE	= EC_UNKNOWN-2,
	EC_POINTER		= EC_UNKNOWN-3,
	EC_LIBVLC		= EC_UNKNOWN-4,
	EC_MEMALLOC		= EC_UNKNOWN-5,
	EC_PLUGIN		= EC_UNKNOWN-6
};

// CIPCamXCtrl : consultez IPCamXCtrl.cpp pour l'implémentation.

class CIPCamXCtrl : public COleControl 
{
	DECLARE_DYNCREATE(CIPCamXCtrl)
// Thread
public:
	static UINT ThreadInitialization(LPVOID lpParameter);

// Constructeur
public:
	CIPCamXCtrl();

// Substitutions
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// Implémentation
protected:
	~CIPCamXCtrl();

	DECLARE_OLECREATE_EX(CIPCamXCtrl)    // Fabrique de classe et guid
	DECLARE_OLETYPELIB(CIPCamXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CIPCamXCtrl)     // ID de page de propriétés
	DECLARE_OLECTLTYPE(CIPCamXCtrl)		// Nom de type et état divers

// Tables des messages
	DECLARE_MESSAGE_MAP()

// Tables de dispatch
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Tables d'événements
	DECLARE_EVENT_MAP()

// ID de dispatch et d'événement
public:
	enum {
		dispidGetImageLabVIEW = 21L,
		dispidUnconfigure = 20L,
		dispidWait = 19,
		dispidConfigure = 18L,
		dispidIndex = 17,
		dispidTimeout = 16,
		dispidGetImageOpenCV = 15L,
		dispidUpdate = 13,
		dispidFPS = 12,
		dispidFinalize = 10L,
		dispidInitialize = 9L,
		dispidPlaying = 6,
		dispidSource = 5,
		dispidHeight = 3,
		dispidWidth = 2
	};
public:
	LONG Initialize(void);
	LONG Finalize(void);
	DOUBLE GetFPS(void);
	LONG GetWidth(void);
	LONG GetHeight(void);
	LONG GetImageOpenCV(void);
	LONG GetIndex(void);
	LONG Configure(LONG Timeout);
	VARIANT_BOOL GetPlaying(void);

	VARIANT_BOOL m_Update;
	DOUBLE m_FPS;
	LONG m_Index;

	void SetWait(VARIANT_BOOL Wait);
	VARIANT_BOOL GetWait(void);

	void SetUpdate(VARIANT_BOOL Wait);
	VARIANT_BOOL GetUpdate(void);

	void OnSourceChanged(void);

protected:
	LONG m_Timeout;
	LONG m_Width;
	LONG m_Height;

	VARIANT_BOOL m_Wait;
	VARIANT_BOOL m_Playing;

	CString m_Source;	


private:
	libvlc_instance_t*		m_libvlc;
	libvlc_media_t*			m_media;
	libvlc_media_player_t*	m_mp;

public:
	HANDLE			m_hEvNewFrame;
	HANDLE			m_hThInit;
	BITMAPINFO*		m_pBitmapInfo;

	CvCapture*		m_CvCapture;
	
	IplImage*		m_Image;
	IplImage*		m_ImageRGB32;

	CRITICAL_SECTION	m_CritSecImage;
	CRITICAL_SECTION	m_CritSecInit;

	BOOL			m_Ready;
	DWORD			m_TimeStart;
	DWORD			m_TimeEnd;
	int				m_FrameCount;
	void*			m_pBuffer;
	int				m_IndexLast;
	char			m_szSource[256];

	BOOL			m_StopThreadInit;
protected:
	LONG Unconfigure(void);
	LONG GetImageLabVIEW(LONG* pData);
};
