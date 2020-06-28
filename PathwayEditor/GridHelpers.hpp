#pragma once
#include <wx/grid.h>
#include "Pathway_class_lite.h"

namespace GridHelpers {

	inline void Clear(wxGrid* const& g) {
		if (g->GetNumberRows()) {
			g->DeleteRows(0, g->GetNumberRows());
		}
	}

	inline void Init(wxGrid* const& gridLines, wxGrid* const& gridPoints) {
		gridLines->SetColFormatBool(1);
		Clear(gridLines);
		gridLines->SetSelectionMode(wxGrid::wxGridSelectRows);

		gridPoints->SetColFormatFloat(0, 4, 0);
		gridPoints->SetColFormatFloat(1, 4, 0);
		gridPoints->SetColFormatFloat(2, 4, 0);
		gridPoints->SetColFormatFloat(3, 3, 3);
		gridPoints->SetColFormatFloat(4, 3, 0);
		gridPoints->SetSelectionMode(wxGrid::wxGridSelectRows);
		Clear(gridPoints);
	}

	inline void Update(wxGrid* const& g, Pathway::Line& line, int i) {
		assert(i < g->GetNumberRows());
		g->SetCellValue({ i, 0 }, line.name);
		g->SetCellValue({ i, 1 }, line.isLoop ? "1" : "");
	}

	inline void Update(wxGrid* const& g, Pathway::Point& point, int i) {
		assert(i < g->GetNumberRows());
		g->SetCellValue({ i, 0 }, std::to_string(point.x));
		g->SetCellValue({ i, 1 }, std::to_string(point.y));
		g->SetCellValue({ i, 2 }, std::to_string(point.z));
		g->SetCellValue({ i, 3 }, std::to_string(point.tension));
		g->SetCellValue({ i, 4 }, std::to_string(point.numSegments));
	}

	inline void Insert(wxGrid* const& g, Pathway::Line& line, int i = -1) {
		if (i == -1) {
			i = g->GetNumberRows();
		}
		g->AppendRows();
		Update(g, line, i);
	}

	inline void Insert(wxGrid* const& g, Pathway::Point& point, int i = -1) {
		if (i == -1) {
			i = g->GetNumberRows();
		}
		g->AppendRows();
		Update(g, point, i);
	}

	inline void Delete(wxGrid* const& g, int const& i) {
		assert(i < g->GetNumberRows());
		g->DeleteRows(i);
	}

	inline void FullSync(wxGrid* const& g, std::vector<Pathway::Line>& lines) {
		Clear(g);
		for (auto&& line : lines) {
			Insert(g, line);
		}
	}

	inline void FullSync(wxGrid* const& g, std::vector<Pathway::Point>& points) {
		Clear(g);
		for (auto&& point : points) {
			Insert(g, point);
		}
	}



	// todo: changed 事件处理 从 grid 读数据到 data

}
