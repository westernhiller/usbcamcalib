#include "camconfig.h"
#include <QSettings>
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>

CamConfig::CamConfig(QString cfgfile)
    : m_cfgFile(cfgfile)
    , m_camid("/dev/video0")
    , m_nWidth(1280)
    , m_nHeight(480)
{
    loadConfig(cfgfile);
}

CamConfig::~CamConfig()
{
}

bool CamConfig::loadConfig(QString cfgfile)
{
    QSettings settings(cfgfile, QSettings::NativeFormat);
    settings.beginGroup("usbcam");
    m_camid = settings.value("camera", "/dev/video0").toString();
    m_nWidth = settings.value("width", "1280").toInt();
    m_nHeight = settings.value("height", "480").toInt();

    settings.endGroup();
    return true;
}

bool CamConfig::saveConfig()
{
    QSettings settings(m_cfgFile, QSettings::NativeFormat);
    settings.beginGroup("usbcam");
    settings.setValue("camera", m_camid);
    settings.setValue("width", m_nWidth);
    settings.setValue("height", m_nHeight);
    settings.endGroup();

    return true;
}

