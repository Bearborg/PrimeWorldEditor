#ifndef CSCRIPTEDITSIDEBAR_H
#define CSCRIPTEDITSIDEBAR_H

#include "Editor/WorldEditor/CWorldEditorSidebar.h"

class CWorldEditor;
class QTabWidget;
class WEditorProperties;
class WCreateTab;
class WModifyTab;
class WInstancesTab;

class CScriptEditSidebar : public CWorldEditorSidebar
{
    Q_OBJECT

    WEditorProperties *mpEditorProperties;
    QTabWidget *mpTabWidget;
    WCreateTab *mpCreateTab;
    WModifyTab *mpModifyTab;
    WInstancesTab *mpInstancesTab;

public:
    explicit CScriptEditSidebar(CWorldEditor *pEditor);

    // Accessors
    WCreateTab* CreateTab() const        { return mpCreateTab; }
    WModifyTab* ModifyTab() const        { return mpModifyTab; }
    WInstancesTab* InstancesTab() const  { return mpInstancesTab; }
};

#endif // CSCRIPTEDITSIDEBAR_H
