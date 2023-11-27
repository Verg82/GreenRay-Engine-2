program GREditor;
uses
  Forms,
  unEditor in 'unEditor.pas' {FRM_EDITOR},
  unAbout in 'unAbout.pas' {FRM_ABOUT},
  unChooseBox in 'unChooseBox.pas' {FRM_SKYCHOOSE},
  unLogo in 'unLogo.pas' {FRM_LOGO},
  unFileEditor in 'EditorSource\unFileEditor.pas';

{$R *.res}

//------------------------------------------------------------------------------

begin
  Application.Initialize();
  Application.CreateForm(TFRM_LOGO, FRM_LOGO);
  FRM_LOGO.Show(); FRM_LOGO.Update();

  Application.Title:= 'GreenRay Engine';
  Application.CreateForm(TFRM_EDITOR, FRM_EDITOR);
  Application.CreateForm(TFRM_ABOUT, FRM_ABOUT);
  Application.CreateForm(TFRM_SKYCHOOSE, FRM_SKYCHOOSE);
  Application.Run();
end.
