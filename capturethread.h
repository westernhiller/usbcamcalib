#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include "camconfig.h"
#include "v4l2capture.h"
#include "imagebuffer.h"

class CaptureThread : public QThread
{
    Q_OBJECT
public:
    explicit CaptureThread(QObject* parent = nullptr);
    ~CaptureThread();

signals:

protected:
    void            run();

private:
    CamConfig*      m_pConfig;
    V4L2Capture *   m_pVcap;
    ImageBuffer*    m_pImageBuffer;

    bool            initCamera();
};

#endif // CAPTURETHREAD_H
