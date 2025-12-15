#ifndef CTWEAKEDITOR_H
#define CTWEAKEDITOR_H

#include "Editor/IEditor.h"

#include <QList>
#include <memory>

namespace Ui {
class CTweakEditor;
}

class CGameProject;
class CTweakData;

class CTweakEditor : public IEditor
{
    Q_OBJECT

    /** Qt UI */
    std::unique_ptr<Ui::CTweakEditor> mpUI;

    /** List of editable tweak assets */
    QList<CTweakData*> mTweakAssets;

    /** Whether the editor window has been shown before */
    bool mHasBeenShown = false;

    /** Index of tweak data currently being edited */
    int mCurrentTweakIndex = -1;

public:
    explicit CTweakEditor(QWidget* pParent = nullptr);
    ~CTweakEditor() override;

    bool HasTweaks() const;
    bool Save() override;

public slots:
    void SetActiveTweakData(CTweakData* pTweakData);
    void SetActiveTweakIndex(int Index);
    void OnTweakTabClicked(int Index);
    void OnProjectChanged(CGameProject* pNewProject);
};

#endif // CTWEAKEDITOR_H
