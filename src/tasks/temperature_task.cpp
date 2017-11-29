/*
 * Copyright (c) 2017 Eclipse Foundation, FH Dortmund and others
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Description:
 *    Temperature and Humidity Sensor DHT22 Task with wiringPi and pThreads
 *    (Adapted from the tutorial: http://www.uugear.com/portfolio/read-dht1122-temperature-humidity-sensor-from-raspberry-pi/)
 *
 * Authors:
 *    M. Ozcelikors,            R.Hottger
 *    <mozcelikors@gmail.com>   <robert.hoettger@fh-dortmund.de>
 *
 * Update History:
 *    02.02.2017   -    first compilation
 *    15.03.2017   -    updated tasks for web-based driving
 *    11.10.2017   -    re-compiled for DHT22 sensor
 *
*/

#include <tasks/temperature_task.h>

#include <ctime>
#include <unistd.h>
#include <libraries/timing/timing.h>
#include <interfaces.h>
#include <pthread.h>

#include <roverapp.h>

void *Temperature_Task(void *arg)
{
	timing temperature_task_tmr;

	temperature_task_tmr.setTaskID("DHT22");
	temperature_task_tmr.setDeadline(0.5);
	temperature_task_tmr.setPeriod(0.5);

	float temperature, humidity;

	while (1)
	{
		temperature_task_tmr.recordStartTime();
		temperature_task_tmr.calculatePreviousSlackTime();

		//Task content starts here -----------------------------------------------

		temperature = r.inRoverSensors().readTemperature();
		humidity = r.inRoverSensors().readHumidity();

		pthread_mutex_lock(&temperature_lock);
			temperature_shared = temperature;
		pthread_mutex_unlock(&temperature_lock);

		pthread_mutex_lock(&humidity_lock);
			humidity_shared = humidity;
		pthread_mutex_unlock(&humidity_lock);

		//Task content ends here -------------------------------------------------

		temperature_task_tmr.recordEndTime();
		temperature_task_tmr.calculateExecutionTime();
		temperature_task_tmr.calculateDeadlineMissPercentage();
		temperature_task_tmr.incrementTotalCycles();
		pthread_mutex_lock(&temperature_task_ti_l);
			temperature_task_ti.deadline = temperature_task_tmr.getDeadline();
			temperature_task_ti.deadline_miss_percentage = temperature_task_tmr.getDeadlineMissPercentage();
			temperature_task_ti.execution_time = temperature_task_tmr.getExecutionTime();
			temperature_task_ti.period = temperature_task_tmr.getPeriod();
			temperature_task_ti.prev_slack_time = temperature_task_tmr.getPrevSlackTime();
			temperature_task_ti.task_id = temperature_task_tmr.getTaskID();
			temperature_task_ti.start_time = temperature_task_tmr.getStartTime();
			temperature_task_ti.end_time = temperature_task_tmr.getEndTime();
		pthread_mutex_unlock(&temperature_task_ti_l);
		temperature_task_tmr.sleepToMatchPeriod();
	}

	/* the function must return something - NULL will do */
	return NULL;
}
