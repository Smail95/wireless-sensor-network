
#!/usr/bin/python3

import mysql.connector as mariadb

# Connect into database
def db_connect(username, passw, db):
		db_connection = mariadb.connect(user=username, password=passw, database=db)
		cursor = db_connection.cursor()
		#print("DB connected successfully");
		return (db_connection, cursor)

# Close database
def db_close(db_connection):
		db_connection.close()
		#print("BD closed successfully")

# Retrieving informations and store them in database 
def db_insert_msg(db_connection, cursor, data):
		liste = data.split(',')
		table = liste[0]
		sql = 'INSERT INTO {}({},{}) VALUES({:f},{})'.format(table, liste[1], liste[2], float(liste[3]), liste[4]);
		print(sql)
		try:
			cursor.execute(sql)
		except mariadb.Error as error:
			print("Error: {} \n".format(error))
			
		db_connection.commit()
		print("The last inserted id was: {}" .format(cursor.lastrowid))
