// RightContextMenu.cpp : CRightContextMenu 的实现

#include "stdafx.h"
#include "Shlwapi.h"
#include "RightContextMenu.h"


// CRightContextMenu



STDMETHODIMP CRightContextMenu::RCM()
{
	// TODO:  在此添加实现代码

	return S_OK;
}

void CRightContextMenu::Clip(HWND hwnd, wstring wstr)
{
	// 打开并清空剪切板
	if (OpenClipboard(hwnd) && EmptyClipboard())
	{
		const wchar_t* wchar = wstr.c_str();

		//分配全局内存
		HGLOBAL clipBuffer;
		clipBuffer = GlobalAlloc(GMEM_DDESHARE, 2 * lstrlen(wchar) + sizeof(wchar_t));

		wchar_t * buffer;
		buffer = (wchar_t*)GlobalLock(clipBuffer);

		//拷贝数据到内存
		wcscpy(buffer, wstr.c_str());
		GlobalUnlock(clipBuffer);

		//设置数据到剪切板
		SetClipboardData(CF_UNICODETEXT, clipBuffer);

		//关闭剪切板
		CloseClipboard();
	}
}

void CRightContextMenu::ClipOperation(int type, HWND hwnd)
{
	wstring wstr;

	while (!queue_string.empty())
	{
		switch (type)
		{
		case CopyName:
			wstr.append(PathFindFileName(queue_string.front().c_str())); //获取文件名
			break;
		case CopyPath:
			wstr.append(queue_string.front());
			break;
		default:
			return;
			break;
		}
		wstr.append(_T(" "));
		queue_string.pop();
	}

	wstr.erase(wstr.size() - 1, 1);

	Clip(hwnd, wstr);
}

// IShellExtInit接口
HRESULT STDMETHODCALLTYPE CRightContextMenu::Initialize(
	/* [unique][in] */
	__in_opt  PCIDLIST_ABSOLUTE pidlFolder,
	/* [unique][in] */
	__in_opt  IDataObject *pdtobj,
	/* [unique][in] */
	__in_opt  HKEY hkeyProgID)
{
	HRESULT hr = E_FAIL;

	if (pdtobj != NULL)
	{
		FORMATETC fe = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
		STGMEDIUM stm;

		// pdtobj 指针指向对象
		if (SUCCEEDED(pdtobj->GetData(&fe, &stm)))
		{
			// 得到HDROP句柄
			HDROP hdrop = static_cast<HDROP>(GlobalLock(stm.hGlobal));

			if (hdrop != NULL)
			{
				// 获取选中的文件或目录数  
				UINT filesCount = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);

				// 枚举被选中的文件和目录
				if (filesCount > 0)
				{
					wchar_t filePath[MAX_PATH];

					for (UINT i = 0; i < filesCount; i++)
					{
						//取得下一个文件或目录的绝对路径
						if (0 != DragQueryFile(hdrop, i, filePath, ARRAYSIZE(filePath)))
						{
							queue_string.push(filePath);
						}
					}

					if (queue_string.size() > 0)
					{
						hr = S_OK;
					}
				}

				GlobalUnlock(stm.hGlobal);
			}

			ReleaseStgMedium(&stm);
		}
	}

	return hr;
}

// IContextMenu接口
HRESULT STDMETHODCALLTYPE CRightContextMenu::QueryContextMenu(
	/* [in] */
	__in  HMENU hmenu,
	/* [in] */
	__in  UINT indexMenu,
	/* [in] */
	__in  UINT idCmdFirst,
	/* [in] */
	__in  UINT idCmdLast,
	/* [in] */
	__in  UINT uFlags)
{
	// 如果 uFlags 参数包含 CMF_DEFAULTONLY，就什么都不要做
	if (uFlags & CMF_DEFAULTONLY)
	{
		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
	}

	// 使用InsertMenuItem添加菜单项
	UINT uID = idCmdFirst;

	MENUITEMINFO menu1 = { sizeof(menu1) };
	menu1.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	menu1.wID = uID++;
	menu1.fType = MFT_STRING;
	menu1.dwTypeData = _T("复制路径"); //支持Unicode编码
	menu1.fState = MFS_ENABLED;
	// InsertMenuItem添加菜单项
	if (!InsertMenuItem(hmenu, indexMenu, true, &menu1))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	MENUITEMINFO menu2 = { sizeof(menu2) };
	menu2.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	menu2.wID = uID++;
	menu2.fType = MFT_STRING;
	menu2.dwTypeData = _T("复制名称");
	menu2.fState = MFS_ENABLED;
	if (!InsertMenuItem(hmenu, indexMenu, true, &menu2))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// 返回一个HRESULT类型的值.
	// 该值为最大的命令标识符的偏移量
	return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, uID - idCmdFirst);
}

HRESULT STDMETHODCALLTYPE CRightContextMenu::InvokeCommand(
	/* [in] */
	__in  CMINVOKECOMMANDINFO *pici)
{
	if (!(HIWORD(((CMINVOKECOMMANDINFOEX *)pici)->lpVerbW)))
	{
		switch (LOWORD(pici->lpVerb))
		{
		case CopyName:
			ClipOperation(CopyName, pici->hwnd);
			break;
		case CopyPath:
			ClipOperation(CopyPath, pici->hwnd);
			break;
		default:
			return E_FAIL;
			break;
		}

		return S_OK;
	}

	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE CRightContextMenu::GetCommandString(
	/* [in] */
	__in  UINT_PTR idCmd,
	/* [in] */
	__in  UINT uType,
	/* [in] */
	__reserved  UINT *pReserved,
	/* [out] */
	__out_awcount(!(uType & GCS_UNICODE), cchMax)  LPSTR pszName,
	/* [in] */
	__in  UINT cchMax)
{
	return S_OK;
}