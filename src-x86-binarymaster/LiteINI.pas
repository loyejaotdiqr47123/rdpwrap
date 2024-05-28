{
  Copyright 2024 bobo.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
}

unit LiteINI;

interface

uses
  SysUtils, Classes;

type
  SList = TArray<String>;
  INIValue = record
    Name: String;
    Value: String;
  end;
  INISection = record
    Name: String;
    Values: TArray<INIValue>;
  end;
  INIFile = TArray<INISection>;

procedure SListClear(var List: SList);
function SListAppend(var List: SList; const S: String): Integer;
function SListFind(const List: SList; const Value: String): Integer;
function INIFindSection(const INI: INIFile; const Section: String): Integer;
function INIFindValue(const INI: INIFile; Section: Integer; const Value: String): Integer;
function INIAddSection(var INI: INIFile; const Section: String): Integer;
function INIAddValue(var INI: INIFile; Section: Integer; const ValueName, Value: String): Integer;
procedure INIUnload(var INI: INIFile);
procedure INILoad(var INI: INIFile; const FileName: String);
function INISectionExists(const INI: INIFile; const Section: String): Boolean;
function INIValueExists(const INI: INIFile; const Section, Value: String): Boolean;
function INIReadSection(const INI: INIFile; const Section: String): SList;
function INIReadString(const INI: INIFile; const Section, Value, Default: String): String;
function INIReadInt(const INI: INIFile; const Section, Value: String; Default: Integer): Integer;
function INIReadDWord(const INI: INIFile; const Section, Value: String; Default: Cardinal): Cardinal;
function INIReadIntHex(const INI: INIFile; const Section, Value: String; Default: Integer): Integer;
function INIReadDWordHex(const INI: INIFile; const Section, Value: String; Default: Cardinal): Cardinal;
function INIReadBool(const INI: INIFile; const Section, Value: String; Default: Boolean): Boolean;
function INIReadBytes(const INI: INIFile; const Section, Value: String): TBytes;
function INIReadBytesDef(const INI: INIFile; const Section, Value: String; const Default: TBytes): TBytes;

implementation

procedure SListClear(var List: SList);
begin
  List := [];
end;

function SListAppend(var List: SList; const S: String): Integer;
begin
  Result := Length(List);
  SetLength(List, Result + 1);
  List[Result] := S;
end;

function SListFind(const List: SList; const Value: String): Integer;
begin
  for Result := 0 to High(List) do
    if List[Result] = Value then
      Exit;
  Result := -1;
end;

function INIFindSection(const INI: INIFile; const Section: String): Integer;
begin
  for Result := 0 to High(INI) do
    if INI[Result].Name = Section then
      Exit;
  Result := -1;
end;

function INIFindValue(const INI: INIFile; Section: Integer; const Value: String): Integer;
begin
  if (Section < 0) or (Section >= Length(INI)) then
    Exit(-1);
  for Result := 0 to High(INI[Section].Values) do
    if INI[Section].Values[Result].Name = Value then
      Exit;
  Result := -1;
end;

function INIAddSection(var INI: INIFile; const Section: String): Integer;
begin
  Result := INIFindSection(INI, Section);
  if Result = -1 then
  begin
    Result := Length(INI);
    SetLength(INI, Result + 1);
    INI[Result].Name := Section;
    INI[Result].Values := [];
  end;
end;

function INIAddValue(var INI: INIFile; Section: Integer; const ValueName, Value: String): Integer;
begin
  if (Section < 0) or (Section >= Length(INI)) then
    Exit(-1);
  Result := INIFindValue(INI, Section, ValueName);
  if Result = -1 then
  begin
    Result := Length(INI[Section].Values);
    SetLength(INI[Section].Values, Result + 1);
    INI[Section].Values[Result].Name := ValueName;
  end;
  INI[Section].Values[Result].Value := Value;
end;

procedure INIUnload(var INI: INIFile);
begin
  INI := [];
end;

