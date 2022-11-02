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
  DesignSize = (
    561
    380)
  PixelsPerInch = 96
  TextHeight = 19
  object Grid: TStringGrid
    Left = 0
    Top = 0
    Width = 430
    Height = 380
    Align = alLeft
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 10
    DefaultColWidth = 56
    FixedCols = 0
    RowCount = 10
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 0
  end
  object Load: TButton
    Left = 436
    Top = 136
    Width = 53
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Load'
    TabOrder = 2
    OnClick = LoadClick
  end
  object Sections: TMemo
    Left = 436
    Top = 231
    Width = 123
    Height = 149
    Anchors = [akTop, akRight, akBottom]
    Lines.Strings = (
      'Sections')
    TabOrder = 3
  end
  object IgnoreDelimPack: TCheckBox
    Left = 436
    Top = 65
    Width = 117
    Height = 17
    Caption = 'IgnoreDelimPack'
    TabOrder = 4
    OnClick = IgnoreDelimPackClick
  end
  object IgnoreFirstString: TCheckBox
    Left = 436
    Top = 88
    Width = 117
    Height = 17
    Caption = 'IgnoreFirstString'
    TabOrder = 5
    OnClick = IgnoreFirstStringClick
  end
  object Edit2: TEdit
    Left = 436
    Top = 167
    Width = 121
    Height = 27
    Hint = 'Filename in this directory'
    Anchors = [akTop, akRight]
    ParentShowHint = False
    ShowHint = True
    TabOrder = 6
    Text = #1087#1077#1088#1074#1072#1103
  end
  object GetSection: TButton
    Left = 436
    Top = 200
    Width = 85
    Height = 25
    Caption = 'GetSection'
    TabOrder = 7
    OnClick = GetSectionClick
  end
  object Button1: TButton
    Left = 527
    Top = 200
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
    OnClick = Button1Click
  end
  object Edit3: TEdit
    Left = 436
    Top = 32
    Width = 121
    Height = 27
    Anchors = [akTop, akRight]
    ReadOnly = True
    TabOrder = 9
    Text = 'iiscbs'
  end
  object Edit1: TEdit
    Left = 436
    Top = 8
    Width = 121
    Height = 27
    Hint = 'Filename in this directory'
    Anchors = [akTop, akRight]
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    Text = #1070#1085#1080#1082#1086#1076'.txt'
  end
  object Resour: TButton
    Left = 488
    Top = 136
    Width = 65
    Height = 25
    Caption = 'Resour'
    TabOrder = 10
    OnClick = ResourClick
  end
  object FromFile: TCheckBox
    Left = 436
    Top = 113
    Width = 117
    Height = 17
    Caption = 'FromFile'
    Checked = True
    State = cbChecked
    TabOrder = 11
    OnClick = FromFileClick
  end
  object PopupMenu1: TPopupMenu
    Left = 344
    Top = 192
    object GetCount1: TMenuItem
      Caption = 'GetCount'
      OnClick = GetCount1Click
    end
  end
end
