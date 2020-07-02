#include "FrameBase.h"

FrameBase::FrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(238, 255, 254));
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_DEFAULT | wxAUI_MGR_LIVE_RESIZE);

	menubarRoot = new wxMenuBar(0);
	menuFile = new wxMenu();
	wxMenuItem* menuItemNew;
	menuItemNew = new wxMenuItem(menuFile, wxID_ANY, wxString(wxT("&New")) + wxT('\t') + wxT("Ctrl + N"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemNew);

	wxMenuItem* menuItemOpen;
	menuItemOpen = new wxMenuItem(menuFile, wxID_ANY, wxString(wxT("&Open")) + wxT('\t') + wxT("Ctrl + O"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemOpen);

	wxMenuItem* menuItemSave;
	menuItemSave = new wxMenuItem(menuFile, wxID_ANY, wxString(wxT("&Save")) + wxT('\t') + wxT("Ctrl + S"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemSave);

	menuFile->AppendSeparator();

	wxMenuItem* menuItemExit;
	menuItemExit = new wxMenuItem(menuFile, wxID_ANY, wxString(wxT("&Exit")) + wxT('\t') + wxT("ALT + F4"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemExit);

	menubarRoot->Append(menuFile, wxT("&File"));

	this->SetMenuBar(menubarRoot);

	toolBarRoot = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORZ_TEXT);
	toolNewLine = toolBarRoot->AddTool(wxID_ANY, wxT("New Line"), wxBitmap(wxT("icon_add.bmp"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);

	toolGroupManage = toolBarRoot->AddTool(wxID_ANY, wxT("Group Manage"), wxBitmap(wxT("icon_add.bmp"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);

	toolBarRoot->Realize();
	m_mgr.AddPane(toolBarRoot, wxAuiPaneInfo().Left().CaptionVisible(false).CloseButton(false).PaneBorder(false).Movable(false).Dock().Fixed().BottomDockable(false).TopDockable(false).LeftDockable(false).RightDockable(false).Floatable(false));


	gridLines = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	gridLines->CreateGrid(55, 2);
	gridLines->EnableEditing(true);
	gridLines->EnableGridLines(true);
	gridLines->EnableDragGridSize(false);
	gridLines->SetMargins(0, 0);

	// Columns
	gridLines->SetColSize(0, 160);
	gridLines->SetColSize(1, 47);
	gridLines->EnableDragColMove(false);
	gridLines->EnableDragColSize(false);
	gridLines->SetColLabelSize(22);
	gridLines->SetColLabelValue(0, wxT("name"));
	gridLines->SetColLabelValue(1, wxT("isLoop"));
	gridLines->SetColLabelAlignment(wxALIGN_LEFT, wxALIGN_CENTER);

	// Rows
	gridLines->EnableDragRowSize(false);
	gridLines->SetRowLabelSize(25);
	gridLines->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	gridLines->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	m_mgr.AddPane(gridLines, wxAuiPaneInfo().Left().Caption(wxT("Lines")).CloseButton(false).Movable(false).Dock().Resizable().FloatingSize(wxDefaultSize).DockFixed(true).BottomDockable(false).TopDockable(false).LeftDockable(false).RightDockable(false).Floatable(false).MinSize(wxSize(250, 200)));

	gridPoints = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	gridPoints->CreateGrid(55, 5);
	gridPoints->EnableEditing(true);
	gridPoints->EnableGridLines(true);
	gridPoints->EnableDragGridSize(false);
	gridPoints->SetMargins(0, 0);

	// Columns
	gridPoints->SetColSize(0, 44);
	gridPoints->SetColSize(1, 44);
	gridPoints->SetColSize(2, 44);
	gridPoints->SetColSize(3, 39);
	gridPoints->SetColSize(4, 36);
	gridPoints->EnableDragColMove(false);
	gridPoints->EnableDragColSize(true);
	gridPoints->SetColLabelSize(22);
	gridPoints->SetColLabelValue(0, wxT("x"));
	gridPoints->SetColLabelValue(1, wxT("y"));
	gridPoints->SetColLabelValue(2, wxT("z"));
	gridPoints->SetColLabelValue(3, wxT("t"));
	gridPoints->SetColLabelValue(4, wxT("n"));
	gridPoints->SetColLabelAlignment(wxALIGN_LEFT, wxALIGN_CENTER);

	// Rows
	gridPoints->EnableDragRowSize(false);
	gridPoints->SetRowLabelSize(25);
	gridPoints->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	gridPoints->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	m_mgr.AddPane(gridPoints, wxAuiPaneInfo().Left().Caption(wxT("Points")).CloseButton(false).Movable(false).Dock().Resizable().FloatingSize(wxDefaultSize).DockFixed(true).BottomDockable(false).TopDockable(false).LeftDockable(false).RightDockable(false).Floatable(false).MinSize(wxSize(250, 200)));

	scrolledWindowPoints = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB | wxHSCROLL | wxVSCROLL);
	scrolledWindowPoints->SetScrollRate(5, 5);
	m_mgr.AddPane(scrolledWindowPoints, wxAuiPaneInfo().Center().Caption(wxT("Points( mouse draw area )")).CloseButton(false).PaneBorder(false).Movable(false).Dock().Resizable().FloatingSize(wxDefaultSize).BottomDockable(false).TopDockable(false).LeftDockable(false).RightDockable(false).Floatable(false));


	m_mgr.Update();
	this->Centre(wxBOTH);

	// Connect Events
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemNewOnMenuSelection), this, menuItemNew->GetId());
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemOpenOnMenuSelection), this, menuItemOpen->GetId());
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemSaveOnMenuSelection), this, menuItemSave->GetId());
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemExitOnMenuSelection), this, menuItemExit->GetId());
	this->Connect(toolNewLine->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(FrameBase::toolNewLineOnToolClicked));
	this->Connect(toolGroupManage->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(FrameBase::toolGroupManageOnToolClicked));
	gridLines->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(FrameBase::gridLinesOnGridCellChange), NULL, this);
	gridLines->Connect(wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler(FrameBase::gridLinesOnGridRangeSelect), NULL, this);
	gridLines->Connect(wxEVT_GRID_SELECT_CELL, wxGridEventHandler(FrameBase::gridLinesOnGridSelectCell), NULL, this);
	gridPoints->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(FrameBase::gridPointsOnGridCellChange), NULL, this);
	gridPoints->Connect(wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler(FrameBase::gridPointsOnGridRangeSelect), NULL, this);
}

FrameBase::~FrameBase()
{
	// Disconnect Events
	this->Disconnect(toolNewLine->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(FrameBase::toolNewLineOnToolClicked));
	this->Disconnect(toolGroupManage->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(FrameBase::toolGroupManageOnToolClicked));
	gridLines->Disconnect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(FrameBase::gridLinesOnGridCellChange), NULL, this);
	gridLines->Disconnect(wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler(FrameBase::gridLinesOnGridRangeSelect), NULL, this);
	gridLines->Disconnect(wxEVT_GRID_SELECT_CELL, wxGridEventHandler(FrameBase::gridLinesOnGridSelectCell), NULL, this);
	gridPoints->Disconnect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(FrameBase::gridPointsOnGridCellChange), NULL, this);
	gridPoints->Disconnect(wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler(FrameBase::gridPointsOnGridRangeSelect), NULL, this);

	m_mgr.UnInit();

}
