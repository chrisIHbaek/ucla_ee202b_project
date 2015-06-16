library(AppliedPredictiveModeling)
library(caret) 
library(MASS)

# Read the data file
Data<-read.csv("Power Model Raw Data.csv")

# Plot the basic figure
# Big CPU
Power_big<-Data[which(Data$Flag==1),"Power"]
Frequency_big<-Data[which(Data$Flag==1),"Frequency"]
Voltage_big<-Data[which(Data$Flag==1),"Voltage"]
plot(Voltage_big*Voltage_big*Frequency_big,Power_big,xlab="(Voltage^2)*Frequency",ylab="Power (W)")
plot(Frequency_big,Voltage_big,xlab="Frequency (MHz)",ylab="Voltage (V)")

# Small CPU
Power_small<-Data[which(Data$Flag==0),"Power"]
Frequency_small<-Data[which(Data$Flag==0),"Frequency"]
Voltage_small<-Data[which(Data$Flag==0),"Voltage"]
plot(Voltage_small*Voltage_small*Frequency_small,Power_small,xlab="(Voltage^2)*Frequency",ylab="Power (W)")
plot(Frequency_small,Voltage_small,xlab="Frequency (MHz)",ylab="Voltage (V)")

# The random number seed is set prior to modeling so that the results can be reproduced
set.seed(1) 

# Fit the ordinary linear regression model
# Big CPU
ctrl <- trainControl(method = "cv", number = 10)  # 10-fold cross-validation
lmFit_train_Voltage <- train(x=data.frame(Frequency_big), y=Voltage_big, method = "lm",trControl = ctrl)
lmFit_train_Power<-train(x=data.frame(Voltage_big*Voltage_big*Frequency_big),y=Power_big,
                         method = "lm",trControl = ctrl)

# Small CPU
ctrl <- trainControl(method = "cv", number = 10)  # 10-fold cross-validation
lmFit_train_Voltage_small <- train(x=data.frame(Frequency_small), y=Voltage_small, method = "lm",trControl = ctrl)
lmFit_train_Power_small<-train(x=data.frame(Voltage_small*Voltage_small*Frequency_small),y=Power_small,
                         method = "lm",trControl = ctrl)

# Use piecewise function
Frequency_small_truncated<-subset(Data,Flag==0 & Frequency>350 ,select=c("Frequency"))
Frequency_small_trun<-Frequency_small_truncated$Frequency
Voltage_small_truncated<-subset(Data,Flag==0 & Frequency>350 ,select=c("Voltage"))
Voltage_small_trun<-Voltage_small_truncated$Voltage
plot(Voltage_small_trun,Frequency_small_trun,xlab="Frequency (MHz)",ylab="Voltage (V)")
lmFit_train_Voltage_small_piecewise <- train(x=data.frame(Frequency_small_trun), y=Voltage_small_trun,method = "lm",trControl = ctrl)

# Plot the fit model figure