procedure INILoad(var INI: INIFile; const FileName: String);
var
  Lines: TStringList;
  Line, S, ValueName, Value: String;
  Sect: Integer;
begin
  INIUnload(INI);
  if not FileExists(FileName) then
    Exit;

  Lines := TStringList.Create;
  try
    Lines.LoadFromFile(FileName);

    Sect := -1;
    for Line in Lines do
    begin
      S := Trim(Line);
      if (S = '') or CharInSet(S[1], [';', '#']) then
        Continue;
      if (S[1] = '[') and (S[High(S)] = ']') then
      begin
        S := Copy(S, 2, Length(S) - 2);
        Sect := INIAddSection(INI, S);
        Continue;
      end;
      if Pos('=', S) > 0 then
      begin
        ValueName := Trim(Copy(S, 1, Pos('=', S) - 1));
        Value := Trim(Copy(S, Pos('=', S) + 1, Length(S)));
        if Sect = -1 then
          Sect := INIAddSection(INI, '');
        INIAddValue(INI, Sect, ValueName, Value);
      end;
    end;
  finally
    Lines.Free;
  end;
end;

function INISectionExists(const INI: INIFile; const Section: String): Boolean;
begin
  Result := INIFindSection(INI, Section) > -1;
end;

function INIValueExists(const INI: INIFile; const Section, Value: String): Boolean;
begin
  Result := INIFindValue(INI, INIFindSection(INI, Section), Value) > -1;
end;

function INIReadSection(const INI: INIFile; const Section: String): SList;
var
  Sect: Integer;
begin
  Sect := INIFindSection(INI, Section);
  if Sect <> -1 then
  begin
    Result := [];
    for var Value in INI[Sect].Values do
      SListAppend(Result, Value.Name);
  end
  else
    Result := [];
end;

function INIReadString(const INI: INIFile; const Section, Value, Default: String): String;
var
  Sect, Val: Integer;
begin
  Sect := INIFindSection(INI, Section);
  Val := INIFindValue(INI, Sect, Value);
  if (Sect <> -1) and (Val <> -1) then
    Result := INI[Sect].Values[Val].Value
  else
    Result := Default;
end;

function INIReadInt(const INI: INIFile; const Section, Value: String; Default: Integer): Integer;
var
  S: String;
begin
  S := INIReadString(INI, Section, Value, '');
  Result := StrToIntDef(S, Default);
end;

function INIReadDWord(const INI: INIFile; const Section, Value: String; Default: Cardinal): Cardinal;
var
  S: String;
begin
  S := INIReadString(INI, Section, Value, '');
  Result := StrToIntDef(S, Default);
end;

function INIReadIntHex(const INI: INIFile; const Section, Value: String; Default: Integer): Integer;
var
  S: String;
begin
  S := INIReadString(INI, Section, Value, '');
  if not TryStrToInt('$' + S, Result) then
    Result := Default;
end;

function INIReadDWordHex(const INI: INIFile; const Section, Value: String; Default: Cardinal): Cardinal;
var
  S: String;
begin
  S := INIReadString(INI, Section, Value, '');
  if not TryStrToUInt('$' + S, Result) then
    Result := Default;
end;

function INIReadBool(const INI: INIFile; const Section, Value: String; Default: Boolean): Boolean;
var
  S: String;
begin
  S := INIReadString(INI, Section, Value, '');
  Result := StrToBoolDef(S, Default);
end;

function INIReadBytes(const INI: INIFile; const Section, Value: String): TBytes;
var
  S: String;
  Len: Integer;
begin
  S := INIReadString(INI, Section, Value, '');
  Len := Length(S) div 2;
  SetLength(Result, Len);
  for var I := 0 to Len - 1 do
    Result[I] := StrToInt('$' + Copy(S, I * 2 + 1, 2));
end;

function INIReadBytesDef(const INI: INIFile; const Section, Value: String; const Default: TBytes): TBytes;
begin
  Result := INIReadBytes(INI, Section, Value);
  if Length(Result) = 0 then
    Result := Default;
end;

end.
