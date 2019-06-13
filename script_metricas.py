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



def regra3(todo, porcento):

	x = (porcento * 100 )/ todo

	return (x/100)


def calcAmdahl(processadores, beta):

	if(processadores == 0): 
		return 1 / beta
	else: 
		return 1 / (beta + ((1 - beta) / processadores))



def calcGustfasonBARSIS(processadores, alfa):
	
	return (alfa + (processadores * (1- alfa)))



#-------------------------VETORES 6K------------------------------------------#
VetAruaSeq6 = [8.184161, 8.181133, 8.178715, 8.177113, 8.179529, 8.177989, 8.178219, 8.178746, 8.180369, 8.177467, 8.232118, 8.226050, 8.229275, 8.226339, 8.227440, 8.228804, 8.217990, 8.220542, 8.218852, 8.232902]

VetAruaP6_2TH_tempo_seq = [0.102209, 0.100067, 0.101637, 0.100784, 0.100605, 0.100848, 0.101403, 0.100754, 0.101382, 0.101057, 0.101405, 0.100686, 0.101372, 0.100657, 0.100258, 0.101529, 0.100987, 0.100334, 0.100547, 0.101720]
VetAruaP6_2TH_tempo_paral = [3.850556, 3.860324, 3.848325, 3.870814, 3.865863, 3.859674, 3.874451, 3.865288, 3.880203, 3.841268, 3.866422, 3.871980, 3.839308, 3.876333, 3.853368, 3.844941, 3.851488, 3.867400, 3.851415, 3.854041]

VetAruaP6_4TH_tempo_seq = [0.103552, 0.100935, 0.101115, 0.100875, 0.101224, 0.100529, 0.101459, 0.101504, 0.101564, 0.101907, 0.101196, 0.101749, 0.100949, 0.101481, 0.101157, 0.101283, 0.101082, 0.101962, 0.101859, 0.101849]
VetAruaP6_4TH_tempo_paral = [1.645759, 1.638767, 1.629933, 1.632660, 1.637659, 1.624398, 1.656851, 1.633761, 1.643140, 1.631256, 1.630964, 1.632081, 1.635562, 1.641411, 1.635927, 1.655263, 1.636851, 1.634968, 1.633497, 1.635893]

VetAruaP6_8TH_tempo_seq = [0.121067, 0.100259, 0.100360, 0.100549, 0.100691, 0.099441, 0.100435, 0.100111, 0.100383, 0.099912, 0.100480, 0.099217, 0.099521, 0.100234, 0.100366, 0.099872, 0.100326, 0.100684, 0.100045, 0.100182]
VetAruaP6_8TH_tempo_paral = [9.203850, 8.568558, 8.647095, 8.447894, 8.281613, 8.699305, 8.471430, 8.609568, 8.696139, 8.396830, 8.614102, 8.673005, 8.594441, 8.511939, 8.569113, 8.347552, 8.788811, 8.673422, 8.614277, 8.676968]

VetAruaP6_16TH_tempo_seq = [0.100574, 0.101884, 0.099221, 0.102239, 0.100180, 0.102321, 0.101907, 0.099898, 0.102133, 0.101649, 0.101587, 0.100013, 0.101039, 0.102679, 0.099999, 0.101596, 0.101237, 0.100462, 0.099564, 0.101631]
VetAruaP6_16TH_tempo_paral = [25.500019, 25.389703, 25.343764, 25.209575, 25.295562, 25.438217, 25.327213, 25.546645, 25.375578, 25.420992, 25.363361, 25.488133, 25.344278, 25.471360, 25.403707, 25.477032, 25.502398, 25.415270, 25.315963, 25.306341]


VetMouseSeq6 = [7.796868, 7.797908, 7.801393, 7.797970, 7.799108, 7.796687, 7.796889, 7.797547, 7.796755, 7.802288, 7.798104, 7.801093, 7.799137, 7.792260, 7.796119, 7.795817, 7.797367, 7.794837, 7.795014, 7.795318]

