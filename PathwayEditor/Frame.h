#pragma once
#include "FrameBase.h"
#include "Pathway_class_lite.h"

struct Button;
struct Frame : public FrameBase {
	std::vector<Button*> buttons;
	Button* lastFocusButton = nullptr;


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

	int lineAutoId = 0;
	Pathway::Data data;
	std::string filePath = "data";	// 默认存档为工作目录的 data 文件
	// todo: wxFileDialog 


	//void ClearAllLines() {
	//	data.lines.clear();
	//	gridLines->DeleteRows(0, gridLines->GetNumberRows());
	//}

	//void AddRow(Pathway::Point const& p) {
	//	auto&& idx = gridPoints->GetNumberRows();
	//	gridPoints->AppendRows();
	//	gridPoints->SetCellValue({ idx, 0 }, std::to_string(p.x));
	//	gridPoints->SetCellValue({ idx, 1 }, std::to_string(p.y));
	//	gridPoints->SetCellValue({ idx, 2 }, std::to_string(p.z));
	//	gridPoints->SetCellValue({ idx, 3 }, std::to_string(p.tension));
	//	gridPoints->SetCellValue({ idx, 4 }, std::to_string(p.numSegments));
	//}

	//void RemoveRow(Pathway::Line& line, int const& idx) {
	//	// todo
	//}

	//// todo: more grid funcs



	Frame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1258, 706), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~Frame() override;

	void menuItemNewOnMenuSelection(wxCommandEvent& event) override;
	void menuItemOpenOnMenuSelection(wxCommandEvent& event) override;
	void menuItemSaveOnMenuSelection(wxCommandEvent& event) override;
	void menuItemExitOnMenuSelection(wxCommandEvent& event) override;
};
