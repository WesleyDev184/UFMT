import mysql.connector

#estabeleçe conexão
con = mysql.connector.connect(user='root', password='deltafox184', host='localhost', database='lab_bd_compras')

#cria um objeto cursor
cur = con.cursor()

#chama procediento armazenado
resultado = cur.callproc('inset_client', [6, 'linder', 5564458])
con.commit()
print(resultado)