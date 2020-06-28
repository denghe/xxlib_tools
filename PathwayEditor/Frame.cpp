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
	dc.SetPen(wxPen(wxColor(255, 0, 255), 2));
	dc.DrawCircle({ centerXY ,centerXY }, radius);
	dc.SetPen(wxPen(wxColor(0, 0, 255), 2));
	dc.DrawRectangle(centerXY - data.designWidth / 2, centerXY - data.designHeight / 2, data.designWidth, data.designHeight);
	dc.SetPen(wxPen(wxColor(111, 111, 111), 2));
	dc.DrawLine({ centerXY, 0 }, { centerXY, rectWH });
	dc.DrawLine({ 0, centerXY }, { rectWH, centerXY });
}

Frame::Frame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: FrameBase(parent, id, title, pos, size, style) {

	GridHelpers::Init(gridLines, gridPoints);

	// 加载文件
	wxCommandEvent e;
	menuItemOpenOnMenuSelection(e);

	// 根据设计尺寸和安全距离，计算整个显示区域（正方形）的 直径
	lineWidth = 5;

	radius = sqrt((data.designWidth / 2) * (data.designWidth / 2) + (data.designHeight / 2) * (data.designHeight / 2)) + data.safeLength;

	centerXY = radius + data.safeLength;
	rectWH = (radius + data.safeLength) * 2;

	DrawBackground();
	sb = new wxStaticBitmap(scrolledWindowPoints, wxID_ANY, *bmp, wxPoint(0, 0));
	sb->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Frame::sbOnLeftDown), NULL, this);
	sb->Connect(wxEVT_PAINT, wxPaintEventHandler(Frame::sbOnPaint), NULL, this);

	scrolledWindowPoints->SetVirtualSize(rectWH, rectWH);
	scrolledWindowPoints->SetScrollRate(50, 50);

	GridHelpers::FullSync(gridLines, data.lines);
	DrawPoints();
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

	buttons.emplace_back(new Button(this, lineIndex, pointIndex));

	// draw points
	sb->Refresh();

	// sync grid
	GridHelpers::Insert(gridPoints, point, pointIndex);
}

void Frame::sbOnPaint(wxPaintEvent& event) {
	wxPaintDC dc(sb);

	dc.DrawBitmap(*bmp, 0, 0, false);

	if (!data.lines.size()) return;

	auto&& line = data.lines[lineIndex];
	if (line.points.size() < 2) return;

	std::vector<Pathway::Point> cs, bs, ps;

	if (line.isLoop && line.points.size() > 2) {
		cs.push_back(line.points[line.points.size() - 2]);
		cs.push_back(line.points[line.points.size() - 1]);
		cs.insert(cs.end(), line.points.begin(), line.points.end());
		cs.push_back(line.points[0]);
		cs.push_back(line.points[1]);
		cs.push_back(line.points[2]);
	}
	else {
		cs = line.points;
	}
	CurveToBezier(bs, cs);

	if (line.isLoop && line.points.size() > 2) {
		bs.erase(bs.end() - 6, bs.end() - 1);
		bs.erase(bs.begin(), bs.begin() + 3);
	}
	BezierToPoints(ps, bs);

	dc.SetBackground(wxBrush(GetBackgroundColour()));
	dc.SetPen(*wxRED);

	//for (auto&& p : ps) {
	//	dc.DrawCircle({ (int)p.x, (int)p.y }, 10);
	//}
	auto idx = ps.size() - 1;
	for (int i = idx; i > 0; --i) {
		dc.DrawLine({ (int)ps[i].x, (int)ps[i].y }, { (int)ps[i - 1].x, (int)ps[i - 1].y });
	}
	if (!(line.isLoop && line.points.size() > 2))
	{
		// 补画到最后一个点的线段
		dc.DrawLine({ (int)ps[idx].x, (int)ps[idx].y }, { (int)cs[cs.size() - 1].x, (int)cs[cs.size() - 1].y });
	}

}


void Frame::DrawPoints() {
	for (auto&& btn : buttons) {
		sb->RemoveChild(btn);
		btn->Destroy();
	}
	buttons.clear();
	if (!data.lines.size()) return;

	auto&& ps = data.lines[lineIndex].points;
	auto&& len = data.lines[lineIndex].points.size();
	GridHelpers::Clear(gridPoints);
	for (int i = 0; i < len; ++i) {
		buttons.emplace_back(new Button(this, lineIndex, i));
		GridHelpers::Insert(gridPoints, ps[i], i);
	}

	if (sb) {
		sb->Refresh();
	}
}

