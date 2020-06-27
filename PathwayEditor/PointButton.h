#pragma once
#include "Pathway_class_lite.h"

struct Frame;
struct Button : public wxButton {
	// for mouse drag
	wxWindow* parent = nullptr;
	bool dragging = false;
	wxPoint lastMP;

	// for logic
	Pathway::Point pos;
	Frame* frame = nullptr;

	Button(Frame* const& frame, Pathway::Point const& pos);

	void OnMouseRightDown(wxMouseEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseMiddleDown(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);

	DECLARE_EVENT_TABLE()
};

