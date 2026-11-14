import cv2 as cv
import threading
import numpy as np

class Camara(threading.Thread):
	"""docstring for Camara"""
	def __init__(self, fuente):
		threading.Thread.__init__(self)
		self.fuente = fuente
		self.corriendo = True
		self.xAzul = -1
		self.yAzul = -1
		print "Camara creada"

	def conectar(self):
		self.cap = cv.VideoCapture(self.fuente)
		print "camara conectada"

	def desconectar(self):
		self.cap.release()
		print "camara desconectada"

	def run(self):
		self.corriendo = True
		while self.corriendo:
			ret, self.imgEnt = self.cap.read()
			self.imgSal = self.imgEnt
			x = np.size(self.imgSal,1)/2
			y = np.size(self.imgSal,0)/2
			cv.circle(self.imgSal,(x,y),60, (127,0,127), 2)
			cv.imshow('Procesamiento de imagen',self.imgSal)
			cv.waitKey(30)
		cv.destroyAllWindows()
		print "Fin del hilo de camara"

