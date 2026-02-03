# Image Classification using Transfer Learning (ResNet18) 

## Description 

This project performs binary image classification (Cats vs Dogs) using transfer learning with a pretrained ResNet18 model. Only the final fully connected layer is trained, while the pretrained backbone is frozen to reduce overfitting and training time. 

## Model Details 
 - Architecture: ResNet18 
 - Pretrained on: ImageNet 
 - Loss function: CrossEntropyLoss 
 - Optimizer: Adam 
 - Learning rate scheduler: ReduceLROnPlateau 
 - Training device: CPU (GPU used if available) 
 
 ## Dataset Structure 
 The dataset is organized as: 
 ```
 data/  
 ├── train/  
 │      ├── cats/  
 │      └── dogs/  
 ├── val/  
 │      ├── cats/  
 │      └── dogs/  
 └── test/  
        ├── cats/  
        └── dogs/
``` 
 
 ## Data Augmentation 
 Applied only to the training set: 
 - Resize 
 - Random crop 
 - Horizontal flip 
 - Random rotation 
 - Color jitter 
 - Normalization (ImageNet mean & std) 
 
 Validation and test sets use deterministic preprocessing only. 
 
 ## Files 
 - train.py — model training and validation 
 - evaluate.py — test evaluation, confusion matrix, and example predictions 
 - best_model.pth — saved model with best validation accuracy 
 - training_curves.png — training & validation loss/accuracy curves 
 - confusion_matrix.png — labeled confusion matrix 
 
 ## Usage 
 - Train the model python train.py 
 - Evaluate on test set python evaluate.py 
 
 ## Outputs 
 - Best model saved as best_model.pth 
 - Training and validation curves saved as training_curves.png 
 - Confusion matrix saved as confusion_matrix.png 
 - Displays 5 correct and 5 incorrect test predictions 
 
 ## Notes 
 - Validation accuracy is used to select the best model 
 - Test set is used only for final evaluation 
 - CPU training is slower but does not affect accuracy