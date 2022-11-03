object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Table Loader'
  ClientHeight = 380
  ClientWidth = 561
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 19
  object Grid: TStringGrid
    Left = 0
    Top = 0
    Width = 432
    Height = 360
    Align = alClient
    ColCount = 7
    DefaultColWidth = 56
    FixedCols = 0
    RowCount = 10
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 0
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 360
    Width = 561
    Height = 20
    Panels = <
      item
        Text = 'StatusBar1'
        Width = 50
      end>
    OnClick = StatusBar1Click
  end
  object Panel1: TPanel
    Left = 432
    Top = 0
    Width = 129
    Height = 360
    Align = alRight
    Caption = 'Panel1'
    ShowCaption = False
    TabOrder = 2
    object Edit1: TEdit
      Left = 1
      Top = 1
      Width = 127
      Height = 27
      Hint = 'Filename in this directory'
      Align = alTop
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Text = #1070#1085#1080#1082#1086#1076'.txt'
    end
    object Edit3: TEdit
      Left = 1
      Top = 28
      Width = 127
      Height = 27
      Align = alTop
      TabOrder = 1
      Text = 'iiscbs'
    end
    object IgnoreDelimPack: TCheckBox
      Left = 1
      Top = 55
      Width = 127
      Height = 17
      Align = alTop
      Caption = 'IgnoreDelimPack'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = IgnoreDelimPackClick
    end
    object IgnoreFirstString: TCheckBox
      Left = 1
      Top = 72
      Width = 127
      Height = 17
      Align = alTop
      Caption = 'IgnoreFirstString'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = IgnoreFirstStringClick
    end
    object LoadFromFileBtn: TButton
      Left = 1
      Top = 89
      Width = 127
      Height = 25
      Align = alTop
      Caption = 'LoadFromFile'
      TabOrder = 4
      OnClick = LoadFromFileBtnClick
    end
    object Resour: TButton
      Left = 1
      Top = 114
      Width = 127
      Height = 25
      Align = alTop
      Caption = 'ResourcePrint'
      TabOrder = 5
      OnClick = ResourClick
    end
    object Edit2: TEdit
      Left = 1
      Top = 168
      Width = 127
      Height = 27
      Hint = 'Filename in this directory'
      Align = alTop
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
      Text = #1087#1077#1088#1074#1072#1103
    end
    object GetSection: TButton
      Left = 1
      Top = 195
      Width = 127
      Height = 25
      Align = alTop
      Caption = 'GetSection'
      TabOrder = 7
      OnClick = GetSectionClick
    end
    object Button1: TButton
      Left = 137
      Top = 172
      Width = 32
      Height = 25
      Caption = 'Name'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 8
    end
    object Sections: TMemo
      Left = 1
      Top = 220
      Width = 127
      Height = 139
      Align = alClient
      Lines.Strings = (
        'Sections')
      TabOrder = 9
    end
    object Panel2: TPanel
      Left = 1
      Top = 139
      Width = 127
      Height = 29
      Align = alTop
      Caption = 'Panel2'
      ShowCaption = False
      TabOrder = 10
      object LoadFromList: TButton
        Left = 24
        Top = 1
        Width = 102
        Height = 27
        Align = alRight
        Caption = 'LoadFromList'
        TabOrder = 0
        OnClick = LoadFromListClick
      end
      object RicheD: TCheckBox
        Left = 5
        Top = 6
        Width = 20
        Height = 17
        TabOrder = 1
        OnClick = RicheDClick
      end
    end
  end
  object Rich: TRichEdit
    Left = 104
    Top = 104
    Width = 185
    Height = 89
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      'Rich')
    ParentFont = False
    TabOrder = 3
    Visible = False
    WantTabs = True
  end
  object PopupMenu1: TPopupMenu
    Left = 344
    Top = 192
    object GetCount1: TMenuItem
      Caption = 'GetCount'
    end
  end
end
