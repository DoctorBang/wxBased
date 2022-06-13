#include "pch.h"
#include "BasedWindow.h"

constexpr wxWindowID ID_RESULT = 900;

BasedWindow::BasedWindow() 
    : wxFrame(NULL, wxID_ANY, "Based")
    , m_scores{ 0 }
    , m_but{ nullptr }
    , m_butState{ false }
    , m_board{ "bingo_politics.png", wxBITMAP_TYPE_PNG }

{
    InitMenu();
    ParseBingo(m_board);
    wxFlexGridSizer* fgs = new wxFlexGridSizer(18, 17, 0, 0);
    int id = 0;
    for(int i = 0; i < 17; ++i) {
        for(int j = 0; j < 17; ++j) {
            m_but[i][j] = new wxBitmapButton(this, id++, m_bitmaps[i][j]);
            fgs->Add(m_but[i][j], 1, wxEXPAND | wxALL, 0);
            Bind(wxEVT_BUTTON, &BasedWindow::OnPress, this, id - 1);
        }
    }
    fgs->Add(new wxButton(this, ID_RESULT, "Get score"));
    SetSizer(fgs);
    Fit();
    Center();
}

void BasedWindow::ParseBingo(wxImage& img) {
    double width  = double(img.GetWidth())   / 17.0;
    double height = double(img.GetHeight()) / 17.0;
    for(int i = 1; i <= 17; ++i) {
        for(int j = 1; j <= 17; ++j) {
            auto sub = img.GetSubImage(
                {
                    wxPoint{int((j-1) * width), int((i-1) * height)},
                    wxPoint{int(j * width), int(i * height)}, 
                });
            sub.Rescale(100, 100, wxIMAGE_QUALITY_HIGH);
            m_bitmaps[i-1][j-1] = sub;
        }
    }
}

constexpr inline static std::array<std::array<int,17>,17> scores{ 
    {
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1,  2,  2, -1,  2,  2,  1,  0,  2,  2, -1 },
        { -1, -1, -1, -1, -1, -1,  2,  1,  2,  2,  2,  2,  2,  2,  2, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1,  2,  2, -1,  2, -1,  1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1,  2,  2,  1,  2,  2,  2,  2,  2, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1,  2,  1,  2, -1,  2,  2,  2,  1, -1 },
        { -1, -1, -1,  2, -1, -1, -1, -1,  0,  2,  2,  2,  1,  1,  2,  1, -1 },
        { -1, -1, -1, -1, -1, -1, -1,  2,  2,  2,  2,  1, -1,  2,  1,  2, -1 },
        { -1, -1, -1,  2, -1,  2,  2,  0,  0,  0,  1,  2,  2,  2,  1,  1, -1 },
        { -1, -1, -1, -1, -1, -1,  1, -1,  0,  2,  0,  1,  2,  1,  2, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,  1,  1,  2, -1,  2,  2, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1, -1,  2, -1,  1,  1, -1,  1, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1,  2,  2,  1,  1, -1,  1,  0, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  1, -1, -1,  1,  1, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1, -1,  2, -1,  1,  1, -1, -1,  2, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } 
    }
};

constexpr static int GetSum() {
    int sum = 0;
    for(auto& arr : scores) {
        for(auto& val : arr) {
            if(val > 0) {
                sum += val;
            }
        }
    }
    return sum;
}

void BasedWindow::OnPress(wxCommandEvent& event) {
    auto id = event.GetId();
    auto ind1 = id / 17;
    auto ind2 = id % 17;
    if(!m_butState[ind1][ind2]) {
        m_scores += scores[ind1][ind2];
        m_but[ind1][ind2]->SetBitmap(
            m_bitmaps[ind1][ind2].Scale(75, 75, wxIMAGE_QUALITY_HIGH)
        );
    } else {
        m_scores -= scores[ind1][ind2];
        m_but[ind1][ind2]->SetBitmap(m_bitmaps[ind1][ind2]);
    }
    m_butState[ind1][ind2] = !m_butState[ind1][ind2];
}

void BasedWindow::OnGetResult(wxCommandEvent& event) {
    wxString disp = wxString::Format(
        "Your based score is: %d / %d",
        m_scores, GetSum()    
    );
    wxMessageBox(disp, "Results");
}

void BasedWindow::InitMenu() {
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(wxID_EXIT);

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("How based are you?");

    Bind(wxEVT_MENU, [&](wxCommandEvent&) { Close(true); });
}

BEGIN_EVENT_TABLE(BasedWindow, wxFrame)
    EVT_BUTTON(ID_RESULT, BasedWindow::OnGetResult)
END_EVENT_TABLE()