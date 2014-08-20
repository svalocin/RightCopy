// RightContextMenu.cpp : CRightContextMenu ��ʵ��

#include "stdafx.h"
#include "Shlwapi.h"
#include "RightContextMenu.h"


// CRightContextMenu



STDMETHODIMP CRightContextMenu::RCM()
{
	// TODO:  �ڴ����ʵ�ִ���

	return S_OK;
}

void CRightContextMenu::Clip(HWND hwnd, wstring wstr)
{
	// �򿪲���ռ��а�
	if (OpenClipboard(hwnd) && EmptyClipboard())
	{
		const wchar_t* wchar = wstr.c_str();

		//����ȫ���ڴ�
		HGLOBAL clipBuffer;
		clipBuffer = GlobalAlloc(GMEM_DDESHARE, 2 * lstrlen(wchar) + sizeof(wchar_t));

		wchar_t * buffer;
		buffer = (wchar_t*)GlobalLock(clipBuffer);

		//�������ݵ��ڴ�
		wcscpy(buffer, wstr.c_str());
		GlobalUnlock(clipBuffer);

		//�������ݵ����а�
		SetClipboardData(CF_UNICODETEXT, clipBuffer);

		//�رռ��а�
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
			wstr.append(PathFindFileName(queue_string.front().c_str())); //��ȡ�ļ���
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

// IShellExtInit�ӿ�
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

		// pdtobj ָ��ָ�����
		if (SUCCEEDED(pdtobj->GetData(&fe, &stm)))
		{
			// �õ�HDROP���
			HDROP hdrop = static_cast<HDROP>(GlobalLock(stm.hGlobal));

			if (hdrop != NULL)
			{
				// ��ȡѡ�е��ļ���Ŀ¼��  
				UINT filesCount = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);

				// ö�ٱ�ѡ�е��ļ���Ŀ¼
				if (filesCount > 0)
				{
					wchar_t filePath[MAX_PATH];

					for (UINT i = 0; i < filesCount; i++)
					{
						//ȡ����һ���ļ���Ŀ¼�ľ���·��
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

// IContextMenu�ӿ�
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
	// ��� uFlags �������� CMF_DEFAULTONLY����ʲô����Ҫ��
	if (uFlags & CMF_DEFAULTONLY)
	{
		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
	}

	// ʹ��InsertMenuItem��Ӳ˵���
	UINT uID = idCmdFirst;

	MENUITEMINFO menu1 = { sizeof(menu1) };
	menu1.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	menu1.wID = uID++;
	menu1.fType = MFT_STRING;
	menu1.dwTypeData = _T("����·��"); //֧��Unicode����
	menu1.fState = MFS_ENABLED;
	// InsertMenuItem��Ӳ˵���
	if (!InsertMenuItem(hmenu, indexMenu, true, &menu1))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	MENUITEMINFO menu2 = { sizeof(menu2) };
	menu2.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	menu2.wID = uID++;
	menu2.fType = MFT_STRING;
	menu2.dwTypeData = _T("��������");
	menu2.fState = MFS_ENABLED;
	if (!InsertMenuItem(hmenu, indexMenu, true, &menu2))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// ����һ��HRESULT���͵�ֵ.
	// ��ֵΪ���������ʶ����ƫ����
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