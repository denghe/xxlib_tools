#pragma once
#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/aui/aui.h>

// the following code is copy from wxFormBuilder
///////////////////////////////////////////////////////////////////////////

class FrameBase : public wxFrame
{
private:

protected:
	wxListBox* listBoxLines;
	wxScrolledWindow* scrolledWindowProperties;
	wxMenuBar* menubarRoot;
	wxMenu* menuFile;
	wxMenu* menuEdit;

	// Virtual event handlers, overide them in your derived class
	virtual void listBoxLinesOnListBox(wxCommandEvent& event) { event.Skip(); }
	virtual void propertyGridPropertiesOnPropertyGridChanged(wxPropertyGridEvent& event) { event.Skip(); }
	virtual void menuItemNewOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void menuItemOpenOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void menuItemSaveOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void menuItemExitOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void menuItemNewLineOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void menuItemDeleteLineOnMenuSelection(wxCommandEvent& event) { event.Skip(); }


public:
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

	listBoxLines = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	m_mgr.AddPane(listBoxLines, wxAuiPaneInfo().Left().Caption(wxT("Lines")).CloseButton(false).Movable(false).Dock().Resizable().FloatingSize(wxDefaultSize).BottomDockable(false).TopDockable(false).Floatable(false).MinSize(wxSize(250, 200)));

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

	menubarRoot->Append(menuEdit, wxT("&Edit"));

	this->SetMenuBar(menubarRoot);


	m_mgr.Update();
	this->Centre(wxBOTH);

	// Connect Events
	listBoxLines->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(FrameBase::listBoxLinesOnListBox), NULL, this);
	propertyGridProperties->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(FrameBase::propertyGridPropertiesOnPropertyGridChanged), NULL, this);
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemNewOnMenuSelection), this, menuItemNew->GetId());
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemOpenOnMenuSelection), this, menuItemOpen->GetId());
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemSaveOnMenuSelection), this, menuItemSave->GetId());
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemExitOnMenuSelection), this, menuItemExit->GetId());
	menuEdit->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemNewLineOnMenuSelection), this, menuItemNewLine->GetId());
	menuEdit->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameBase::menuItemDeleteLineOnMenuSelection), this, menuItemDeleteLine->GetId());
}

FrameBase::~FrameBase()
{
	// Disconnect Events
	listBoxLines->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(FrameBase::listBoxLinesOnListBox), NULL, this);
	propertyGridProperties->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(FrameBase::propertyGridPropertiesOnPropertyGridChanged), NULL, this);

	m_mgr.UnInit();

}


///////////////////////////////////////////////////////////////////////////


#include "Pathway_class_lite.h"
#include "xx_file.h"


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
	wxWindow* parent = nullptr;
	bool dragging = false;
	wxPoint lastMP;

	// for logic
	Pathway::Point pos;
	Frame* frame = nullptr;
	wxPropertyGrid* pg = nullptr;

	Button(Frame* const& frame, Pathway::Point const& pos);

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
	std::vector<Button*> buttons;
	Button* lastFocusButton = nullptr;

	std::unique_ptr<wxBitmap> bmp;
	wxStaticBitmap* sb = nullptr;
	void sbOnLeftDown(wxMouseEvent& event);
	void sbOnPaint(wxPaintEvent& event);

	int lineAutoId = 0;
	Pathway::Data data;
	std::string filePath = "data";	// 默认存档为工作目录的 data 文件
	// todo: wxFileDialog 

	Frame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1258, 706), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~Frame() override;

	void propertyGridPropertiesOnPropertyGridChanged(wxPropertyGridEvent& event) override;
	void listBoxLinesOnListBox(wxCommandEvent& event) override;
	void menuItemNewOnMenuSelection(wxCommandEvent& event) override;
	void menuItemOpenOnMenuSelection(wxCommandEvent& event) override;
	void menuItemSaveOnMenuSelection(wxCommandEvent& event) override;
	void menuItemExitOnMenuSelection(wxCommandEvent& event) override;
	void menuItemNewLineOnMenuSelection(wxCommandEvent& event) override;
	void menuItemDeleteLineOnMenuSelection(wxCommandEvent& event) override;
};







