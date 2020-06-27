#pragma once
#include "Frame.h"
#include "PointButton.h"
#include "GridHelpers.hpp"

BEGIN_EVENT_TABLE(Button, wxButton)
EVT_LEFT_DOWN(Button::OnMouseLeftDown)
EVT_LEFT_UP(Button::OnMouseLeftUp)
EVT_MIDDLE_DOWN(Button::OnMouseMiddleDown)
EVT_RIGHT_DOWN(Button::OnMouseRightDown)
EVT_MOTION(Button::OnMouseMove)
EVT_LEAVE_WINDOW(Button::OnMouseLeave)
END_EVENT_TABLE()

Button::Button(Frame* const& frame, int const& lineIndex, int const& pointIndex)
	: wxButton(frame->sb, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(15, 15))
	, frame(frame)
	, lineIndex(lineIndex)
	, pointIndex(pointIndex)
	, parent(frame->sb)
{
	SetBackgroundColour(*wxBLUE);

	auto&& point = frame->data.lines[lineIndex].points[pointIndex];
	Move(wxPoint(point.x - 7, point.y - 7));
}

void Button::OnMouseRightDown(wxMouseEvent& event) {
	//auto&& fb = frame->lastFocusButton;
	//if (fb) {
	//	fb->SetBackgroundColour(*wxBLUE);
	//}
	//fb = this;
	//SetBackgroundColour(*wxRED);

	// todo: sync grid's select row?
	frame->gridPoints->SelectRow(pointIndex);
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
	//if (frame->lastFocusButton == this) {
	//	frame->lastFocusButton = nullptr;
	//	//pg->Clear();
	//	// todo: sync grid
	//}

	// 定位到点容器
	auto&& ps = frame->data.lines[lineIndex].points;
	// 删点
	ps.erase(ps.begin() + pointIndex);
	// 修正后续点对应的 button 的下标
	for (int i = pointIndex + 1; i < frame->buttons.size(); ++i) {
		frame->buttons[i]->pointIndex -= 1;
	}
	// 从 grid 删一行
	GridHelpers::Delete(frame->gridPoints, pointIndex);
	// 删 button
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
		auto&& point = frame->data.lines[lineIndex].points[pointIndex];
		point.x = p.x + 7;
		point.y = p.y + 7;
		parent->Refresh();
		GridHelpers::Update(frame->gridPoints, point, pointIndex);
	}
}

void Button::OnMouseLeave(wxMouseEvent& event) {
	if (dragging) {
		OnMouseMove(event);
	}
}
