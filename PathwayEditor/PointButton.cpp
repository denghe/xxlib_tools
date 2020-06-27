#pragma once
#include "Frame.h"
#include "PointButton.h"

BEGIN_EVENT_TABLE(Button, wxButton)
EVT_LEFT_DOWN(Button::OnMouseLeftDown)
EVT_LEFT_UP(Button::OnMouseLeftUp)
EVT_MIDDLE_DOWN(Button::OnMouseMiddleDown)
EVT_RIGHT_DOWN(Button::OnMouseRightDown)
EVT_MOTION(Button::OnMouseMove)
EVT_LEAVE_WINDOW(Button::OnMouseLeave)
END_EVENT_TABLE()

Button::Button(Frame* const& frame, Pathway::Point const& pos)
	: wxButton(frame->sb, wxID_ANY, wxEmptyString, wxPoint(pos.x - 7, pos.y - 7), wxSize(15, 15))
	, parent(frame->sb)
	, pos(pos)
	, frame(frame) {
	SetBackgroundColour(*wxBLUE);

	//frame->gridPoints->ClearGrid();
	frame->gridPoints->AppendRows();
}

void Button::OnMouseRightDown(wxMouseEvent& event) {
	auto&& fb = frame->lastFocusButton;
	if (fb) {
		fb->SetBackgroundColour(*wxBLUE);
	}
	fb = this;
	SetBackgroundColour(*wxRED);

	//pg->Clear();
	//pg->Append(new wxFloatProperty("x", wxPG_LABEL, pos.x));
	//pg->Append(new wxFloatProperty("y", wxPG_LABEL, pos.y));
	//pg->Append(new wxFloatProperty("z", wxPG_LABEL, pos.z));
	//pg->Append(new wxFloatProperty("tension", wxPG_LABEL, pos.tension));
	//pg->Append(new wxIntProperty("numSegments", wxPG_LABEL, pos.numSegments));
}

void Button::OnMouseLeftDown(wxMouseEvent& event) {
	CaptureMouse();
	lastMP = { event.GetX(),event.GetY() };
	dragging = true;
}

void Button::OnMouseLeftUp(wxMouseEvent& event) {
	if (dragging) {
		ReleaseMouse();
		dragging = false;
	}
}

void Button::OnMouseMiddleDown(wxMouseEvent& event) {
	if (frame->lastFocusButton == this) {
		frame->lastFocusButton = nullptr;
		//pg->Clear();
	}
	frame->buttons.erase(std::find(frame->buttons.begin(), frame->buttons.end(), this));
	parent->RemoveChild(this);
	auto p = parent;
	this->Destroy();
	p->Refresh();
}

void Button::OnMouseMove(wxMouseEvent& event) {
	if (dragging) {
		auto&& currPos = wxGetMousePosition();
		auto&& tarPos = currPos - lastMP;
		auto p = parent->ScreenToClient(tarPos);
		Move(p);
		pos.x = p.x + 7;
		pos.y = p.y + 7;
		parent->Refresh();
	}
}

void Button::OnMouseLeave(wxMouseEvent& event) {
	if (dragging) {
		OnMouseMove(event);
	}
}
