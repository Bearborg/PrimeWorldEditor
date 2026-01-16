#ifndef CPROGRESSBARNOTIFIER_H
#define CPROGRESSBARNOTIFIER_H

#include <Core/IProgressNotifier.h>
#include <QProgressBar>

#include <cmath>

/** Progress notifier class that updates a QProgressBar. */
class CProgressBarNotifier : public IProgressNotifier
{
    /** The progress bar we are relaying updates to */
    QProgressBar* mpProgressBar = nullptr;

    /** Whether the user has requested to cancel */
    bool mCancel = false;

public:
    CProgressBarNotifier() = default;

    void SetProgressBar(QProgressBar* pProgressBar)
    {
        mpProgressBar = pProgressBar;
    }

    void SetCanceled(bool ShouldCancel)
    {
        mCancel = ShouldCancel;
    }

    /** IProgressNotifier interface */
    bool ShouldCancel() const override
    {
        return mCancel;
    }

protected:
    void UpdateProgress(const std::string&, const std::string&, float ProgressPercent) override
    {
        if (!mpProgressBar)
            return;

        // Defer setValue call so it runs on the correct thread
        const int Alpha = std::lerp(mpProgressBar->minimum(), mpProgressBar->maximum(), ProgressPercent);
        QMetaObject::invokeMethod(mpProgressBar, &QProgressBar::setValue, Qt::AutoConnection, Alpha);
    }
};

#endif // CPROGRESSBARNOTIFIER_H
