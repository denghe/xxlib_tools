#pragma once
#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/grid.h>

class FrameBase : public wxFrame
{
private:

protected:
	wxMenuBar* menubarRoot;
	wxMenu* menuFile;
	wxToolBar* toolBarRoot;
	wxToolBarToolBase* toolNewLine;

	// Virtual event handlers, overide them in your derived class
	virtual void menuItemNewOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void menuItemOpenOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void menuItemSaveOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void menuItemExitOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void toolNewLineOnToolClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void gridLinesOnGridCellChange(wxGridEvent& event) { event.Skip(); }
	virtual void gridLinesOnGridRangeSelect(wxGridRangeSelectEvent& event) { event.Skip(); }
	virtual void gridLinesOnGridSelectCell(wxGridEvent& event) { event.Skip(); }
	virtual void gridPointsOnGridCellChange(wxGridEvent& event) { event.Skip(); }
	virtual void gridPointsOnGridRangeSelect(wxGridRangeSelectEvent& event) { event.Skip(); }


public:
	wxGrid* gridLines;
	wxGrid* gridPoints;
	wxScrolledWindow* scrolledWindowPoints;

	FrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1008, 782), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	wxAuiManager m_mgr;

	~FrameBase();

};
