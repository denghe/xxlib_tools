#pragma once
#include "FrameBase.h"
#include "Pathway_class_lite.h"

struct Button;
struct Frame : public FrameBase {
	std::vector<Button*> buttons;


	// 根据设计尺寸和安全距离，计算整个显示区域（正方形）的 直径
	int designWidth = 1280;
	int designHeight = 720;
	int safeLength = 100;

	int lineWidth = 5;

	int radius = sqrt((designWidth / 2) * (designWidth / 2) + (designHeight / 2) * (designHeight / 2)) + safeLength;

	int centerXY = radius + safeLength;
	int rectWH = (radius + safeLength) * 2;

	std::unique_ptr<wxBitmap> bmp;
	void DrawBackground();

	wxStaticBitmap* sb = nullptr;
	void sbOnLeftDown(wxMouseEvent& event);
	void sbOnPaint(wxPaintEvent& event);

	int lineAutoId = 0;	// 放到 data?
	Pathway::Data data;
	std::string filePath = "data";	// 默认存档为工作目录的 data 文件

	// 当前线下标	// todo: 和 gridLines select 同步?
	int lineIndex = -1;
	// todo: wxFileDialog 


	Frame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1258, 706), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~Frame() override;

	void menuItemNewOnMenuSelection(wxCommandEvent& event) override;
	void menuItemOpenOnMenuSelection(wxCommandEvent& event) override;
	void menuItemSaveOnMenuSelection(wxCommandEvent& event) override;
	void menuItemExitOnMenuSelection(wxCommandEvent& event) override;

	void toolNewLineOnToolClicked(wxCommandEvent& event) override;

	void gridLinesOnGridCellChange(wxGridEvent& event) override;
	void gridLinesOnGridRangeSelect(wxGridRangeSelectEvent& event) override;
	void gridLinesOnGridSelectCell(wxGridEvent& event) override;
};
