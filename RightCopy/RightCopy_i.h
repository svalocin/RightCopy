

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Aug 19 21:07:55 2014
 */
/* Compiler settings for RightCopy.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __RightCopy_i_h__
#define __RightCopy_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IRightContextMenu_FWD_DEFINED__
#define __IRightContextMenu_FWD_DEFINED__
typedef interface IRightContextMenu IRightContextMenu;
#endif 	/* __IRightContextMenu_FWD_DEFINED__ */


#ifndef __RightContextMenu_FWD_DEFINED__
#define __RightContextMenu_FWD_DEFINED__

#ifdef __cplusplus
typedef class RightContextMenu RightContextMenu;
#else
typedef struct RightContextMenu RightContextMenu;
#endif /* __cplusplus */

#endif 	/* __RightContextMenu_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IRightContextMenu_INTERFACE_DEFINED__
#define __IRightContextMenu_INTERFACE_DEFINED__

/* interface IRightContextMenu */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRightContextMenu;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DA6660DA-2A57-46C0-982F-12F48E690D9F")
    IRightContextMenu : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RCM( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRightContextMenuVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRightContextMenu * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRightContextMenu * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRightContextMenu * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRightContextMenu * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRightContextMenu * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRightContextMenu * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRightContextMenu * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RCM )( 
            IRightContextMenu * This);
        
        END_INTERFACE
    } IRightContextMenuVtbl;

    interface IRightContextMenu
    {
        CONST_VTBL struct IRightContextMenuVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRightContextMenu_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRightContextMenu_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRightContextMenu_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRightContextMenu_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRightContextMenu_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRightContextMenu_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRightContextMenu_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRightContextMenu_RCM(This)	\
    ( (This)->lpVtbl -> RCM(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRightContextMenu_INTERFACE_DEFINED__ */



#ifndef __RightCopyLib_LIBRARY_DEFINED__
#define __RightCopyLib_LIBRARY_DEFINED__

/* library RightCopyLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_RightCopyLib;

EXTERN_C const CLSID CLSID_RightContextMenu;

#ifdef __cplusplus

class DECLSPEC_UUID("46DB5DB8-BD44-4AF4-853A-7428B04E7CBA")
RightContextMenu;
#endif
#endif /* __RightCopyLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


