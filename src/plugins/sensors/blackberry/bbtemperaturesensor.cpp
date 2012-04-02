/****************************************************************************
**
** Copyright (C) 2012 Research In Motion
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "bbtemperaturesensor.h"

class BbTemperatureReadingPrivate
{
public:
    BbTemperatureReadingPrivate()
        : temperature(0)
    {
    }

    qreal temperature;
};

IMPLEMENT_READING(BbTemperatureReading)

qreal BbTemperatureReading::temperature() const
{
    return d->temperature;
}

void BbTemperatureReading::setTemperature(qreal temperature)
{
    d->temperature = temperature;
}

BbTemperatureSensor::BbTemperatureSensor(QSensor *sensor)
    : BbSensorBackend<BbTemperatureReading>(devicePath(), SENSOR_TYPE_TEMPERATURE, sensor)
{
    setDescription(QLatin1String("Temperature in degrees Celsius"));
}

QString BbTemperatureSensor::devicePath()
{
    return QLatin1String("/dev/sensor/temp");
}

bool BbTemperatureSensor::updateReadingFromEvent(const sensor_event_t &event, BbTemperatureReading *reading)
{
    // TODO: I was unable to test this since the device I was testing this with did not have
    //       a temperature sensor. Verify that this works and check that the units are correct.
    reading->setTemperature(event.temperature_s.temperature);
    return true;
}
