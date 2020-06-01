#pragma once
#include <wx/wx.h>
#include "xx_point.h"
#include "Pathway_class_lite.h"

// 下面这两段参考自 wxFormBuilder 生成物

///////////////////////////////////////////////////////////////////////////

class FrameBase : public wxFrame
{
private:

protected:

	// Virtual event handlers, overide them in your derived class
	virtual void FrameOnLeftDClick(wxMouseEvent& event) { event.Skip(); }
	virtual void FrameOnPaint(wxPaintEvent& event) { event.Skip(); }


public:

	FrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(794, 513), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~FrameBase();

};


///////////////////////////////////////////////////////////////////////////


FrameBase::FrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(238, 255, 254));

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(FrameBase::FrameOnLeftDClick));
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(FrameBase::FrameOnPaint));
}

FrameBase::~FrameBase()
{
	// Disconnect Events
	this->Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(FrameBase::FrameOnLeftDClick));
	this->Disconnect(wxEVT_PAINT, wxPaintEventHandler(FrameBase::FrameOnPaint));
}

///////////////////////////////////////////////////////////////////////////










struct Frame;

struct Button : public wxButton {
	bool dragging = false;
	wxPoint lastMP;

	int id = 0;
	xx::Point pos;
	Button(Frame* f, int id, xx::Point const& pos);

	void OnMouseLeftDoubleClick(wxMouseEvent& evt);
	void OnMouseDown(wxMouseEvent& evt);
	void OnMouseUp(wxMouseEvent& evt);
	void OnMove(wxMouseEvent& evt);

	DECLARE_EVENT_TABLE()
};
BEGIN_EVENT_TABLE(Button, wxButton)
EVT_LEFT_DCLICK(Button::OnMouseLeftDoubleClick)
EVT_LEFT_DOWN(Button::OnMouseDown)
EVT_LEFT_UP(Button::OnMouseUp)
EVT_MOTION(Button::OnMove)
END_EVENT_TABLE()



struct Frame : public FrameBase {
	FrameBase::FrameBase;

	int buttonId = 0;
	std::vector<Button*> buttons;

	void NewButton(int id, xx::Point const& pos);

	virtual void FrameOnLeftDClick(wxMouseEvent& event) override;
	virtual void FrameOnPaint(wxPaintEvent& event) override;
};








Button::Button(Frame* f, int id, xx::Point const& pos)
	: wxButton(f, wxID_ANY, wxEmptyString, wxPoint(pos.x - 7, pos.y - 7), wxSize(15, 15))
	, id(id)
	, pos(pos) {
}

void Button::OnMouseLeftDoubleClick(wxMouseEvent& evt) {
	((Frame*)GetParent())->Refresh();
}
void Button::OnMouseDown(wxMouseEvent& evt) {
	lastMP = { evt.GetX(),evt.GetY() };
	dragging = true;
}
void Button::OnMouseUp(wxMouseEvent& evt) {
	dragging = false;
}
void Button::OnMove(wxMouseEvent& evt) {
	if (dragging) {
		auto p = GetParent()->ScreenToClient(wxGetMousePosition() - lastMP);
		this->Move(p);
		pos.x = p.x + 7;
		pos.y = p.y + 7;
		GetParent()->Refresh();
	}
}




void Frame::NewButton(int id, xx::Point const& pos) {
	auto&& btn = buttons.emplace_back(new Button(this, id, pos));
	Refresh();
}

void Frame::FrameOnLeftDClick(wxMouseEvent& event) {
	NewButton(++buttonId, { (float)event.GetX(), (float)event.GetY() });
}

void Frame::FrameOnPaint(wxPaintEvent& event) {
	wxPaintDC dc(this);
	//dc.SetBrush(*wxGREEN_BRUSH);
	dc.SetPen(wxPen(wxColor(255, 0, 0), 5));

	if (buttons.size() > 1) {
		std::vector<xx::Point> cs, bs, ps;

		for (auto&& btn : buttons) {
			cs.push_back(btn->pos);
		}

		xx::CurveToBezier(bs, cs);
		xx::BezierToPoints(ps, bs, 500);

		for (auto&& pos : ps) {
			dc.DrawPoint({ (int)pos.x, (int)pos.y });
		}
	}
}

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
