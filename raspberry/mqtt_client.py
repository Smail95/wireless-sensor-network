import paho.mqtt.client as paho

broker	= "localhost"
port	= 1883
out_topic 		= "out_peri_al"

def on_publish(client,userdata,result):		#create function for callback
    print("data published \n")
    pass

client1= paho.Client("MQTT_Client")			#create client object
client1.on_publish = on_publish				#assign function to callback
client1.connect(broker,port)                #establish connection

ret= client1.publish(out_topic, "distance,10.5;distance,50")  
