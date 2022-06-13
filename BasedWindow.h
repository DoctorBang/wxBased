#ifndef BASED_H
#define BASED_H

class BasedWindow : public wxFrame {
private:
    std::array<std::array<wxBitmapButton*, 17>, 17> m_but;
    std::array<std::array<bool, 17>, 17>            m_butState;
    std::array<std::array<wxImage, 17>, 17>         m_bitmaps;
    int m_scores;
    wxImage m_board;

public:
    BasedWindow();

private:
    void ParseBingo(wxImage&);
    void OnPress(wxCommandEvent&);
    void OnGetResult(wxCommandEvent&);
    void InitMenu();
    DECLARE_EVENT_TABLE();
};

#endif // BASED_h