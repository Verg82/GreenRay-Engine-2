unit unLogo;
interface uses
  Windows,Messages,SysUtils,Variants,Classes,Graphics,Controls,Forms,
  Dialogs,JPEG,ExtCtrls;
type
  TFRM_LOGO = class(TForm)
    _tmrLoad: TTimer;
    _imgLogo: TImage;
    procedure _tmrLoadTimer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    {Private declarations}
  public
    {Public declarations}
  end;

var FRM_LOGO: TFRM_LOGO;
implementation uses unEditor;
{$R *.dfm}

//--------------------------_tmrLoadTimerDirectives-----------------------------

procedure TFRM_LOGO._tmrLoadTimer(Sender: TObject);
begin
  _tmrLoad.Enabled:= False;
  FRM_LOGO.Hide();
  FRM_EDITOR.Show();
  _imgLogo.Picture:= nil; _imgLogo.Destroy(); //Release Logo Image
end; //End_tmrLoadTimerDirectivesProcedure

//----------------------------FormCreateDirectives------------------------------

procedure TFRM_LOGO.FormCreate(Sender: TObject);
begin
  _imgLogo.Picture.LoadFromFile(ExtractFilePath(ParamStr(0))+'Textures\Logo\GRLogo02.jpg');
  FRM_LOGO.Height:= _imgLogo.Picture.Height;
  FRM_LOGO.Width:= _imgLogo.Picture.Width;
end; //EndFormCreateDirectivesProcedure

end.
 