VetMouseP6_2TH_tempo_seq = [0.101436, 0.101736, 0.101558, 0.100848, 0.100458, 0.101050, 0.101075, 0.101251, 0.100876, 0.100269, 0.101728, 0.100667, 0.101805, 0.100935, 0.101279, 0.100729, 0.100983, 0.101751, 0.100951, 0.101182]
VetMouseP6_2TH_tempo_paral = [3.867503, 3.826176, 3.836608, 3.847084, 3.857498, 3.865793, 3.847039, 3.833566, 3.869934, 3.818845, 3.849307, 3.863739, 3.830492, 3.837196, 3.851236, 3.888749, 3.849927, 3.894318, 3.867564, 3.854496]


VetMouseP6_4TH_tempo_seq = [0.101716, 0.100699, 0.101252, 0.101060, 0.101406, 0.100965, 0.101320, 0.100874, 0.101816, 0.102045, 0.101870, 0.114293, 0.101424, 0.101699, 0.100494, 0.101867, 0.100728, 0.101128, 0.100959, 0.101305]
VetMouseP6_4TH_tempo_paral = [1.644371, 1.643645, 1.643291, 1.632836, 1.663332, 1.642848, 1.643411, 1.639835, 1.633823, 1.631707, 1.683793, 1.624920, 1.643234, 1.618375, 1.627610, 1.638174, 1.634443, 1.642481, 1.639647, 1.644641]


VetMouseP6_8TH_tempo_seq = [0.141222, 0.101861, 0.100340, 0.099948, 0.099606, 0.100541, 0.100673, 0.100106, 0.099914, 0.099711, 0.100069, 0.099911, 0.100489, 0.099505, 0.100142, 0.100429, 0.099189, 0.099447, 0.100102, 0.099822]
VetMouseP6_8TH_tempo_paral = [8.749168, 8.709176, 8.966297, 8.652727, 8.473382, 8.557477, 8.419041, 8.520073, 8.646928, 8.653528, 8.541381, 8.658233, 8.617192, 8.694900, 8.605425, 8.775872, 8.590359, 8.686831, 8.536165, 8.726994]

VetMouseP6_16TH_tempo_seq = [0.103252, 0.102554, 0.102305, 0.102395, 0.102477, 0.102842, 0.101409, 0.102039, 0.102209, 0.100220, 0.101899, 0.100115, 0.101861, 0.101123, 0.101692, 0.101938, 0.100878, 0.101882, 0.100418, 0.102591]
VetMouseP6_16TH_tempo_paral = [25.394605, 25.531417, 25.413738, 25.503017, 25.375347, 25.381611, 25.343448, 25.497360, 25.299962, 25.390411, 25.395831, 25.422296, 25.574010, 25.282563, 25.630700, 25.443926, 25.515927, 25.535457, 25.332491, 25.629464]



# -------------------------VETORES 13K------------------------------------------#

# VetAruaSeq6 = [32.629124, 32.608572, 32.602035, 32.603817, 32.602466, 32.605077, 32.605401, 32.604505, 32.602779, 32.603429, 32.608623, 32.604885, 32.604233, 32.606270, 32.605955, 32.601779, 32.602192, 32.602772, 32.602643, 32.601151]

# VetAruaP6_2TH_tempo_seq = [0.397564, 0.396331, 0.395165, 0.396744, 0.395660, 0.396868, 0.395701, 0.395649, 0.395340, 0.397607, 0.398269, 0.395278, 0.396959, 0.396342, 0.396712, 0.396985, 0.397349, 0.396228, 0.397668, 0.397878]
# VetAruaP6_2TH_tempo_paral = [21.912156, 21.921425, 22.056808, 21.969161, 21.944778, 21.976233, 21.903874, 22.015960, 21.973072, 22.031523, 22.080107, 21.942912, 21.962790, 21.977297, 22.006360, 21.996944, 22.090392, 22.102033, 22.089984, 22.073643]

