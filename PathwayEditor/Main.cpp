#pragma once
#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/aui/aui.h>

///////////////////////////////////////////////////////////////////////////

class FrameBase : public wxFrame
{
private:

protected:
	wxScrolledWindow* scrolledWindowProperties;
	wxMenuBar* menubarRoot;
	wxMenu* menuFile;
	wxMenu* menuEdit;

	// Virtual event handlers, overide them in your derived class
	virtual void scrolledWindowPointsOnLeftDown(wxMouseEvent& event) { event.Skip(); }
	virtual void scrolledWindowPointsOnMotion(wxMouseEvent& event) { event.Skip(); }
	virtual void scrolledWindowPointsOnPaint(wxPaintEvent& event) { event.Skip(); }
	virtual void propertyGridPropertiesOnPropertyGridChanged(wxPropertyGridEvent& event) { event.Skip(); }


public:
	wxScrolledWindow* scrolledWindowLines;
	wxScrolledWindow* scrolledWindowPoints;
	wxPropertyGrid* propertyGridProperties;

	FrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1258, 706), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	wxAuiManager m_mgr;

	~FrameBase();

};


///////////////////////////////////////////////////////////////////////////

FrameBase::FrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(238, 255, 254));
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_DEFAULT | wxAUI_MGR_LIVE_RESIZE);

	scrolledWindowLines = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB | wxVSCROLL);
	scrolledWindowLines->SetScrollRate(5, 5);
	m_mgr.AddPane(scrolledWindowLines, wxAuiPaneInfo().Left().Caption(wxT("Lines")).CloseButton(false).Movable(false).Dock().Fixed().BottomDockable(false).TopDockable(false).Floatable(false).MinSize(wxSize(250, 200)));

	scrolledWindowPoints = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB | wxHSCROLL | wxVSCROLL);
	scrolledWindowPoints->SetScrollRate(5, 5);
	m_mgr.AddPane(scrolledWindowPoints, wxAuiPaneInfo().Center().Caption(wxT("Points")).CloseButton(false).Movable(false).Dock().Resizable().FloatingSize(wxDefaultSize).BottomDockable(false).TopDockable(false).LeftDockable(false).RightDockable(false).Floatable(false));

	scrolledWindowProperties = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	scrolledWindowProperties->SetScrollRate(5, 5);
	m_mgr.AddPane(scrolledWindowProperties, wxAuiPaneInfo().Right().Caption(wxT("properties")).CloseButton(false).Movable(false).Dock().Fixed().BottomDockable(false).TopDockable(false).Floatable(false).MinSize(wxSize(250, 200)).Layer(0));

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	propertyGridProperties = new wxPropertyGrid(scrolledWindowProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer2->Add(propertyGridProperties, 1, wxALL | wxEXPAND, 5);


	scrolledWindowProperties->SetSizer(bSizer2);
	scrolledWindowProperties->Layout();
	bSizer2->Fit(scrolledWindowProperties);
	menubarRoot = new wxMenuBar(0);
	menuFile = new wxMenu();
	wxMenuItem* menuItemNew;
	menuItemNew = new wxMenuItem(menuFile, wxID_ANY, wxString(wxT("&New")) + wxT('\t') + wxT("Ctrl + N"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemNew);

	wxMenuItem* menuItemOpen;
	menuItemOpen = new wxMenuItem(menuFile, wxID_ANY, wxString(wxT("&Open")) + wxT('\t') + wxT("Ctrl + O"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemOpen);

	wxMenuItem* menuItemSave;
	menuItemSave = new wxMenuItem(menuFile, wxID_ANY, wxString(wxT("&Save")) + wxT('\t') + wxT("Ctrl + S"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemSave);

	menuFile->AppendSeparator();

	wxMenuItem* menuItemExit;
	menuItemExit = new wxMenuItem(menuFile, wxID_ANY, wxString(wxT("&Exit")) + wxT('\t') + wxT("ALT + F4"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemExit);

	menubarRoot->Append(menuFile, wxT("&File"));

	menuEdit = new wxMenu();
	wxMenuItem* menuItemNewLine;
	menuItemNewLine = new wxMenuItem(menuEdit, wxID_ANY, wxString(wxT("&New Line")) + wxT('\t') + wxT("Ctrl + N"), wxEmptyString, wxITEM_NORMAL);
	menuEdit->Append(menuItemNewLine);

	wxMenuItem* menuItemDeleteLine;
	menuItemDeleteLine = new wxMenuItem(menuEdit, wxID_ANY, wxString(wxT("&Delete Line")) + wxT('\t') + wxT("Ctrl + W"), wxEmptyString, wxITEM_NORMAL);
	menuEdit->Append(menuItemDeleteLine);

	wxMenuItem* menuItemDeletePoint;
	menuItemDeletePoint = new wxMenuItem(menuEdit, wxID_ANY, wxString(wxT("&Delete Point")) + wxT('\t') + wxT("Ctrl + D"), wxEmptyString, wxITEM_NORMAL);
	menuEdit->Append(menuItemDeletePoint);

	menubarRoot->Append(menuEdit, wxT("&Edit"));

	this->SetMenuBar(menubarRoot);


	m_mgr.Update();
	this->Centre(wxBOTH);

	// Connect Events
	scrolledWindowPoints->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(FrameBase::scrolledWindowPointsOnLeftDown), NULL, this);
	scrolledWindowPoints->Connect(wxEVT_MOTION, wxMouseEventHandler(FrameBase::scrolledWindowPointsOnMotion), NULL, this);
	scrolledWindowPoints->Connect(wxEVT_PAINT, wxPaintEventHandler(FrameBase::scrolledWindowPointsOnPaint), NULL, this);
	propertyGridProperties->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(FrameBase::propertyGridPropertiesOnPropertyGridChanged), NULL, this);
}

FrameBase::~FrameBase()
{
	// Disconnect Events
	scrolledWindowPoints->Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(FrameBase::scrolledWindowPointsOnLeftDown), NULL, this);
	scrolledWindowPoints->Disconnect(wxEVT_MOTION, wxMouseEventHandler(FrameBase::scrolledWindowPointsOnMotion), NULL, this);
	scrolledWindowPoints->Disconnect(wxEVT_PAINT, wxPaintEventHandler(FrameBase::scrolledWindowPointsOnPaint), NULL, this);
	propertyGridProperties->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(FrameBase::propertyGridPropertiesOnPropertyGridChanged), NULL, this);

	m_mgr.UnInit();

}



