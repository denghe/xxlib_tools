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

	// ��;�õ���һЩ�ߴ����
	int lineWidth = 0, radius = 0, centerXY = 0, rectWH = 0;

	int lineAutoId = 0;
	Pathway::Data data;
	std::string filePath = "data";	// Ĭ�ϴ浵Ϊ����Ŀ¼�� data �ļ�

	// ��ǰ���±�
	int lineIndex = 0;

	// todo: wxFileDialog 

	// ѡ�ߺ��ػ����е�
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
