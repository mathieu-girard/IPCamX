

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Aug 08 19:19:06 2012
 */
/* Compiler settings for .\IPCamX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __IPCamXidl_h__
#define __IPCamXidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DIPCamX_FWD_DEFINED__
#define ___DIPCamX_FWD_DEFINED__
typedef interface _DIPCamX _DIPCamX;
#endif 	/* ___DIPCamX_FWD_DEFINED__ */


#ifndef ___DIPCamXEvents_FWD_DEFINED__
#define ___DIPCamXEvents_FWD_DEFINED__
typedef interface _DIPCamXEvents _DIPCamXEvents;
#endif 	/* ___DIPCamXEvents_FWD_DEFINED__ */


#ifndef __IPCamX_FWD_DEFINED__
#define __IPCamX_FWD_DEFINED__

#ifdef __cplusplus
typedef class IPCamX IPCamX;
#else
typedef struct IPCamX IPCamX;
#endif /* __cplusplus */

#endif 	/* __IPCamX_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __IPCamXLib_LIBRARY_DEFINED__
#define __IPCamXLib_LIBRARY_DEFINED__

/* library IPCamXLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_IPCamXLib;

#ifndef ___DIPCamX_DISPINTERFACE_DEFINED__
#define ___DIPCamX_DISPINTERFACE_DEFINED__

/* dispinterface _DIPCamX */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DIPCamX;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("45D7D8C8-E87B-4799-9E4B-4AB504E64F8E")
    _DIPCamX : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DIPCamXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DIPCamX * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DIPCamX * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DIPCamX * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DIPCamX * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DIPCamX * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DIPCamX * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DIPCamX * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DIPCamXVtbl;

    interface _DIPCamX
    {
        CONST_VTBL struct _DIPCamXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DIPCamX_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DIPCamX_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DIPCamX_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DIPCamX_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DIPCamX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DIPCamX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DIPCamX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DIPCamX_DISPINTERFACE_DEFINED__ */


#ifndef ___DIPCamXEvents_DISPINTERFACE_DEFINED__
#define ___DIPCamXEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DIPCamXEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DIPCamXEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9D08856C-694B-4170-9FD4-41BF7612A99C")
    _DIPCamXEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DIPCamXEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DIPCamXEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DIPCamXEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DIPCamXEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DIPCamXEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DIPCamXEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DIPCamXEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DIPCamXEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DIPCamXEventsVtbl;

    interface _DIPCamXEvents
    {
        CONST_VTBL struct _DIPCamXEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DIPCamXEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DIPCamXEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DIPCamXEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DIPCamXEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DIPCamXEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DIPCamXEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DIPCamXEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DIPCamXEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_IPCamX;

#ifdef __cplusplus

class DECLSPEC_UUID("E9FBB53F-3373-4568-A7D3-D0E160EAF912")
IPCamX;
#endif
#endif /* __IPCamXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


