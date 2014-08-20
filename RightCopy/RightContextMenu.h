// RightContextMenu.h : CRightContextMenu 的声明

#pragma once
#include "resource.h"       // 主符号
#include <queue>
#include <string>
#include "RightCopy_i.h"

#define CopyName 1
#define CopyPath 0

using std::wstring;


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CRightContextMenu

class ATL_NO_VTABLE CRightContextMenu :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRightContextMenu, &CLSID_RightContextMenu>,
	public IDispatchImpl<IRightContextMenu, &IID_IRightContextMenu, &LIBID_RightCopyLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
private:
	std::queue<wstring> queue_string;
	// 复制内容到剪切板
	void Clip(HWND, wstring);
	// 剪切操作函数，第一个参数为操作类型
	void ClipOperation(int, HWND);
public:
	CRightContextMenu()
	{
	}

	//----------------------------------------------------------------------------
	// IShellExtInit½Ó¿Ú
	HRESULT STDMETHODCALLTYPE Initialize(
		__in_opt  PCIDLIST_ABSOLUTE,
		__in_opt  IDataObject *,
		__in_opt  HKEY);

	// IContextMenu½Ó¿Ú
	HRESULT STDMETHODCALLTYPE QueryContextMenu(
		__in  HMENU,
		__in  UINT,
		__in  UINT,
		__in  UINT,
		__in  UINT);

	HRESULT STDMETHODCALLTYPE InvokeCommand(__in  CMINVOKECOMMANDINFO *);

	HRESULT STDMETHODCALLTYPE GetCommandString(
		__in  UINT_PTR,
		__in  UINT,
		__reserved  UINT *,
		__out_awcount(!(uType & GCS_UNICODE), cchMax)  LPSTR,
		__in  UINT);
	//----------------------------------------------------------------------------

DECLARE_REGISTRY_RESOURCEID(IDR_RIGHTCONTEXTMENU)


BEGIN_COM_MAP(CRightContextMenu)
	COM_INTERFACE_ENTRY(IRightContextMenu)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(RCM)();
};

OBJECT_ENTRY_AUTO(__uuidof(RightContextMenu), CRightContextMenu)