///////////////////////////////////////////////////////////////////////////


#include "Pathway_class_lite.h"


// 2 控制点的贝塞尔( p c c p c c p ... ) 切片转点
inline void BezierToPoints(std::vector<Pathway::Point>& ps, std::vector<Pathway::Point> const& bs) {
	auto len = (bs.size() - 1) / 3;
	size_t totalSegments = 0;
	for (size_t j = 0; j < len; ++j) {
		totalSegments += bs[j * 3].numSegments;
	}
	ps.resize(totalSegments);
	totalSegments = 0;
	for (size_t j = 0; j < len; ++j) {
		auto idx = j * 3;
		auto numSegments = bs[idx].numSegments;
		auto step = 1.0f / numSegments;
		for (size_t i = 0; i < numSegments; ++i) {
			auto t = step * i;
			auto t1 = 1 - t;
			ps[totalSegments + i] = bs[idx] * t1 * t1 * t1
				+ bs[idx + 1] * 3 * t * t1 * t1
				+ bs[idx + 2] * 3 * t * t * (1 - t)
				+ bs[idx + 3] * t * t * t;
		}
		totalSegments += numSegments;
	}
}

// 途径点曲线( p p p ... ) 转 2 控制点的贝塞尔( p c c p c c p ... )
inline void CurveToBezier(std::vector<Pathway::Point>& bs, std::vector<Pathway::Point> const& cs) {
	auto n = cs.size();
	auto len = n * 3 - 2;
	bs.resize(len);

	bs[0] = cs[0];
	bs[1] = (cs[1] - cs[0]) * cs[0].tension + cs[0];

	for (size_t i = 0; i < n - 2; i++) {
		auto diff = (cs[i + 2] - cs[i]) * cs[i].tension;
		bs[3 * i + 2] = cs[i + 1] - diff;
		bs[3 * i + 3] = cs[i + 1];
		bs[3 * i + 4] = cs[i + 1] + diff;
	}
	bs[len - 2] = (cs[n - 2] - cs[n - 1]) * cs[n - 2].tension + cs[n - 1];
	bs[len - 1] = cs[n - 1];
}










struct Frame;

struct Button : public wxButton {
	// for mouse drag
	wxPanel* parent = nullptr;
	bool dragging = false;
	wxPoint lastMP;

	// for logic
	int id = 0;
	Pathway::Point pos;
	Frame* frame = nullptr;
	wxPropertyGrid* pg = nullptr;

	Button(Frame* const& f, int const& id, Pathway::Point const& pos);