# VetAruaP6_4TH_tempo_seq = [0.399495, 0.398563, 0.397692, 0.398061, 0.397066, 0.396357, 0.398385, 0.396024, 0.397864, 0.396172, 0.397743, 0.396676, 0.396729, 0.396233, 0.396878, 0.395804, 0.397303, 0.397381, 0.395590, 0.396160]
# VetAruaP6_4TH_tempo_paral = [10.524692, 10.474119, 10.458047, 10.412007, 10.377925, 10.406916, 10.406111, 10.412650, 10.415488, 10.439373, 10.400769, 10.365330, 10.492888, 10.422106, 10.396626, 10.451465, 10.445952, 10.417925, 10.393092, 10.390583]

# VetAruaP6_8TH_tempo_seq = [0.403093, 0.398243, 0.397710, 0.396295, 0.396448, 0.396972, 0.396537, 0.398069, 0.395879, 0.397700, 0.398280, 0.397382, 0.398243, 0.398031, 0.395375, 0.395397, 0.397398, 0.393018, 0.395967, 0.396912]
# VetAruaP6_8TH_tempo_paral = [30.829959, 30.834361, 30.444851, 30.665807, 30.831553, 30.711499, 31.095511, 31.023773, 31.207645, 31.202289, 31.165548, 31.297043, 31.148774, 31.326226, 31.155990, 30.815224, 30.757919, 30.824660, 30.691653, 30.998671]

# VetAruaP6_16TH_tempo_seq = [0.443436, 0.396850, 0.400698, 0.397333, 0.398491, 0.399257, 0.399111, 0.397577, 0.396091, 0.398777, 0.399533, 0.400100, 0.398243, 0.399551, 0.399271, 0.397953, 0.396894, 0.397563, 0.397580, 0.396499]
# VetAruaP6_16TH_tempo_paral = [60.841315, 60.445550, 59.987415, 60.535432, 60.747023, 60.532010, 59.894293, 60.097605, 60.134836, 60.270446, 60.270847, 59.622793, 60.337313, 60.268495, 60.046456, 60.313954, 60.590416, 60.352726, 60.539719, 60.266053]


# VetMouseSeq6 = [31.434426, 31.436229, 31.432391, 31.436806, 31.436125, 31.435951, 31.430903, 31.434775, 31.448397, 31.426420, 31.422958, 31.429632, 31.449119, 31.434647, 31.432016, 31.429839, 31.435565, 31.430397, 31.439679, 31.473416]

# VetMouseP6_2TH_tempo_seq = [0.395102, 0.397524, 0.396871, 0.395916, 0.395986, 0.394870, 0.397480, 0.396353, 0.396581, 0.395094, 0.394606, 0.395811, 0.398064, 0.396306, 0.396923, 0.395320, 0.395581, 0.395544, 0.395433, 0.395338]
# VetMouseP6_2TH_tempo_paral = [21.942620, 22.044792, 21.882703, 22.066749, 21.847476, 21.831852, 21.810449, 21.912738, 21.922804, 21.980950, 21.860090, 21.940491, 21.991512, 21.855577, 22.007099, 21.889304, 21.896523, 21.857209, 21.829766, 21.839024]


# VetMouseP6_4TH_tempo_seq = [0.396911, 0.396761, 0.396298, 0.395937, 0.395711, 0.395137, 0.398545, 0.396436, 0.396428, 0.396213, 0.397733, 0.395857, 0.395469, 0.395028, 0.397491, 0.398774, 0.397832, 0.396995, 0.397003, 0.397571]
# VetMouseP6_4TH_tempo_paral = [10.402966, 10.587769, 10.396738, 10.413751, 10.847223, 10.430893, 10.408745, 10.434373, 10.409166, 10.489169, 10.382300, 10.394625, 10.403164, 10.399459, 10.438223, 10.413725, 10.421078, 10.405468, 10.386347, 10.385663]


