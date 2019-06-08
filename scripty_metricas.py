# -*- coding: utf-8 -*-

import cv2
import numpy as np


def calcMedia(vet, denom):
	soma = 0
	for valores in vet:
	    soma += valores

	media = soma/denom

	return(media)


def calcSpeedup(tempoSequencial, tempoParalelo):

	speedUP = tempoSequencial/tempoParalelo

	return(speedUP)


def calcOverhead(processadores, tempoParalelo, tempoSequencial):

	overh = (processadores * tempoParalelo) - tempoSequencial

	return(overh)

def calcEficiencia(speedUP, processadores):

	return speedUP / processadores


def calcAmdahl(processadores, beta):

	if(processadores == 0): 
		return 1 / beta
	else: 
		return 1 / (beta + ((1 - beta) / processadores))

def calcGustfasonBARSIS(processadores, alfa):
	
	return alfa + (processadores * (1- alfa))


VetSeq6 = [33.373253, 33.727434, 33.389694, 33.736162, 33.372311, 33.740675, 33.233553, 33.120458, 33.247564, 33.741801, 33.360104, 33.746740, 33.260322, 33.177195, 33.740661, 33.373523, 33.221584, 33.339183, 33.370472, 33.995265]
VetSeq26 = [136.392719, 134.188535, 134.209531, 136.611937, 135.697468, 134.192384, 136.698974, 134.300582, 136.402915, 134.087831, 133.412241, 133.658623, 132.410277, 133.223952, 133.228544, 133.417440, 134.525835, 134.511860, 134.529007, 134.471252]


VetP6_2TH = [4.026066, 3.951985, 3.901425, 3.876339, 3.933987, 3.913015, 3.908657, 3.924088, 3.849635, 3.933831, 3.898943, 3.919641, 3.924053, 3.902148, 3.939766, 3.897542, 3.912134, 3.948074, 3.926687, 3.911111]
VetP13_2TH = [22.035483, 22.511302, 22.366174, 22.671771, 22.905184, 22.715470, 22.738485, 22.762820, 22.695353, 22.763558, 22.723849, 22.625791, 22.691374, 22.632902, 22.303461, 22.113088, 22.058298, 22.490228, 22.538998, 22.541757]
VetP26_2TH = [111.440663, 113.157188, 110.552957, 111.376244, 111.502750, 110.527951, 111.594318, 112.358696, 110.918499, 111.500565, 114.114125, 111.901429, 110.612300, 110.220121, 110.421949, 110.368840, 113.202939, 116.327932, 110.921254, 110.639645]

VetP6_4TH = [1.661932, 1.686207, 1.657347, 1.640746, 1.697516, 1.655139, 1.714547, 1.716372, 1.654856, 1.646009, 1.642680, 1.649961, 1.649622, 1.685559, 1.660343, 1.650191, 1.652901, 1.650416, 1.659024, 1.650007]
VetP13_4TH = [10.745443, 10.809139, 10.843245, 11.233266, 10.757725, 10.813384, 10.885201, 10.706337, 10.683860, 10.694678, 10.693714, 10.723676, 10.725282, 10.758881, 10.726157, 10.742542, 10.728401, 10.735656, 10.662773, 10.661647]
VetP26_4TH = [60.773801, 61.119308, 61.076931, 61.578608, 60.787980, 60.673722, 61.028864, 60.912748, 61.237787, 60.953302, 60.839215, 60.795362, 61.036328, 61.175086, 75.561949, 65.461542, 61.156747, 61.073770, 61.627854]


sequencial6k = calcMedia(VetSeq6, 20)
paralelo6k_2th = calcMedia(VetP6_2TH, 20)
paralelo6k_4th = calcMedia(VetP6_4TH, 20)

paralelo13k_2th = calcMedia(VetP13_2TH, 20)
paralelo13k_4th = calcMedia(VetP13_4TH, 20)

sequencial26k = calcMedia(VetSeq26, 20)
paralelo26k_2th = calcMedia(VetP26_2TH, 20)
paralelo26k_4th = calcMedia(VetP26_4TH, 19)


speedUP_6k_2th = calcSpeedup(sequencial6k, paralelo6k_2th)
speedUP_6k_4th = calcSpeedup(sequencial6k, paralelo6k_4th)

speedUP_26k_2th = calcSpeedup(sequencial26k, paralelo26k_2th)
speedUP_26k_4th = calcSpeedup(sequencial26k, paralelo26k_4th)


print("Resultados para a sequencia de tamanho de 6k:")
print("Media sequencial: " + str(sequencial6k))
print("Media paralelo 2TH: " + str(paralelo6k_2th))
print("Media paralelo 4TH: " + str(paralelo6k_4th))
print("SpeedUP paralelo 2TH: " + str(speedUP_6k_2th))
print("SpeedUP paralelo 4TH: " + str(speedUP_6k_4th))
print("Overhead para 2TH: " + str(calcOverhead(2, paralelo6k_2th, sequencial6k)))
print("Overhead para 4TH: " + str(calcOverhead(4, paralelo6k_4th, sequencial6k)))
print("Eficiencia para 2TH: " + str(calcEficiencia(speedUP_6k_2th, 2)))
print("Eficiencia para 4TH: " + str(calcEficiencia(speedUP_6k_4th, 4)))
print("Lei de Amdahl: " + "*** TODO ***")
print("Gustafson-BaRSIS: " + "*** TODO ***")
print('\n')

print("Resultados para a sequencia de tamanho de 13k:")
print("Media sequencial: " + "*** TODO ***")
print("Media paralelo 2TH: " + str(paralelo13k_2th))
print("Media paralelo 4TH: " + str(paralelo13k_4th))
print("SpeedUP paralelo 2TH: " + "*** TODO ***")
print("SpeedUP paralelo 4TH: " + "*** TODO ***")
print("Overhead para 2TH: " + "*** TODO ***")
print("Overhead para 4TH: " + "*** TODO ***")
print("Eficiencia para 2TH: " + "*** TODO ***")
print("Eficiencia para 4TH: " + "*** TODO ***")
print("Lei de Amdahl: " + "*** TODO ***")
print("Gustafson-BaRSIS: " + "*** TODO ***")
print('\n')


print("Resultados para a sequencia de tamanho de 26k")
print("Media Sequencial 26k: " + str(sequencial26k))
print("Media paralelo 2TH: " + str(paralelo26k_2th))
print("Media paralelo 4TH: " + str(paralelo26k_4th))
print("SpeedUP paralelo 2TH: " + str(speedUP_26k_2th))
print("SpeedUP paralelo 4TH: " + str(speedUP_26k_4th))
print("Overhead para 2TH: " + str(calcOverhead(2, paralelo26k_2th, sequencial26k)))
print("Overhead para 4TH: " + str(calcOverhead(4, paralelo26k_4th, sequencial26k)))
print("Eficiencia para 2TH: " + str(calcEficiencia(speedUP_26k_2th, 2)))
print("Eficiencia para 4TH: " + str(calcEficiencia(speedUP_26k_4th, 4)))
print("Lei de Amdahl: " + "*** TODO ***")
print("Gustafson-BaRSIS: " + "*** TODO ***")
print('\n')