Button::Button(Frame* const& frame, Pathway::Point const& pos)
	: wxButton(frame->sb, wxID_ANY, wxEmptyString, wxPoint(pos.x - 7, pos.y - 7), wxSize(15, 15))
	, parent(frame->sb)
	, pos(pos)
	, frame(frame)
	, pg(frame->propertyGridProperties) {
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
	if (frame->lastFocusButton == this) {
		frame->lastFocusButton = nullptr;
		pg->Clear();
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





Frame::Frame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: FrameBase(parent, id, title, pos, size, style) {

	// 根据设计尺寸和安全距离，计算整个显示区域（正方形）的 直径
	int designWidth = 1280;
	int designHeight = 720;
	int safeLength = 100;

	int lineWidth = 5;

	int radius = sqrt((designWidth / 2) * (designWidth / 2) + (designHeight / 2) * (designHeight / 2)) + safeLength;

	int centerXY = radius + safeLength;
	int rectWH = (radius + safeLength) * 2;

	// 创建背景图并放入 scrolledWindowPoints
	bmp.reset(new wxBitmap(rectWH, rectWH));
	wxMemoryDC dc;
	dc.SelectObject(*bmp);
	dc.SetBackground(wxBrush(GetBackgroundColour()));
	dc.Clear();
	dc.SetBrush(wxBrush(GetBackgroundColour()));
	dc.SetPen(wxPen(wxColor(255, 0, 0), 2));
	dc.DrawCircle({ centerXY ,centerXY }, radius);
	dc.SetPen(wxPen(wxColor(0, 0, 255), 2));
	dc.DrawRectangle(centerXY - designWidth / 2, centerXY - designHeight / 2, designWidth, designHeight);
	dc.SetPen(wxPen(wxColor(111, 111, 111), 2));
	dc.DrawLine({ centerXY, 0 }, { centerXY, rectWH });
	dc.DrawLine({ 0, centerXY }, { rectWH, centerXY });

	sb = new wxStaticBitmap(scrolledWindowPoints, wxID_ANY, *bmp, wxPoint(0, 0));
	sb->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Frame::sbOnLeftDown), NULL, this);
	sb->Connect(wxEVT_PAINT, wxPaintEventHandler(Frame::sbOnPaint), NULL, this);

	scrolledWindowPoints->SetVirtualSize(rectWH, rectWH);
	scrolledWindowPoints->SetScrollRate(50, 50);

	// 加载文件
	wxCommandEvent e;
	menuItemOpenOnMenuSelection(e);
}

Frame::~Frame() {
	sb->Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Frame::sbOnLeftDown), NULL, this);
	sb->Disconnect(wxEVT_PAINT, wxPaintEventHandler(Frame::sbOnPaint), NULL, this);
}

void Frame::sbOnLeftDown(wxMouseEvent& event) {
	auto&& btn = buttons.emplace_back(new Button(this, { (float)event.GetX(), (float)event.GetY(), 0.0f, 0.3f, 50 }));
	btn->OnMouseRightDown(event);
	sb->Refresh();
}

void Frame::sbOnPaint(wxPaintEvent& event) {
	wxPaintDC dc(sb);

	dc.DrawBitmap(*bmp, 0, 0, false);

	if (buttons.size() > 1) {
		std::vector<Pathway::Point> cs, bs, ps;

		for (auto&& btn : buttons) {
			cs.push_back(btn->pos);
		}

		CurveToBezier(bs, cs);
		BezierToPoints(ps, bs);

		dc.SetBackground(wxBrush(GetBackgroundColour()));
		dc.SetPen(wxPen(wxColor(255, 0, 0), 4));

		for (auto&& pos : ps) {
			dc.DrawCircle({ (int)pos.x, (int)pos.y }, 5);
		}
	}
}

void Frame::propertyGridPropertiesOnPropertyGridChanged(wxPropertyGridEvent& event) {

	// todo: 判断当前显示的是什么东西的属性: Line 或者 Point

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


void Frame::menuItemNewOnMenuSelection(wxCommandEvent& event) {
	data = Pathway::Data();
	for (auto&& btn : buttons) {
		sb->RemoveChild(btn);
		btn->Destroy();
	}
	buttons.clear();
	lastFocusButton = nullptr;
	propertyGridProperties->Clear();
	sb->Refresh();
	// todo: list box sync
}
void Frame::menuItemOpenOnMenuSelection(wxCommandEvent& event) {
	// cleanup
	menuItemNewOnMenuSelection(event);

	// try load from file
	if (std::filesystem::exists(filePath)) {
		xx::Data d;
		xx::ReadAllBytes("data", d);
		xx::DataReader dr(d);
		dr.Read(data);
		// todo: check read error
	}
	else {
		// init
		data = Pathway::Data();
		data.designWidth = 1280;
		data.designHeight = 720;
		data.safeLength = 100;
		menuItemNewLineOnMenuSelection(event);
	}

	// fill list & select first
	for (auto&& line : data.lines) {
		listBoxLines->Insert(line.name, listBoxLines->GetCount());
	}
	listBoxLines->Select(0);

	// sync property grid
	listBoxLinesOnListBox(event);
}
void Frame::menuItemSaveOnMenuSelection(wxCommandEvent& event) {
	xx::Data d;
	xx::Write(d, data);
	xx::WriteAllBytes("data", d);
}
void Frame::menuItemExitOnMenuSelection(wxCommandEvent& event) {
	ExitProcess(0);
}
void Frame::menuItemNewLineOnMenuSelection(wxCommandEvent& event) {
	auto&& line = data.lines.emplace_back();
	line.name = std::string("line_") + std::to_string(++lineAutoId);
	line.isLoop = false;
}
void Frame::menuItemDeleteLineOnMenuSelection(wxCommandEvent& event) {
	// todo
}
void Frame::listBoxLinesOnListBox(wxCommandEvent& event) {
	// todo
	//listBoxLines->GetSelection()
	auto&& name = listBoxLines->GetStringSelection();
	for (auto&& line : data.lines) {
		if (line.name == name) {
			// todo: propery grid
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
