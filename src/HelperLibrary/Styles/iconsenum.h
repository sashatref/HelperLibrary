#pragma once

#include <QStyle>
#include <QApplication>

class IconsEnum
{
    Q_GADGET
public:
    enum Icons
    {
        BaseIcon = QStyle::SP_CustomBase + 1,
        SP_Save1,
        SP_SaveAs1,
        SP_AppExit,
        SP_Reload1,
        SP_Reload2,
        SP_Restart1,
        SP_ReloadDatabase,
        SP_StopWatch1,
        SP_StopWatch2,
        SP_StopWatch3,
        SP_Plus1,
        SP_Plus2,
        SP_Minus1,
        SP_Minus2,
        SP_Apply1,
        SP_Apply2,
        SP_Apply3,
        SP_Apply4,
        SP_CheckBoxChecked1,
        SP_Search1,
        SP_Services1,
        SP_Setting1,
        SP_Setting2,
        SP_Trash1,
        SP_Trash2,
        SP_Cancel1,
        SP_Login1,
        SP_Appearance1,
        SP_Edit1,
        SP_Edit2,
        SP_Edit3,
        SP_Erase1,
        SP_ListView1,
        SP_ListViewFilled1,
        SP_FlagUa,
        SP_FlagRu,
        SP_FlagBy,
        SP_FlagEn,
        SP_FlagDe,
        SP_FlagFr,
        SP_FlagEs,
        SP_Table1,
        SP_ChangeUser1,
        SP_Print1,
        SP_PDF1,
        SP_PDF2,
        SP_Copy1,
        SP_Paste1,
        SP_Paste2,
        SP_Cut1,
        SP_Preview1,
        SP_UAC1,
        SP_DatabaseDownload1,
        SP_DatabaseUpload1,
        SP_DatabaseRemove1,
        SP_DatabaseReload1,
        SP_DatabaseEdit1,
        SP_DatabaseAdd1,
        SP_DatabaseConfig,
        SP_CloudDonwload1,
        SP_CloudUpload1,
        SP_CloudReload1,
        SP_CloudSearch1,
        SP_CloudConfig1,
        SP_FileAdd1,
        SP_FileEdit1,
        SP_FileCheck1,
        SP_FileDelete1,
        SP_FileCancel1,
        SP_FileOpen1,
        SP_FileView1,
        SP_FileCopy1,

        SP_ArrowDown1,
        SP_ArrowDownLeft1,
        SP_ArrowDownRight1,
        SP_ArrowLeft1,
        SP_ArrowRight1,
        SP_ArrowUp1,
        SP_ArrowUpLeft1,
        SP_ArrowUpRight1,

        SP_Xml1,
        SP_Import1,
        SP_Export1,
        SP_ExportXml1,

        SP_Reset1,
        SP_Shuffle1,

        SP_InternetBrowser1,
        SP_InternetBrowser2,
        SP_ZoomIn1,
        SP_ZoomOut1,

        SP_Connected1,
        SP_Disconnected1,

        SP_PC1,
        SP_PC2,
        SP_PC3,
        SP_PC4,
        SP_PC5,

        SP_AddDocument1,
        SP_AddDocument2,
        SP_AddItem1,

        SP_OpenInBrowser1,
        SP_OpenInBrowser2,

        SP_Hide1,

        SP_Asceding1,
        SP_Desceding1,

        SP_SearchNext1,
        SP_SearchPrev1,

        SP_Undo1,
        SP_Redo1,

        SP_NewDocument1,
        SP_NewDocument2,

        SP_Radar1,
        SP_Radar2,

        SP_Record1,
        SP_Record2,
        SP_Record3,

        SP_RecordStop1,
        SP_RecordStop2,
        SP_RecordStop3,

        SP_TextWidth1,

        SP_Web1,

        SP_Firefox1,
        SP_InternetExplorer1,
        SP_Chrome1,

        SP_Filter1,
        SP_Filter2,
        SP_Filter3,
        SP_Filter4,

        SP_FilterClear1,
        SP_Infinity1,

        SP_Delete1,

        SP_FormBuilder1,
        SP_FormBuilder2,
        SP_FormBuilder3,
        SP_FormBuilder4,

        SP_Recorder1,
        SP_Recorder2,

        SP_Check1,
        SP_Uncheck1,

        SP_WhatIsThis1,

        SP_Replace1,

        SP_AlwaysOnTop1,
        SP_AlwaysOnTop2,
        SP_AlwaysOnTop3,
        SP_AlwaysOnTop4,

        SP_WaitGif1,

        SP_Max_Value
    };

    Q_ENUM(Icons)

    static QIcon getIcon(int _code)
    {
        return qApp->style()->standardIcon(static_cast<QStyle::StandardPixmap>(_code));
    }

    static QIcon applyButtonIcon()
    {
        return getIcon(Icons::SP_Apply2);
    }

    static QIcon closeButtonIcon()
    {
        return getIcon(QStyle::SP_DialogCloseButton);
    }
};

