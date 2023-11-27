unit unChooseBox;
interface uses
  Windows,Messages,SysUtils,Variants,Classes,Graphics,Controls,Forms,
  Dialogs,StdCtrls,ExtCtrls,ComCtrls,ImgList, Buttons;
type
  TFRM_SKYCHOOSE = class(TForm)
    Bevel1: TBevel;
    _btnOK: TButton;
    _btnCancel: TButton;
    _lvwList: TListView;
    ImageList1: TImageList;
    Btn_Refresh: TBitBtn;
    procedure _btnCancelClick(Sender: TObject);
    procedure _btnOKClick(Sender: TObject);
    procedure _lvwListClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure Btn_RefreshClick(Sender: TObject);
  private
    {Private declarations}
  public
    {Public declarations}
  end;

var FRM_SKYCHOOSE: TFRM_SKYCHOOSE;
    _SkyBoxFolder: string;

implementation uses unEditor,GREngine_h,unFileEditor;
{$R *.dfm}

//------------------------------------------------------------------------------
// Name: TFRM_SKYCHOOSE.FormCreate()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_SKYCHOOSE.FormCreate(Sender: TObject);
begin
  _SkyBoxFolder:= (ExtractFilePath(ParamStr(0))+'Textures\SkyBox\');
end; //EndFormCreateProcedure

//------------------------------------------------------------------------------
// Name: TFRM_SKYCHOOSE.FormShow()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_SKYCHOOSE.FormShow(Sender: TObject);
begin
  Btn_Refresh.Click();
end; //EndFormShowProcedure

//------------------------------------------------------------------------------
// Name: TFRM_SKYCHOOSE.Btn_RefreshClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_SKYCHOOSE.Btn_RefreshClick(Sender: TObject);
begin
  _BrowseFolder(_ReadDirectory(_SkyBoxFolder,Application.Handle,False),_lvwList);
end; //EndBtn_RefreshClickProcedure

//------------------------------------------------------------------------------
// Name: TFRM_SKYCHOOSE._btnCancelClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_SKYCHOOSE._btnCancelClick(Sender: TObject);
begin
  Close();
end; //End_btnCancelClickProcedure

//------------------------------------------------------------------------------
// Name: TFRM_SKYCHOOSE._btnOKClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_SKYCHOOSE._btnOKClick(Sender: TObject);
var _LItem: TListItem;
    _FileCheck,_Name: string;
    I: Integer;
begin
  _LItem:= _lvwList.Selected;
  _Name:= _LItem.Caption;

  //Check On Valid SkyBox Materials In Selected Folder
  _FileCheck:=  _SkyBoxFolder+_Name;
  if ((not FileExists(_FileCheck+'\zneg.png')) or
  (not FileExists(_FileCheck+'\xpos.png')) or
  (not FileExists(_FileCheck+'\zpos.png')) or
  (not FileExists(_FileCheck+'\xneg.png')) or
  (not FileExists(_FileCheck+'\yneg.png')) or
  (not FileExists(_FileCheck+'\ypos.png'))) then begin
  ShowMessage('Данная папка не содержит SkyBox элементов. '+
  'Убедитесь, что в папке содержатся все файлы типа *.png'); Exit; end;

  //If Is Ok Then Set SkyBox Materials Into The Engine
  for I:= 0 to 5 do GR_SetSkyBoxTexModel(I,_Name);
  _SkyBoxName:= _Name;
  //Close();
end; //End_btnOKClickProcedure

//------------------------------------------------------------------------------
// Name: TFRM_SKYCHOOSE._lvwListClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_SKYCHOOSE._lvwListClick(Sender: TObject);
begin
  if (_lvwList.Items.Count = 0) then begin _btnOK.Enabled:= False; Exit; end;
  if (_lvwList.SelCount = 0) then begin _btnOK.Enabled:= False; Exit; end;
  _btnOK.Enabled:= True;
end; //End_lvwListClickProcedure

end.
