object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'RDP Wrapper Configuration and Check utility by sebaxakerhtc'
  ClientHeight = 442
  ClientWidth = 566
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poDesktopCenter
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object rgNLA: TRadioGroup
    Left = 290
    Top = 195
    Width = 268
    Height = 102
    BiDiMode = bdLeftToRight
    Caption = 'Authentication Mode'
    DefaultHeaderFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -13
    HeaderFont.Name = 'Tahoma'
    HeaderFont.Style = [fsBold]
    Items.Strings = (
      'GUI Authentication Only'
      'Default RDP Authentication'
      'Network Level Authentication')
    ParentBiDiMode = False
    ParentFont = False
    TabOrder = 2
    OnClick = cbAllowTSConnectionsClick
  end
  object bOK: TButton
    Left = 0
    Top = 404
    Width = 138
    Height = 30
    Caption = 'OK'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ModalResult = 1
    ParentFont = False
    TabOrder = 4
    OnClick = bOKClick
  end
  object bCancel: TButton
    Left = 150
    Top = 404
    Width = 130
    Height = 30
    Caption = 'Cancel'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ModalResult = 2
    ParentFont = False
    TabOrder = 5
    OnClick = bCancelClick
  end
  object bApply: TButton
    Left = 290
    Top = 404
    Width = 130
    Height = 30
    Caption = 'Apply'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    OnClick = bApplyClick
  end
  object rgShadow: TRadioGroup
    Left = 8
    Top = 195
    Width = 272
    Height = 143
    BiDiMode = bdLeftToRight
    Caption = 'Session Shadowing Mode'
    DefaultHeaderFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -13
    HeaderFont.Name = 'Tahoma'
    HeaderFont.Style = [fsBold]
    Items.Strings = (
      'Disable Shadowing'
      'Full access with user'#39's permission'
      'Full access without permission'
      'View only with user'#39's permission'
      'View only without permission')
    ParentBiDiMode = False
    ParentFont = False
    TabOrder = 3
    OnClick = cbAllowTSConnectionsClick
  end
  object bLicense: TButton
    Left = 432
    Top = 404
    Width = 130
    Height = 30
    Caption = 'View license...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
    OnClick = bLicenseClick
  end
  object gbDiag: TGroupBox
    Left = 8
    Top = 6
    Width = 272
    Height = 183
    BiDiMode = bdLeftToRight
    Caption = ' Diagnostics'
    DefaultHeaderFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -13
    HeaderFont.Name = 'Tahoma'
    HeaderFont.Style = [fsBold]
    ParentBiDiMode = False
    ParentFont = False
    TabOrder = 0
    object lListener: TLabel
      Left = 7
      Top = 90
      Width = 99
      Height = 19
      Caption = 'Listener state:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object lService: TLabel
      Left = 7
      Top = 68
      Width = 94
      Height = 19
      Caption = 'Service state:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object lsListener: TLabel
      Left = 117
      Top = 90
      Width = 76
      Height = 19
      Caption = 'Unknown'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lsService: TLabel
      Left = 117
      Top = 68
      Width = 76
      Height = 19
      Caption = 'Unknown'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lsTSVer: TLabel
      Left = 117
      Top = 112
      Width = 76
      Height = 19
      Caption = 'Unknown'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lsWrapper: TLabel
      Left = 117
      Top = 24
      Width = 76
      Height = 19
      Caption = 'Unknown'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lsWrapVer: TLabel
      Left = 117
      Top = 46
      Width = 76
      Height = 19
      Caption = 'Unknown'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lTSVer: TLabel
      Left = 7
      Top = 112
      Width = 86
      Height = 19
      Caption = 'termsrv ver.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object lWrapper: TLabel
      Left = 7
      Top = 24
      Width = 104
      Height = 19
      Caption = 'Wrapper state:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object lWrapVer: TLabel
      Left = 7
      Top = 46
      Width = 92
      Height = 19
      Caption = 'Wrapper ver.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object lsSuppVer: TLabel
      Left = 46
      Top = 137
      Width = 155
      Height = 25
      Caption = '[support level]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object gbGeneral: TGroupBox
    Left = 290
    Top = 8
    Width = 268
    Height = 181
    BiDiMode = bdLeftToRight
    Caption = '      General Settings'
    DefaultHeaderFont = False
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -13
    HeaderFont.Name = 'Tahoma'
    HeaderFont.Style = [fsBold]
    ParentBiDiMode = False
    TabOrder = 1
    object lRDPPort: TLabel
      Left = 19
      Top = 29
      Width = 70
      Height = 19
      Caption = 'RDP port:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object cbAllowTSConnections: TCheckBox
      Left = 16
      Top = 54
      Width = 209
      Height = 38
      Caption = 'Enable Remote Desktop'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = cbAllowTSConnectionsClick
    end
    object cbSingleSessionPerUser: TCheckBox
      Left = 16
      Top = 91
      Width = 209
      Height = 28
      Caption = 'Single session per user'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = cbAllowTSConnectionsClick
    end
    object cbHideUsers: TCheckBox
      Left = 16
      Top = 114
      Width = 257
      Height = 39
      Caption = 'Hide users on logon screen'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = cbAllowTSConnectionsClick
    end
    object seRDPPort: TSpinEdit
      Left = 108
      Top = 26
      Width = 93
      Height = 29
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxValue = 65535
      MinValue = 0
      ParentFont = False
      TabOrder = 1
      Value = 0
      OnChange = seRDPPortChange
    end
    object cbCustomPrg: TCheckBox
      Left = 16
      Top = 145
      Width = 225
      Height = 36
      Hint = 'The author of renaming: "sashaqwert"'
      Caption = 'Allow unlisted RemoteApps'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = cbAllowTSConnectionsClick
    end
  end
  object gbLocalRDPChecker: TGroupBox
    Left = 8
    Top = 344
    Width = 545
    Height = 54
    Hint = 
      'Choose your resolution. We prefore "mstsc" button. You can click' +
      ' every button many times ;)'
    Caption = '         Check yor settings with mstsc'
    DefaultHeaderFont = False
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -13
    HeaderFont.Name = 'Tahoma'
    HeaderFont.Style = [fsBold]
    ParentShowHint = False
    ShowHint = True
    TabOrder = 8
    object bmstsc: TButton
      Left = 11
      Top = 21
      Width = 100
      Height = 25
      Caption = 'Fullscreen'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = bmstscClick
    end
    object b800x600: TButton
      Left = 117
      Top = 21
      Width = 100
      Height = 25
      Caption = '800x600'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = b800x600Click
    end
    object b1024x768: TButton
      Left = 223
      Top = 21
      Width = 100
      Height = 25
      Caption = '1024x768'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = b1024x768Click
    end
    object b1366x768: TButton
      Left = 329
      Top = 21
      Width = 100
      Height = 25
      Caption = '1366x768'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = b1366x768Click
    end
    object b1920x1080: TButton
      Left = 435
      Top = 21
      Width = 100
      Height = 25
      Caption = '1920x1080'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = b1920x1080Click
    end
  end
  object bUpdateINI: TButton
    Left = 290
    Top = 303
    Width = 130
    Height = 35
    Caption = 'Update INI'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 9
    OnClick = bUpdateINIClick
  end
  object bRestartTS: TButton
    Left = 426
    Top = 303
    Width = 127
    Height = 35
    Caption = 'Restart TermService'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 10
    OnClick = bRestartTSClick
  end
  object Timer: TTimer
    Interval = 250
    OnTimer = TimerTimer
    Left = 248
    Top = 27
  end
end