void Frame::toolNewLineOnToolClicked(wxCommandEvent& event) {
	auto idx = data.lines.size();
	Pathway::Line line;
LabRetry:
	line.name = std::string("line_") + std::to_string(++lineAutoId);
	for (auto&& o : data.lines) {
		if (o.name == line.name) goto LabRetry;
	}
	line.isLoop = false;
	data.lines.emplace_back(std::move(line));

	GridHelpers::Insert(gridLines, data.lines[idx], idx);
	gridLines->SelectRow(idx, false);
	DrawPoints();
}

void Frame::menuItemNewOnMenuSelection(wxCommandEvent& event) {
	data = Pathway::Data();
	lineAutoId = 0;
	GridHelpers::Clear(gridLines);
	GridHelpers::Clear(gridPoints);
	DrawPoints();

	toolNewLineOnToolClicked(event);
}

void Frame::menuItemOpenOnMenuSelection(wxCommandEvent& event) {
	lineAutoId = 0;
	// try load from file
	if (std::filesystem::exists(filePath)) {
		xx::Data d;
		xx::ReadAllBytes("data", d);
		xx::DataReader dr(d);
		dr.Read(data);
		// todo: check read error
	}
	else {
		// todo: 弹面板问这几个参数?
		menuItemNewOnMenuSelection(event);
		data.designWidth = 1280;
		data.designHeight = 720;
		data.safeLength = 100;
	}
}

void Frame::menuItemSaveOnMenuSelection(wxCommandEvent& event) {
	xx::Data d;
	xx::Write(d, data);
	xx::WriteAllBytes("data", d);
}

void Frame::menuItemExitOnMenuSelection(wxCommandEvent& event) {
	ExitProcess(0);
}




void Frame::gridLinesOnGridRangeSelect(wxGridRangeSelectEvent& event) {
	// 限定只能选中 1 行
	auto&& ints = gridLines->GetSelectedRows();
	if (ints.size() > 1) {
		gridLines->SelectRow(ints[0]);
	}
	else if (ints.size()) {
		lineIndex = ints[0];
		DrawPoints();
	}
}

void Frame::gridLinesOnGridSelectCell(wxGridEvent& event) {
	gridLines->SelectRow(event.GetRow());
}

void Frame::gridLinesOnGridCellChange(wxGridEvent& event) {
	int r = event.GetRow();
	int c = event.GetCol();
	auto&& ov = event.GetString();
	auto&& v = gridLines->GetCellValue(r, c);

	switch (c) {
	case 0: {
		// 如果重复了就还原并退出
		for (auto&& o : data.lines) {
			if (o.name == v) {
				gridLines->SetCellValue(r, 0, ov);
				return;
			}
		}
		// 保存
		data.lines[r].name = v;
		break;
	}
	case 1: {
		// 保存
		data.lines[r].isLoop = (v != "");
		DrawPoints();
		break;
	}
	}
}

void Frame::gridPointsOnGridRangeSelect(wxGridRangeSelectEvent& event) {
	// 多个选中则对应的 button 都变色
	auto&& ints = gridPoints->GetSelectedRows();
	for (auto&& btn : buttons) {
		if (std::find(ints.begin(), ints.end(), btn->pointIndex) != ints.end()) {
			btn->SetBackgroundColour(*wxRED);
		}
		else {
			btn->SetBackgroundColour(*wxBLUE);
		}
	}
}

void Frame::gridPointsOnGridCellChange(wxGridEvent& event) {
	int r = event.GetRow();
	int c = event.GetCol();

	auto&& ov = event.GetString();
	auto&& v = gridPoints->GetCellValue(r, c);

	// 多行一起改受控件限制，先不做( cell change 事件似乎会顶掉多行选择 )

	auto&& p = data.lines[lineIndex].points[r];
	switch (c) {
	case 0: {
		p.x = atoi(v.c_str());
		buttons[r]->Move(wxPoint(p.x - 7, p.y - 7));
		break;
	}
	case 1: {
		p.y = atoi(v.c_str());
		buttons[r]->Move(wxPoint(p.x - 7, p.y - 7));
		break;
	}
	case 2: {
		p.z = atoi(v.c_str());
		break;
	}
	case 3: {
		p.tension = atof(v.c_str());
		break;
	}
	case 4: {
		p.numSegments = atoi(v.c_str());
		break;
	}
	}
	sb->Refresh();
}