# VetMouseP6_8TH_tempo_seq = [0.459583, 0.394413, 0.396891, 0.395489, 0.395677, 0.396293, 0.396607, 0.396459, 0.395192, 0.395804, 0.397709, 0.395421, 0.396547, 0.397263, 0.394512, 0.393561, 0.394746, 0.481872, 0.397108, 0.396584]
# VetMouseP6_8TH_tempo_paral = [31.595353, 30.531527, 31.229451, 31.314484, 31.078388, 31.019555, 31.176826, 30.998391, 30.814530, 31.018650, 31.088581, 31.044483, 31.134384, 30.807911, 31.046600, 31.104376, 31.950120, 30.853747, 31.412122, 30.720518]

# VetMouseP6_16TH_tempo_seq = [0.399985, 0.397421, 0.398263, 0.397543, 0.398197, 0.397342, 0.398525, 0.397350, 0.396295, 0.395510, 0.398754, 0.401484, 0.397623, 0.398276, 0.396240, 0.396668, 0.397592, 0.400963, 0.396920, 0.401910]
# VetMouseP6_16TH_tempo_paral = [60.478102, 60.933047, 60.207688, 60.259547, 60.379875, 60.266264, 60.215569, 60.232559, 59.970840, 60.249937, 60.449238, 60.317359, 60.226089, 60.437776, 60.060496, 60.477136, 60.530266, 60.347438, 60.222220, 60.177858]


# -------------------------VETORES 26K------------------------------------------#

# VetAruaSeq6 = [131.655702, 131.371536, 131.350121, 131.409553, 131.343274, 131.341469, 131.382699, 131.352956, 131.406462, 131.354997, 131.370099, 131.346187, 131.333433, 131.380181, 131.596956, 131.697788, 131.380128, 131.327508, 131.331295, 131.349733]

# VetAruaP6_2TH_tempo_seq = [1.583673, 1.579147, 1.581665, 1.581977, 1.584539, 1.583332, 1.580850, 1.579249, 1.585297, 1.580756, 1.584317, 1.584945, 1.581489, 1.582596, 1.590550, 1.581200, 1.626531, 1.582331, 1.582284, 1.584434]
# VetAruaP6_2TH_tempo_paral = [109.432425, 109.177256, 109.695499, 109.688360, 109.485317, 109.297680, 108.655224, 108.565799, 109.307734, 108.726722, 108.917654, 108.997664, 109.313317, 108.714126, 108.254262, 108.647461, 109.282304, 108.957150, 109.882288, 109.694935]

# VetAruaP6_4TH_tempo_seq = [1.603606, 1.575722, 1.570117, 1.575362, 1.571038, 1.572305, 1.578501, 1.573207, 1.578123, 1.572239, 1.574195, 1.571502, 1.579645, 1.578229, 1.571252, 1.577134, 1.572072, 1.573693, 1.570609, 1.571556]
# VetAruaP6_4TH_tempo_paral = [58.703603, 59.290585, 58.700015, 59.288303, 58.961326, 58.622334, 58.889995, 59.239638, 57.873516, 58.995814, 58.031362, 58.375758, 58.781857, 58.975902, 58.450280, 58.557927, 58.549428, 58.624387, 58.755102, 58.131585]

# VetAruaP6_8TH_tempo_seq = [1.586352, 1.578026, 1.585811, 1.578611, 1.582999, 1.577046, 1.575153, 1.581937, 1.576907, 1.585832, 1.576706, 1.585090, 1.584783, 1.580027, 1.583641, 1.583086, 1.580634, 1.577273, 1.574843, 1.579443]
# VetAruaP6_8TH_tempo_paral = [111.378411, 108.861513, 112.132807, 109.285539, 109.064673, 109.570604, 109.478073, 109.849921, 109.426943, 108.847233, 110.079738, 109.253465, 110.034445, 109.265168, 111.994173, 113.502626, 112.772477, 109.868536, 112.096887, 110.700451]


# VetAruaP6_16TH_tempo_seq = [1.580728, 1.579079, 1.579967, 1.584627, 1.579944, 1.585261, 1.580411, 1.582588, 1.585005, 1.580860, 1.579131, 1.612974, 1.581708, 1.590609, 1.596542, 1.585289, 1.584369, 1.584191, 1.579502, 1.579469]
# VetAruaP6_16TH_tempo_paral = [173.354512, 173.047892, 173.265236, 172.788320, 173.133696, 169.104592, 168.206484, 168.240077, 167.301865, 167.749103, 168.450716, 168.659896, 169.027506, 168.343427, 168.485445, 169.505967, 173.953761, 173.123748, 174.135831, 172.721092]


