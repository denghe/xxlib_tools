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
	auto&& ps = frame->gridPoints;
	if (ps->IsInSelection(pointIndex, 0)) {
		ps->DeselectRow(pointIndex);
		SetBackgroundColour(*wxBLUE);
	}
	else {
		ps->SelectRow(pointIndex, true);
		SetBackgroundColour(*wxRED);
	}
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
	// ��λ��������
	auto&& ps = frame->data.lines[lineIndex].points;
	// ɾ��
	ps.erase(ps.begin() + pointIndex);
	// �����������Ӧ�� button ���±�
	for (int i = pointIndex + 1; i < frame->buttons.size(); ++i) {
		frame->buttons[i]->pointIndex -= 1;
	}
	// �� grid ɾһ��
	GridHelpers::Delete(frame->gridPoints, pointIndex);
	// ɾ button
	frame->buttons.erase(std::find(frame->buttons.begin(), frame->buttons.end(), this));
	parent->RemoveChild(this);
	auto p = parent;
	this->Destroy();
	// ����
	p->Refresh();
}

void Button::OnMouseMove(wxMouseEvent& event) {
	if (dragging) {
		// ��ϵ�ǰ������꣬�Լ� mouse down ʱѹ�µ�λ�ã�����µ�����
		auto&& currPos = wxGetMousePosition();
		auto&& tarPos = currPos - lastMP;
		auto p = parent->ScreenToClient(tarPos);
		// �뵱ǰ������������õ� x, y �ƶ���ֵ
		auto&& op = GetPosition();
		auto&& diff = p - op;
		
		// ���ѡ���м��ϡ������ǰ��û��ѡ�У�����ʱ�ӵ�����
		auto&& ints = frame->gridPoints->GetSelectedRows();
		if (std::find(ints.begin(), ints.end(), pointIndex) == ints.end()) {
			ints.push_back(pointIndex);
		}
		// ͬʱ�ƶ��������
		auto&& ps = frame->data.lines[frame->lineIndex].points;
		for (auto&& i : ints) {
			auto&& b = frame->buttons[i];
			b->Move(b->GetPosition() + diff);
			ps[i].x += diff.x;
			ps[i].y += diff.y;
			GridHelpers::Update(frame->gridPoints, ps[i], i);
		}
		parent->Refresh();
	}
}

void Button::OnMouseLeave(wxMouseEvent& event) {
	if (dragging) {
		OnMouseMove(event);
	}
}
