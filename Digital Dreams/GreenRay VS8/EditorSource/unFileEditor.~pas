unit unFileEditor;
interface uses Windows,SysUtils,StdCtrls,ComCtrls;

function _ReadDirectory(_strPath: string;_Handle: THandle;_bFiles: Bool): string;
procedure _BrowseFolder(_Data: string;_ListHandle: TListView);

implementation

//------------------------------------------------------------------------------
// Name: AdjustFolder()
// Desc:
//------------------------------------------------------------------------------
function _AdjustFolder(_Folder: string): string;
var _L: Longint;
begin
  _Folder:= Trim(_Folder);
  _L:= Length(_Folder);
  if Copy(_Folder,_L,_L) = '\' then Result:= _Folder
  else Result:= _Folder+'\';
end; //EndAdjustFolderFunction

//------------------------------------------------------------------------------
// Name: ReadDirectory()
// Desc:
//------------------------------------------------------------------------------
function _ReadDirectory(_strPath: string;_Handle: THandle;_bFiles: Bool): string;
const _FileFlags: array[0..7] of Integer =
  (FILE_ATTRIBUTE_READONLY,FILE_ATTRIBUTE_HIDDEN,
  FILE_ATTRIBUTE_SYSTEM,FILE_ATTRIBUTE_ARCHIVE,
  FILE_ATTRIBUTE_NORMAL,FILE_ATTRIBUTE_TEMPORARY,
  FILE_ATTRIBUTE_COMPRESSED,FILE_ATTRIBUTE_OFFLINE);
var _C,_R: string;
    _FileHandle,_J: Longint;
    _WFD: _WIN32_FIND_DATAA;
    _FileList: TListBox;
    _Size: Int64;
    _FormatSize: string;
begin
  _FileList:= TListBox.CreateParented(_Handle);
  _FileList.Sorted:= True;

  _C:= Chr(13);
  _strPath:= _AdjustFolder(_strPath);
  _FileHandle:= FindFirstFile(PChar(_strPath+'*.*'),_WFD);

  if _FileHandle <> -1 then begin _R:= _strPath+_C;
  repeat begin
  if Ord(_WFD.cFileName[0]) <> 46 then begin

  if (not _bFiles ) then begin
  if (_WFD.dwFileAttributes and FILE_ATTRIBUTE_DIRECTORY) = FILE_ATTRIBUTE_DIRECTORY then
  _FileList.Items.Add('\'+string(_WFD.cFileName)); end;

  if (_bFiles) then begin
  for _J:= 0 to 7 do
  if Bool(_WFD.dwFileAttributes and _FileFlags[_J]) then begin
  _FileList.Items.Add(string(_WFD.cFileName));
  Break; end; end;

  end; end;

  until FindNextFile(_FileHandle,_WFD) = False;
  Windows.FindClose(_FileHandle);
  for _J:= 0 to _FileList.Items.Count-1 do begin _R:= _R+_FileList.Items[_J]+_C; end;
  end else _R:= _strPath; _FileList.Free();
  Result:= Copy(_R,1,Length(_R)-1);
end; //EndReadDirectoryFunction

//------------------------------------------------------------------------------
// Name: BrowseFolder()
// Desc:
//------------------------------------------------------------------------------
procedure _BrowseFolder(_Data: string;_ListHandle: TListView);
var _PosData: Longint;
    _Path,_EntCharData,_GetStrData: string;
    _LItem: TListItem;
    _ImgIndex: Integer;
    //_Types: array[0..1] of string;
    _NeedExit: Boolean;
begin
  _ListHandle.Items.Clear;
  _EntCharData:= Chr(13); _PosData:= Pos(_EntCharData,_Data);

  if _PosData > 0 then begin
  _Path:= Trim(Copy(_Data,1,_PosData-1));
  _NeedExit:= False;
  end else begin _Path:= _Data; _NeedExit:= True; end;

  if _NeedExit then Exit;
  _Data:= Copy(_Data,_PosData+1,Length(_Data));
  _PosData:= Pos(_EntCharData,_Data);

  while _PosData > 0 do begin
  _GetStrData:= Copy(_Data,1,_PosData-1);

  if Copy(_GetStrData,1,1) = '\' then begin
  _GetStrData:= Copy(_GetStrData,2,Length(_GetStrData));
  _ImgIndex:= 0; end else _ImgIndex:= 0;

  _LItem:= _ListHandle.Items.Add;
  _LItem.ImageIndex:= _ImgIndex;
  _LItem.Caption:= _GetStrData;

  _Data:= Copy(_Data,_PosData+1,Length(_Data));
  _PosData:= Pos(_EntCharData,_Data); end;

  if Copy(_Data,1,1) = '\' then begin
  _Data:= Copy(_Data,2,Length(_Data));
  _ImgIndex:= 0;

  end else _ImgIndex:= 0;
  _LItem:= _ListHandle.Items.Add();
  _LItem.ImageIndex:= _ImgIndex;
  _LItem.Caption:= _Data;
end; //EndBrowseFolderProcedure

//------------------------------------------------------------------------------

end.
 