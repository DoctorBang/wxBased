#include "pch.h"
#include "BasedWindow.h"
#include "App.h"

wxIMPLEMENT_APP(BasedApp);

bool BasedApp::OnInit() {
    wxInitAllImageHandlers();
    BasedWindow* bsd = new BasedWindow();
    bsd->Show(true);
    return true;
}