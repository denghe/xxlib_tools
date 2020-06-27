#pragma once
#include "Frame.h"


class MyApp : public wxApp
{
public:
	virtual bool OnInit() {
		auto frame = new Frame(nullptr, wxID_ANY, L"mouse click to draw a point!");
		frame->Show(true);
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);
