# Importing the libraries
import matplotlib.pyplot as plt
import pandas as pd
               
#--------------------------------------------------------                
# Importing the dataset
dataset= pd.read_csv('points_engine_uc1_simulator.csv',sep=';')
dataset.sample(frac=1)
#--------------------------------------------------------
dataset.columns
dataset=dataset.drop(columns=['gid', 'car_id', 'point_time', 'lat', 'lon', 'segment_id', 'speedup_ratio',  'segment_changed', 'duration_segment',
       'duration', 'duration_move', 'good', 'duration_good', 'bearing',
       'interpolated','distance_total_m'])
dataset.columns
#_____________________________________________________                  
dataset ['moved']= dataset ['moved'].apply(lambda x:1 if x=="t" else 0)          
#_____________________________________________________ 

X = dataset.iloc[:,:4].values

X[0]  

y = dataset ['zone']
#--------------------------------------------------------
# Splitting the dataset into the Training set and Test set
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 0)
#____________________________________________________
#Fitting Logistic Regression to the Training set
from sklearn.linear_model import LogisticRegression
classifier=LogisticRegression()
classifier.fit(X_train,y_train)
#____________________________________________________________

#Fitting KNN to the Training set
from sklearn.neighbors import KNeighborsClassifier
classifier = KNeighborsClassifier(n_neighbors=7)
classifier.fit(X_train, y_train)
#_____________________________________________________________
#Fitting naive_bayes to the Training set
from sklearn.naive_bayes import GaussianNB
classifier = GaussianNB()
classifier.fit(X_train, y_train)
#____________________________________________________________
# Predicting the Test set results
y_pred = classifier.predict(X_test)

#calculate accuracy
from sklearn.metrics import accuracy_score
accuracy = accuracy_score(y_test, y_pred)
print(accuracy)
#--------------------------------------------------------
# Making the Confusion Matrix
from sklearn.metrics import confusion_matrix
cm = confusion_matrix(y_test, y_pred)

# Visualising the Confusion Matrix
from sklearn.metrics import plot_confusion_matrix
plot_confusion_matrix(classifier, X_test, y_test)  
plt.show() 
#--------------------------------------------------------
import pickle
# save the model to disk
modelfilename = 'KNN_99.sav'
pickle.dump(classifier, open(modelfilename, 'wb'))

print("done")


