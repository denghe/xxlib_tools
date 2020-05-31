#pragma once
#include <wx/wx.h>

// 下面这两段参考自 wxFormBuilder 生成物

///////////////////////////////////////////////////////////////////////////

class FrameBase : public wxFrame
{
private:

protected:

	// Virtual event handlers, overide them in your derived class
	virtual void FrameOnLeftDClick(wxMouseEvent& event) { event.Skip(); }
	virtual void FrameOnPaint(wxPaintEvent& event) { event.Skip(); }
	virtual void ButtonOnClick(wxCommandEvent& event) { event.Skip(); }


public:

	FrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(794, 513), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~FrameBase();

};


///////////////////////////////////////////////////////////////////////////


FrameBase::FrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(238, 255, 254));

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(FrameBase::FrameOnLeftDClick));
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(FrameBase::FrameOnPaint));
}

FrameBase::~FrameBase()
{
	// Disconnect Events
	this->Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(FrameBase::FrameOnLeftDClick));
	this->Disconnect(wxEVT_PAINT, wxPaintEventHandler(FrameBase::FrameOnPaint));
}

///////////////////////////////////////////////////////////////////////////





struct Pos {
	float x = 0, y = 0;

	inline bool operator==(const Pos& v) const noexcept {
		return x == v.x && y == v.y;
	}
	inline Pos& operator+=(Pos const& v) noexcept {
		x += v.x;
		y += v.y;
		return *this;
	}
	inline Pos operator+(Pos const& v) const noexcept {
		return Pos{ x + v.x, y + v.y };
	}
	inline Pos operator-(Pos const& v) const noexcept {
		return Pos{ x - v.x, y - v.y };
	}
	inline Pos operator*(float const& s) const noexcept {
		return Pos{ x * s, y * s };
	}
	inline Pos operator/(float const& s) const noexcept {
		return Pos{ x / s, y / s };
	}
};

inline void BezierToPoints(std::vector<Pos>& ps, std::vector<Pos> const& bs, int numSegments = 50) {
	auto len = (bs.size() - 1) / 3;
	ps.resize(numSegments * len);
	auto step = 1.0f / numSegments;
	for (size_t i = 0; i < numSegments; ++i) {
		auto t = step * i;
		auto t1 = 1 - t;
		for (size_t j = 0; j < len; ++j)
		{
			auto idx = j * 3;
			ps[j * numSegments + i] = bs[idx] * t1 * t1 * t1
				+ bs[idx + 1] * 3 * t * t1 * t1
				+ bs[idx + 2] * 3 * t * t * (1 - t)
				+ bs[idx + 3] * t * t * t;
		}
	}
}

inline void CurveToBezier(std::vector<Pos>& bs, std::vector<Pos> const& cs, float tension = 0.3f) {
	auto n = cs.size();
	auto len = n * 3 - 2;
	bs.resize(len);

	bs[0] = cs[0];
	bs[1] = (cs[1] - cs[0]) * tension + cs[0];

	for (size_t i = 0; i < n - 2; i++) {
		auto diff = (cs[i + 2] - cs[i]) * tension;
		bs[3 * i + 2] = cs[i + 1] - diff;
		bs[3 * i + 3] = cs[i + 1];
		bs[3 * i + 4] = cs[i + 1] + diff;
	}
	bs[len - 2] = (cs[n - 2] - cs[n - 1]) * tension + cs[n - 1];
	bs[len - 1] = cs[n - 1];
}





struct Frame;

struct Button : public wxButton {
	int id = 0;
	Pos pos;
	Button(Frame* f, int id, Pos const& pos);
};

struct Frame : public FrameBase {
	FrameBase::FrameBase;
	~Frame();

	int buttonId = 0;
	std::vector<Button*> buttons;

	void NewButton(int id, Pos const& pos);

	virtual void FrameOnLeftDClick(wxMouseEvent& event) override;
	virtual void FrameOnPaint(wxPaintEvent& event) override;
	virtual void ButtonOnClick(wxCommandEvent& event) override;
};




Button::Button(Frame* f, int id, Pos const& pos)
	: wxButton(f, wxID_ANY, wxEmptyString, wxPoint(pos.x - 7, pos.y - 7), wxSize(15, 15))
	, id(id)
	, pos(pos) {
}



void Frame::NewButton(int id, Pos const& pos) {
	auto&& btn = buttons.emplace_back(new Button(this, id, pos));
	btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frame::ButtonOnClick), nullptr, this);
}

void Frame::FrameOnLeftDClick(wxMouseEvent& event) {
	NewButton(++buttonId, { (float)event.GetX(), (float)event.GetY() });
}

Frame::~Frame() {
	for (auto&& btn : buttons) {
		btn->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frame::ButtonOnClick), nullptr, this);
	}
}

void Frame::FrameOnPaint(wxPaintEvent& event) {
	wxPaintDC dc(this);
	//dc.SetBrush(*wxGREEN_BRUSH);
	dc.SetPen(wxPen(wxColor(255, 0, 0), 5));

	if (buttons.size() > 1) {
		std::vector<Pos> cs, bs, ps;

		for (auto&& btn : buttons) {
			cs.push_back(btn->pos);
		}

		CurveToBezier(bs, cs);
		BezierToPoints(ps, bs, 500);

		for (auto&& pos : ps) {
			dc.DrawPoint({ (int)pos.x, (int)pos.y });
		}
	}
}

void Frame::ButtonOnClick(wxCommandEvent& event) {
	auto btn = (Button*)event.GetEventObject();
	this->SetTitle(std::to_string(btn->id));
	Refresh();
}



class MyApp : public wxApp
{
public:
	virtual bool OnInit() {
		auto frame = new Frame(nullptr, wxID_ANY, L"Hello World");
		frame->Show(true);
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);