# VetMouseSeq6 = [126.039833, 126.034988, 126.107880, 126.042929, 126.136728, 126.084382, 126.106158, 126.121601, 126.056967, 126.053472, 126.422292, 126.384496, 126.302633, 126.358141, 126.409859, 126.324103, 126.304570, 126.011559, 126.080126, 125.935829]

# VetMouseP6_2TH_tempo_seq = [1.588142, 1.582300, 1.587424, 1.586762, 1.587702, 1.578272, 1.584013, 1.583212, 1.578513, 1.582007, 1.582648, 1.589099, 1.582487, 1.578563, 1.587436, 1.584506, 1.579429, 1.577793, 1.577578, 1.585798]
# VetMouseP6_2TH_tempo_paral = [109.443637, 108.975979, 109.520306, 108.887700, 109.332115, 108.873872, 108.876122, 109.063145, 108.590579, 109.075452, 108.839660, 108.310851, 108.913197, 108.845360, 109.622774, 109.173471, 109.028643, 108.599998, 109.000890, 111.034238]


# VetMouseP6_4TH_tempo_seq = [1.586151, 1.569021, 1.569828, 1.571440, 1.572571, 1.577087, 1.569491, 1.572765, 1.568103, 1.572266, 1.573424, 1.568375, 1.574159, 1.570680, 1.566415, 1.573428, 1.569846, 1.575666, 1.576895, 1.568638]
# VetMouseP6_4TH_tempo_paral = [58.163176, 58.304417, 58.554994, 59.534734, 58.838642, 58.582985, 58.418065, 58.820854, 58.195008, 58.547669, 58.332453, 58.566418, 58.403048, 58.196064, 57.979987, 59.578329, 58.549106, 58.911891, 58.889247, 58.567341]

# VetMouseP6_8TH_tempo_seq = [1.632333, 1.575269, 1.580460, 1.577071, 1.577070, 1.590744, 1.577668, 1.588618, 1.580469, 1.578021, 1.577238, 1.581542, 1.578821, 1.584753, 1.583940, 1.587789, 1.581937, 1.583311, 1.577189, 1.579336]
# VetMouseP6_8TH_tempo_paral = [109.537393, 111.138534, 112.141899, 109.502858, 110.154884, 111.013946, 110.271571, 109.964614, 109.876699, 110.172187, 110.395666, 110.184199, 111.155481, 114.631118, 113.687827, 112.218889, 111.295813, 112.364925, 112.536523, 113.099171]

# VetMouseP6_16TH_tempo_seq = [1.587252, 1.575461, 1.595586, 1.576422, 1.578190, 1.573127, 1.578895, 1.576929, 1.581763, 1.575333, 1.581460, 1.572559, 1.579532, 1.578063, 1.574829, 1.584234, 1.571306, 1.577539, 1.577120, 1.584240]
# VetMouseP6_16TH_tempo_paral = [167.379068, 168.141763, 168.140802, 168.296517, 168.229074, 169.157255, 168.595216, 168.325207, 168.974259, 167.502997, 167.969527, 168.657424, 168.280421, 168.413020, 168.168287, 168.071344, 168.837680, 168.125125, 168.631644, 167.942377]


# CALCULA MEDIA PARA ARUA#
sequencialArua6k = calcMedia(VetAruaSeq6, 20)

paraleloArua6k_2th_tempo_seq = calcMedia(VetAruaP6_2TH_tempo_seq, 20)
paraleloArua6k_2th_tempo_paral = calcMedia(VetAruaP6_2TH_tempo_paral, 20)

paraleloArua6k_4th_tempo_seq = calcMedia(VetAruaP6_4TH_tempo_seq, 20)
paraleloArua6k_4th_tempo_paral = calcMedia(VetAruaP6_4TH_tempo_paral, 20)

