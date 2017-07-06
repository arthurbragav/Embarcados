#!/usr/bin/env python
# -*- coding: utf-8 -*-  
#Bibliotecas
import urllib2
import json
 
#Enviar notificações
def sendNotification(token, channel, message):
	data = {
		"body" : message,
		"message_type" : "text/plain"
	}
 
	req = urllib2.Request('http://api.pushetta.com/api/pushes/{0}/'.format(channel))
	req.add_header('Content-Type', 'application/json')
	req.add_header('Authorization', 'Token {0}'.format(token))
 
	response = urllib2.urlopen(req, json.dumps(data))
 
#Notificação enviada no formato  Apikey+Canal+Mensagem
sendNotification("08fcaec6180e4f146626645ebfd81d0b10a47d09", "Ricardo", "ALERTA!")
 
#Notifica o usuário que a mensagem foi enviada
print "Mensagem enviada!"
