unit WindowsDarkMode;

// Originally written by Ian Barker
//            https://github.com/checkdigits
//            https://about.me/IanBarker
//            ian.barker@gmail.com
//
// Free software - use for any purpose including commercial use.

interface

// Checks the Windows registry to see if Windows Dark Mode is enabled
function DarkModeIsEnabled: Boolean;

// Automatically sets a Dark Mode theme if Windows is running in Dark Mode
// To use:
//   1. Go to project properties
//   2. Select appearance and choose two or more themes. Note down the names!
//   3. In your FormCreate (or wherever) put the following line:
//      SetAppropriateThemeMode(DarkModeThemeName, LightModeThemeName);
//
//      For example:
//      SetAppropriateThemeMode('Carbon', 'Windows10');
//
procedure SetAppropriateThemeMode(const DarkModeThemeName, LightModeThemeName: string);

// Sets either a Dark Mode or non Dark Mode theme based on the "AsDarkMode" boolean
// For example:
//     SetSpecificThemeMode(False, 'TheDarkModeThemeName', 'TheLightModeThemeName');
//     Would change the application theme to the theme with the name 'TheLightModeThemeName'
//     if it exists.
//
procedure SetSpecificThemeMode(const AsDarkMode: Boolean; const DarkModeThemeName, LightModeThemeName: string);

implementation

uses
  {$IFDEF MSWINDOWS}
  Winapi.Windows,       // for the pre-defined registry key constants
  System.Win.Registry,  // for the registry read access
  {$ENDIF}
  Vcl.Themes;           // Used for access to TStyleManager

function DarkModeIsEnabled: Boolean;
{$IFDEF MSWINDOWS}
const
  REG_PATH = 'Software\Microsoft\Windows\CurrentVersion\Themes\Personalize';
  REG_VALUE = 'AppsUseLightTheme';
var
  Registry: TRegistry;
{$ENDIF}
begin
  Result := False;
  {$IFDEF MSWINDOWS}
  Registry := TRegistry.Create(KEY_READ);
  try
    Registry.RootKey := HKEY_CURRENT_USER;
    if Registry.OpenKeyReadOnly(REG_PATH) then
    try
      if Registry.ValueExists(REG_VALUE) then
        Result := Registry.ReadInteger(REG_VALUE) = 0;
    finally
      Registry.CloseKey;
    end;
  finally
    Registry.Free;
  end;
  {$ELSE}
  {$MESSAGE WARN '"DarkModeIsEnabled" will only work on MS Windows targets'}
  {$ENDIF}
end;

procedure SetAppropriateThemeMode(const DarkModeThemeName, LightModeThemeName: string);
begin
  SetSpecificThemeMode(DarkModeIsEnabled, DarkModeThemeName, LightModeThemeName);
end;

procedure SetSpecificThemeMode(const AsDarkMode: Boolean; const DarkModeThemeName, LightModeThemeName: string);
var
  ChosenTheme: string;
begin
  if AsDarkMode then
    ChosenTheme := DarkModeThemeName
  else
    ChosenTheme := LightModeThemeName;

  TStyleManager.TrySetStyle(ChosenTheme, False);
end;

end.
