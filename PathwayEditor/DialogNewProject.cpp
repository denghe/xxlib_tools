#include "DialogNewProject.h"

DialogNewProject::DialogNewProject( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("design environment settings"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("design width:"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
	m_staticText2->Wrap( -1 );
	fgSizer1->Add( m_staticText2, 0, wxALL, 5 );

	textCtrlWidth = new wxTextCtrl( this, wxID_ANY, wxT("1280"), wxDefaultPosition, wxSize( 200,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !textCtrlWidth->HasFlag( wxTE_MULTILINE ) )
	{
	textCtrlWidth->SetMaxLength( 4 );
	}
	#else
	textCtrlWidth->SetMaxLength( 4 );
	#endif
	fgSizer1->Add( textCtrlWidth, 0, wxALL, 5 );

	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("design height:"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
	m_staticText21->Wrap( -1 );
	fgSizer1->Add( m_staticText21, 0, wxALL, 5 );

	textCtrlHeight = new wxTextCtrl( this, wxID_ANY, wxT("720"), wxDefaultPosition, wxSize( 200,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !textCtrlHeight->HasFlag( wxTE_MULTILINE ) )
	{
	textCtrlHeight->SetMaxLength( 4 );
	}
	#else
	textCtrlHeight->SetMaxLength( 4 );
	#endif
	fgSizer1->Add( textCtrlHeight, 0, wxALL, 5 );

	m_staticText211 = new wxStaticText( this, wxID_ANY, wxT("safe length:"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
	m_staticText211->Wrap( -1 );
	fgSizer1->Add( m_staticText211, 0, wxALL, 5 );

	textCtrlSafeLength = new wxTextCtrl( this, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize( 200,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !textCtrlSafeLength->HasFlag( wxTE_MULTILINE ) )
	{
	textCtrlSafeLength->SetMaxLength( 4 );
	}
	#else
	textCtrlSafeLength->SetMaxLength( 4 );
	#endif
	fgSizer1->Add( textCtrlSafeLength, 0, wxALL, 5 );


	bSizer1->Add( fgSizer1, 1, wxEXPAND, 5 );

	buttonSumbit = new wxButton( this, wxID_ANY, wxT("&Submit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( buttonSumbit, 0, wxALL|wxALIGN_RIGHT, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	buttonSumbit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogNewProject::buttonSumbitOnButtonClick ), NULL, this );
}

DialogNewProject::~DialogNewProject()
{
	// Disconnect Events
	buttonSumbit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogNewProject::buttonSumbitOnButtonClick ), NULL, this );

}
