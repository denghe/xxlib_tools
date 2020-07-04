#include "MyDialogGroup.h"
#include "GridHelpers.hpp"
#include "Frame.h"

MyDialogGroup::MyDialogGroup(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: DialogGroup(parent, id, title, pos, size, style)
	, frame((Frame*)parent) {
	GridHelpers::InitGroupLines(gridGroups, gridLines);
	//frame->data
	
	// todo: fill data
}
