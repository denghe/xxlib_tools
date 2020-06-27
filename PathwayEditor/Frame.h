#pragma once
#include "FrameBase.h"
#include "Pathway_class_lite.h"

struct Button;
struct Frame : public FrameBase {
	std::vector<Button*> buttons;


	// ������Ƴߴ�Ͱ�ȫ���룬����������ʾ���������Σ��� ֱ��
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

	int lineAutoId = 0;	// �ŵ� data?
	Pathway::Data data;
	std::string filePath = "data";	// Ĭ�ϴ浵Ϊ����Ŀ¼�� data �ļ�

	// ��ǰ���±�	// todo: �� gridLines select ͬ��?
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
