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


public:
	wxScrolledWindow* scrolledWindowLines;
	wxScrolledWindow* scrolledWindowPoints;
	wxPropertyGrid* propertyGridProperties;

	FrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(835, 528), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
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
	m_mgr.AddPane(scrolledWindowLines, wxAuiPaneInfo().Left().Caption(wxT("Lines")).CloseButton(false).Movable(false).Dock().Fixed().BottomDockable(false).TopDockable(false).Floatable(false).MinSize(wxSize(200, 200)));

	scrolledWindowPoints = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB | wxHSCROLL | wxVSCROLL);
	scrolledWindowPoints->SetScrollRate(5, 5);
	m_mgr.AddPane(scrolledWindowPoints, wxAuiPaneInfo().Center().Caption(wxT("Points")).CloseButton(false).Movable(false).Dock().Resizable().FloatingSize(wxDefaultSize).BottomDockable(false).TopDockable(false).LeftDockable(false).RightDockable(false).Floatable(false));

	scrolledWindowProperties = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB | wxVSCROLL);
	scrolledWindowProperties->SetScrollRate(5, 5);
	m_mgr.AddPane(scrolledWindowProperties, wxAuiPaneInfo().Right().Caption(wxT("properties")).CloseButton(false).Movable(false).Dock().Fixed().BottomDockable(false).TopDockable(false).Floatable(false).MinSize(wxSize(200, 200)).Layer(0));

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	propertyGridProperties = new wxPropertyGrid(scrolledWindowProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer2->Add(propertyGridProperties, 0, wxALL | wxEXPAND, 5);


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
}

FrameBase::~FrameBase()
{
	// Disconnect Events
	scrolledWindowPoints->Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(FrameBase::scrolledWindowPointsOnLeftDown), NULL, this);
	scrolledWindowPoints->Disconnect(wxEVT_MOTION, wxMouseEventHandler(FrameBase::scrolledWindowPointsOnMotion), NULL, this);
	scrolledWindowPoints->Disconnect(wxEVT_PAINT, wxPaintEventHandler(FrameBase::scrolledWindowPointsOnPaint), NULL, this);

	m_mgr.UnInit();

}


///////////////////////////////////////////////////////////////////////////


#include "xx_point.h"
#include "Pathway_class_lite.h"








struct Frame;

struct Button : public wxButton {
	// for mouse drag
	wxPanel* parent = nullptr;
	bool dragging = false;
	wxPoint lastMP;

	// for logic
	int id = 0;
	xx::Point pos;
	Frame* frame = nullptr;

	Button(Frame* const& f, int const& id, xx::Point const& pos);

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
};







Button::Button(Frame* const& f, int const& id, xx::Point const& pos)
	: wxButton(f->scrolledWindowPoints, wxID_ANY, wxEmptyString, wxPoint(pos.x - 7, pos.y - 7), wxSize(15, 15))
	, parent(f->scrolledWindowPoints)
	, id(id)
	, pos(pos)
	, frame(f) {
	SetBackgroundColour(*wxBLUE);
}

void Button::OnMouseRightDown(wxMouseEvent& event) {
	auto&& fb = frame->lastFocusButton;
	if (fb) {
		fb->SetBackgroundColour(*wxBLUE);
	}
	fb = this;
	SetBackgroundColour(*wxRED);
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
	auto&& btn = buttons.emplace_back(new Button(this, ++buttonId, { (float)event.GetX(), (float)event.GetY() }));
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
		std::vector<xx::Point> cs, bs, ps;

		for (auto&& btn : buttons) {
			cs.push_back(btn->pos);
		}

		xx::CurveToBezier(bs, cs, 0.5f);
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
