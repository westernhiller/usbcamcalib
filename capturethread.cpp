#include "capturethread.h"
#include "calibdialog.h"
#include "jpegdecode.h"

CaptureThread::CaptureThread(QObject* parent)
    : QThread(parent)
    , m_pVcap(nullptr)
{
    CalibDialog* pDlg = static_cast<CalibDialog*>(parent);
    m_pConfig = pDlg->getConfig();
    m_pImageBuffer = pDlg->getImageBuffer();
}

CaptureThread::~CaptureThread()
{
    requestInterruption();
    if(m_pVcap)
        delete m_pVcap;
    quit();
    wait();
}

bool CaptureThread::initCamera()
{
    int width = m_pConfig->width();
    int height = m_pConfig->height();

    m_pVcap = new V4L2Capture((char *)m_pConfig->camId().toStdString().data(), width, height);
    m_pVcap->openDevice();
    if(-1 == m_pVcap->initDevice(width, height))
    {
        qDebug() << "failed initializing camera " << m_pConfig->camId();
        return false;
    }
    return true;
}

void CaptureThread::run()
{
    if(!m_pImageBuffer || !initCamera())
        return;

    m_pVcap->startCapture();
    uint8_t *yuv422frame = nullptr;
    uint64_t yuvframeSize = 0;

    while (!isInterruptionRequested())
    {
        if(-1 != m_pVcap->getFrame((void **) &yuv422frame, (int *)&yuvframeSize))
        {
            Mat imgFrame = Jpeg2Mat(yuv422frame, yuvframeSize);
            if(imgFrame.data)
            {
                FRAMEINFO frame;
                frame.matImg = imgFrame;
                frame.timeStamp = QDateTime::currentDateTime();
                m_pImageBuffer->writeImage(frame);
            }
            m_pVcap->backFrame();
        }
        usleep(1000);
    }
}

