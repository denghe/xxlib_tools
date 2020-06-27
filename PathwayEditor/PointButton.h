#pragma once
#include "Pathway_class_lite.h"

struct Frame;
struct Button : public wxButton {
	Frame* frame = nullptr;
	int lineIndex = -1;
	int pointIndex = -1;

	// for mouse drag
	wxWindow* parent = nullptr;
	bool dragging = false;
	wxPoint lastMP;

	Button(Frame* const& frame, int const& lineIndex, int const& pointIndex);

	void OnMouseRightDown(wxMouseEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseMiddleDown(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);

	DECLARE_EVENT_TABLE()
};
