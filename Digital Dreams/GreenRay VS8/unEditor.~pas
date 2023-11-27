{*******************************************************************************
// It's Unofficial Version Of The GreenRay Editor v.1.0.0.1
// unEditor.pas
// It's An GreenRay Editor Application For Manipulations Under Base Engine.
// Made Specially For Implement Visual Engine Parameters.
// Date Creation: 29 August 2005
// Last Changing: 6 January 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************}
unit unEditor;
interface uses
  Windows,Messages,SysUtils,Variants,Classes,Graphics,Controls,Forms,
  Dialogs,Menus,ComCtrls,Buttons,ToolWin,ExtCtrls,StdCtrls,ImgList;
type
  TFRM_EDITOR = class(TForm)
    CoolBar1: TCoolBar;
    ToolBar2: TToolBar;
    ToolButton1: TToolButton;
    _btnControl: TSpeedButton;
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    _About: TMenuItem;
    _Exit: TMenuItem;
    StatusBar1: TStatusBar;
    _pnlOutput: TPanel;
    _pnlTools: TPanel;
    _tmrRender: TTimer;
    _grbFill: TGroupBox;
    _rbtnSolid: TRadioButton;
    _rbtnWireframe: TRadioButton;
    _rbtnPoint: TRadioButton;
    _grbBColor: TGroupBox;
    _TrackRed: TTrackBar;
    _lblRed: TLabel;
    _RValue: TLabel;
    _GValue: TLabel;
    _BValue: TLabel;
    _TrackGreen: TTrackBar;
    _TrackBlue: TTrackBar;
    _lblGreen: TLabel;
    _lblBlue: TLabel;
    _btnLeft1: TSpeedButton;
    _btnRight1: TSpeedButton;
    _btnLeft2: TSpeedButton;
    _btnLeft3: TSpeedButton;
    _btnRight2: TSpeedButton;
    _btnRight3: TSpeedButton;
    Options1: TMenuItem;
    _ChooseSky: TMenuItem;
    N1: TMenuItem;
    _lblMesh: TLabel;
    Lvw_Sounds: TListView;
    _grbTexturing: TGroupBox;
    _lblFrontWall: TLabel;
    _lblBackWall: TLabel;
    _lblRightWall: TLabel;
    _lblLeftWall: TLabel;
    _lblFloor: TLabel;
    _lblCeiling: TLabel;
    Button1: TButton;
    Btn_Sound: TSpeedButton;
    _spdSkyBox: TSpeedButton;
    _cboBackWall: TComboBoxEx;
    _cboLeftWall: TComboBoxEx;
    _cboFrontWall: TComboBoxEx;
    _cboRightWall: TComboBoxEx;
    _cboFloor: TComboBoxEx;
    _cboCeiling: TComboBoxEx;
    _grbCamera: TGroupBox;
    _TrackCamera: TTrackBar;
    _lblCamera: TLabel;
    _lblSVal: TLabel;
    _btnMaxValue: TSpeedButton;
    _btnMinValue: TSpeedButton;
    _btnNoClip: TSpeedButton;
    Lst_Icons: TImageList;
    Pop_Sounds: TPopupMenu;
    RefreshList: TMenuItem;
    PlaySound1: TMenuItem;
    N2: TMenuItem;
    FuckVitiaInAss1: TMenuItem;
    procedure _tmrRenderTimer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure _TrackRedChange(Sender: TObject);
    procedure _btnControlClick(Sender: TObject);
    procedure _rbtnSolidClick(Sender: TObject);
    procedure _btnLeft1Click(Sender: TObject);
    procedure _btnRight1Click(Sender: TObject);
    procedure _AboutClick(Sender: TObject);
    procedure _ChooseSkyClick(Sender: TObject);
    procedure _ExitClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure _TrackCameraChange(Sender: TObject);
    procedure _btnMaxValueClick(Sender: TObject);
    procedure _btnMinValueClick(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure _btnNoClipClick(Sender: TObject);
    procedure RefreshListClick(Sender: TObject);
    procedure Lvw_SoundsDblClick(Sender: TObject);
    procedure Btn_SoundClick(Sender: TObject);
  private
    {Private declarations}
    procedure _WMGetMinMaxInfo(var _Msg: TWMGetMinMaxInfo); message WM_GETMINMAXINFO;
  public
    {Public declarations}
  end;

var FRM_EDITOR: TFRM_EDITOR;
    _SkyBoxName: string;
implementation uses unAbout,unChooseBox,unLogo,unFileEditor,
//#include <GREngine.h>
GREngine_h;
{$R *.dfm}

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR._WMGetMinMaxInfo()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR._WMGetMinMaxInfo(var _Msg: TWMGetMinMaxInfo);
begin
  inherited;
  _Msg.MinMaxInfo^.ptMinTrackSize:= Point(859,670); //MinForm Size
end; //EndWMGetMinMaxInfoProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR._tmrRenderTimer()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR._tmrRenderTimer(Sender: TObject);
begin
  RenderingDirect3D();
end; //End_tmrRenderTimerProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR.FormCreate()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR.FormCreate(Sender: TObject);
var _WPos,_FillMode,I: Integer;
begin
  GR_InitializeMyGraphics(); //Direct3D In GreenRay Editor Window Init

  //Load GreenRay Editor Configuration
  with TStringList.Create do try
  LoadFromFile(ExtractFilePath(ParamStr(0))+'GREditor.ini');

  //Disposition Directives
  _WPos:= StrToInt(Copy(Strings[5],16,20));
  if (_WPos = 1) then begin
  Top:= StrToInt(Copy(Strings[6],5,5));
  Left:= StrToInt(Copy(Strings[7],6,5));
  Height:= StrToInt(Copy(Strings[8],8,5));
  Width:= StrToInt(Copy(Strings[9],7,5)); end;
  if (_WPos = 2) then WindowState:= wsMaximized;

  //BackBufferColor States
  _TrackRed.Position:= StrToInt(Copy(Strings[12],20,5));   //R
  _TrackGreen.Position:= StrToInt(Copy(Strings[13],22,5)); //G
  _TrackBlue.Position:= StrToInt(Copy(Strings[14],21,5));  //B

  //FillMode States
  _FillMode:= StrToInt(Copy(Strings[17],10,5));
  if (_FillMode = 1) then _rbtnSolid.Checked:= True;     //Solid
  if (_FillMode = 2) then _rbtnWireframe.Checked:= True; //Wireframe
  if (_FillMode = 3) then _rbtnPoint.Checked:= True;     //Point

  //SkyBox States
  _SkyBoxName:= Copy(Strings[20],12,50);
  for I:= 0 to 5 do GR_SetSkyBoxTexModel(I,_SkyBoxName); //Set Loded SkyBox Textures

  //Tracking Camera Speed States
  _TrackCamera.Position:= StrToInt(Copy(Strings[23],23,5));
  _lblSVal.Caption:= (CameraSpeed);

  finally Free; end;

  FRM_LOGO._tmrLoad.Enabled:= True; //Hide FRM_LOGO With Load Timer
  RefreshList.Click();
end; //EndFormCreateProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR.FormClose()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR.FormClose(Sender: TObject; var Action: TCloseAction);
var F_Inp: TextFile;
begin
  _tmrRender.Enabled:= False;
  ReleaseDirect3D();
  //Save GreenRay Editor Configuration
  AssignFile(F_Inp,(ExtractFilePath(ParamStr(0))+'GREditor.ini'));
  Rewrite(F_Inp);
  WriteLn(F_Inp,'###This GreenRay Editor Configuration File:');
  WriteLn(F_Inp,'');
  WriteLn(F_Inp,'Author Rights By: (C)DDD Digital Dreams Development Inc., 2006');
  WriteLn(F_Inp,'');
  WriteLn(F_Inp,'[WindowDispositionDirectives]');
  if (FRM_EDITOR.WindowState = wsNormal) then WriteLn(F_Inp,'WindowPosition=',IntToStr(1));
  if (FRM_EDITOR.WindowState = wsMaximized) then WriteLn(F_Inp,'WindowPosition=',IntToStr(2));
  WriteLn(F_Inp,'Top=',IntToStr(Top));
  WriteLn(F_Inp,'Left=',IntToStr(Left));
  WriteLn(F_Inp,'Height=',IntToStr(Height));
  WriteLn(F_Inp,'Width=',IntToStr(Width));
  WriteLn(F_Inp,'');
  WriteLn(F_Inp,'[BackBufferColorDirectives]');
  WriteLn(F_Inp,'_TrackRed.Position=',IntToStr(_TrackRed.Position));     //R
  WriteLn(F_Inp,'_TrackGreen.Position=',IntToStr(_TrackGreen.Position)); //G
  WriteLn(F_Inp,'_TrackBlue.Position=',IntToStr(_TrackBlue.Position));   //B
  WriteLn(F_Inp,'');
  WriteLn(F_Inp,'[FillModeDirectives]');
  if (_rbtnSolid.Checked) then WriteLn(F_Inp,'FillMode=',IntToStr(gr_Solid));         //Solid
  if (_rbtnWireframe.Checked) then WriteLn(F_Inp,'FillMode=',IntToStr(gr_Wireframe)); //Wireframe
  if (_rbtnPoint.Checked) then WriteLn(F_Inp,'FillMode=',IntToStr(gr_Point));         //Point
  WriteLn(F_Inp,'');
  WriteLn(F_Inp,'[SkyBoxDirectives]');
  WriteLn(F_Inp,'SkyBoxName=',_SkyBoxName);
  WriteLn(F_Inp,'');
  WriteLn(F_Inp,'[TrackCameraDirectives]');
  WriteLn(F_Inp,'_TrackCamera.Position=',IntToStr(_TrackCamera.Position)); //Camera Speed Position
  CloseFile(F_Inp);

  FRM_LOGO.Close(); //Unload FRM_LOGO From Memory
end; //EndFormCloseProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR.FormKeyDown()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key = 80{P}) then SetDebugConsole();
  //if (Key = 192{~}) then
end; //EndFormKeyDownProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR._TrackRedChange()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR._TrackRedChange(Sender: TObject);
begin
  GR_SetTrackingColor(Sender);
end; //End_TrackRedChangeProcedure

//-------------------------_spdControlClickDirectives---------------------------

procedure TFRM_EDITOR._btnControlClick(Sender: TObject);
begin
  GR_ConnectToCamera(True,False);
  GR_SetCameraSpeed(StrToFloat(CameraSpeed)); //Setting Up To Engine Camera Move Speed
end; //End_spdControlClickProcedure

procedure TFRM_EDITOR._btnNoClipClick(Sender: TObject);
begin
  GR_ConnectToCamera(True,True);
  GR_SetCameraSpeed(StrToFloat(CameraSpeed)); //Setting Up To Engine Camera Move Speed
end; //End_btnNoClipClickProcedure

//-------------------------_rbtnSolidClickDirectives----------------------------

procedure TFRM_EDITOR._rbtnSolidClick(Sender: TObject);
begin
  GR_SetFillMode(Sender);
end; //End_rbtnSolidClickDirectivesProcedure

//-------------------------_btnLeft1ClickDirectives-----------------------------

procedure TFRM_EDITOR._btnLeft1Click(Sender: TObject);
begin
  GR_SetMinColorPosition(Sender);
end; //End_btnLeft1ClickDirectivesProcedure

//------------------------_btnRight1ClickDirectives-----------------------------

procedure TFRM_EDITOR._btnRight1Click(Sender: TObject);
begin
  GR_SetMaxColorPosition(Sender);
end; //End_btnRight1ClickDirectivesProcedure

//--------------------------_AboutClickDirectives-------------------------------

procedure TFRM_EDITOR._AboutClick(Sender: TObject);
begin
  FRM_ABOUT.ShowModal();
end; //End_AboutClickDirectivesProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR._ChooseSkyClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR._ChooseSkyClick(Sender: TObject);
begin
  FRM_SKYCHOOSE.Show();
end; //End_ChooseSkyClickProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR._ExitClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR._ExitClick(Sender: TObject);
begin
  Close();
end; //End_ExitClickProcedure

procedure TFRM_EDITOR.Button1Click(Sender: TObject);
begin
  GR_SetTextureModelToEngine(0); //Tex Back
  GR_SetTextureModelToEngine(1); //Tex Left
  GR_SetTextureModelToEngine(2); //Tex Front
  GR_SetTextureModelToEngine(3); //Tex Right
  GR_SetTextureModelToEngine(4); //Tex Floor
  GR_SetTextureModelToEngine(5); //Tex Ceiling
end;

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR._TrackCameraChange()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR._TrackCameraChange(Sender: TObject);
var _CurrPos: Integer;
begin
  _CurrPos:= _TrackCamera.Position;
  if (_CurrPos < 10.0) then CameraSpeed:= ('0,00'+IntToStr(_CurrPos));
  if (_CurrPos >= 10.0) then CameraSpeed:= ('0,0'+IntToStr(_CurrPos));
  if (_CurrPos >= 100.0) then CameraSpeed:= ('0,'+IntToStr(_CurrPos));

  _lblSVal.Caption:= (CameraSpeed);
  //SetCameraSpeed(StrToFloat(CameraSpeed)); //Setting Up To Engine Camera Move Speed
end; //End_TrackCameraChangeProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR._btnMaxValueClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR._btnMaxValueClick(Sender: TObject);
var _Pos: Integer;
begin
  _Pos:= _TrackCamera.Position;
  if (_Pos = 999) then Exit;
  Inc(_Pos); _TrackCamera.Position:= _Pos;
end; //End_btnMaxValueClickProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR._btnMinValueClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR._btnMinValueClick(Sender: TObject);
var _Pos: Integer;
begin
  _Pos:= _TrackCamera.Position;
  if (_Pos = 0) then Exit;
  Dec(_Pos); _TrackCamera.Position:= _Pos;
end; //End_btnMinValueClickProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR.RefreshListClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR.RefreshListClick(Sender: TObject);
var _Mp3Folder: string;
begin
  _Mp3Folder:= (ExtractFilePath(ParamStr(0))+'Music\Mp3\');
  _BrowseFolder(_ReadDirectory(_Mp3Folder,Application.Handle,True),Lvw_Sounds);
end; //EndRefreshListClickProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR.Lvw_SoundsDblClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR.Lvw_SoundsDblClick(Sender: TObject);
var _LItem: TListItem;
    _FileName,_Folder,_Name: string;
    _ResName: PWideChar;
begin
  Playing:= False;
  if (Lvw_Sounds.Items.Count = 0) then Exit;
  if (Lvw_Sounds.SelCount = 0) then Exit;
  _LItem:= Lvw_Sounds.Selected;

  _FileName:= _LItem.Caption;
  _Folder:= (ExtractFilePath(ParamStr(0))+'Music\Mp3\');
  _Name:= _Folder+_FileName;

  if (not FileExists(_Name)) then begin
  ShowMessage('Файл удалён, обновите список!');
  end else begin
  _ResName:= _EncodeToUCS(_Name); //Prepare String To UCS Format
  GR_PlaybackSelectedSound(_ResName,False); //PlayBack Some Sound From Engine
  Playing:= True; end;
end; //EndLvw_SoundsDblClickProcedure

//------------------------------------------------------------------------------
// Name: TFRM_EDITOR.Btn_SoundClick()
// Desc:
//------------------------------------------------------------------------------
procedure TFRM_EDITOR.Btn_SoundClick(Sender: TObject);
var _Folder: string;
begin
  _Folder:= (ExtractFilePath(ParamStr(0))+'Textures\HUD\Editor\');

  if (Playing) then begin
  GR_PlaySound(False); //Stop Playing
  Btn_Sound.Glyph.LoadFromFile(_Folder+'MusicOFF.bmp');
  Playing:= False;
  end else begin
  GR_PlaySound(True); //Playback Now
  Btn_Sound.Glyph.LoadFromFile(_Folder+'MusicON.bmp');
  Playing:= True; end;
end; //EndBtn_SoundClickProcedure

end.