paraleloArua6k_8th_tempo_seq = calcMedia(VetAruaP6_8TH_tempo_seq, 20)
paraleloArua6k_8th_tempo_paral = calcMedia(VetAruaP6_8TH_tempo_paral, 20)

paraleloArua6k_16th_tempo_seq = calcMedia(VetAruaP6_16TH_tempo_seq, 20)
paraleloArua6k_16th_tempo_paral = calcMedia(VetAruaP6_16TH_tempo_paral, 20)


# CALCULA MEDIA PARA MOUSE#
sequencialMouse6k = calcMedia(VetMouseSeq6, 20)

paraleloMouse6k_2th_tempo_seq = calcMedia(VetMouseP6_2TH_tempo_seq, 20)
paraleloMouse6k_2th_tempo_paral = calcMedia(VetMouseP6_2TH_tempo_paral, 20)

paraleloMouse6k_4th_tempo_seq = calcMedia(VetMouseP6_4TH_tempo_seq, 20)
paraleloMouse6k_4th_tempo_paral = calcMedia(VetMouseP6_4TH_tempo_paral, 20)

paraleloMouse6k_8th_tempo_seq = calcMedia(VetMouseP6_8TH_tempo_seq, 20)
paraleloMouse6k_8th_tempo_paral = calcMedia(VetMouseP6_8TH_tempo_paral, 20)

paraleloMouse6k_16th_tempo_seq = calcMedia(VetMouseP6_16TH_tempo_seq, 20)
paraleloMouse6k_16th_tempo_paral = calcMedia(VetMouseP6_16TH_tempo_paral, 20)


# CALCULA SPEEDUP PARA ARUA#
speedUP_Arua_6k_2th = calcSpeedup(sequencialArua6k, paraleloArua6k_2th_tempo_paral)
speedUP_Arua_6k_4th = calcSpeedup(sequencialArua6k, paraleloArua6k_4th_tempo_paral)
speedUP_Arua_6k_8th = calcSpeedup(sequencialArua6k, paraleloArua6k_8th_tempo_paral)
speedUP_Arua_6k_16th = calcSpeedup(sequencialArua6k, paraleloArua6k_16th_tempo_paral)


# CALCULA SPEEDUP PARA MOUSE#
speedUP_Mouse_6k_2th = calcSpeedup(sequencialMouse6k, paraleloMouse6k_2th_tempo_paral)
speedUP_Mouse_6k_4th = calcSpeedup(sequencialMouse6k, paraleloMouse6k_4th_tempo_paral)
speedUP_Mouse_6k_8th = calcSpeedup(sequencialMouse6k, paraleloMouse6k_8th_tempo_paral)
speedUP_Mouse_6k_16th = calcSpeedup(sequencialMouse6k, paraleloMouse6k_16th_tempo_paral)



