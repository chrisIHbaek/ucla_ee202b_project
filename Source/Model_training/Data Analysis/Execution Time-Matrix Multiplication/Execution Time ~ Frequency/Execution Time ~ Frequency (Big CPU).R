library(AppliedPredictiveModeling)
library(caret) 
library(MASS)

# The random number seed is set prior to modeling so that the results can be reproduced
set.seed(1)  

# Read the data file
Data<-read.csv("Execution Time Raw Data_Big CPU.csv")

#Matrix dimension=850
#Data Pre-processing
Features_850=subset(Data,Matrix_Dimension==850,select=c("Predictor"))
Target_850=Data[which(Data$Matrix_Dimension==850),"Execution_Time"]
#Fit a model
ctrl <- trainControl(method = "cv", number = 10)  # 10-fold cross-validation
lmFit_train_850 <- train(x=Features_850, y=Target_850, method = "lm",trControl = ctrl)

#Matrix dimension=800
#Data Pre-processing
Features_800=subset(Data,Matrix_Dimension==800,select=c("Predictor"))
Target_800=Data[which(Data$Matrix_Dimension==800),"Execution_Time"]
#Fit a model
lmFit_train_800 <- train(x=Features_800, y=Target_800, method = "lm",trControl = ctrl)

#Matrix dimension=750
#Data Pre-processing
Features_750=subset(Data,Matrix_Dimension==750,select=c("Predictor"))
Target_750=Data[which(Data$Matrix_Dimension==750),"Execution_Time"]
#Fit a model
lmFit_train_750 <- train(x=Features_750, y=Target_750, method = "lm",trControl = ctrl)

#Matrix dimension=700
#Data Pre-processing
Features_700=subset(Data,Matrix_Dimension==700,select=c("Predictor"))
Target_700=Data[which(Data$Matrix_Dimension==700),"Execution_Time"]
#Fit a model
lmFit_train_700 <- train(x=Features_700, y=Target_700, method = "lm",trControl = ctrl)

#Matrix dimension=650
#Data Pre-processing
Features_650=subset(Data,Matrix_Dimension==650,select=c("Predictor"))
Target_650=Data[which(Data$Matrix_Dimension==650),"Execution_Time"]
#Fit a model
lmFit_train_650 <- train(x=Features_650, y=Target_650, method = "lm",trControl = ctrl)

#Matrix dimension=600
#Data Pre-processing
Features_600=subset(Data,Matrix_Dimension==600,select=c("Predictor"))
Target_600=Data[which(Data$Matrix_Dimension==600),"Execution_Time"]
#Fit a model
lmFit_train_600 <- train(x=Features_600, y=Target_600, method = "lm",trControl = ctrl)

#Matrix dimension=550
#Data Pre-processing
Features_550=subset(Data,Matrix_Dimension==550,select=c("Predictor"))
Target_550=Data[which(Data$Matrix_Dimension==550),"Execution_Time"]
#Fit a model
lmFit_train_550 <- train(x=Features_550, y=Target_550, method = "lm",trControl = ctrl)

#Matrix dimension=500
#Data Pre-processing
Features_500=subset(Data,Matrix_Dimension==500,select=c("Predictor"))
Target_500=Data[which(Data$Matrix_Dimension==500),"Execution_Time"]
#Fit a model
lmFit_train_500 <- train(x=Features_500, y=Target_500, method = "lm",trControl = ctrl)

#Matrix dimension=450
#Data Pre-processing
Features_450=subset(Data,Matrix_Dimension==450,select=c("Predictor"))
Target_450=Data[which(Data$Matrix_Dimension==450),"Execution_Time"]
#Fit a model
lmFit_train_450 <- train(x=Features_450, y=Target_450, method = "lm",trControl = ctrl)

#Matrix dimension=400
#Data Pre-processing
Features_400=subset(Data,Matrix_Dimension==400,select=c("Predictor"))
Target_400=Data[which(Data$Matrix_Dimension==400),"Execution_Time"]
#Fit a model
lmFit_train_400 <- train(x=Features_400, y=Target_400, method = "lm",trControl = ctrl)

#Matrix dimension=350
#Data Pre-processing
Features_350=subset(Data,Matrix_Dimension==350,select=c("Predictor"))
Target_350=Data[which(Data$Matrix_Dimension==350),"Execution_Time"]
#Fit a model
lmFit_train_350 <- train(x=Features_350, y=Target_350, method = "lm",trControl = ctrl)

#Matrix dimension=300
#Data Pre-processing
Features_300=subset(Data,Matrix_Dimension==300,select=c("Predictor"))
Target_300=Data[which(Data$Matrix_Dimension==300),"Execution_Time"]
#Fit a model
lmFit_train_300 <- train(x=Features_300, y=Target_300, method = "lm",trControl = ctrl)

#Matrix dimension=250
#Data Pre-processing
Features_250=subset(Data,Matrix_Dimension==250,select=c("Predictor"))
Target_250=Data[which(Data$Matrix_Dimension==250),"Execution_Time"]
#Fit a model
lmFit_train_250 <- train(x=Features_250, y=Target_250, method = "lm",trControl = ctrl)

#Matrix dimension=200
#Data Pre-processing
Features_200=subset(Data,Matrix_Dimension==200,select=c("Predictor"))
Target_200=Data[which(Data$Matrix_Dimension==200),"Execution_Time"]
#Fit a model
lmFit_train_200 <- train(x=Features_200, y=Target_200, method = "lm",trControl = ctrl)

#Matrix dimension=150
#Data Pre-processing
Features_150=subset(Data,Matrix_Dimension==150,select=c("Predictor"))
Target_150=Data[which(Data$Matrix_Dimension==150),"Execution_Time"]
#Fit a model
lmFit_train_150 <- train(x=Features_150, y=Target_150, method = "lm",trControl = ctrl)

#Matrix dimension=100
#Data Pre-processing
Features_100=subset(Data,Matrix_Dimension==100,select=c("Predictor"))
Target_100=Data[which(Data$Matrix_Dimension==100),"Execution_Time"]
#Fit a model
lmFit_train_100 <- train(x=Features_100, y=Target_100, method = "lm",trControl = ctrl)

