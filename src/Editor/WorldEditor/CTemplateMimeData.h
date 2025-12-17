#ifndef CTEMPLATEMIMEDATA_H
#define CTEMPLATEMIMEDATA_H

#include <QMimeData>

class CScriptTemplate;

class CTemplateMimeData : public QMimeData
{
    Q_OBJECT
    CScriptTemplate *mpTemplate;

public:
    explicit CTemplateMimeData(CScriptTemplate *pTemplate)
        : mpTemplate(pTemplate)
    {}

    CScriptTemplate* Template() const { return mpTemplate; }
};

#endif // CTEMPLATEMIMEDATA_H
