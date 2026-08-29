// =====
// Please Read:
// This code is using exdisp.h and oleauto.h
// You must add option to '-lole32 -loleaut32 -luuid'
// 
// Command:
//   ./run.bat "Call COM (Windows)" "-lole32 -loleaut32 -luuid"
// =====

#define COBJMACROS
#include <stdio.h>
#include <windows.h>
#include <exdisp.h>
#include <oleauto.h>

int main(void) {
    HRESULT hr;
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED); // init COM
    if (FAILED(hr)) {
        printf("CoInitializeEx failed: 0x%08lX\n", (unsigned long)hr);
        return 1;
    }
    
    IWebBrowser2 *ie = NULL;
    // call COM
    hr = CoCreateInstance(&CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER, &IID_IWebBrowser2, (void**)&ie);
    if (FAILED(hr)) {
        printf("CoCreateInstance failed: 0x%08lX\n", (unsigned long)hr);
        CoUninitialize();
        return 1;
    }

    IWebBrowser2_put_Visible(ie, VARIANT_TRUE); // Set Visible to True
    
    BSTR url = SysAllocString(L"https://badssl.com/"); // Alloc String
    VARIANT empty;
    VariantInit(&empty);
    IWebBrowser2_Navigate(ie, url, &empty, &empty, &empty, &empty); // Navigate
    SysFreeString(url); // Delete String from Memory

    printf("Any key to quit IE");
    system("pause > nul");
    printf("\n");

    IWebBrowser2_Quit(ie);
    IWebBrowser2_Release(ie);

    CoUninitialize();
}