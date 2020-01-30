#!/usr/bin/python3

import paho.mqtt.client as mqtt 
from db import *

# Network infos 
mqtt_server 	= "localhost" 
port 			= 1883
out_topic 		= "out_peri_al"

# Database infos 
username 	= 'root'
password 	= 'peri2019'
database 	= 'enclos'

# MQTT functions 
def on_message(client, userdata, msg):
	# Connect into DB
	(db_connection, cursor) = db_connect(username, password, database)
	# Insert data 
	db_insert_msg(db_connection, cursor, str(msg.payload)[2:-1])
	# Close DB
	db_close(db_connection)
	
def on_publish(client, userdata, msg):
	pass

def on_connect(client, userdata, flags, rc):
	# Subscribe to a topic and receive messages
	client.subscribe(out_topic)
	print("Connected !! \n")

# Create client instance
client = mqtt.Client("MQTT_SERVER")
client.on_message = on_message
client.on_publish = on_publish
client.on_connect = on_connect

# Connect to a broker (mqtt server)
client.connect(mqtt_server, port);

client.loop_forever()
