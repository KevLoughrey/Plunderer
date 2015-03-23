from datetime import date
import tornado.escape
import tornado.ioloop
import tornado.web
import datetime
import mysql.connector
import random
random.random()


class VersionHandler(tornado.web.RequestHandler):
	def get(self):
		response = { 'version': '3.5.1',
					'last_build':  date.today().isoformat() }
		self.write(response)

class GetNames(tornado.web.RequestHandler):
	def post(self):
		cnx = mysql.connector.connect(user='root', password='root',
									host='localhost',
									database='plunderer')
		cursor=cnx.cursor()
		name= self.get_argument('name','')
		friend = self.get_argument('friend','')
		query=("SELECT ip, port, random FROM players where name = "+friend+" and friend = "+name+";")
		
		cursor.execute(query)
		s = " "
		for (first_name, last_name, random) in cursor:
			s += "{} {} {}".format(
			last_name, first_name,random)
		self.write(s)
		
		query=("DELETE FROM players where name = "+friend+" and friend = "+name+";")
		cursor.execute(query)
		cnx.commit()
		cursor.close()
		cnx.close()

class PostNames(tornado.web.RequestHandler):
	def post(self):
		cnx = mysql.connector.connect(user='root', password='root',
							host='127.0.0.1',
							database='plunderer')
		cursor=cnx.cursor()
		ip = self.get_argument('ip','')
		port = self.get_argument('port','')
		name = self.get_argument('name','')
		fname = self.get_argument('friend','')
		random.seed()
		rand = random.random()
		query="INSERT INTO players (ip,port,name,friend,random) VALUES ("+ip+","+port+","+name+","+fname+","+str(rand)+");"
		cursor.execute(query)
		self.write(str(rand))
		cnx.commit()
		cursor.close()
		cnx.close()

class PostScore(tornado.web.RequestHandler):
	def post(self):
		cnx = mysql.connector.connect(user='root', password='root',
							host='127.0.0.1',
							database='plunderer')
		cursor=cnx.cursor()
		name = self.get_argument('name','')
		score = self.get_argument('score','')
		if len(name) > 2:
			query="INSERT INTO highScores (name, score) VALUES ("+name+","+score+");"
			cursor.execute(query)
		cnx.commit()
		cursor.close()
		cnx.close()

class PostCoopScore(tornado.web.RequestHandler):
	def post(self):
		cnx = mysql.connector.connect(user='root', password='root',
							host='127.0.0.1',
							database='plunderer')
		cursor=cnx.cursor()
		name = self.get_argument('name','')
		friend = self.get_argument('friend','')
		score = self.get_argument('score','')
		if len(name) > 2:
			query="INSERT INTO coopHighScores (name1,name2, score) VALUES ("+name+","+friend+","+score+");"
			cursor.execute(query)
		cnx.commit()
		cursor.close()
		cnx.close()

class GetScore(tornado.web.RequestHandler):
	def get(self):
		cnx = mysql.connector.connect(user='root', password='root',
							host='127.0.0.1',
							database='plunderer')
		cursor = cnx.cursor()
		query = ("SELECT name, score FROM highScores order by cast(score as unsigned) DESC limit 5")
		cursor.execute(query)
		s = " "
		for (first_name, last_name) in cursor:
			s += "{} {}".format(
			first_name, last_name)
			s += "&"
		self.write(s)
		cursor.close()
		
class GetCoopScore(tornado.web.RequestHandler):
	def get(self):
		cnx = mysql.connector.connect(user='root', password='root',
							host='127.0.0.1',
							database='plunderer')
		cursor = cnx.cursor()
		query = ("SELECT name1, name2, score FROM coopHighScores order by score DESC limit 5")
		cursor.execute(query)
		s = " "
		for (name1, name2, score) in cursor:
			s += "{} {} {}".format(
			name1, name2, score)
			s += "&"
		self.write(s)
		cursor.close()

class ClearTable(tornado.web.RequestHandler):
	def get(self):
		cnx = mysql.connector.connect(user='root', password='root',
							host='127.0.0.1',
							database='plunderer')
		cursor=cnx.cursor()
		
		query="truncate table players;"
		cursor.execute(query)
		cnx.commit()
		cursor.close()
		cnx.close()
		
application = tornado.web.Application([
	(r"/GetNames", GetNames),
	(r"/PostName", PostNames),
	(r"/ClearTable", ClearTable),
	(r"/PostScore", PostScore),
	(r"/GetScore", GetScore),
	(r"/GetCoopScore", GetCoopScore),
	(r"/PostCoopScore", PostCoopScore)
])

if __name__ == "__main__":
	application.listen(8000)
	tornado.ioloop.IOLoop.instance().start()