	void OnMouseRightDown(wxMouseEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseMiddleDown(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);

	DECLARE_EVENT_TABLE()
};
BEGIN_EVENT_TABLE(Button, wxButton)
EVT_LEFT_DOWN(Button::OnMouseLeftDown)
EVT_LEFT_UP(Button::OnMouseLeftUp)
EVT_MIDDLE_DOWN(Button::OnMouseMiddleDown)
EVT_RIGHT_DOWN(Button::OnMouseRightDown)
EVT_MOTION(Button::OnMouseMove)
EVT_LEAVE_WINDOW(Button::OnMouseLeave)
END_EVENT_TABLE()







struct Frame : public FrameBase {
	FrameBase::FrameBase;

	int buttonId = 0;
	std::vector<Button*> buttons;
	Button* lastFocusButton = nullptr;

	virtual void scrolledWindowPointsOnLeftDown(wxMouseEvent& event) override;
	virtual void scrolledWindowPointsOnMotion(wxMouseEvent& event) override;
	virtual void scrolledWindowPointsOnPaint(wxPaintEvent& event) override;
	virtual void propertyGridPropertiesOnPropertyGridChanged(wxPropertyGridEvent& event) override;
};







Button::Button(Frame* const& f, int const& id, Pathway::Point const& pos)
	: wxButton(f->scrolledWindowPoints, wxID_ANY, wxEmptyString, wxPoint(pos.x - 7, pos.y - 7), wxSize(15, 15))
	, parent(f->scrolledWindowPoints)
	, id(id)
	, pos(pos)
	, frame(f)
	, pg(f->propertyGridProperties) {
	SetBackgroundColour(*wxBLUE);
}

void Button::OnMouseRightDown(wxMouseEvent& event) {
	auto&& fb = frame->lastFocusButton;
	if (fb) {
		fb->SetBackgroundColour(*wxBLUE);
	}
	fb = this;
	SetBackgroundColour(*wxRED);

	pg->Clear();
	pg->Append(new wxFloatProperty("x", wxPG_LABEL, pos.x));
	pg->Append(new wxFloatProperty("y", wxPG_LABEL, pos.y));
	pg->Append(new wxFloatProperty("z", wxPG_LABEL, pos.z));
	pg->Append(new wxFloatProperty("tension", wxPG_LABEL, pos.tension));
	pg->Append(new wxIntProperty("numSegments", wxPG_LABEL, pos.numSegments));
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
	// todo: delete point
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







void Frame::scrolledWindowPointsOnLeftDown(wxMouseEvent& event) {
	auto&& btn = buttons.emplace_back(new Button(this, ++buttonId, {  (float)event.GetX(), (float)event.GetY(), 0.0f, 0.3f, 500 }));
	// todo: set focus? show property?
	scrolledWindowPoints->Refresh();
}

void Frame::scrolledWindowPointsOnMotion(wxMouseEvent& event) {
}

void Frame::scrolledWindowPointsOnPaint(wxPaintEvent& event) {
	wxPaintDC dc(scrolledWindowPoints);
	//dc.SetBrush(*wxGREEN_BRUSH);
	dc.SetPen(wxPen(wxColor(255, 0, 0), 5));

	if (buttons.size() > 1) {
		std::vector<Pathway::Point> cs, bs, ps;

		for (auto&& btn : buttons) {
			cs.push_back(btn->pos);
		}

		CurveToBezier(bs, cs);
		BezierToPoints(ps, bs);

		for (auto&& pos : ps) {
			dc.DrawPoint({ (int)pos.x, (int)pos.y });
		}
	}
}


void Frame::propertyGridPropertiesOnPropertyGridChanged(wxPropertyGridEvent& event) {
	if (auto&& p = event.GetProperty()) {
		auto&& n = p->GetName();
		auto&& v = p->GetValue();
		if (n == "x") {
			auto&& v = p->GetValue();
			lastFocusButton->pos.x = v.GetDouble();
		}
		else if (n == "y") {
			auto&& v = p->GetValue();
			lastFocusButton->pos.y = v.GetDouble();
		}
		else if (n == "z") {
			auto&& v = p->GetValue();
			lastFocusButton->pos.z = v.GetDouble();
		}
		else if (n == "tension") {
			auto&& v = p->GetValue();
			lastFocusButton->pos.tension = v.GetDouble();
		}
		else if (n == "numSegments") {
			auto&& v = p->GetValue();
			lastFocusButton->pos.numSegments = v.GetInteger();
		}
		else {
			throw std::logic_error("not impl");
		}
		Refresh();
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
