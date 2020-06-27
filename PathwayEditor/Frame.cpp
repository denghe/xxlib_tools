#include "Frame.h"
#include "PointButton.h"
#include "Algorithm.hpp"
#include "xx_file.h"

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

	// 初始化grid显示格式
	gridLines->SetColFormatBool(1);

	gridPoints->SetColFormatFloat(0, 6, 2);
	gridPoints->SetColFormatFloat(1, 6, 2);
	gridPoints->SetColFormatFloat(2, 6, 2);
	gridPoints->SetColFormatFloat(3, 3, 3);
	gridPoints->SetColFormatFloat(4, 3, 0);

	//gridLines->DeleteRows()
	//gridLines->GetNumberRows();


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
		dc.SetPen(wxPen(wxColor(255, 0, 0), 2));

		for (auto&& pos : ps) {
			dc.DrawCircle({ (int)pos.x, (int)pos.y }, 3);
		}
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
