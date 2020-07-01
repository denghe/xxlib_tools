#pragma once
#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/grid.h>

class DialogGroup : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText10;
		wxButton* buttonNewGroup;
		wxButton* buttonDelete;
		wxStaticText* m_staticText101;

		// Virtual event handlers, overide them in your derived class
		virtual void buttonNewGroupOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void buttonDeleteOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void gridGroupsOnGridCellChange( wxGridEvent& event ) { event.Skip(); }
		virtual void gridGroupsOnGridRangeSelect( wxGridRangeSelectEvent& event ) { event.Skip(); }
		virtual void gridGroupsOnGridSelectCell( wxGridEvent& event ) { event.Skip(); }
		virtual void gridLinesOnGridCellChange( wxGridEvent& event ) { event.Skip(); }
		virtual void gridLinesOnGridRangeSelect( wxGridRangeSelectEvent& event ) { event.Skip(); }
		virtual void gridLinesOnGridSelectCell( wxGridEvent& event ) { event.Skip(); }


	public:
		wxBoxSizer* sizerRoot;
		wxBoxSizer* sizerGroups;
		wxGrid* gridGroups;
		wxBoxSizer* sizerLines;
		wxGrid* gridLines;

		DialogGroup( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("group & lines bind"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 827,722 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DialogGroup();

};
