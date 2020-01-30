# Instalation

1. Copier le contenu du repertoire <raspberry> sur la carte Raspberry Pi.
Vous pouvez utiliser le Makefile fourni en veillant à bien l'adapter. 

2. Placer le fichier /raspberry/projet.conf dans le repertoire /etc/apache2/sites-available/.

3. Faites les configurations nécessaires, voir le rapport du projet, section: 1.Configuration.

# Utilisation

1. Sur la carte Raspberry:
- Lancer le serveur MQTT
$ python3 raspberry/mqtt_server.py

2. Sur la machine hote:
- Lancer le programme esp/esp.ino
- Lancer un browser et taper: peri:8842
- Attention:: 
-- Veuillez à ne pas utiliser un proxy pour l'addresse IP <peri>.
-- Mozilla -> preferences -> Settings
-- Ajouter <peri> dans la section: <No proxy for>

