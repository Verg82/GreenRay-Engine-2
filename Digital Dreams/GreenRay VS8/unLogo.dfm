object FRM_LOGO: TFRM_LOGO
  Left = 316
  Top = 325
  BorderStyle = bsNone
  Caption = 'Logo'
  ClientHeight = 375
  ClientWidth = 562
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object _imgLogo: TImage
    Left = 0
    Top = 0
    Width = 562
    Height = 375
    Align = alClient
  end
  object _tmrLoad: TTimer
    Enabled = False
    Interval = 500
    OnTimer = _tmrLoadTimer
    Left = 8
    Top = 8
  end
end
