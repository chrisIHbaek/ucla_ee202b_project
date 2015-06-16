library(AppliedPredictiveModeling)
library(caret) 
library(MASS)

# The random number seed is set prior to modeling so that the results can be reproduced
set.seed(1)  

# Read the data file
Data<-read.csv("Execution Time Raw Data.csv")

# Frequency = 1600MHz
# Data Pre-processing
Features_1600=subset(Data,Frequency==1600,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_1600=Data[which(Data$Frequency==1600),"Execution_Time"]
# Fit a model
ctrl <- trainControl(method = "cv", number = 10)  # 10-fold cross-validation
lmFit_train_1600 <- train(x=Features_1600, y=Target_1600, method = "lm",trControl = ctrl)

# Frequency = 1500MHz
# Data Pre-processing
Features_1500=subset(Data,Frequency==1500,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_1500=Data[which(Data$Frequency==1500),"Execution_Time"]
# Fit a model
lmFit_train_1500 <- train(x=Features_1500, y=Target_1500, method = "lm",trControl = ctrl)

# Frequency = 1400MHz
# Data Pre-processing
Features_1400=subset(Data,Frequency==1400,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_1400=Data[which(Data$Frequency==1400),"Execution_Time"]
# Fit a model
lmFit_train_1400 <- train(x=Features_1400, y=Target_1400, method = "lm",trControl = ctrl)

# Frequency = 1300MHz
# Data Pre-processing
Features_1300=subset(Data,Frequency==1300,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_1300=Data[which(Data$Frequency==1300),"Execution_Time"]
# Fit a model
lmFit_train_1300 <- train(x=Features_1300, y=Target_1300, method = "lm",trControl = ctrl)

# Frequency = 1200MHz
# Data Pre-processing
Features_1200=subset(Data,Frequency==1200,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_1200=Data[which(Data$Frequency==1200),"Execution_Time"]
# Fit a model
lmFit_train_1200 <- train(x=Features_1200, y=Target_1200, method = "lm",trControl = ctrl)

# Frequency = 1100MHz
# Data Pre-processing
Features_1100=subset(Data,Frequency==1100,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_1100=Data[which(Data$Frequency==1100),"Execution_Time"]
# Fit a model
lmFit_train_1100 <- train(x=Features_1100, y=Target_1100, method = "lm",trControl = ctrl)

# Frequency = 1000MHz
# Data Pre-processing
Features_1000=subset(Data,Frequency==1000,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_1000=Data[which(Data$Frequency==1000),"Execution_Time"]
# Fit a model
lmFit_train_1000 <- train(x=Features_1000, y=Target_1000, method = "lm",trControl = ctrl)

# Frequency = 900MHz
# Data Pre-processing
Features_900=subset(Data,Frequency==900,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_900=Data[which(Data$Frequency==900),"Execution_Time"]
# Fit a model
lmFit_train_900 <- train(x=Features_900, y=Target_900, method = "lm",trControl = ctrl)

# Frequency = 800MHz
# Data Pre-processing
Features_800=subset(Data,Frequency==800,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_800=Data[which(Data$Frequency==800),"Execution_Time"]
# Fit a model
lmFit_train_800 <- train(x=Features_800, y=Target_800, method = "lm",trControl = ctrl)

# Frequency = 600MHz
# Data Pre-processing
Features_600=subset(Data,Frequency==600,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_600=Data[which(Data$Frequency==600),"Execution_Time"]
# Fit a model
lmFit_train_600 <- train(x=Features_600, y=Target_600, method = "lm",trControl = ctrl)

# Frequency = 550MHz
# Data Pre-processing
Features_550=subset(Data,Frequency==550,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_550=Data[which(Data$Frequency==550),"Execution_Time"]
# Fit a model
lmFit_train_550 <- train(x=Features_550, y=Target_550, method = "lm",trControl = ctrl)

# Frequency = 500MHz
# Data Pre-processing
Features_500=subset(Data,Frequency==500,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_500=Data[which(Data$Frequency==500),"Execution_Time"]
# Fit a model
lmFit_train_500 <- train(x=Features_500, y=Target_500, method = "lm",trControl = ctrl)

# Frequency = 450MHz
# Data Pre-processing
Features_450=subset(Data,Frequency==450,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_450=Data[which(Data$Frequency==450),"Execution_Time"]
# Fit a model
lmFit_train_450 <- train(x=Features_450, y=Target_450, method = "lm",trControl = ctrl)

# Frequency = 400MHz
# Data Pre-processing
Features_400=subset(Data,Frequency==400,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_400=Data[which(Data$Frequency==400),"Execution_Time"]
# Fit a model
lmFit_train_400 <- train(x=Features_400, y=Target_400, method = "lm",trControl = ctrl)

# Frequency = 350MHz
# Data Pre-processing
Features_350=subset(Data,Frequency==350,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_350=Data[which(Data$Frequency==350),"Execution_Time"]
# Fit a model
lmFit_train_350 <- train(x=Features_350, y=Target_350, method = "lm",trControl = ctrl)

# Frequency = 300MHz
# Data Pre-processing
Features_300=subset(Data,Frequency==300,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_300=Data[which(Data$Frequency==300),"Execution_Time"]
# Fit a model
lmFit_train_300 <- train(x=Features_300, y=Target_300, method = "lm",trControl = ctrl)

# Frequency = 250MHz
# Data Pre-processing
Features_250=subset(Data,Frequency==250,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_250=Data[which(Data$Frequency==250),"Execution_Time"]
# Fit a model
lmFit_train_250 <- train(x=Features_250, y=Target_250, method = "lm",trControl = ctrl)

# Frequency = 200MHz
# Data Pre-processing
Features_200=subset(Data,Frequency==200,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_200=Data[which(Data$Frequency==200),"Execution_Time"]
# Fit a model
lmFit_train_200 <- train(x=Features_200, y=Target_200, method = "lm",trControl = ctrl)

# Frequency = 150MHz
# Data Pre-processing
Features_150=subset(Data,Frequency==150,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_150=Data[which(Data$Frequency==150),"Execution_Time"]
# Fit a model
lmFit_train_150 <- train(x=Features_150, y=Target_150, method = "lm",trControl = ctrl)

# Frequency = 100MHz
# Data Pre-processing
Features_100=subset(Data,Frequency==100,select=c("Matrix_Dimension_2","Matrix_Dimension_3"))
Target_100=Data[which(Data$Frequency==100),"Execution_Time"]
# Fit a model
lmFit_train_100 <- train(x=Features_100, y=Target_100, method = "lm",trControl = ctrl)




