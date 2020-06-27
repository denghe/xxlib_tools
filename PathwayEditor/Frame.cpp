#include "Frame.h"
#include "PointButton.h"
#include "Algorithm.hpp"
#include "xx_file.h"
#include "GridHelpers.hpp"

void Frame::DrawBackground() {
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
}

Frame::Frame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: FrameBase(parent, id, title, pos, size, style) {

	GridHelpers::Init(gridLines, gridPoints);

	DrawBackground();
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
	// 首次画点?
	if (!data.lines.size()) {
		wxCommandEvent e;
		toolNewLineOnToolClicked(e);
	}

	auto&& pointIndex = data.lines[lineIndex].points.size();
	auto&& point = data.lines[lineIndex].points.emplace_back();
	point.x = (float)event.GetX();
	point.y = (float)event.GetY();
	point.z = 0.0f;
	point.tension = 0.3f;
	point.numSegments = 50;

	auto&& btn = buttons.emplace_back(new Button(this, lineIndex, pointIndex));
	btn->OnMouseRightDown(event);

	// draw points
	sb->Refresh();

	// sync grid
	GridHelpers::Insert(gridPoints, point, pointIndex);
}

void Frame::sbOnPaint(wxPaintEvent& event) {
	wxPaintDC dc(sb);

	dc.DrawBitmap(*bmp, 0, 0, false);

	if (lineIndex == -1) return;
	auto&& line = data.lines[lineIndex];
	if (line.points.size() < 2) return;

	std::vector<Pathway::Point> cs, bs, ps;

	if (line.isLoop) {
		cs.clear();
		cs.push_back(line.points[line.points.size() - 1]);
		cs.push_back(line.points[line.points.size() - 2]);
		cs.insert(cs.end(), line.points.begin(), line.points.end());
		cs.push_back(line.points[0]);
		cs.push_back(line.points[1]);
		cs.push_back(line.points[2]);
	}
	else {
		cs = line.points;
	}
	CurveToBezier(bs, cs);

	if (line.isLoop) {
		bs.erase(bs.end() - 2, bs.end() - 1);
		bs.erase(bs.begin(), bs.begin() + 1);
	}
	BezierToPoints(ps, bs);

	dc.SetBackground(wxBrush(GetBackgroundColour()));
	dc.SetPen(wxPen(wxColor(255, 0, 0), 2));

	for (int i = ps.size() - 1; i > 0; --i) {
		dc.DrawLine({ (int)ps[i].x, (int)ps[i].y }, { (int)ps[i - 1].x, (int)ps[i - 1].y });
	}
}

void Frame::menuItemNewOnMenuSelection(wxCommandEvent& event) {
	data = Pathway::Data();
	for (auto&& btn : buttons) {
		sb->RemoveChild(btn);
		btn->Destroy();
	}
	buttons.clear();
	//lastFocusButton = nullptr;
	//propertyGridProperties->Clear();
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
		//menuItemNewLineOnMenuSelection(event);
	}

	//// fill list & select first
	//for (auto&& line : data.lines) {
	//	listBoxLines->Insert(line.name, listBoxLines->GetCount());
	//}
	//listBoxLines->Select(0);

	//// sync property grid
	//listBoxLinesOnListBox(event);

}
void Frame::menuItemSaveOnMenuSelection(wxCommandEvent& event) {
	xx::Data d;
	xx::Write(d, data);
	xx::WriteAllBytes("data", d);
}
void Frame::menuItemExitOnMenuSelection(wxCommandEvent& event) {
	ExitProcess(0);
}


void Frame::toolNewLineOnToolClicked(wxCommandEvent& event) {
	lineIndex = data.lines.size();
	auto&& line = data.lines.emplace_back();
	line.name = std::string("line_") + std::to_string(++lineAutoId);
	line.isLoop = false;

	// sync grid
	GridHelpers::Insert(gridLines, line, lineIndex);
}


void Frame::gridLinesOnGridCellChange(wxGridEvent& event) {

}
void Frame::gridLinesOnGridRangeSelect(wxGridRangeSelectEvent& event) {

}
void Frame::gridLinesOnGridSelectCell(wxGridEvent& event) {

}
