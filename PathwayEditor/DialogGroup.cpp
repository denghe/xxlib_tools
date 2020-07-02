#include "DialogGroup.h"

DialogGroup::DialogGroup(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	sizerRoot = new wxBoxSizer(wxHORIZONTAL);

	sizerGroups = new wxBoxSizer(wxVERTICAL);

	m_staticText10 = new wxStaticText(this, wxID_ANY, wxT("groups"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText10->Wrap(-1);
	sizerGroups->Add(m_staticText10, 0, wxALL, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	buttonNewGroup = new wxButton(this, wxID_ANY, wxT("NewGroup"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(buttonNewGroup, 0, wxALL, 5);

	buttonDelete = new wxButton(this, wxID_ANY, wxT("DeleteSeleted"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(buttonDelete, 0, wxALL, 5);


	sizerGroups->Add(bSizer5, 0, wxEXPAND, 5);

	gridGroups = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	gridGroups->CreateGrid(55, 1);
	gridGroups->EnableEditing(true);
	gridGroups->EnableGridLines(true);
	gridGroups->EnableDragGridSize(false);
	gridGroups->SetMargins(0, 0);

	// Columns
	gridGroups->SetColSize(0, 358);
	gridGroups->EnableDragColMove(false);
	gridGroups->EnableDragColSize(false);
	gridGroups->SetColLabelSize(22);
	gridGroups->SetColLabelValue(0, wxT("group name"));
	gridGroups->SetColLabelAlignment(wxALIGN_LEFT, wxALIGN_CENTER);

	// Rows
	gridGroups->EnableDragRowSize(false);
	gridGroups->SetRowLabelSize(25);
	gridGroups->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	gridGroups->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	gridGroups->SetMinSize(wxSize(400, -1));

	sizerGroups->Add(gridGroups, 1, wxALL | wxEXPAND, 5);


	sizerRoot->Add(sizerGroups, 1, wxEXPAND, 5);

	sizerLines = new wxBoxSizer(wxVERTICAL);

	m_staticText101 = new wxStaticText(this, wxID_ANY, wxT("all lines"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText101->Wrap(-1);
	sizerLines->Add(m_staticText101, 0, wxALL, 5);

	gridLines = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	gridLines->CreateGrid(55, 2);
	gridLines->EnableEditing(true);
	gridLines->EnableGridLines(true);
	gridLines->EnableDragGridSize(false);
	gridLines->SetMargins(0, 0);

	// Columns
	gridLines->SetColSize(0, 22);
	gridLines->SetColSize(1, 325);
	gridLines->EnableDragColMove(false);
	gridLines->EnableDragColSize(false);
	gridLines->SetColLabelSize(22);
	gridLines->SetColLabelValue(0, wxEmptyString);
	gridLines->SetColLabelValue(1, wxT("line name"));
	gridLines->SetColLabelAlignment(wxALIGN_LEFT, wxALIGN_CENTER);

	// Rows
	gridLines->EnableDragRowSize(false);
	gridLines->SetRowLabelSize(25);
	gridLines->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	gridLines->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	gridLines->SetMinSize(wxSize(400, -1));

	sizerLines->Add(gridLines, 0, wxALL, 5);


	sizerRoot->Add(sizerLines, 1, wxEXPAND, 5);


	this->SetSizer(sizerRoot);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	buttonNewGroup->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogGroup::buttonNewGroupOnButtonClick), NULL, this);
	buttonDelete->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogGroup::buttonDeleteOnButtonClick), NULL, this);
	gridGroups->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(DialogGroup::gridGroupsOnGridCellChange), NULL, this);
	gridGroups->Connect(wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler(DialogGroup::gridGroupsOnGridRangeSelect), NULL, this);
	gridGroups->Connect(wxEVT_GRID_SELECT_CELL, wxGridEventHandler(DialogGroup::gridGroupsOnGridSelectCell), NULL, this);
	gridLines->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(DialogGroup::gridLinesOnGridCellChange), NULL, this);
	gridLines->Connect(wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler(DialogGroup::gridLinesOnGridRangeSelect), NULL, this);
	gridLines->Connect(wxEVT_GRID_SELECT_CELL, wxGridEventHandler(DialogGroup::gridLinesOnGridSelectCell), NULL, this);
}

DialogGroup::~DialogGroup()
{
	// Disconnect Events
	buttonNewGroup->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogGroup::buttonNewGroupOnButtonClick), NULL, this);
	buttonDelete->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogGroup::buttonDeleteOnButtonClick), NULL, this);
	gridGroups->Disconnect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(DialogGroup::gridGroupsOnGridCellChange), NULL, this);
	gridGroups->Disconnect(wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler(DialogGroup::gridGroupsOnGridRangeSelect), NULL, this);
	gridGroups->Disconnect(wxEVT_GRID_SELECT_CELL, wxGridEventHandler(DialogGroup::gridGroupsOnGridSelectCell), NULL, this);
	gridLines->Disconnect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(DialogGroup::gridLinesOnGridCellChange), NULL, this);
	gridLines->Disconnect(wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler(DialogGroup::gridLinesOnGridRangeSelect), NULL, this);
	gridLines->Disconnect(wxEVT_GRID_SELECT_CELL, wxGridEventHandler(DialogGroup::gridLinesOnGridSelectCell), NULL, this);

}
