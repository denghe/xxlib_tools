#pragma once
#include "DialogGroup.h"

struct Frame;
struct MyDialogGroup : public DialogGroup {
	Frame* frame = nullptr;
	MyDialogGroup(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("group & lines bind"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(827, 722), long style = wxDEFAULT_DIALOG_STYLE);
};
