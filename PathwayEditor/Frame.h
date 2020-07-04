#pragma once
#include "FrameBase.h"
#include "Pathway_class_lite.h"

struct Button;
struct Frame : public FrameBase {
	std::vector<Button*> buttons;

	std::unique_ptr<wxBitmap> bmp;
	void DrawBackground();

	wxStaticBitmap* sb = nullptr;
	void sbOnLeftDown(wxMouseEvent& event);
	void sbOnPaint(wxPaintEvent& event);

	// 中途用到的一些尺寸变量
	int lineWidth = 0, radius = 0, centerXY = 0, rectWH = 0;

	int lineAutoId = 0;
	Pathway::Data data;
	std::string filePath = "data";	// 默认存档为工作目录的 data 文件

	// 当前线下标
	int lineIndex = 0;

	// todo: wxFileDialog 

	// 选线后重绘所有点
	void DrawPoints();


	Frame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1258, 706), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~Frame() override;

	void menuItemNewOnMenuSelection(wxCommandEvent& event) override;
	void menuItemOpenOnMenuSelection(wxCommandEvent& event) override;
	void menuItemSaveOnMenuSelection(wxCommandEvent& event) override;
	void menuItemExitOnMenuSelection(wxCommandEvent& event) override;

	void toolNewLineOnToolClicked(wxCommandEvent& event) override;
	void toolGroupManageOnToolClicked(wxCommandEvent& event) override;

	void gridLinesOnGridRangeSelect(wxGridRangeSelectEvent& event) override;
	void gridLinesOnGridCellChange(wxGridEvent& event) override;
	void gridLinesOnGridSelectCell(wxGridEvent& event) override;

	void gridPointsOnGridCellChange(wxGridEvent& event) override;
	void gridPointsOnGridRangeSelect(wxGridRangeSelectEvent& event) override;
};
