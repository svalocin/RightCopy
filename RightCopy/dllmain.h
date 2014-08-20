// dllmain.h : 模块类的声明。

class CRightCopyModule : public ATL::CAtlDllModuleT< CRightCopyModule >
{
public :
	DECLARE_LIBID(LIBID_RightCopyLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_RIGHTCOPY, "{4B4637D6-098A-4CEF-93D4-43C76EAE9F45}")
};

extern class CRightCopyModule _AtlModule;
