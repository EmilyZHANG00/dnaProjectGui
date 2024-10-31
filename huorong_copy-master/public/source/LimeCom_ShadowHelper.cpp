#include "LimeCom_ShadowHelper.h"

LimeCom_ShadowHelper::LimeCom_ShadowHelper()
	: dwmapi_dll_(LoadLibraryW(L"dwmapi.dll"))
	, dwm_is_composition_enabled_(NULL) {
	if (dwmapi_dll_) {
		dwm_is_composition_enabled_ = \
			reinterpret_cast<DwmIsCompositionEnabledPtr>(GetProcAddress(dwmapi_dll_, "DwmIsCompositionEnabled"));
		dwm_extendframe_into_client_area_ = \
			reinterpret_cast<DwmExtendFrameIntoClientAreaPtr>(GetProcAddress(dwmapi_dll_, "DwmExtendFrameIntoClientArea"));
	}
}

LimeCom_ShadowHelper::~LimeCom_ShadowHelper() {
	if (dwmapi_dll_)
		FreeLibrary(dwmapi_dll_);
}

HRESULT LimeCom_ShadowHelper::DwmIsCompositionEnabled(BOOL* pfEnabled) const {
	if (dwm_is_composition_enabled_)
		return dwm_is_composition_enabled_(pfEnabled);
	return E_NOTIMPL;
}

HRESULT LimeCom_ShadowHelper::DwmExtendFrameIntoClientArea(HWND hWnd, const MARGINS* pMarInset) const {
	if (dwm_extendframe_into_client_area_)
		return dwm_extendframe_into_client_area_(hWnd, pMarInset);
	return E_NOTIMPL;
}

const LimeCom_ShadowHelper* LimeCom_ShadowHelper::instance() {
	static const LimeCom_ShadowHelper s_dwmapi;
	return &s_dwmapi;
}
