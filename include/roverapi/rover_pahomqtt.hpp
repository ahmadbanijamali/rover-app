/*
 * Copyright (c) 2017 FH Dortmund and others
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Description:
 *    Rover PahoMQTT API - Interfaces for Rover PahoMQTT cloud application development - Header file
 *
 * Contributors:
 *    M.Ozcelikors <mozcelikors@gmail.com>, created PahoMQTT API 07.12.2017
 *
 */

#ifndef ROVERAPI_ROVER_PAHOMQTT_HPP_
#define ROVERAPI_ROVER_PAHOMQTT_HPP_

#include <roverapi/rover_cloud.hpp>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "MQTTClient.h"
#include "MQTTAsync.h"

using namespace std;

namespace rover
{

	typedef struct
	{
		char * clientID;
		char * topic;
		char * payload;
		int			qos;		// 1
		long int	timeout;	// Such as 10000L usec
	} RoverMQTT_Configure_t;

	/**
	 * @brief RoverPahoMQTT contains member functions to use rover as a client and to publish / subscribe to Eclipse Paho MQTT server topics.
	 */
	class RoverPahoMQTT : public RoverCloud
	{
		private:
			/**
			 * @brief Host name used for connecting to the Eclipse Paho MQTT server
			 */
			char * HOST_NAME;

			/**
			 * @brief Port used for connecting to the Eclipse Paho MQTT server
			 */
			int PORT;

			RoverMQTT_Configure_t rover_MQTT_configure;

			/* Internal attributes */
			MQTTAsync client;

			/**
			 * @brief Connect options
			 */
			MQTTAsync_connectOptions conn_opts;

			/**
			 * @brief Disconnect options
			 */
			MQTTAsync_disconnectOptions disc_opts;



		public:

			~RoverPahoMQTT ();

			/**
			 * @brief Copy constructor for RoverPahoMQTT
			 */
			RoverPahoMQTT (char * host_name, int port, RoverMQTT_Configure_t MQTT_Configure);

			/**
			 * @brief Sets private attribute HOST_NAME
			 * @param host_name
			 */
			void setHostName (char * host_name);

			/**
			 * @brief Sets private attribute PORT
			 * @param port
			 */
			void setPort (const int port);

			void setPayload (char * payload);

			void setTopic (char * topic);



			int publish (void);

			int subscribe (void);

			int unsubscribe (void);

			int destroy (void);

		private:
			void constructAddress (char* string);

			/* Internal callbacks */
			/* Related to publisher */
			static void onPublisherConnect (void* context, MQTTAsync_successData* response);
			static void onPublisherSend (void* context, MQTTAsync_successData* response);

			/* Related to subscriber */
			static void onSubscriberConnect (void* context, MQTTAsync_successData* response);
			static int onSubscriberMessageArrived (void *context, char *topicName, int topicLen, MQTTAsync_message *message);
			static void onSubscribe (void* context, MQTTAsync_successData* response);
			static void onSubscribeFailure (void* context, MQTTAsync_failureData* response);

			/* Related to both */
			static void onConnectFailure (void* context, MQTTAsync_failureData* response);
			static void onConnectionLost (void *context, char *cause);
			static void onDisconnect (void* context, MQTTAsync_successData* response);

	};
}



#endif /* ROVERAPI_ROVER_PAHOMQTT_HPP_ */