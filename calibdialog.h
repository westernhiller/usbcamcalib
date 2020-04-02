#ifndef CALIBDIALOG_H
#define CALIBDIALOG_H

#include <QDialog>
#include "matchthread.h"
#include "imagebuffer.h"
#include "capturethread.h"
#include "camconfig.h"

class CalibDialog : public QDialog
{
    Q_OBJECT

public:
    CalibDialog(QString cfgfile, QWidget *parent = 0);
    ~CalibDialog();

    inline CamConfig* getConfig() { return m_pConfig;}
    inline ImageBuffer* getImageBuffer() { return m_pImageBuffer;}
signals:
    void updateLeftImage(QImage);
    void updateRightImage(QImage);

private:
    ImageBuffer*    m_pImageBuffer;
    CaptureThread*  m_pCapturer;
    MatchThread*    m_pMatcher;
    CamConfig*      m_pConfig;

public slots:
    void updateImages(QImage, QImage);
};

#endif // CALIBDIALOG_H