print("Resultados para a sequencia Arua de tamanho de 6k:")
print("Media sequencial: " + str(sequencialArua6k))
print("Media paralelo 2TH: " + str(paraleloArua6k_2th_tempo_paral))
print("Media paralelo 4TH: " + str(paraleloArua6k_4th_tempo_paral))
print("Media paralelo 8TH: " + str(paraleloArua6k_8th_tempo_paral))
print("Media paralelo 16TH: " + str(paraleloArua6k_16th_tempo_paral))
print("SpeedUP paralelo 2TH: " + str(speedUP_Arua_6k_2th))
print("SpeedUP paralelo 4TH: " + str(speedUP_Arua_6k_4th))
print("SpeedUP paralelo 8TH: " + str(speedUP_Arua_6k_8th))
print("SpeedUP paralelo 16TH: " + str(speedUP_Arua_6k_16th))
print("Eficiencia para 2TH: " + str(calcEficiencia(speedUP_Arua_6k_2th, 2)))
print("Eficiencia para 4TH: " + str(calcEficiencia(speedUP_Arua_6k_4th, 4)))
print("Eficiencia para 8TH: " + str(calcEficiencia(speedUP_Arua_6k_8th, 8)))
print("Eficiencia para 16TH: " + str(calcEficiencia(speedUP_Arua_6k_16th, 16)))
print("Lei de Amdahl para 2TH: " + str(calcAmdahl(2, regra3(paraleloArua6k_2th_tempo_paral+ paraleloArua6k_2th_tempo_seq,paraleloArua6k_2th_tempo_seq))))
print("Lei de Amdahl para 4TH: " + str(calcAmdahl(4, regra3(paraleloArua6k_4th_tempo_paral+ paraleloArua6k_4th_tempo_seq,paraleloArua6k_4th_tempo_seq))))
print("Lei de Amdahl para 8TH: " + str(calcAmdahl(8, regra3(paraleloArua6k_8th_tempo_paral+ paraleloArua6k_8th_tempo_seq,paraleloArua6k_8th_tempo_seq))))
print("Lei de Amdahl para 16TH: " + str(calcAmdahl(16, regra3(paraleloArua6k_16th_tempo_paral+ paraleloArua6k_16th_tempo_seq,paraleloArua6k_16th_tempo_seq))))
print("Lei de Amdahl para INF: " + str(calcAmdahl(0, regra3(paraleloArua6k_4th_tempo_paral+ paraleloArua6k_4th_tempo_seq,paraleloArua6k_4th_tempo_seq))))
print('\n')


print("Resultados para a sequencia Mouse de tamanho de 6k:")
print("Media sequencial: " + str(sequencialMouse6k))
print("Media paralelo 2TH: " + str(paraleloMouse6k_2th_tempo_paral))
print("Media paralelo 4TH: " + str(paraleloMouse6k_4th_tempo_paral))
print("Media paralelo 8TH: " + str(paraleloMouse6k_8th_tempo_paral))
print("Media paralelo 16TH: " + str(paraleloMouse6k_16th_tempo_paral))
print("SpeedUP paralelo 2TH: " + str(speedUP_Mouse_6k_2th))
print("SpeedUP paralelo 4TH: " + str(speedUP_Mouse_6k_4th))
print("SpeedUP paralelo 8TH: " + str(speedUP_Mouse_6k_8th))
print("SpeedUP paralelo 16TH: " + str(speedUP_Mouse_6k_16th))
print("Eficiencia para 2TH: " + str(calcEficiencia(speedUP_Mouse_6k_2th, 2)))
print("Eficiencia para 4TH: " + str(calcEficiencia(speedUP_Mouse_6k_4th, 4)))
print("Eficiencia para 8TH: " + str(calcEficiencia(speedUP_Mouse_6k_8th, 8)))
print("Eficiencia para 16TH: " + str(calcEficiencia(speedUP_Mouse_6k_16th, 16)))
print("Lei de Amdahl para 2TH: " + str(calcAmdahl(2, regra3(paraleloMouse6k_2th_tempo_paral+ paraleloMouse6k_2th_tempo_seq,paraleloMouse6k_2th_tempo_seq))))
print("Lei de Amdahl para 4TH: " + str(calcAmdahl(4, regra3(paraleloMouse6k_4th_tempo_paral+ paraleloMouse6k_4th_tempo_seq,paraleloMouse6k_4th_tempo_seq))))
print("Lei de Amdahl para 8TH: " + str(calcAmdahl(8, regra3(paraleloMouse6k_8th_tempo_paral+ paraleloMouse6k_8th_tempo_seq,paraleloMouse6k_8th_tempo_seq))))
print("Lei de Amdahl para 16TH: " + str(calcAmdahl(16, regra3(paraleloMouse6k_16th_tempo_paral+ paraleloMouse6k_16th_tempo_seq,paraleloMouse6k_16th_tempo_seq))))
print("Lei de Amdahl para INF: " + str(calcAmdahl(0, regra3(paraleloMouse6k_4th_tempo_paral+ paraleloMouse6k_4th_tempo_seq,paraleloMouse6k_4th_tempo_seq))))
print('\n')