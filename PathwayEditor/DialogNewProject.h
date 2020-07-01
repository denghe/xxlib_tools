#pragma once
#include <wx/wx.h>

class DialogNewProject : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxTextCtrl* textCtrlWidth;
		wxStaticText* m_staticText21;
		wxTextCtrl* textCtrlHeight;
		wxStaticText* m_staticText211;
		wxTextCtrl* textCtrlSafeLength;
		wxButton* buttonSumbit;

		// Virtual event handlers, overide them in your derived class
		virtual void buttonSumbitOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		DialogNewProject( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("new project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DialogNewProject();

};
