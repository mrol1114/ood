#pragma once

#include <wx/wx.h>

#include "./lib/view/CPictureView.h"
#include "./lib/controller/CPictureController.h"

class App : public wxApp {
public:
    bool OnInit() {
        CPictureView* mainFrame = new CPictureView("Graphics", wxDefaultPosition, wxSize(660, 590));
        mainFrame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);