import pickle
import numpy as np
# load the model from disk
modelfilename = 'KNN_99.sav'
loaded_model = pickle.load(open(modelfilename, 'rb'))
#-------------------------------------------
def predict(reads):    
    predication=loaded_model.predict(reads) 
    return predication
#-------------------------------------------
#speed_kmh,speed_avg_kmh,distance_delta_m,moved zone
reads=[80,64,30,1]
reads=np.array(reads)
output=predict([reads])
print('result=',output)
